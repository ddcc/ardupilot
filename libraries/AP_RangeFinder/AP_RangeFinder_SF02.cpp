// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 *       AP_RangeFinder_SF02.cpp - Arduino Library for LightWare OptoElectronics SF02/F
 *       Code by Dominic Chen
 *
 *       datasheet: http://lightware.co.za/shop/en/index.php?controller=attachment&id_attachment=1
 *
 *       Sensor should be connected to UART2
 *
 *       Methods:
 *               read() : read last distance measured (in cm)
 *
 */

// AVR LibC Includes
#include "AP_RangeFinder_SF02.h"
#include <AP_HAL.h>

extern const AP_HAL::HAL& hal;

// Constructor //////////////////////////////////////////////////////////////

AP_RangeFinder_SF02::AP_RangeFinder_SF02(AP_HAL::UARTDriver *uart, FilterInt16 *filter) :
    RangeFinder(NULL, filter),
    _port(uart),
    reading(false)
{
    min_distance = AP_RANGE_FINDER_SF02_MIN_DISTANCE;
    max_distance = AP_RANGE_FINDER_SF02_MAX_DISTANCE;
}

// Public Methods //////////////////////////////////////////////////////////////

// do-nothing calculate scaler function to maintain compatibility with analog rangefinders
float AP_RangeFinder_SF02::calculate_scaler(int sonar_type, float adc_refence_voltage) {
    return 1.0f;
}

// read - return value measured by sensor
int AP_RangeFinder_SF02::read() {
    uint8_t value, pos = 0;
    char buf[8];
    float raw;
    char tmp;
    
    // attempt to start reading if not reading
    _port->write('d');

    while (_port->available()) {
        tmp = _port->read();

        // if it is a digit
        if (tmp >= '0' && tmp <= '9' || tmp == '.') {
            buf[pos++] = tmp;
        }
        else if (tmp == '\r' || tmp == '\n') {
            if (pos >= 3) {
                // complete 4+ digit float received, quit receive loop
                buf[pos] = '\0';
                break;
            }
            else {
                // received incomplete float, reset position
                pos = 0;
            }
        }
    }

    if (pos >= 3) {
        // convert result from string to float, then multiply by 100 for cm
        raw = atof(buf);

        // set raw value
        raw_value = (int) (raw * 100);

        // ensure distance is within min and max
        value = constrain_float(raw_value, min_distance, max_distance);

        // apply mode (median?) filter?
        // value = _mode_filter->apply(value);

        // reset position
        pos = 0;

        return value;
    }

    // failed to get reading, return error
    return -1;
}
