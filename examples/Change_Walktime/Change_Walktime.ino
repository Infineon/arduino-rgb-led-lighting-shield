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
    Serial.println("This example shows how the walk-time is influencing the shield. A linear walk is used to");
    Serial.println("smoothly change the colour intensities. The intensities change linearly over time. The time");  
    Serial.println("taken for the channels to reach their target intensities is called the linear walk time.");
    Serial.println("The linear walk time can be adjusted. In this example the walktime is set to about 7s");
    Serial.println("This corresponds to a value of 0x2AC(684 dec) for the walk-time.");
    Serial.println("*********************************************************************************************\n\n");
}
    
void loop()
{
    RGB_Shield.setColor(RED);
    Serial.println("Red\n");
    delay(3000);
    RGB_Shield.setWalkTime(0x2AC);
    RGB_Shield.setColor(BLUE);
    Serial.println("Start walk from red to blue");
    delay(7000);
    RGB_Shield.setColor(BLACK);
    Serial.println("Start walk from blue to black\n");
    delay(7000);
    RGB_Shield.setWalkTime(0x000);
    Serial.println("To start the example again press ENTER\n\n");
    while(Serial.read() != '\r'){}
}

#endif /** RGB_LED_LIGHTING_SHIELD_FRAMEWORK == RGB_LED_LIGHTING_SHIELD_FRMWK_ARDUINO **/