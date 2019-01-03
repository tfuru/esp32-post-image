# esp32-post-image
ESP32 で SDカード内のファイルをPOSTするサンプルコード

# 構成
[Adafruit ESP32 Feather](https://www.adafruit.com/product/3405)  
[マイクロＳＤカードスロットＤＩＰ化キット](http://akizukidenshi.com/catalog/g/gK-05488/)  

# SPI接続
Adafruit ESP32 Feather と マイクロＳＤカードスロットＤＩＰ化キット を SPI接続する  

|--|ESP32||SDカード|  
|SPI_SCL|5|2|  
|SPI_MISO|19|7|  
|SPI_MOSI|18|3|  
|SPI_CS_SD|16|5|
|3V3|--|4|
|GND|--|6|


