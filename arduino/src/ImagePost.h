#ifndef IMAGE_POST_H
#define IMAGE_POST_H

#include "config.h"
#include <Arduino.h> 
#include <HTTPClient.h>

typedef void (* FUNC_POST_IMAGE_CALLBACK)(const char *response); 

class ImagePost{
    public:
        ImagePost(void);
        bool postImage(const char* path,FUNC_POST_IMAGE_CALLBACK callback);
    private:
        WiFiClient client;
};
#endif