/** 
 * @file        rgb-led-lighting-shield-ino.cpp
 * @brief       RGB LED LIGHTING SHIELD Library KIT Arduino
 * @date        February 2021
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "rgb-led-lighting-shield-ino.hpp"

I2CPAL * custom_i2cpal = nullptr;

RGBShieldIno::RGBShieldIno(TwoWire *wire): RGBShield((custom_i2cpal = new I2CPALIno(wire)))
{
    _shieldState = UNINITED;
}

RGBShieldIno::~RGBShieldIno()
{
    if(nullptr != custom_i2cpal)
    {
        delete custom_i2cpal;
        custom_i2cpal = nullptr;
    }
}

Error_t RGBShieldIno::begin()
{   
    Error_t err = OK;

    init();
    Serial.println("Initialization done\n\n\n\n\n\n\n\n\n\n");

    return err;
}