/** 
 * @file        rgb-led-lighting-shield.cpp
 * @brief       RGB LED LIGHTING SHIELD Library KIT
 * @date        November 2020
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "rgb-led-lighting-shield.hpp"

/**
 * @brief Constructor of the RGBShield-Class
 * 
 * @details This constructor is used to create an object of the RGBShield class.
 * It is getting a class pointer to the I2C-Class which is given to the private IC2-class-pointer.
 * It is also initializing the status of the shield to UNINITED, because the board is not yet initialized.
 * 
 * @param[in] *i2c  Pointer to a I2C instance
 */
RGBShield::RGBShield(I2CPAL *i2c){
    _shieldState = UNINITED;
    _boardI2C = i2c;
}

/**
 * @brief Destructor of the RGBShield-Class
 * 
 * @details This destructor is used to destruct the object of the RGBShield class.
 */
RGBShield::~RGBShield(){
    _shieldState = UNINITED;
    _boardI2C = nullptr;
}


/**
 * @brief Initialization
 * 
 * @details This function is initializing the I2C instance given in the constructor
 * as well as all private membervariables of the class. It is also changing the board
 * status to enable, which means the board is ready to operate. Furthermore, the function
 * is setting the maximum current ratings for the shield as well as the off-times of the 
 * channels. It is also setting the brightness of the shield to zero.
 * 
 * @return Error_t 
 */
Error_t RGBShield::init(){
    Error_t err = OK;
    bool valid = false;
    int counter = 0;

    _boardI2C->init();
    _shieldState = INITED;
    _shieldState = ENAB;

    _redCurr     = 0x00;
    _greenCurr   = 0x00;
    _blueCurr    = 0x00;
    _redOff      = 0x00;
    _greenOff    = 0x00;
    _blueOff     = 0x00;
    _redInt      = 0x00;
    _greenInt    = 0x00;
    _blueInt     = 0x00;
    _fadeTime    = 0x00;
    _walk        = 0x00;
    _brightness  = 0x00;

    while(valid != 1){
        uint16_t dataRead = 0x0000;
        _boardI2C->writeDMX(ADDRESS, DMXOFF);
        _boardI2C->write(ADDRESS, FADERATE, 0x0000);
        _boardI2C->write(ADDRESS, DIMMINGLEVEL, 0x0000);
        _boardI2C->read(ADDRESS, READ_DIMMINGLEVEL, &dataRead);
        if(dataRead == 0){     //Check if the dimming level is set correctly
            valid = true;
        }
        counter++;
        if(counter >= 20){
            err = TIMEOUT_ERROR;
            return err;
        }
    }

    counter = 0;
    while (_redCurr != 0x15 || _greenCurr != 0x15 || _blueCurr != 0x15 || _redOff != 0x38 || _greenOff != 0x39 || _blueOff != 0x38 || _brightness != 0)
    {
        uint16_t lightOff[] = {0x0000, 0x0000, 0x0000};
        _boardI2C->write(ADDRESS, INTENSITY_RGB, lightOff, sizeof(lightOff));
        _boardI2C->write(ADDRESS, OFFTIME_RED, 0x38);
        _boardI2C->write(ADDRESS, OFFTIME_GREEN, 0x39);
        _boardI2C->write(ADDRESS, OFFTIME_BLUE, 0x38);
        _boardI2C->write(ADDRESS, CURRENT_RED, 0x15);
        _boardI2C->write(ADDRESS, CURRENT_GREEN, 0x15);
        _boardI2C->write(ADDRESS, CURRENT_BLUE, 0x15);
        _boardI2C->write(ADDRESS, DIMMINGLEVEL, 0x0000);

        _boardI2C->read(ADDRESS, READ_CURRENT_RED, &_redCurr);
        _boardI2C->read(ADDRESS, READ_CURRENT_GREEN, &_greenCurr);
        _boardI2C->read(ADDRESS, READ_CURRENT_BLUE, &_blueCurr);
        _boardI2C->read(ADDRESS, READ_OFFTIME_RED, &_redOff);
        _boardI2C->read(ADDRESS, READ_OFFTIME_GREEN, &_greenOff);
        _boardI2C->read(ADDRESS, READ_OFFTIME_BLUE, &_blueOff);
        _boardI2C->read(ADDRESS, READ_DIMMINGLEVEL, &_brightness);
        counter++;
        if(counter >= 20){
            err = TIMEOUT_ERROR;
            return err;
        }
    }
    return err;
}

