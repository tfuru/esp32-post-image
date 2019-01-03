#include <Arduino.h>
#include "ImagePost.h"
#include "SDCardFile.h"

SDCardFile sd(SPI_CS_SD);
ImagePost imagePost;

//POST レスポンス
void imagePostCallback(const char *response){
    Serial.println(F("callback "));
    Serial.println(response);
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("start"));

  //SPI 初期化
  SPI.begin(SPI_SCL, SPI_MISO, SPI_MOSI);
  SPI.setFrequency(SPI_FREQUENCY);

  //SD初期化
  sd.init();
  
  //Wi-Fi 設定
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void loop() {
  //WiFi が接続されるまで待つ
  if(WiFi.status() != WL_CONNECTED){
    Serial.print(F("."));
    delay(100);
    return;
  }
  Serial.println(F(""));
  delay(5000);

  //SD内の画像 0.jpg をPOST
  void (*callback)(const char *result) = imagePostCallback;
  File file = SD.open("/0.jpg", FILE_READ);
  imagePost.postImage(&file, callback);
  file.close();
}