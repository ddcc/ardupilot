// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef __AP_RANGEFINDER_SF01_H__
#define __AP_RANGEFINDER_SF01_H__

#include "RangeFinder.h"

#define AP_RANGE_FINDER_SF01_MIN_DISTANCE  0
#define AP_RANGE_FINDER_SF01_MAX_DISTANCE  6000

class AP_RangeFinder_SF01 : public RangeFinder {
    public:
        AP_RangeFinder_SF01(AP_HAL::UARTDriver *uart, FilterInt16 *filter);
        int read();

        float calculate_scaler(int sonar_type, float adc_refence_voltage);
        
    protected:
        AP_HAL::UARTDriver* _port;
};

#endif  // __AP_RANGEFINDER_SF01_H__