/**
 * @brief Deinitialization
 * 
 * @details This function deinitializes the IC2 instance given in the constructor.
 * It is also setting the shieldstate back to uninitialize.
 * 
 * @return Error_t 
 */
Error_t RGBShield::deinit(){
    Error_t err = OK;
    
    _boardI2C->deinit();
    _shieldState = UNINITED;

    return err;
}

/**
 * @brief Set intensity of all channels
 * 
 * @details This functions is setting the intensity of the red-, green- and blue-channel.
 * You have to pass a 12-bit value for every channel to the function. The maximum value is
 * therefore 0xFFF (4095 Dec) for every channel.
 * 
 * @param[in] red       Intensity of the red-channel. Range is 0x000 to 0xFFF
 * @param[in] green     Intensity of the green-channel. Range is 0x000 to 0xFFF
 * @param[in] blue      Intensity of the blue-channel. Range is 0x000 to 0xFFF
 * 
 * @return Error_t 
 */
Error_t RGBShield::setIntensityRGB(uint16_t red, uint16_t green, uint16_t blue){
    Error_t err = OK;

    uint16_t color[] = {red, green, blue};
    _boardI2C->write(ADDRESS, INTENSITY_RGB, color, sizeof(color));

    return err;
}

/**
 * @brief Set intensity of the red-channel
 * 
 * @details This function is setting the intensity of the red-channel.
 * You have to pass a 12-bit value. Therefore, the maximum value is 0xFFF (4095 Dec)
 * 
 * @param[in] red   Intensity of the red-channel. Range is 0x000 to 0xFFF. 
 * @return Error_t 
 */
Error_t RGBShield::setIntensityRed(uint16_t red){
    Error_t err = OK;

    _boardI2C->write(ADDRESS, INTENSITY_RED, red);

    return err;
}

/**
 * @brief Set intensity of the green-channel
 * 
 * @details This function is setting the intensity of the green-channel.
 * You have to pass a 12-bit value. Therefore, the maximum value is 0xFFF (4095 Dec)
 * 
 * @param[in] green   Intensity of the green-channel. Range is 0x000 to 0xFFF. 
 * @return Error_t 
 */
Error_t RGBShield::setIntensityGreen(uint16_t green){
    Error_t err = OK;

    _boardI2C->write(ADDRESS, INTENSITY_GREEN, green);

    return err;
}

/**
 * @brief Set intensity of the blue-channel
 * 
 * @details This function is setting the intensity of the blue-channel.
 * You have to pass a 12-bit value. Therefore, the maximum value is 0xFFF (4095 Dec)
 * 
 * @param[in] blue   Intensity of the blue-channel. Range is 0x000 to 0xFFF.
 *  
 * @return Error_t 
 */
Error_t RGBShield::setIntensityBlue(uint16_t blue){
    Error_t err = OK;

    _boardI2C->write(ADDRESS, INTENSITY_BLUE, blue);

    return err;
}

/**
 * @brief Set dimming level
 * 
 * @details This function is setting the dimming level of the shield. A low value means
 * a low brightness of the LEDs, a high value means bright LEDs. The dimming level is a 12-bit value,
 * therefore the maximum value is 0xFFF (4095 Dec).
 * 
 * @param[in] level   Brightness of the LEDs. Range is 0x000 to 0xFFF.
 * 
 * @return Error_t 
 */
