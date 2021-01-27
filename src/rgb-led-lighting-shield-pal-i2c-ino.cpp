/** 
 * @file        rgb-led-lighting-shield-pal-i2c-ino.cpp
 * @brief       RGB LED LIGHTING SHIELD I2C Platform Abstraction Layer Arduino
 * @date        November 2020
 * @copyright   Copyright (c) 2020 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "rgb-led-lighting-shield-pal-i2c-ino.hpp"

#if (RGB_LED_LIGHTING_SHIELD_FRAMEWORK == RGB_LED_LIGHTING_SHIELD_FRMWK_ARDUINO)

/**
 * @brief Constructor of the IC2-Class for Arduino
 * 
 * @details This is the default constructor of the I2C-Class for Arduino.
 * It is getting a pointer to the TwoWire-Class.
 * 
 * @param[in] wire      Pointer to the TwoWire-Class. 
 */
I2CPALIno::I2CPALIno(TwoWire *wire)
{
    this->_wire = wire;
}

/**
 * @brief Destructor of the Arduino I2C-Class
 * 
 * @details This is the destructor of the I2C-Class for Arduino.
 * 
 */
I2CPALIno::~I2CPALIno()
{

}

/**
 * @brief Initialization of the I2C bus
 * 
 * @details This function is initializing the I2C bus. It takes care
 * that all necessary values are set, so that the I2C bus can work properly.
 * 
 * @return Error_t 
 */
Error_t I2CPALIno::init()
{
    Error_t err = OK;
    do{
        if(nullptr == _wire){
            err = INTF_ERROR;
            break;
        }

        _wire->begin();

    }while(0);
    return err;
}

/**
 * @brief Set the clock frequency of the I2C bus
 * 
 * @details This function is setting the clock frequency of the I2C bus, if the
 * default value(100 kHz) should be changed.
 * 
 * @param[in] clockHz       Clock frequency in Hz
 * 
 * @return Error_t 
 */
Error_t I2CPALIno::setClockFreq(uint32_t clockHz)
{
    Error_t err = OK;

    do{
        if(nullptr == _wire){
            err = INTF_ERROR;
            break;
        }

        _wire->setClock((uint32_t)clockHz);

    }while(0);

    return err;
}

/**
 * @brief Deinitialize the I2C bus
 * 
 * @details This function is de-initializing the I2C bus. The bus
 * has to be initialized again for further usage.
 * 
 * @return Error_t 
 */
Error_t I2CPALIno::deinit()
{
    Error_t err = OK;

    _wire->end();

    return err;
}

/**
 * @brief Read several bytes from the slave via I2C
 * 
 * @details This functions is used to read from a slave on the I2C bus. It needs the
 * address of the slave, the required command (see rgb-led-lighting-shield-reg.hpp), a pointer to the
 * data buffer, where the received data is stored and the length of the data buffer that should be sent.
 * 
 * @param[in] addr          Address of the slave device.
 * @param[in] command       Command to read out the board.
 * @param[in,out] data      Pointer to a buffer where the received data is stored.
 * @param[in] length        Number of bytes to read.
 * 
 * @return Error_t 
 */
Error_t I2CPALIno::read(uint16_t addr, uint8_t command, uint16_t *data, uint16_t length)
{
    Error_t err = OK;

    int i = 0;
    int y = 0;
    uint8_t buffer[length];

    uint8_t upperAddressByte = addr >> 8;
    uint8_t lowerAddressByte = addr & 0x00FF;
    upperAddressByte |= 0x79;

    _wire->beginTransmission(upperAddressByte);
    _wire->write(lowerAddressByte);
    _wire->write(command);
    _wire->endTransmission((uint8_t)false);

    _wire->beginTransmission(upperAddressByte);
    _wire->write(lowerAddressByte);
    _wire->requestFrom(upperAddressByte, (uint8_t)length, (uint8_t)true);

    while(_wire->available() > 0){
        buffer[i] = _wire->read();
        if(i%1 == 1){
            data[y] = (buffer[i] << 8) | buffer[i-1];
            y++;
        }
        i++;
    }
    _wire->endTransmission(true);

    return err;
}

/**
 * @brief Read two byte (an unsigned int16) from the I2C slave
 * 
 * @details This function is used to read two byte from the I2C slave. It requires the
 * address of the slave, the command of what should be read (see rgb-led-lighting-shield-reg.hpp)
 * and a pointer to an uint16 variable where the received data is stored.
 * 
 * @param[in] addr          Address of the slave device.
 * @param[in] command       Command to read out the board.
 * @param[in, out] data     Pointer to an uint16 variable to store the received data.
 *  
 * @return Error_t 
 */
