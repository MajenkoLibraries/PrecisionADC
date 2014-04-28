/*
 * %LIBRARY%
 * Copyright (C)  Majenko Technologies
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


#ifndef _PRECISIONADC_H
#define _PRECISIONADC_H

#if (ARDUINO >= 100) 
# include <Arduino.h>
#else
# include <WProgram.h>
#endif

#include <SPI.h>

class PrecisionADC {
    public:
        // Private functions and variables here.  They can only be accessed
        // by functions within the class.
        uint8_t _adcPin;
        uint8_t _dacPin;
        uint16_t _vref;
        uint8_t _overflow;

    public:
        // Public functions and variables.  These can be accessed from
        // outside the class.
        PrecisionADC(uint8_t adc, uint8_t dac) : _adcPin(adc), _dacPin(dac) {}
        void begin();
        void setReference(uint16_t mv);
        void setVOut(uint16_t mv);
        int32_t read();
        float readMV();
        uint8_t overflow();
};
#endif
