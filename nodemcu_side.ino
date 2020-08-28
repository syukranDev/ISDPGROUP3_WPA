#ifdef ESP32
 #include <WiFi.h>
 #include <HTTPClient.h>
#else
 #include <ESP8266WiFi.h>
 #include <ESP8266HTTPClient.h>
 #include <WiFiClient.h>
#endif


const char* ssid     = "iPhone";
const char* password = "syukranbaik";

const char* serverName = "http://gggguj.000webhostapp.com/example_sendData.php";



void setup() {
// For data transfer from MEGA to NodeMCU:
  Serial.begin(115200);
  while (!Serial) { ; }

// WiFi Setup
 WiFi.begin(ssid, password);
 Serial.println("Connecting");
 while(WiFi.status() != WL_CONNECTED) { 
   delay(500);
   Serial.print("Searching for Wifi...");
   Serial.println(" ");
 }
 Serial.println("");
 Serial.print("Connected to WiFi network with IP Address: ");
 Serial.println(WiFi.localIP());
 delay(6000); //delay 6s after succesfully connected to Wi-FI. --MUST ON THIS

}




void loop() { 
  
  //=== FOR TESTTING GOES HERE
  //         if (Serial.available()) {
  // //          Serial.write(Serial.read()); 
  //           String fetchData = Serial.readString();
  //           Serial.print("httpRequestData: ");
  //           Serial.print(fetchData);
  //        }
  // }
  //=== TESTING END HERE



  //=== Real codes goes here
 if(WiFi.status()== WL_CONNECTED){

   if (Serial.available()) {
   String httpRequestData = Serial.readString(); //fetch data from MEGA
   //data sent to nodemcu will be parse as a long string 
   // example= &value2=23&value3=3&value4=23&value5=23..... and list goes on
  

   HTTPClient http;
   http.begin(serverName);
   http.addHeader("Content-Type", "application/x-www-form-urlencoded");

   
   
   Serial.print("httpRequestData: " + httpRequestData);  //Show at serial monitor
   int httpResponseCode = http.POST(httpRequestData);
    
       
   if (httpResponseCode>0) {
     Serial.print("HTTP Response code: ");
     Serial.println(httpResponseCode); //if HTML 200 then OK
   }
   else {
     Serial.print("Error code: ");
     Serial.println(httpResponseCode); //if HTML -1 then wifi disconnected (usually)
   }
   // Free resources
   http.end();  
   }     
 }
 else {
   Serial.println("WiFi Disconnected");
 }
 delay(1000);  // delay 1 sec for every new data comes in
}
