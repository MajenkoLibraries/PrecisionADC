/*
 * PrecisionADC
 * Copyright (C) 2014 Majenko Technologies
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <PrecisionADC.h>

void PrecisionADC::begin() {
    _spi->begin();
    pinMode(_adcPin, OUTPUT);
    pinMode(_dacPin, OUTPUT);
    digitalWrite(_adcPin, HIGH);
    digitalWrite(_dacPin, HIGH);
}

void PrecisionADC::setReference(uint16_t mv) {
    mv &= 0x0FFF;
    _vref = mv;
    mv |= 0x1000;
#ifdef __PIC32MX__
    _spi->setMode(DSPI_MODE0);
    _spi->setSpeed(10000000UL);
#else
    _spi->setDataMode(SPI_MODE0);
    _spi->setClockDivider(SPI_CLOCK_DIV2);
#endif

    digitalWrite(_dacPin, LOW);
    _spi->transfer((uint8_t)(mv >> 8));
    _spi->transfer((uint8_t)(mv & 0xFF));
    digitalWrite(_dacPin, HIGH);
}

void PrecisionADC::setVOut(uint16_t mv) {
    mv &= 0x0FFF;
    mv |= 0x9000;

#ifdef __PIC32MX__
    _spi->setMode(DSPI_MODE0);
    _spi->setSpeed(10000000UL);
#else
    _spi->setDataMode(SPI_MODE0);
    _spi->setClockDivider(SPI_CLOCK_DIV2);
#endif

    digitalWrite(_dacPin, LOW);
    _spi->transfer((uint8_t)(mv >> 8));
    _spi->transfer((uint8_t)(mv & 0xFF));
    digitalWrite(_dacPin, HIGH);
}

int32_t PrecisionADC::read() {
    int32_t out = 0;
    digitalWrite(_adcPin, LOW);
    delay(20);

#ifdef __PIC32MX__
    _spi->setMode(DSPI_MODE3);
    _spi->setSpeed(10000000UL);
#else
    _spi->setDataMode(SPI_MODE3);
    _spi->setClockDivider(SPI_CLOCK_DIV2);
#endif

    uint8_t bh = _spi->transfer((uint8_t)0xFF);
    uint8_t bm = _spi->transfer((uint8_t)0xFF);
    uint8_t bl = _spi->transfer((uint8_t)0xFF);
    digitalWrite(_adcPin, HIGH);

    out = ((uint32_t)bh << 16) | ((uint32_t)bm << 8) | (uint32_t)bl;

    if ((out & 0xC00000UL) == 0) {
        out |= ((out & 0x200000UL) ? 0xFFC00000UL : 0x000000UL);
        _overflow = 0;
    } else {
        out &= ~0x400000UL;
        out |= ((out & 0x800000UL) ? 0xFFC00000UL : 0x000000UL);
        _overflow = 1;
    }

#ifdef __PIC32MX__
    _spi->setMode(DSPI_MODE0);
    _spi->setSpeed(10000000UL);
#else
    _spi->setDataMode(SPI_MODE0);
    _spi->setClockDivider(SPI_CLOCK_DIV2);
#endif
    return out;
}

float PrecisionADC::readMV() {
    float a = read();
    a = a / 2097151.0 * _vref;
    return a;
}

uint8_t PrecisionADC::overflow() {
    return _overflow;
}
