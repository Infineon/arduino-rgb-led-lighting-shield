/** 
 * @file        rgb-led-lighting-shield-pal-i2c.hpp
 * @brief       RGB LED LIGHTING SHIELD I2C Platform Abstraction Layer
 * @date        November 2020
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef RGB_LED_LIGHTING_SHIELD_PAL_I2C_HPP_
#define RGB_LED_LIGHTING_SHIELD_PAL_I2C_HPP_

#include "rgb-led-lighting-shield-types.hpp"
#include <stdint.h>

namespace rgbShield
{

class I2CPAL
{
    public:

        virtual Error_t init() = 0;
        virtual Error_t deinit() = 0;
        virtual Error_t setClockFreq(uint32_t clockHz) = 0;
        virtual Error_t read(uint16_t addr, uint8_t command, uint16_t *data, uint16_t length) = 0;
        virtual Error_t read(uint16_t addr, uint8_t command, uint16_t *data) = 0;
        virtual Error_t write(uint16_t addr, uint8_t command, uint16_t *data, uint16_t length) = 0;
        virtual Error_t write(uint16_t addr, uint8_t command, uint16_t data) = 0;
        virtual Error_t writeDMX(uint16_t addr, uint8_t command) = 0;
};

}
#endif /** RGB_LED_LIGHTING_SHIELD_PAL_I2C_HPP_ **/