#include <Arduino.h>

#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>


#define PIN_ANALOG_IN  4 //GPIO4作为模拟量（电压）的输入

#define TFT_GREY 0x5AEB // New colour
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

void setup(void) {
  Serial.begin(115200);

  tft.init();
  tft.setRotation(1);
  // Fill screen with grey so we can see the effect of printing with and without 
  // a background colour defined
  tft.fillScreen(TFT_GREY);
}

void loop() {
  
  int adcVal = analogRead(PIN_ANALOG_IN);//读取该GPIO的模拟量，返回ADC转换后的值(0-4095 for 12 bits).
  int dacVal = map(adcVal, 0, 4095, 0, 255);//将ADC读取的12-bit数字量重新映射成8-bit（因为DAC的数字量为8-bit）
  double voltage = adcVal / 4095.0 * 3.3;
  dacWrite(DAC1, dacVal);//将dacVal通过DAC引脚输出成对应电压（DAC1为GPIO25）
  Serial.printf("ADC Val: %d, \t DAC Val: %d, \t Voltage: %.2fV\n", adcVal, dacVal, voltage);
  
  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with 'tft.println'
  //  or stay on the line if there is room for the text with tft.print)
  tft.setCursor(0, 0, 2);

  // Set the font colour to be green with black background, set to font 2, set text size multiplier to 1
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.println("Hello");

  tft.setTextColor(TFT_RED,TFT_BLACK);
  tft.setTextFont(2);
  tft.print("Voltage = "); tft.print(voltage); tft.println("V");           // Print valtage
  
  delay(100);


}
