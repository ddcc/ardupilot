// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef __AP_RANGEFINDER_SF02_H__
#define __AP_RANGEFINDER_SF02_H__

#include "RangeFinder.h"

#define AP_RANGE_FINDER_SF02_MIN_DISTANCE  0
#define AP_RANGE_FINDER_SF02_MAX_DISTANCE  4000

class AP_RangeFinder_SF02 : public RangeFinder {
    public:
        AP_RangeFinder_SF02(AP_HAL::UARTDriver *uart, FilterInt16 *filter);
        bool start_reading();
        bool stop_reading();
        int read();

        float calculate_scaler(int sonar_type, float adc_refence_voltage);
        
    protected:
        AP_HAL::UARTDriver* _port;
        bool reading;
};

#endif  // __AP_RANGEFINDER_SF02_H__
