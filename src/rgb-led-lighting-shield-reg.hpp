/** 
 * @file        rgb-led-lighting-shield-reg.hpp
 * @brief       RGB LED LIGHTING SHIELD Library KIT REGISTERS
 * @date        November 2020
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef RGB_LED_LIGHTING_SHIELD_REG_HPP_
#define RGB_LED_LIGHTING_SHIELD_REG_HPP_

#define ADDRESS				0x795E              /**< Address of the XMC-I2C-Slave */
#define FIRSTADDRESSBYTE 	0x79				/**< First address byte which has to be sent */
#define SECONDADDRESSBYTE	0x5E				/**< Second address byte which has to be sent */

/**
 * @brief Write commands
 * List of all the I2C-Write commands
 */
enum AccesCommands_t{
    INTENSITY_RED               = 0x11U,    /**< Set intensity of the red channel */ 
    INTENSITY_GREEN             = 0x12U,    /**< Set intensity of the green channel */
    INTENSITY_BLUE              = 0x13U,    /**< Set intensity of the blue channel */
    INTENSITY_RGB               = 0x14U,    /**< Set intensity of all three channels */

    CURRENT_RED                 = 0x21U,    /**< Set the peak current reference of the red channel */
    CURRENT_GREEN               = 0x22U,    /**< Set the peak current reference of the green channel */
    CURRENT_BLUE                = 0x23U,    /**< Set the peak current reference of the blue channel */
    CURRENT_RGB                 = 0x24U,    /**< Set the peak current reference of the three channels */

    DMXOFF                      = 0x30U,    /**< Enable DMX-Standard for the shield */
    DMXON                       = 0x31U,    /**< Disable DMX-Standard for the shield */
    DMXSLOT                     = 0x32U,    /**< Starting slot number of DMX */
    DMX8BIT                     = 0x33U,    /**< Configuration for 8bit DMX */
    DMX16BIT                    = 0x34U,    /**< Configuration for 16bit DMX */
    
    OFFTIME_RED                 = 0x41U,    /**< Set off-time of the red channel */
    OFFTIME_GREEN               = 0x42U,    /**< Set off-time of the green channel */
    OFFTIME_BLUE                = 0x43U,    /**< Set off-time of the blue channel */
    WALKTIME                    = 0x50U,    /**< Set the walk-time */
    DIMMINGLEVEL                = 0x60U,    /**< Set the dimming level */
    FADERATE                    = 0x61U,     /**< Set the fade rate */

    _CHANGE_ADDRESS             = 0x70U,    /**< Change address of the slave */

    SAVEPARAMETERS              = 0xA0U     /**< Save the set parameters */
};

 /**
 * @brief Read commands
 * List of all the I2C-Read commands
 */
enum ReadCommands_t{
     READ_INTENSITY_RED         = 0x81U,    /**< Read the intensity of the red channel */
     READ_INTENSITY_GREEN       = 0x82U,    /**< Read the intensity of the green channel */
     READ_INTENSITY_BLUE        = 0x83U,    /**< Read the intensity of the blue channel */

     READ_CURRENT_RED           = 0x84U,    /**< Read the peak current reference of the red channel */
     READ_CURRENT_GREEN         = 0x85U,    /**< Read the peak current reference of the green channel */
     READ_CURRENT_BLUE          = 0x86U,    /**< Read the peak current reference of the blue channel */

     READ_OFFTIME_RED           = 0x87U,    /**< Read the off-time of the red channel */
     READ_OFFTIME_GREEN         = 0x88U,    /**< Read the off-time of the green channel */
     READ_OFFTIME_BLUE          = 0x89U,    /**< Read the off-time of the blue channel */

     READ_WALKTIME              = 0x8AU,    /**< Read the walk-time */
     READ_DIMMINGLEVEL          = 0x8BU,    /**< Read the dimming level */
     READ_FADERATE              = 0x8CU,    /**< Read the faderate */

     DIRECTACCESS_READ          = 0x90U,    /**< Read directly from register */
     DIRECTACCESS_MOVE   	    = 0x91U,    /**< Move register */    
     DIRECTACCESS_AND           = 0x92U,    /**< Logic AND with send data */
     DIRECTACCESS_OR            = 0x93U     /**< Logic OR with send data */
};

/**
 * @brief List of the available, predefined colors for
 * the shield 
 */
enum Colors_t{
    WHITE,          /**< Color white */
    SILVER,         /**< Color silver */
    GRAY,           /**< Color gray */
    BLACK,          /**< Color black */
    RED,            /**< Color red */
    MAROON,         /**< Color maroon */
    YELLOW,         /**< Color yellow */
    OLIVE,          /**< Color olive */
    LIME,           /**< Color lime */
    GREEN,          /**< Color green */
    AQUA,           /**< Color aqua */
    TEAL,           /**< Color teal */
    BLUE,           /**< Color blue */
    NAVY,           /**< Color navy */
    FUCHSIA,        /**< Color fuchsia */
    PURPLE          /**< Color purple */
};

#endif /** RGB_LED_LIGHTING_SHIELD_REG_HPP_ **/
