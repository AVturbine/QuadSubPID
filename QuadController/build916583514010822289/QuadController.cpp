#line 1 "QuadController.ino"
#include <Arduino.h>                                                                
                           
   
                                                                 
   
   

#include "Arduino.h"
float getAccel(char axis);
float pid(float actual, float kp, float ki, float kd);
void xcontrol();
void ycontrol();
void setup();
void loop();
#line 8
int motorFL = 6;                                                                                
int motorFR = 9; 
int motorBL = 10;
int motorBR = 11;

int accvcc = A0;                                                                             
int accx = A1;
int accy = A2;
float accz = A3;
int accgnd = A4;

int motorSettingFL = 255;
int motorSettingFR = 255;
int motorSettingBL = 255;
int motorSettingBR = 255;

float getAccel(char axis) {
 switch (axis) {
   case 'x':{
     float x = analogRead(accx);
     float xmv = x*0.0048*100; 
     float xg = xmv/160;
     return xg;
   }
   case 'y':{
     float y = analogRead(accy);
     float ymv = y*0.00488758553*100;
     float yg = ymv/160;
     return yg;
   }
   case 'z':{ 
     float z = analogRead(accz);
     float zmv = z*0.00488758553*100;
     float zg = zmv/195;
     return zg;
   }
 }
}
float pid(float actual, float kp, float ki, float kd) {
  float olddiff;
  float diff = actual - 1;                      
  float sum = sum + diff;                            
  float deltadiff = diff - olddiff;
  olddiff = diff;
  float output = kp*diff + ki*sum + kd*deltadiff;
  return output;
}
  
void xcontrol(){
  motorSettingFL = motorSettingFL + 3*pid(getAccel('x'), 1, 3, 5);
  motorSettingFR = motorSettingFR + 3*pid(getAccel('x'), 1, 3, 5);
  motorSettingBL = motorSettingBL - 3*pid(getAccel('x'), 1, 3, 5);
  motorSettingBR = motorSettingBR - 3*pid(getAccel('x'), 1, 3, 5);
  analogWrite(motorFL, motorSettingFL);
  analogWrite(motorFR, motorSettingFR);
  analogWrite(motorBL, motorSettingBL);
  analogWrite(motorBR, motorSettingBR);
  
}
void ycontrol(){
  motorSettingFL = motorSettingFL + 3*pid(getAccel('y'), 1, 3, 5);
  motorSettingFR = motorSettingFR - 3*pid(getAccel('y'), 1, 3, 5);
  motorSettingBL = motorSettingBL + 3*pid(getAccel('y'), 1, 3, 5);
  motorSettingBR = motorSettingBR - 3*pid(getAccel('y'), 1, 3, 5);
  analogWrite(motorFL, motorSettingFL);
  analogWrite(motorFR, motorSettingFR);
  analogWrite(motorBL, motorSettingBL);
  analogWrite(motorBR, motorSettingBR);
}
    
void setup() {
  Serial.begin(9600);
  pinMode(accvcc, OUTPUT);
  pinMode(accgnd, OUTPUT);
  digitalWrite(accvcc, HIGH);                                        
  digitalWrite(accgnd, LOW);                      
  
  
}

void loop() {
                                                
  xcontrol();
  delay(10);
  ycontrol();
  delay(10);
 motorSettingFL = 255;
 motorSettingFR = 255;
 motorSettingBL = 255;
 motorSettingBR = 255;
 delay(10);
  
}

