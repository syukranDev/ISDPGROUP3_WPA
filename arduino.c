
#ifdef ESP32
#include <WiFi.h>
#include <HTTPClient.h>
#else
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#endif

//#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>

// Replace with your network credentials
const char* ssid     = "2ndPlanet_2G@unifi";
const char* password = "26JalanEmas18";

const char* serverName = "http://gggguj.000webhostapp.com/example_sendData.php";

String sensorName = "temperature";
String sensorLocation = "home";
String test1 = "30";
String test2 = "36";
String test3 = "38";


void setup() {
Serial.begin(115200);
  
WiFi.begin(ssid, password);
Serial.println("Connecting");
while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
}
Serial.println("");
Serial.print("Connected to WiFi network with IP Address: ");
Serial.println(WiFi.localIP());
}

void loop() {
//Check WiFi connection status
if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "&sensor=" + sensorName + "&location=" + sensorLocation + "&value1=" + test1 + "&value2=" + test2 + "&value3=" + test3 + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
   
    int httpResponseCode = http.POST(httpRequestData);
     
        
    if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    }
    else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
}
else {
    Serial.println("WiFi Disconnected");
}
//Send an HTTP POST request every 30 seconds
delay(5000);  
}