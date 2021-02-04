/** 
 * @file        rgb-led-lighting-shield-ino.hpp
 * @brief       RGB LED LIGHTING SHIELD Library KIT Arduino
 * @date        February 2021
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef RGB_LED_LIGHTING_SHIELD_INO_HPP_
#define RGB_LED_LIGHTING_SHIELD_INO_HPP_

#include "rgb-led-lighting-shield.hpp"
#include "rgb-led-lighting-shield-pal-i2c-ino.hpp"
#include <Arduino.h>
#include <Wire.h>

class RGBShieldIno : virtual public RGBShield
{
    public:
        RGBShieldIno(TwoWire *wire = &Wire);
        ~RGBShieldIno();
        Error_t begin();
};

#endif /** RGB_LED_LIGHTING_SHIELD_INO_HPP_ **/
