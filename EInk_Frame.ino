#include <epd.h>
#define Threshold 40
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "SSID";          //Enter your WiFi SSID
const char* password = "PASSWORD";  //Enter your WiFi Password
unsigned long previousMillis = 0;
const long interval = 3600000;
int touchPad;
bool touchDetected = false;
int flag = 0;
int i = 0;

HTTPClient http;
                      
void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  //Serial.println("Booting");
//  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  delay(1000);
  
  touchAttachInterrupt(T0, gotTouch0, Threshold);
  touchAttachInterrupt(T3, gotTouch3, Threshold);
  touchAttachInterrupt(T4, gotTouch4, Threshold);
  touchAttachInterrupt(T5, gotTouch5, Threshold);
  touchAttachInterrupt(T6, gotTouch6, Threshold);
  touchAttachInterrupt(T7, gotTouch7, Threshold);
  touchAttachInterrupt(T8, gotTouch8, Threshold);

  epd_init();
  epd_wakeup();
  epd_clear();
  epd_set_memory(MEM_TF);
}

void loop(){
  unsigned long currentMillis = millis();
  if(touchDetected){ //Check continuously if any touch is detected
    epd_wakeup();
    epd_clear();
    switch(touchPad){
      case 0  : epd_disp_bitmap("PIC1.BMP", 0, 0); break;
      case 3  : epd_disp_bitmap("PIC2.BMP", 0, 0); break;
      case 4  : epd_disp_bitmap("PIC3.BMP", 0, 0); break;
      case 5  : epd_disp_bitmap("PIC4.BMP", 0, 0); break;
      case 6  : epd_disp_bitmap("PIC5.BMP", 0, 0); break;
      case 7  : epd_disp_bitmap("PIC6.BMP", 0, 0); break;
      case 8  : epd_disp_bitmap("PIC7.BMP", 0, 0); break;
      default : break;
    }
    epd_udpate();
    touchDetected = false;
  }

  //Get a random joke from JokeAPI after every 1 hour if WiFi is connected
  if (currentMillis - previousMillis >= interval && WiFi.status() == WL_CONNECTED && flag == 0){
    epd_wakeup();
    epd_clear();
    http.begin("https://official-joke-api.appspot.com/random_joke");
    http.GET();
    DynamicJsonBuffer jb;
    JsonObject& obj = jb.parseObject(http.getStream());
    if (!obj.success()){
      Serial.println("parseObject() failed");
      return;
    }
    String joke = obj["setup"];
    String punch = obj["punchline"];
    if(joke.length() > 60){
      String joke1 = joke.substring(0, 60);
      String joke2 = joke.substring(60);
      const void * joke1_c = joke1.c_str();
      const void * joke2_c = joke2.c_str();
      epd_set_color(BLACK, WHITE);
      epd_set_en_font(ASCII32);
      epd_disp_string(joke1_c, 0, 220);
      epd_disp_string(joke2_c, 0, 250);
    }
    else{
      const void * joke_c = joke.c_str();
      epd_set_color(BLACK, WHITE);
      epd_set_en_font(ASCII32);
      epd_disp_string(joke_c, 0, 250);
    }
    if(punch.length() > 60){
      String punch1 = punch.substring(0, 60);
      String punch2 = punch.substring(60);
      const void * punch1_c = punch1.c_str();
      const void * punch2_c = punch2.c_str();
      epd_set_en_font(ASCII32);
      epd_disp_string(punch1_c, 0, 300);
      epd_disp_string(punch2_c, 0, 330);
    }
    else{
      const void * punch_c = punch.c_str();
      epd_set_color(DARK_GRAY, WHITE);
      epd_set_en_font(ASCII32);
      epd_disp_string(punch_c, 0, 330);
    }
    previousMillis = currentMillis;
    epd_udpate();
    flag = 1; //set flag to get quote after next 1 hour
  }

  //Get a random quote from Quotable after every one hour if WiFi is connected
  if (currentMillis - previousMillis >= interval && WiFi.status() == WL_CONNECTED && flag == 1){
    epd_wakeup();
    epd_clear();
    http.begin("https://api.quotable.io/random?maxLength=110");
    http.GET();
    DynamicJsonBuffer jb;
    JsonObject& obj = jb.parseObject(http.getStream());
    if (!obj.success()){
      Serial.println("parseObject() failed");
      return;
    }
    String quote = obj["content"];
    
    if(quote.length() > 60){
      String quote1 = quote.substring(0, 60);
      String quote2 = quote.substring(60);
      const void * quote1_c = quote1.c_str();
      const void * quote2_c = quote2.c_str();
      epd_set_color(BLACK, WHITE);
      epd_set_en_font(ASCII32);
      epd_disp_string(quote1_c, 0, 220);
      epd_disp_string(quote2_c, 0, 250);
    }
    else{
      const void * quote_c = quote.c_str();
      epd_set_color(BLACK, WHITE);
      epd_set_en_font(ASCII32);
      epd_disp_string(quote_c, 0, 250);
    }
    previousMillis = currentMillis;
    epd_udpate();
    flag = 0; //reset flag to get joke after next 1 hour
  }
  //ArduinoOTA.handle();
}

void gotTouch0(){
 touchDetected = true;
 touchPad = 0;
 delay(500);
}

void gotTouch3(){
 touchDetected = true;
 touchPad = 3;
 delay(500);
}

void gotTouch4(){
 touchDetected = true;
 touchPad = 4;
 delay(500);
}

void gotTouch5(){
 touchDetected = true;
 touchPad = 5;
 delay(500);
}

void gotTouch6(){
 touchDetected = true;
 touchPad = 6;
 delay(500);
}

void gotTouch7(){
 touchDetected = true;
 touchPad = 7;
 delay(500);
}

void gotTouch8(){
 touchDetected = true;
 touchPad = 8;
 delay(500);
}
