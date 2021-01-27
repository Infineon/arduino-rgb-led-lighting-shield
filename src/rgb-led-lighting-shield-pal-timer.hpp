/** 
 * @file        rgb-led-lighting-shield-pal-timer.hpp
 * @brief       RGB LED LIGHTING SHIELD TIMER Platform Abstraction Layer
 * @date        November 2020
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef RGB_LED_LIGHTING_SHIELD_PAL_TIMER_HPP_
#define RGB_LED_LIGHTING_SHIELD_PAL_TIMER_HPP_

#include <stdint.h>
#include "rgb-led-lighting-shield-types.hpp"

namespace rgbShield
{

class Timer
{
    public:

        virtual Error_t init () = 0;
        virtual Error_t deinit () = 0;
        virtual Error_t start () = 0;
        virtual Error_t elapsed (uint32_t &elapsed) = 0;
        virtual Error_t stop () = 0;
        virtual Error_t delay (uint32_t timeout) = 0;
};

}

#endif /** RGB_LED_LIGHTING_SHIELD_PAL_TIMER_HPP_ **/