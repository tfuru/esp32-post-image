#include "SDCardFile.h"

SDCardFile::SDCardFile(int pin):ssPin(pin){

}

void SDCardFile::init(void){
    pinMode(ssPin, OUTPUT);

    if (!SD.begin(ssPin))
    {
        Serial.println(F("SD Card Mount Failed"));
        while(1);
    }

    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE)
    {
        Serial.println(F("No SD card attached"));
        while(1);
    }
    Serial.print(F("SD Card Type: "));
    if (cardType == CARD_MMC)
    {
        Serial.println(F("MMC"));
    }
    else if (cardType == CARD_SD)
    {
        Serial.println(F("SDSC"));
    }
    else if (cardType == CARD_SDHC)
    {
        Serial.println(F("SDHC"));
    }
    else
    {
        Serial.println(F("UNKNOWN"));
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

//ファイル削除
bool SDCardFile::remove(const char* path){
    return SD.remove(path);
}

//ファイル読み込み
bool SDCardFile::read(const char* path, char* value,unsigned long size){
    File file = SD.open(path, FILE_READ);
    if (!file){
        Serial.println(F("Failed to open file"));
        return false;
    }
    unsigned long i = 0;
    while (file.available()) {
        value[i] = file.read();
        ++i;
    }
    file.close();
    return true;
}

bool SDCardFile::write(const char* path,const char* value,unsigned long size){
    File file = SD.open(path, FILE_WRITE);
    if (!file){
        Serial.println(F("Failed to open file"));
        return false;
    }
    file.print(value);
    file.close();
    return true;
}