Error_t RGBShield::setDimmingLevel(uint16_t level){
    Error_t err = OK;

    _boardI2C->write(ADDRESS, DIMMINGLEVEL, level);

    return err;
}

/**
 * @brief Set off-time for the three channels
 * 
 * @details This function is setting the off-time for all three channels of the RGB-Shield.
 * The off-time is influencing the current ripple on the channel and should be adjusted to the used
 * LEDs accordingly. For more details take a look into the datasheet on page 23.
 * 
 * @param[in] red   Off-time of the red channel. Range is 0x000 to 0xFFF.
 * @param[in] green Off-time of the green channel. Range is 0x000 to 0xFFF.
 * @param[in] blue  Off-time of the blue channel. Range is 0x000 to 0xFFF.
 * 
 * @return Error_t 
 */
Error_t RGBShield::setOffTimesRGB(uint16_t red, uint16_t green, uint16_t blue){
    Error_t err = OK;

    _boardI2C->write(ADDRESS, OFFTIME_RED, red);
    _boardI2C->write(ADDRESS, OFFTIME_GREEN, green);
    _boardI2C->write(ADDRESS, OFFTIME_BLUE, blue);

    return err;
}

/**
 * @brief Set peak-current for the three channels
 * 
 * @details This function is setting the peak-current value of each channel.
 * This value is limmiting the current that flowing through the LEDs. If one
 * of the channels exceeds the set limitation the channel will turn off.
 * The maximum value for one channel is 0x80, which results in a theoretical
 * peak-current of 781 mA (see board manual page 22 for more details).
 * 
 * @param[in] red       Peak-Current for the red channel. Range is 0x000 0x80.
 * @param[in] green     Peak-Current for the green channel. Range is 0x000 0x80. 
 * @param[in] blue      Peak-Current for the blue channel. Range is 0x000 0x80. 
 * 
 * @return Error_t 
 */
Error_t RGBShield::setCurrentRGB(uint16_t red, uint16_t green, uint16_t blue){
    Error_t err = OK;

    _boardI2C->write(ADDRESS, CURRENT_RED, red);
    _boardI2C->write(ADDRESS, CURRENT_GREEN, green);
    _boardI2C->write(ADDRESS, CURRENT_BLUE, blue);

    return err;
}

/**
 * @brief Set the fade rate of the board
 * 
 * @details This function is setting the fade rate of the board. The fade rate
 * controlls how fast the LEDs can change the brightness. On page 31 of the board
 * manual is a description how to calculate the time.
 * 
 * @param[in] fRate     Value of the fade rate. Range is 0x000 to 0x3FF (10-bit).
 *  
 * @return Error_t 
 */
Error_t RGBShield::setFadeRate(uint16_t fRate){
    Error_t err = OK;

    _boardI2C->write(ADDRESS, FADERATE, fRate);

    return err;
}

/**
 * @brief Set the walk-time of the board
 * 
 * @details This functions is setting the walk-time of the board. The walk-time
 * is setting the length of the linear walk. A linear walk can be used to smoothly
 * change the color intensity. For more information take a look at the manual page 25.
 * 
 * @param[in] wTime     Walk time of the board. Range is 0x000 to 0xFFF.
 * 
 * @return Error_t 
 */
Error_t RGBShield::setWalkTime(uint16_t wTime){
    Error_t err = OK;

    _boardI2C->write(ADDRESS, WALKTIME, wTime);

    return err;
}

/**
 * @brief Save the current parameters
 * 
 * @details This functions is used to save the current parameters to the
 * flash memory of the board. It can be called if the current settings
 * should be saved for the future.
 * 
 * @return Error_t 
 */
Error_t RGBShield::saveParameters(){
    Error_t err = OK;
    uint16_t data = 0x0000;
    uint16_t readBuffer[3];

    _boardI2C->write(ADDRESS, SAVEPARAMETERS, data);
    _boardI2C->read(ADDRESS, 0, readBuffer, 2);

    return err;
}

