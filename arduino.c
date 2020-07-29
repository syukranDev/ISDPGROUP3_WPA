//git clone from Github.com/Syukran.Dev  <repo isdp>
//===================================================
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


const char* ssid     = "iPhone";
const char* password = "syukranbaik";

const char* serverName = "http://gggguj.000webhostapp.com/example_sendData.php";

int i = 0;
int j = 0;
int k = 0;
int l = 0;
int m = 0;

//=================================    PRE-RECORDED VALUE  =============================================================================
String value1[]    = {"35.4","34.6","37.2","36.3","36.7","36.8","35.9","38.9","39.2","37.3","34.5"}; //=========>>Value1:  Temperature (C)
String value3[]    = {"466","483","350","350","477","497","585","595","697","477","477"};            //=========>>Value3:  ECG (mV) rate
String value4[]    = {"82","94","76","88","88","93","77","83","79","92","86"};                       //=========>>Value4:  Heart Rate (BPM) rate
String value11[11] = { "4.384753","4.383886","4.383234","4.382838","4.382174",
                      "4.383010", "4.382241","4.381285","4.380469", "4.380968","4.381945"};         //=========>>Value11: Indoor positioning (X-value)
String value12[11] = {"100.963805","100.963419","100.963987","100.96374","100.965382","100.966747",
                      "100.967351","100.967424","100.968107","100.968712","100.969441"};             //=========>>Value12: Indoor Positioning (Y-value)

String value2="0",value5="0",value6="0",value7="0",value8="0",value9="0",value10="0",value13="0",value14="0",value15="0",value16="0"; //unused for now.                  
//========================================================================================================================================
void setup() {
  Serial.begin(115200);
  
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
  delay(6000); //delay 6 sec
}

void loop() {
  //int test1=digitalRead(4); //D2
  // Serial.println(sensorValue);
  
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String value1_rev = value1[i];
    String value3_rev = value3[j];
    String value4_rev = value4[m];
    String value11_rev = value11[k];
    String value12_rev = value12[l];
    
    String httpRequestData = "&value1=" + value1_rev + 
                            "&value2=" + value2 + 
                            "&value3=" + value3_rev + 
                            "&value4=" + value4_rev +
                            "&value5=" + value5 +
                            "&value6=" + value6 +
                            "&value7=" + value7 +
                            "&value8=" + value8 +
                            "&value9=" + value9 +
                            "&value10=" + value10 +
                            "&value11=" + value11_rev +
                            "&value12=" + value12_rev +
                            "&value13=" + value13 +
                            "&value14=" + value14 +
                            "&value15=" + value15 +
                            "&value16=" + value16 + "";
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
  i++;
  j++;
  k++;
  l++;
  m++;
  if(i > 10){
    i = 0; 
  }
  if(j > 10){
    j = 0; 
  }
  if(k > 10){
    k = 0; 
  }
  if(l > 10){
    l = 0; 
  }
  if(m > 10){
    m = 0; 
  }
  delay(1000);  // delay 1 sec for every new data comes in
}