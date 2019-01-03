# esp32-post-image
ESP32 で SDカード内のファイルをPOSTするサンプルコード

# 構成
[Adafruit ESP32 Feather](https://www.adafruit.com/product/3405)  
[マイクロＳＤカードスロットＤＩＰ化キット](http://akizukidenshi.com/catalog/g/gK-05488/)  

# SPI接続
Adafruit ESP32 Feather と マイクロＳＤカードスロットＤＩＰ化キット を SPI接続する  

|--|ESP32|SDカード|  
|:--:|:--:|:-:|  
|SPI_SCL|5|2|  
|SPI_MISO|19|7|  
|SPI_MOSI|18|3|  
|SPI_CS_SD|16|5|
|3V3|--|4|
|GND|--|6|

# 開発環境
[PlatformIO IDE for VSCode](https://docs.platformio.org/en/latest/ide/vscode.html#installation)   
環境でビルドとESP32へ書き込みができるのでリンクを参考にインストールする。