/**
 * @brief Set a predefined color
 * 
 * @details This function is setting a predefined color. The available colors
 * can be found in the enum "colors_t" in the rgb-led-lighting-shield-reg.hpp-file.
 * 
 * @param[in] color     Predefined color.
 * 
 * @return Error_t 
 */
Error_t RGBShield::setColor(uint16_t color){
    Error_t err = OK;

    switch (color)
    {
        case WHITE:
        {
            uint16_t colors[] = {0x800, 0x800, 0x800};
            _boardI2C->write(ADDRESS, INTENSITY_RGB, colors, sizeof(colors));
            break;
        }

        case SILVER:
        {
            uint16_t colors[] = {0xC00, 0xC00, 0xC00};
            _boardI2C->write(ADDRESS, INTENSITY_RGB, colors, sizeof(colors));
            break;
        }

        case GRAY:
        {
            uint16_t colors[] = {0x800, 0x800, 0x800};
            _boardI2C->write(ADDRESS, INTENSITY_RGB, colors, sizeof(colors));
            break;
        }
        
        case BLACK:
        {
            uint16_t colors[] = {0x0, 0x0, 0x0};
            _boardI2C->write(ADDRESS, INTENSITY_RGB, colors, sizeof(colors));
            break;
        }
        
        case RED:
        {
            uint16_t colors[] = {0xFFF, 0x0, 0x0};
            _boardI2C->write(ADDRESS, INTENSITY_RGB, colors, sizeof(colors));
            break;
        }

        case MAROON:
        {
            uint16_t colors[] = {0x800, 0x0, 0x0};
            _boardI2C->write(ADDRESS, INTENSITY_RGB, colors, sizeof(colors));
            break;
        }

        case YELLOW:
        {
            uint16_t colors[] = {0xFFF, 0xFFF, 0x0};
            _boardI2C->write(ADDRESS, INTENSITY_RGB, colors, sizeof(colors));
            break;
        }

        case OLIVE:
        {
            uint16_t colors[] = {0x800, 0x800, 0x0};
            _boardI2C->write(ADDRESS, INTENSITY_RGB, colors, sizeof(colors));
            break;
        }

        case LIME:
        {
            uint16_t colors[] = {0x0, 0xFFF, 0x0};
            _boardI2C->write(ADDRESS, INTENSITY_RGB, colors, sizeof(colors));
            break;
        }

        case GREEN:
        {
            uint16_t colors[] = {0x0, 0x800, 0x0};
            _boardI2C->write(ADDRESS, INTENSITY_RGB, colors, sizeof(colors));
            break;
        }

        case AQUA:
        {
            uint16_t colors[] = {0x0, 0xFFF, 0xFFF};
            _boardI2C->write(ADDRESS, INTENSITY_RGB, colors, sizeof(colors));
            break;
        }

        case TEAL:
        {
            uint16_t colors[] = {0x0, 0x800, 0x800};
            _boardI2C->write(ADDRESS, INTENSITY_RGB, colors, sizeof(colors));
            break;
        }

        case BLUE:
        {
            uint16_t colors[] = {0x0, 0x0, 0xFFF};
            _boardI2C->write(ADDRESS, INTENSITY_RGB, colors, sizeof(colors));
            break;
        }

        case NAVY:
        {
            uint16_t colors[] = {0x0, 0x0, 0x800};
            _boardI2C->write(ADDRESS, INTENSITY_RGB, colors, sizeof(colors));
            break;
        }

        case FUCHSIA:
        {
            uint16_t colors[] = {0xFFF, 0x0, 0xFFF};
            _boardI2C->write(ADDRESS, INTENSITY_RGB, colors, sizeof(colors));
            break;
        }

        case PURPLE:
        {
            uint16_t colors[] = {0x800, 0x0, 0x800};
            _boardI2C->write(ADDRESS, INTENSITY_RGB, colors, sizeof(colors));
            break;
        }
        
        default:
        {
            break;
        }

    }

    return err;
}
