#include "ImagePost.h"

ImagePost::ImagePost(void){

}

bool ImagePost::postImage(File *file, FUNC_POST_IMAGE_CALLBACK callback){
#ifdef IMAGE_POST_DEBUG  
    Serial.println(F("postImage"));
#endif
    String response = "";    
    if(file == nullptr){
        Serial.println(F("Failed to open file for writing"));
        return false;
    }
    int fileSize = file->size();

    char contentType[100];
    char boundary[32] = "--";

    //boundary 作成
    randomSeed(micros() + analogRead(A0));
    for (int i = 0; i < 3; i++) {
      ltoa(random(0x7FFFFFF), boundary + strlen(boundary), 16);
    }
    strcpy(contentType, "multipart/form-data; boundary=");
    strcat(contentType, boundary);

    String payloadHeaderFormat = ""
                     "--%s\r\n"
                     "Content-Disposition: form-data; name=\"image\"; filename=\"%s\"\r\n"
                     "Content-Type: application/octet-stream\r\n"
                     "Content-Transfer-Encoding: binary\r\n"
                     "\r\n"
                     ;
    char payloadHeader[200] = {0};
    sprintf(payloadHeader,
                payloadHeaderFormat.c_str(),
                boundary,
                file->name());

    char payloadFooter[50] = {0};
    sprintf(payloadFooter, "\r\n--%s--\r\n", boundary);
    
#ifdef IMAGE_POST_DEBUG
    Serial.println("--- request --- ");
#endif

    String bodyHeader = String(payloadHeader);
    String bodyFooter = String(payloadFooter);
    int contentLength = bodyHeader.length() + fileSize + bodyFooter.length();

#ifdef IMAGE_POST_DEBUG
    Serial.print(F("contentLength "));    Serial.println(contentLength);
    Serial.print(F("bodyHeaderLength ")); Serial.println(bodyHeader.length());
    Serial.print(F("bodyFooterLength ")); Serial.println(bodyFooter.length());
    Serial.print(F("fileSize "));         Serial.println(fileSize);
#endif

    if (client.connect(API_HOST,API_PORT)){
        client.printf("POST %s HTTP/1.1\n",API_PLANTER_IMAGE);
        client.print(F("Host: "));client.println(API_HOST);
        client.println(F("Accept: application/json"));
        client.println(F("Connection: close"));
        client.print(F("Content-Type: "));client.println(contentType);
        client.print(F("Content-Length: "));client.println(contentLength);        
        client.println();
        client.print(bodyHeader.c_str());
        client.flush();
        
        //error 12  Not enough space
        //error 104 Connection reset by peer
        //error 113 Software caused connection abort
#ifdef IMAGE_POST_DEBUG        
        Serial.println(F("write --"));
#endif        
        size_t w = 0;
        while (file->available()) {
            w += client.write(file->read());            
            if((w % API_POST_IMAGE_FLASH_SIZE) == 0){
                client.flush();
            }
        }
        client.flush();
#ifdef IMAGE_POST_DEBUG        
        Serial.printf("write %d --\n", w);
#endif
        client.print(bodyFooter.c_str());
        client.flush();

        //レスポンス タイムアウト
        int timeout = millis() + (API_POST_IMAGE_RESPONSE_TIMEOUT_SEC * 1000);
        bool isTimeout = false;
        while (client.available() == 0) {
            if (timeout - millis() < 0) {
                Serial.println(">>> Client Timeout !");
                isTimeout = true;
                break;
            }
        }
        if(isTimeout == false){
#ifdef IMAGE_POST_DEBUG            
            Serial.println(F("--- response "));
#endif            
            String line = "";
            while(client.available()){
                line = client.readStringUntil('\r');
#ifdef IMAGE_POST_DEBUG                
                Serial.print(line);
#endif
                response += line;
            }
#ifdef IMAGE_POST_DEBUG            
            Serial.println(F(""));
            Serial.println(F("response --- "));
#endif
        }
        client.stop();        
    }
    //コールバック
    callback(response.c_str());
    return true;
}