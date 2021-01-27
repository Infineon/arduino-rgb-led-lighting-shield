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
    Serial.println("This example shows the usage of the setIntensityRGB-Function. This function can be used to");
    Serial.println("change the color of all three channels(red, green, blue) at the same time.");
    Serial.println("*********************************************************************************************\n\n");
}
    
void loop()
{
    RGB_Shield.setIntensityRGB(0xFFF, 0x000, 0x000);
    Serial.println("Red\n");
    delay(5000);
    RGB_Shield.setIntensityRGB(0x000, 0xFFF, 0x000);
    Serial.println("Green\n");
    delay(5000);
    RGB_Shield.setIntensityRGB(0x000, 0x000, 0xFFF);
    Serial.println("Blue\n");
    delay(5000);
    RGB_Shield.setIntensityRGB(0xFFF, 0x400, 0x000);
    Serial.println("Yellow\n");
    delay(5000);
    RGB_Shield.setIntensityRGB(0x800, 0x000, 0x800);
    Serial.println("Purple\n");
    delay(5000);
    RGB_Shield.setIntensityRGB(0x000, 0x000, 0x000);
    Serial.println("Black\n");
    Serial.println("To start the example again press ENTER\n\n");
    while(Serial.read() != '\r'){}
}

#endif /** LED_DALI_KIT_FRAMEWORK == LED_DALI_KIT_FRMWK_ARDUINO **/