#ifndef CONFIG_H
#define CONFIG_H

//#define IMAGE_POST_DEBUG 

#define WIFI_SSID "W03_F0434732EAC2"
#define WIFI_PASSWORD "rqnfqy85e32deqn"

#define API_HOST "192.168.100.140"
#define API_PORT 8080
#define API_PLANTER_IMAGE "/api/image"
#define API_POST_IMAGE_FLASH_SIZE 512
#define API_POST_IMAGE_RESPONSE_TIMEOUT_SEC 30

//SPI 4MHz
#define SPI_FREQUENCY 4000000
#define SPI_SCL  5
#define SPI_MISO 19
#define SPI_MOSI 18
#define SPI_CS_SD  16

#endif