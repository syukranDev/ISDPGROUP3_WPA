void acc_data() {
  // This function collect the data from accelerometer
  mpu6050.getRawAccX();
  mpu6050.getRawAccY();
  mpu6050.getRawAccZ();

  // Data is converted into unit gravity (g)
  mpu6050.getAccX();
  mpu6050.getAccY();
  mpu6050.getAccZ();
}

void gyro_data() {
  // This function collect the data from gyroscope
  mpu6050.getRawGyroX();
  mpu6050.getRawGyroY();
  mpu6050.getRawGyroZ();

  // Data is converted into unit degree per second (dps)
  mpu6050.getGyroX();
  mpu6050.getGyroY();
  mpu6050.getGyroZ();
}

void angle()  {
  // This function uses data from sensors and calculate angles

  // Calculate angle in axis x and y for accelerometer
  mpu6050.getAccAngleX();
  mpu6050.getAccAngleY();

  // Calculate angle in axis x,y and z for gyroscope
  mpu6050.getGyroAngleX();
  mpu6050.getGyroAngleY();
  mpu6050.getGyroAngleZ();

  // Data fusion of accelerometer and gyroscope
  roll = mpu6050.getAngleX();
  pitch = mpu6050.getAngleY();
  yaw = mpu6050.getAngleZ();
}

void display_angle(){
    // This function display angle of rotation
    Serial.print("\t");
    Serial.print("roll  : ");
    Serial.print(roll);
    Serial.print("\t");
    Serial.print("\tpitch  : ");
    Serial.print(pitch);
    Serial.print("\t");
    Serial.print("\tyaw  : ");
    Serial.println(yaw);
}

void classify() {
  // This function uses angles calculation and comparison are made to do
  // activity classificattion

  /*_________________STANDING_______________*/
  if ( (pitch <= 30) && (pitch >= -30) && (roll <= 30) && (roll >= -30) ){
    s = 1;
    
  } else {
    s = 0;
  }

/*  //_________________WALKING________________
  if ( (roll >= 70) && (roll <= 85 ) && (pitch >= -5)  ){
    w = 1;
    Serial.println("Activity : Walking"); 
    Serial.println("Note : User is walking");
    delay(10);
  }
*/
  /*________________LYING DOWN______________*/
  if ( (roll >= 60) || (roll <= -60) || (pitch >= 60) || (pitch <= -60) ){
    l = 1;
    
  } else {
    l = 0;
  }

  if (mag > 5000){
    l_c = 5;
  }else {
    l_c = l_c - 1;
  }
//  ______________ABRUPT FALLING____________
  if ( (l == 1) && (l_c > 0) ){
    f = 1;
     
  }else {
    f = 0;
  }
   //Serial.println(s);
  if ((s == 1) && (v == 0)){
//    Serial.println("Activity : Standing Detected!"); 
//    Serial.println("Note : User is standing still"); 
    String action = "Standing";
    value16 = action;
  }
  
  if ((v == 1) && (f == 0) && (l == 0)){
//    Serial.println("Activity : Walking Detected!"); 
//    Serial.println("Note : User is walking");
    String action = "Walking";
    value16 = action; 
  }
  
  if (f == 1){
//    Serial.println("Activity : Fall Detected!");
//    Serial.println("Note : Emergency! Please check user's condition!");
    String action = "Falling Down";
    value16 = action;
    
  }
  
  if ((f != 1) && (l == 1)){
//    Serial.println("Activity : Lying down"); 
//    Serial.println("Note : User is lying down");
    String action = "Lying Down";
    value16 = action;
  }
  
}

  


  //ANGLE RESET ===========================================================================================================================================        
void angle_reset(){
        x1 = digitalRead(OFF_SET);  
        if (x1 == HIGH)
        {
          ANGLE[0] = 0;
          ANGLE[1] = 0;
          ANGLE[2] = 0;
        }
        
        
        E_ANGLE[0] = roll;
        E_ANGLE[1] = pitch;
        E_ANGLE[2] = yaw;
        

        OFFSET[0] = E_ANGLE[0] - P_ANGLE[0];
        OFFSET[1] = E_ANGLE[1] - P_ANGLE[1];
        OFFSET[2] = E_ANGLE[2] - P_ANGLE[2];

        if(OFFSET[0] < -355)
          OFFSET[0] = E_ANGLE[0] + 360 - P_ANGLE[0];
        else if(OFFSET[0] > 355)
          OFFSET[0] = 360 - E_ANGLE[0] + P_ANGLE[0];

        if(OFFSET[1] < -355)
          OFFSET[1] = E_ANGLE[1] + 360 - P_ANGLE[1];
        else if(OFFSET[1] > 355)
          OFFSET[1] = 360 - E_ANGLE[1] + P_ANGLE[1];

        if(OFFSET[2] < -355)
          OFFSET[2] = E_ANGLE[2] + 360 - P_ANGLE[2];
        else if(OFFSET[2] > 355)
          OFFSET[2] = 360 - E_ANGLE[2] + P_ANGLE[2];
          

        ANGLE[0] = ANGLE[0] + OFFSET[0];
        ANGLE[1] = ANGLE[1] + OFFSET[1];
        ANGLE[2] = ANGLE[2] + OFFSET[2];

        
        if(ANGLE[0] > 180)
          ANGLE[0] = ANGLE[0] - 360;
        else if (ANGLE[0] <= -180)
          ANGLE[0] = ANGLE[0] + 360;
       
        if(ANGLE[1] > 180)
          ANGLE[1] = ANGLE[1] - 360;
        else if (ANGLE[1] <= -180)
          ANGLE[1] = ANGLE[1] + 360;

        if(ANGLE[2] > 180)
          ANGLE[2] = ANGLE[2] - 360;
        else if (ANGLE[2] <= -180)
          ANGLE[2] = ANGLE[2] + 360;

        P_ANGLE[0] = E_ANGLE[0];
        P_ANGLE[1] = E_ANGLE[1];
        P_ANGLE[2] = E_ANGLE[2];
           
        //Serial.print(ANGLE[1]);
        //Serial.print(" ");
        //Serial.print(ANGLE[1]);
        //Serial.print(" ");
        //Serial.print(ANGLE[2]); 
        Serial.print(" ");

//==QUANTIZATION OF ANGLE====================================================================================================

  if((ANGLE[2] >= -180 && ANGLE[2] <= -178)||(ANGLE[2] <= 180 && ANGLE[2] >= 178)){
    N_ANGLE = 180;
  }else{  
    DIV = ANGLE[2]/10;
    REM = (int)ANGLE[2]%10;
    if (REM>3)
      N_ANGLE = (DIV + 1)*10;
    else
      N_ANGLE = (DIV)*10;
  }
  //Serial.println(N_ANGLE);

//===================================================================================================================================

}

