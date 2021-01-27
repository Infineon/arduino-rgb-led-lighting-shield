/** 
 * @file        rgb-led-lighting-shield-types.hpp
 * @brief       RGB LED LIGHTING SHIELD Library Types
 * @date        November 2020
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef RGB_LED_LIGHTING_SHIELD_TYPES_HPP_
#define RGB_LED_LIGHTING_SHIELD_TYPES_HPP_

namespace rgbShield
{
    /**
     * @brief Error List
     * @details List of all the errors that can occur during the use
     * of the board
     */
    enum Error_t
    {
        OK              =  0,               /**< Success. No error */
        INTF_ERROR      = -1,               /**< Interface error */
        RESET_ERROR     = -2,               /**< Reset error */
        POWER12V_ERROR  = -3,               /**< IR Power error */
        TEMP_ERROR      = -4,               /**< Temperature excedded error */
        COMM_ERROR      = -5,               /**< Serial comm. interface error */
        REG_ERROR       = -6,               /**< Register operation error */ 
        INVALID_FUNC_STATUS_ERROR = -7,     /**< Function not supported for current status error */
        INVALID_FUNC_INTF_ERROR   = -8,     /**< Function not supported for current interface error */
        INVALID_CONFIG_ERROR      = -9,     /**< Invalid configuration error */
        TIMEOUT_ERROR             = -10     /**< Timeout error */
    };

    /**
     * @brief Status List
     * @details List of different statuses the board can have
     * during use
     */
    enum Status_t
    {
        UNINITED       =  0x00,             /**< Uninitialized */
        INITED         =  0x01,             /**< Initialized */
        ENAB           =  0x02              /**< Enabled */         
    };
}

#endif /** RGB_LED_LIGHTING_SHIELD_TYPES_HPP_ **/