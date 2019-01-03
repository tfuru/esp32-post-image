#ifndef SD_CARD_FILE_H
#define SD_CARD_FILE_H

#include "config.h"
#include <Arduino.h>

#include <SD.h>
#include <SPI.h>

class SDCardFile {
    public:
        SDCardFile(int pin);
        void init(void);

        bool remove(const char* path);
        bool read(const char* path,char* value,unsigned long size);
        bool write(const char* path,const char* value,unsigned long size);
    private:
        int ssPin;
};

#endif
