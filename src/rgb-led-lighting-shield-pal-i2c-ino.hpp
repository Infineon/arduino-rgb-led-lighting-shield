/** 
 * @file        rgb-led-lighting-shield-pal-i2c-ino.hpp
 * @brief       RGB LED LIGHTING SHIELD I2C Platform Abstraction Layer Arduino
 * @date        February 2021
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef RGB_LED_LIGHTING_SHIELD_PAL_I2C_INO_HPP_
#define RGB_LED_LIGHTING_SHIELD_I2C_INO_HPP_

#include <Wire.h>
#include "rgb-led-lighting-shield-pal-i2c.hpp"

using namespace rgbShield;

class I2CPALIno : virtual public I2CPAL
{
    public:
        I2CPALIno(TwoWire *wire);
        ~I2CPALIno();
        Error_t init();
        Error_t deinit();
        Error_t setClockFreq(uint32_t clockHz);
        Error_t read(uint16_t addr, uint8_t command, uint16_t *data, uint16_t length);
        Error_t read(uint16_t addr, uint8_t command, uint16_t *data);
        Error_t write(uint16_t addr, uint8_t command, uint16_t *data, uint16_t length);
        Error_t write(uint16_t addr, uint8_t command, uint16_t data);
        Error_t writeDMX(uint16_t addr, uint8_t command);

    private:
        TwoWire *_wire;
};

#endif /** RGB_LED_LIGHTING_SHIELD_PAL_I2C_INO_HPP_ **/