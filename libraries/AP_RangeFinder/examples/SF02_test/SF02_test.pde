#include <AP_Common.h>
#include <AP_Progmem.h>
#include <AP_Param.h>
#include <AP_HAL.h>
#include <AP_Math.h>
#include <AP_RangeFinder.h>
#include <Filter.h>
#include <AP_Buffer.h>
#include <AP_HAL_AVR.h>

const AP_HAL::HAL& hal = AP_HAL_BOARD_DRIVER;

// declare global instances
ModeFilterInt16_Size5 mode_filter(2);

AP_RangeFinder_SF02 *rf;

void setup() {
    hal.uartC->begin(9600, 8, 4);

    hal.console->println("SF02 Laser Rangefinder Test v1.0");
 
    rf = new AP_RangeFinder_SF02(hal.uartC, &mode_filter);
}

void loop() {
    int result = 0;

    if ((result = rf->read()) != -1) {
        hal.console->print("distance: ");
        hal.console->println(result);
    }

    hal.scheduler->delay(100);
}

AP_HAL_MAIN();