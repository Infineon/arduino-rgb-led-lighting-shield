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
    Serial.println("This example shows the usage of the setColor-Function. This function can be used to");
    Serial.println("change the color of the LED-Stripe to predefined colors. The set of colors can be found");
    Serial.println("in the rgb-led-lighting-shield-reg.hpp file.");
    Serial.println("*********************************************************************************************\n\n");
}
    
void loop()
{
    RGB_Shield.setColor(RED);
    Serial.println("Red\n");
    delay(5000);
    RGB_Shield.setColor(GREEN);
    Serial.println("Green\n");
    delay(5000);
    RGB_Shield.setColor(BLUE);
    Serial.println("Blue\n");
    delay(5000);
    RGB_Shield.setColor(FUCHSIA);
    Serial.println("Fuchsia\n");
    delay(5000);
    RGB_Shield.setColor(TEAL);
    Serial.println("Teal\n");
    delay(5000);
    RGB_Shield.setColor(BLACK);
    Serial.println("Black\n");
    Serial.println("To start the example again press ENTER\n\n");
    while(Serial.read() != '\r'){}
}

#endif /** RGB_LED_LIGHTING_SHIELD_FRAMEWORK == RGB_LED_LIGHTING_SHIELD_FRMWK_ARDUINO **/