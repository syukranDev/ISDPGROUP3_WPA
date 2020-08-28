///////////////////////////////////////////||
//     Data transfer from Mega to NodeMCU
///////////////////////////////////////////||

#include <SoftwareSerial.h>
SoftwareSerial espSerial(25, 23); // TX RX
String str;
String value1; //temperature
String value3; //ecg (mV)
String value4; //BPM
String value11; //x value indoor
String value12; //y value indoor
String value16; //action 
String value10; //angle indoor
float xValue, yvalue;

//below for power
String value5; //power
String value6; //timeleft
String value7; //percentage
String value8; //voltage
String value9; //amp

///////////////////////////////////////////////////////////////Temperature_declaration
#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 3 //== (D3)
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
float temp_data;

///////////////////////////////////////////////////////////////ECG_declaration-- 9600br
int x = 0;
int LastTime = 0;
bool BPMTiming = false;
bool BeatComplete = false;
int BPM = 0;    
#define UpperThreshold 518
#define LowerThreshold 490   
int Signal; 

////////////////////////////////////////////////////////////////HAR + IndoorPos
//function for this is at different file "elvern_function.c"
#include <Wire.h> 
#include <MPU.h> 

MPU mpu6050(Wire);    // <-- use for AD0 high

#define PI 3.14159265358
#define OFF_SET 6 // reset angle and coordinates to zero (D6)
#define START 8 // press to not update x & y (D8)
#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards (D2)
#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)

float roll, pitch, yaw;   // variables for angle of rotation
long t = 0;               // timer
int i, s, v, l, f, l_c;

float OFFSET[3] = {0,0,0};  // store offset
float ANGLE[3] = {0,0,0};
float E_ANGLE[3] = {0,0,0};
float P_ANGLE[3] = {0,0,0};
float mag; //accel mag
int x1; // used for OFFSET pin state storage
int x2;
int W;
//int OFF_SET = 7;

float sample_x[20] = {0};
float sample_y[20] = {0};
float sample_z[20] = {0};
float sample[20] = {0};

float sum_x;
float sum_y;
float sum_z;
float sum;

float avg_x;
float avg_y;
float avg_z;
float avg;

float POSITION[2] = {0,0};

float aaReal_x, aaReal_y, aaReal_z;

int DIV;
int REM;
int N_ANGLE;

int count = 0;

unsigned long time_taken = 0;
unsigned long start_time;

int flag = 0;
float freq = 0;

////////////////////////////////////////////////////////////////Power Declaration
#include <Adafruit_INA219.h> ;
Adafruit_INA219 ina219;
#include <Wire.h> //sebabHAR dah pakai
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR    0x27 //Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
#define led_pin 13
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

float Batt_left;
float time_left;
float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
float power = 0;
float power_mW = 0.0;
float energy_mwh= 13700;
float voltage_type = 7.4 ;
float MPU6050_power = 5 * 1.74;
float Wifi_power = 5 * 250 ;
float DHT_power = 5 * 0.3 ;
float ECG_power = 5 * 0.27 ;



////////////////////////////////////////////////////////////////////////////////////////////////

void setup(){
    Serial.begin(115200);
    espSerial.begin(115200);

    ////////////////////////////////////Temperature Setup
    sensors.begin(); 

    ///////////////////////////////////Indoor Positioning + HAR Setup
    Wire.begin();
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true); 
    pinMode(OFF_SET, INPUT);
    pinMode(START, INPUT);

    ///////////////////////////////////ECG Setup
     
    
    ///////////////////////////////////BPM Setup
    pinMode(10, INPUT); 
    pinMode(11, INPUT); 

    ///////////////////////////////////POWER Setup
     uint32_t currentFrequency;
     ina219.setCalibration_16V_400mA();
     ina219.begin();
     pinMode(2,OUTPUT);

}

void loop() {
//
//
//
//
//   
//////////////////////Indoor Positioning + HAR////////////////////////////////////////////////////////
  mpu6050.update();
  if(millis() - t > 90) {// reduce the 90 to improve detection of angle
    //mpu6050.update();
    acc_data();
    gyro_data();
    angle();
    angle_reset();
    //walking_detection();
    //display_angle();  // uncomment to display angle of rotation
    classify();
    //Serial.println();
    //delay(100);
    t = millis();
  }
  walking_detection();
/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
///////////////////////////  ECG ////////////////////////////////////////////////////////////////////
//    ecg_data = analogRead(A4); //ecg use below 
//    value3 = ecg_data; 
//    Serial.println(analogRead(A0);
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
///////////////////////////  BPM  & ECG ////////////////////////////////////////////////////////////////////
      int valueECG = analogRead(4);  //ECG use this
      
  
      if (valueECG > UpperThreshold) {
        if (BeatComplete) {
          BPM = millis() - LastTime;
          BPM = int(60 / (float(BPM) / 1000));
          BPMTiming = false;
          BeatComplete = false;
        }
        if (BPMTiming == false) {
          LastTime = millis();
          BPMTiming = true; 
        }
      }
      
      if ((valueECG < LowerThreshold) & (BPMTiming)){
        BeatComplete = true;
        // display bpm
        value4 = BPM;
        value3 = valueECG; //ECG goes here
      }
      
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//////////////////////Temperature///////////////////////////////////////////////////////////////////
     sensors.requestTemperatures();
     temp_data =  sensors.getTempCByIndex(0);
     value1 = temp_data;
////////////////////////////////////////////////////////////////////////////////////////////////////
   
///////////////////////////Power////////////////////////////////////////////////////////////////////
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  power = current_mA * loadvoltage;
  power_mW = ina219.getPower_mW();
  Batt_left = 40.0 * busvoltage - 404.0;   
  time_left = 24.42 * 1000 / power_mW;

  value5 = power; //power consumption
  value6 = time_left; //float time
  value7= Batt_left; //percentage
  value8 = busvoltage; //volt
  value9 = current_mA; //ampere

////////////////////////////////////////////////////////////////////////////////////////////////////

   String value2, value13, value14, value15 = "0"; //not use db column make it = 0

    String httpRequestData = "&value1=" + value1 +         //Temperature
                           "&value2=" + value2 +   //not used = 0       
                            "&value3=" + value3 +  //ecg
                            "&value4=" + value4 +  //BPM
                            "&value5=" + value5 +  //Power
                            "&value6=" + value6 +  //timeLeft
                            "&value7=" + value7 +  //percentage
                            "&value8=" + value8 +  //voltage
                            "&value9=" + value9 +  //current
                            "&value10=" + value10 + //angle
                            "&value11=" + value11 + //x-coordinate
                            "&value12=" + value12 + //y-coodinate
                            "&value13=" + value13 + //not used = 0   
                            "&value14=" + value14 + //not used = 0   
                            "&value15=" + value15 + //not used = 0   
                            "&value16=" + value16 + //action
                              "";

    Serial.println("POST Request: " + httpRequestData);
    espSerial.println(httpRequestData);                       


   
//    delay(1000);  // delay 1 sec for every new data comes in FOR ALL SUBSYSTEM  -- better set at NODEMCU                 
}