void walking_detection(){

//ELVARN'S OFFSET COMPENSATION AND STABILISATION CODE=================================================================================================================================
         aaReal_x = mpu6050.getRawAccX();
         aaReal_y = mpu6050.getRawAccY();
         aaReal_z = mpu6050.getRawAccZ();
        
       // mag = sqrt((aaReal_x)*(aaReal_x) + (aaReal_y)*(aaReal_y) + (aaReal_z)*(aaReal_z));

        for (int i=0; i<20; i++) {
          if (i<19) {
            sample_x[i]=sample_x[i+1];
            sample_y[i]=sample_y[i+1];
            sample_z[i]=sample_z[i+1];
          }else {
            sample_x[i]=aaReal_x;
            sample_y[i]=aaReal_y;
            sample_z[i]=aaReal_z;
          }

          sum_x = sum_x + sample_x[i];
          sum_y = sum_y + sample_y[i];
          sum_z = sum_z + sample_z[i];
        }

        avg_x = sum_x / 20;
        avg_y = sum_y / 20;
        avg_z = sum_z / 20;

        sum_x = 0;
        sum_y = 0;
        sum_z = 0;
 
  //WALKING DETECTION==========================================================================================================


        
        mag = (aaReal_x - avg_x + aaReal_y - avg_y + aaReal_z - avg_z)/(3);

        //Serial.println(freq);
        /*if (mag >= 2000 && mag <= 2050 && flag == 1){
          time_taken = millis() - start_time;
        }*/
        
        if (mag <= 2000 && flag == 1){
          time_taken = millis() - start_time;
          start_time = millis();
          flag = !flag;
          freq = 1000.0/time_taken;
          W = 5;
        }else if (W > 0){
          W = W - 1;
        }
     
        if (mag >= 2000 && flag == 0){
          flag = !flag;
        }


        if (W <= 0){
          freq = 0;
        }

        for (int i=0; i<5; i++) {
          if (i<4) {
            sample[i]=sample[i+1];
          }else {
            sample[i]=freq;
          }

          sum = sum + sample[i];
        }

        avg = sum / 5;

        sum = 0;

        if (avg > 0 && avg <=10){
          v = 1;
        }else {
          v = 0;
        }
        //Serial.println(mag);
        //Serial.println(freq);
       // Serial.println("");
       // Serial.println("");
        
        //Serial.println(mag);
        //Serial.print(count);
        //count++;
        /*if (mag > 4000){
          W=30; 
          //Serial.print("WALKING");
          x2 = HIGH;
        }if (W > 0){
          //Serial.print("WALKING");
          x2 = HIGH;
          W = W - 1;
        }*/
//==================================================================================================================================
//POSITIONAL PLOT===========(TESTING NEEDED)========================================================================================
        x2 = digitalRead(START);          //walking trigger
        if ((x2 == LOW) && (v == 1)){
          POSITION[0] = POSITION[0] + 0.1*sin(N_ANGLE*PI/180);
          POSITION[1] = POSITION[1] + 0.1*cos(N_ANGLE*PI/180);
          x2 = HIGH;
        }

        x1 = digitalRead(OFF_SET);  
        if (x1 == HIGH){
          POSITION[0] = 0;
          POSITION[1] = 0;
        }
        

//============================================================================================================================  
// FINAL OUTPUT TO DISPLAY IN APP
        
//        Serial.print(N_ANGLE); 
//        Serial.print(" || ");
//        Serial.print(" ");
//        Serial.print(POSITION[0]); //======= X COORDINATE
//        Serial.print(" ");
//        Serial.println(POSITION[1]); //======= Y COORDINATE

        int angle = N_ANGLE;
        float xValue = POSITION[0];
        float yValue = POSITION[1];

        value11 = xValue;
        value12 = yValue;
        value10 = angle;

}


//===============================================================================================================================================
