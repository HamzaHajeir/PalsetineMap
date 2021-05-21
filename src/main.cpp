#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "PalestineMap.h"
#define MAP_HEIGHT 48
#define MAP_WIDTH 16

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void drawMap(void);
void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h);

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS, true, false))
    {
        Serial.println("SSD1306 allocation failed");
        for (;;)
            ; // Don't proceed, loop forever
    }
    Serial.printf("Begin-ed\n");

    // Clear the buffer
    display.clearDisplay();

    drawMap(); // Draw a small bitmap image

    // Invert and restore display, pausing in-between
    //   display.invertDisplay(true);
    //   delay(1000);
    //   display.invertDisplay(false);
    //   delay(1000);

    //   testanimate(PalestineMap, MAP_WIDTH, MAP_HEIGHT); // Animate bitmaps
}

void loop()
{
}

void drawMap(void)
{
    display.clearDisplay();
    uint32_t middleHorizontalThird = (display.width() - MAP_WIDTH) / 3;
    uint32_t middleVerticalHalf = (display.height() - MAP_HEIGHT) / 2;
    display.drawBitmap(
        middleHorizontalThird - (MAP_WIDTH / 2),
        middleVerticalHalf,
        PalestineMap, MAP_WIDTH, MAP_HEIGHT, 1);
    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(middleHorizontalThird * 2, display.height() / 2 - 16);
    display.println("Free");
    display.setCursor(middleHorizontalThird * 2, display.height() / 2 );
    display.println("Palestine");

    display.display();
}