Error_t I2CPALIno::read(uint16_t addr, uint8_t command, uint16_t *data)
{
    Error_t err = OK;
    int i = 0;
    uint16_t buffer[3];

    uint8_t upperAddressByte = addr >> 8;
    uint8_t lowerAddressByte = addr & 0x00FF;
    upperAddressByte |= 0x79;

    _wire->beginTransmission(upperAddressByte);
    _wire->write(lowerAddressByte);
    _wire->write(command);
    _wire->endTransmission((uint8_t)false);

    _wire->beginTransmission(upperAddressByte);
    _wire->write(lowerAddressByte);
    _wire->requestFrom(upperAddressByte, (uint8_t)2, (uint8_t)true);

    while(_wire->available() > 0){
        buffer[i] = _wire->read();
        i++;
    }
    _wire->endTransmission(true);

    *data = (buffer[1] << 8) | buffer[0];

    return err;
}

/**
 * @brief Write several bytes to the I2C slave
 * 
 * @details This functions is used to write several bytes to an I2C slave.
 * It needs the address of the I2C slave, the write command (see rgb-led-lighting-shield-reg.hpp),
 * the pointer to data buffer which should be sent and the length of the data buffer.
 * 
 * @param[in] addr      Address of the I2C slave device.
 * @param[in] command   Command to write to the board.
 * @param[in] data      Pointer to the data buffer that should be written to the slave. 
 * @param[in] length    Number of bytes that should be written.
 *  
 * @return Error_t 
 */
Error_t I2CPALIno::write(uint16_t addr, uint8_t command, uint16_t *data, uint16_t length)
{
    Error_t err = OK;
    int j = 0;
    uint8_t dataBuffer[length];
    uint8_t upperAddressByte = addr >> 8;
    uint8_t lowerAddressByte = addr & 0x00FF;
    upperAddressByte |= 0x79;

    for(uint16_t i=0; i<length; i+=2){
        dataBuffer[i] = data[j] >> 8;
        dataBuffer[i+1] = data[j];
        j++;
    }

    _wire->beginTransmission(upperAddressByte);
    _wire->write(lowerAddressByte);
    _wire->write(command);
    _wire->write(dataBuffer, length);
    _wire->endTransmission(true);

    return err;
}

/**
 * @brief Write two bytes to the I2C slave
 * 
 * @details This function is used to write two bytes (an unsigned int16) to the slave device.
 * It needs the address of the slave device, the write command (see rgb-led-lighting-shield-reg.hpp) and
 * the data that should be sent.
 * 
 * @param[in] addr      Address of the I2C slave device.    
 * @param[in] command   Command to write to the board. 
 * @param[in] data      Data which should be written to the slave.
 *  
 * @return Error_t 
 */
Error_t  I2CPALIno::write(uint16_t addr, uint8_t command, uint16_t data)
{
    Error_t err = OK;

    uint8_t lowerAddressByte = (addr & 0x00FF);
    uint8_t upperAddressByte = addr >> 8;
    
    upperAddressByte |= 0x79;

    uint8_t lowerDataByte = data;
    uint8_t upperDataByte = data >> 8;
    

    _wire->beginTransmission(upperAddressByte);
    _wire->write(lowerAddressByte);
    _wire->write(command);
    _wire->write(upperDataByte);
    _wire->write(lowerDataByte);
    _wire->endTransmission(true);

    return err;
}

/**
 * @brief Write to the slave via DMX
 * 
 * @details This function is used to write to the slave device via the DMX-Standard.
 * It needs the address of the slave and the command (see rgb-led-lighting-shield-reg.hpp)
 * of what should be written to the slave.
 * 
 * @param[in] addr      Address of the slave device 
 * @param[in] command   Write command
 * 
 * @return Error_t 
 */
Error_t I2CPALIno::writeDMX(uint16_t addr, uint8_t command)
{
    Error_t err = OK;

    uint8_t upperAddressByte = addr >> 8;
    uint8_t lowerAddressByte = addr & 0x00FF;
    upperAddressByte |= 0x79;

    _wire->beginTransmission(upperAddressByte);
    _wire->write(lowerAddressByte);
    _wire->write(command);
    _wire->endTransmission(true);

    return err;
}

#endif /** RGB_LED_LIGHTING_SHIELD_FRMWK_ARDUINO **/
