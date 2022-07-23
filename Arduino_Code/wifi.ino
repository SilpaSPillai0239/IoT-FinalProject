#include<WiFi.h>
const char* ssid="silpa";
const char* pass="dhanajjaisilpa";
void setup(){
  serial.begin(115200);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    serial.println("connecting to wifi..");
  }
  serial.println(WiFi.localIP());
}
void loop()
{}
