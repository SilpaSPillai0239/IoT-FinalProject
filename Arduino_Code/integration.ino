#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <string.h>
#include "DHT.h"
#include <SPI.h>
#include <Wire.h>
#include <DHT.h>

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085.h>//DHT library from Adafruit
#define DHT11PIN 4 //Adafruit Unified Sensor library.
#define DHTTYPE    DHT11 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//#define OLED_RESET -1
#define NUMFLAKES 10
#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16
const char* ssid     = "Silpa";
const char* password = "dhanajjaisilpa";
char simple_json1[200];
char json[200];
#define BOTtoken "5486061774:AAHSipsJOKggNKu9FGnj4asCyaCJmQ7c7tQ"  // your Bot Token (Get from Botfather)


#define CHAT_ID "872187501"
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.43.193:8000/readings";
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;
const int ledPin = 2;
bool ledState = LOW;
DHT dht(DHT11PIN, DHT11);
// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Send data every  30 seconds (5000)
unsigned long timerDelay = 5000;

AsyncWebServer server(80);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//Adafruit_SSD1306 display(-1);

Adafruit_BMP085 bmp;
const int moisture_sensor_pin = 34;
int moisture_sensor_value = 0;

void handleNewMessages(float humi,float temp,float pressure,float p_temp,int moisture_sensor_value) {
      String welcome="";
    if (moisture_sensor_value<=1500) {
      welcome +="EMERGENCY RAIN ATTENTION.\n";
   
      welcome+="-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n\n";
      welcome += "EXPECTED RAIN SOON\n";
     
      welcome += "Moisture value:"+String(moisture_sensor_value)+"\n\n";
     
      bot.sendMessage(CHAT_ID, welcome, "");
    }

//    if (text == "/led_on") {
//      bot.sendMessage(chat_id, "LED state set to ON", "");
//      ledState = HIGH;
//      digitalWrite(ledPin, ledState);
//    }
//    
//    if (text == "/led_off") {
//      bot.sendMessage(chat_id, "LED state set to OFF", "");
//      ledState = LOW;
//      digitalWrite(ledPin, ledState);
//    }
//    
//    if (text == "/state") {
//      if (digitalRead(ledPin)){
//        bot.sendMessage(chat_id, "LED is ON", "");
//      }
//      else{
//        bot.sendMessage(chat_id, "LED is OFF", "");
//      }
    }

void server_Connection(const char* serverName,float humi,float temp,float pressure,float p_temp,int moisture_sensor_value) {
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
      WiFiClient client;
      HTTPClient http;

      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
   
      // If you need an HTTP request with a content type: application/json, use the following:

      http.addHeader("Content-Type", "application/json");
     
   
   
      
      sprintf(simple_json1, "{\"device_id\":\"%d\",\"temp_reading\":\"%.2f\",\"hum_reading\":\"%.2f\",\"pressure_reading\":\"%.2f\",\"temp1_reading\":\"%.2f\",\"moisture_value\":\"%d\"}", 1,serverName,temp,humi,pressure,p_temp,moisture_sensor_value);
      int httpResponseCode1 = http.POST(simple_json1);
      delay(1000);
      
    
      Serial.print("temperature:");
      Serial.println(temp);
      Serial.print("Humidity:");
      Serial.println(humi);
      Serial.print("Pressure:");
      Serial.println(pressure);
      Serial.print("Temperature:");
      Serial.println(p_temp);
      Serial.print("Moisture_value:");
      Serial.println(moisture_sensor_value);
     
      Serial.print("HTTP Response code1: ");
      Serial.println(httpResponseCode1);
     

      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }

}

void setup()
{
Serial.begin(115200);

  dht.begin();
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
  

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  Serial.print("start");
  display.setTextColor(WHITE);
  Serial.println("ing.....");

 /* Start the DHT11 Sensor */

  if (!bmp.begin())
  {
    Serial.println("BMP180 Sensor not found ! ! !");
    while (1)
    {

    }
  }
}

void loop(){

//delay(5000);

  //read temperature and humidity
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("ºC ");
  Serial.print("Humidity: ");
  Serial.println(h);
  Serial.print("Pressure = ");
  float pressure=bmp.readPressure();
  Serial.print(pressure);

  Serial.print(" hPa");
  Serial.print("  Temp = ");
   float pressure_temp=bmp.readTemperature();
  Serial.print(pressure_temp);
  Serial.print("ºC");
  moisture_sensor_value = analogRead(moisture_sensor_pin);
  Serial.print("Moisture value:");
  Serial.println(moisture_sensor_value);
  
  // clear display
  display.clearDisplay();
  
  // display temperature
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temperature: ");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(t);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("C");
  display.display();
  
  // display humidity
  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Humidity: ");
  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(h);
  display.print(" %"); 
  display.display();

  delay(2000);
  
  display.clearDisplay();
  
  //display bmp180 and moisture_sensor
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Temp=");
  display.print(bmp.readTemperature());
  display.setCursor(0,10);
  display.println("*C");
  //display.setTextSize(1);
  //display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.print("Pressure=");
  display.print(bmp.readPressure());
  display.setCursor(0,25);
  display.println("Pa");
  
  display.setCursor(0,30);
  display.print("Moisture value=");
  display.print(moisture_sensor_value);
  display.display();
  delay(3000);
//   if (millis() > lastTimeBotRan + botRequestDelay)  {
//    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
//
//    while(numNewMessages) {
//      Serial.println("got response");
//      handleNewMessages(numNewMessages);
//      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
//    }
//    lastTimeBotRan = millis();
//  }
  handleNewMessages(h,t,pressure,pressure_temp,moisture_sensor_value);
  server_Connection(serverName,h,t,pressure,pressure_temp,moisture_sensor_value);
}
