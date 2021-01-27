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

    Serial.println("*********************************************************************************************");
    Serial.println("This example shows how the fade-rate is influencing the shield. The fade-rate defines the");
    Serial.println("time the shield needs to reach the desired brightness. In this case we set a fade-rate of");
    Serial.println("about 5s. This corresponds to a fade-rate of 0x48(72 dec). The exact formula to calculate the");
    Serial.println("time needed for the change can be found in the datasheet on page 31.");
    Serial.println("*********************************************************************************************\n\n");
}
    
void loop()
{
    RGB_Shield.setFadeRate(0x48);
    Serial.println("Set the fade-rate to about 5s\n");
    delay(3000);
    RGB_Shield.setColor(RED);
    RGB_Shield.setDimmingLevel(0xFFF);
    Serial.println("Set the color to red and the brightness to 100 percent\n");
    delay(5500);
    Serial.print("Reached the 100 percent! ");
    delay(2000);
    Serial.println("-> Set the brightness to 0 percent\n");
    RGB_Shield.setDimmingLevel(0x000);
    delay(5500);
    Serial.println("Reached the 0 percent!\n");
    RGB_Shield.setFadeRate(0x000);
    RGB_Shield.setColor(BLACK);
    Serial.println("To start the example again press ENTER\n\n");
    while(Serial.read() != '\r'){}
}

#endif /** RGB_LED_LIGHTING_SHIELD_FRAMEWORK == RGB_LED_LIGHTING_SHIELD_FRMWK_ARDUINO **/