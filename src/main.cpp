#include <Arduino.h>

#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>


#define TPS_IN  4
#define BPS_IN  32
#define TPS_THRESHOLD 36
#define BPS_THRESHOLD 39
#define TPS_LOSS_REFERENCE 34
#define BPS_LOSS_REFERENCE 35

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
  
  int tps_in_adc = analogRead(TPS_IN);
  int bps_in_adc = analogRead(BPS_IN);
  int tps_threshold_adc = analogRead(TPS_THRESHOLD);
  int bps_threshold_adc = analogRead(BPS_THRESHOLD);
  int tps_loss_refference_adc = analogRead(TPS_LOSS_REFERENCE);
  int bps_loss_refference_adc = analogRead(BPS_LOSS_REFERENCE);
  double tps_in_volt = tps_in_adc / 4095.0 * 3.3;
  double bps_in_volt = bps_in_adc / 4095.0 * 3.3;
  double tps_threshold_volt = tps_threshold_adc / 4095.0 * 3.3;
  double bps_threshold_volt = bps_threshold_adc / 4095.0 * 3.3;
  double tps_loss_refference_volt = tps_loss_refference_adc / 4095.0 * 3.3;
  double bps_loss_refference_volt = bps_loss_refference_adc / 4095.0 * 3.3;

  // ---serial monitor---
  Serial.printf("tps_in_volt: %.2fV, \t bps_in_volt: %.2fV, \t tps_threshold_volt: %.2fV, \t bps_threshold_volt: %.2fV, \t tps_loss_refference_volt: %.2fV, \t bps_loss_refference_volt: %.2fV\r",
    tps_in_volt,
    bps_in_volt,
    tps_threshold_volt,
    bps_threshold_volt,
    tps_loss_refference_volt,
    bps_loss_refference_volt);
  
  // ---screen---
  // Set "cursor" at top left corner of display (0,0) and select font 2
  // (cursor will move to next line automatically during printing with 'tft.println'
  //  or stay on the line if there is room for the text with tft.print)
  tft.setCursor(0, 0, 2);

  // Set the font colour to be green with black background, set to font 2, set text size multiplier to 1
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.println("BSPD Setting Mode");

  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setTextFont(2);
  tft.print("tps_in = "); tft.print(tps_in_volt); tft.println("V");
  tft.setTextColor(TFT_RED,TFT_BLACK);
  tft.setTextFont(2);
  tft.print("bps_in = "); tft.print(bps_in_volt); tft.println("V");
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setTextFont(2);
  tft.print("tps_thresh = "); tft.print(tps_threshold_volt); tft.println("V");
  tft.print("bps_thresh = "); tft.print(bps_threshold_volt); tft.println("V");
  tft.print("tps_lossref = "); tft.print(tps_loss_refference_volt); tft.println("V");
  tft.print("bps_lossref = "); tft.print(bps_loss_refference_volt); tft.println("V");
  
  delay(100);


}
