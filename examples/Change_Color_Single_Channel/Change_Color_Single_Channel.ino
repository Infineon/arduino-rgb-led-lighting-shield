#if RGB_LED_LIGHTING_SHIELD_FRAMEWORK == RGB_LED_LIGHTING_SHIELD_FRMWK_ARDUINO

#include <Arduino.h>
#include <rgb-led-lighting-shield-ino.hpp>

RGBShieldIno RGB_Shield = RGBShieldIno();

void setup()
{
    Serial.begin(9600);
    delay(1000);
    Serial.println("Serial initialized");
    delay(1000);
    RGB_Shield.begin();
    RGB_Shield.setDimmingLevel(0xFFF);

    Serial.println("*********************************************************************************************");
    Serial.println("This example shows the usage of the setIntensityX-Functions. These functions can be used to");
    Serial.println("change the color of a specific channel(red, green or blue) without influencing the others.");
    Serial.println("*********************************************************************************************\n\n");
}

void loop()
{
    RGB_Shield.setIntensityRed(0xFFF);
    Serial.println("Red\n");
    delay(5000);
    RGB_Shield.setIntensityRed(0x000);
    RGB_Shield.setIntensityGreen(0xFFF);
    Serial.println("Green\n");
    delay(5000);
    RGB_Shield.setIntensityGreen(0x000);
    RGB_Shield.setIntensityBlue(0xFFF);
    Serial.println("Blue\n");
    delay(5000);
    RGB_Shield.setIntensityBlue(0x000);
    Serial.println("Black\n");
    Serial.println("To start the example again press ENTER\n\n");
    while(Serial.read() != '\r'){}
}

#endif /** RGB_LED_LIGHTING_SHIELD_FRAMEWORK == RGB_LED_LIGHTING_SHIELD_FRMWK_ARDUINO **/