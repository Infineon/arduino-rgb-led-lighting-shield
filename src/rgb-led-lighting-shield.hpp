/** 
 * @file        rgb-led-lighting-shield.hpp
 * @brief       RGB LED LIGHTING SHIELD Library KIT
 * @date        November 2020
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef RGB_LED_LIGHTING_SHIELD_HPP_
#define RGB_LED_LIGHTING_SHIELD_HPP_

#include <stdint.h>
#include "rgb-led-lighting-shield-pal-timer.hpp"
#include "rgb-led-lighting-shield-pal-i2c.hpp"
#include "rgb-led-lighting-shield-reg.hpp"

using namespace rgbShield;

/**
 * @class RGBShield
 * @brief RGB LED Lighting Shield Class
 * @details This class defines the XMC-RGB-LED-Lighting-Shield from Infineon
 * with all its functionality
 */
class RGBShield
{
    public:
        RGBShield(I2CPAL *i2c);
        ~RGBShield();
        Error_t init();
        Error_t deinit();
        Error_t setIntensityRGB(uint16_t red, uint16_t green, uint16_t blue);
        Error_t setIntensityRed(uint16_t red);
        Error_t setIntensityGreen(uint16_t green);
        Error_t setIntensityBlue(uint16_t blue);
        Error_t setDimmingLevel(uint16_t level);
        Error_t setOffTimesRGB(uint16_t red, uint16_t green, uint16_t blue);
        Error_t setCurrentRGB(uint16_t red, uint16_t green, uint16_t blue);
        Error_t setFadeRate(uint16_t fRate);
        Error_t setWalkTime(uint16_t wTime);
        Error_t saveParameters();
        Error_t setColor(uint16_t color);

    protected:
        Status_t _shieldState;      /**< Variable to store the status of the shield */

        I2CPAL *_boardI2C;          /**< Class pointer to the I2CPAL class */

        uint16_t _redCurr;          /**< Variable to store the peak current reference for the red channel */
		uint16_t _greenCurr;        /**< Variable to store the peak current reference for the green channel */
		uint16_t _blueCurr;         /**< Variable to store the peak current reference for the blue channel */
		uint16_t _redOff;           /**< Variable to store the off-time of the red channel */
		uint16_t _greenOff;         /**< Variable to store the off-time of the green channel */
		uint16_t _blueOff;          /**< Variable to store the off-time of the blue channel */
		uint16_t _redInt;           /**< Variable to store the intensity for the red channel */
		uint16_t _greenInt;         /**< Variable to store the intensity for the green channel */
		uint16_t _blueInt;          /**< Variable to store the intensity for the blue channel */
		uint16_t _fadeTime;         /**< Variable to store the fadetime */
		uint16_t _walk;             /**< Variable to store the walktime */
		uint16_t _brightness;       /**< Variable to store the _brightness */
};

#endif /** RGB_LED_LIGHTING_SHIELD_HPP_ **/