#include <Arduino.h> // Just so that you can compile it without additional software.
/*Quadcopter PID Controller
 * 
 * Written by Timothy Kanarsky for the AVBotz Entrance Assignment
 * 
 */

int motorFL = 6; // Motor pins, reason for inconsistent numbering is that these pins support PWM
int motorFR = 9; 
int motorBL = 10;
int motorBR = 11;

int accvcc = A0;  // Analog accelerometer, ADXL3XX, plugged into analog header of Arduino Uno
int accx = A1;
int accy = A2;
float accz = A3;
int accgnd = A4;

int motorSettingFL = 255; // Initial motor setting: full thrust
int motorSettingFR = 255;
int motorSettingBL = 255;
int motorSettingBR = 255;

float getAccel(char axis) { // A function I wrote to get the raw accel data from the ADXL, convert it into g's and return selected axis.
 switch (axis) {
   case 'x':{
     float x = analogRead(accx);
     float xmv = x*0.0048875*100; //Dark conversion magic going on here
     float xg = xmv/160;
     return xg;
   }
   case 'y':{
     float y = analogRead(accy);
     float ymv = y*0.0048875*100;
     float yg = ymv/160;
     return yg;
   }
   case 'z':{ 
     float z = analogRead(accz);
     float zmv = z*0.0048875*100;
     float zg = zmv/195;
     return zg;
   }
 }
}
float pid(float actual, float kp, float ki, float kd) {
  float olddiff;
  float diff = actual - 1; // 1g is our setpoint
  float sum = sum + diff; // Making the sum for the integral
  float deltadiff = diff - olddiff; // and the derivative
  olddiff = diff;  // this is now our olddiff
  float output = kp*diff + ki*sum + kd*deltadiff; // combining all three parts
  return output; // and returns output
}
  
void xcontrol(){
  motorSettingFL = motorSettingFL + 3*pid(getAccel('x'), 1, 3, 5); // Controls x setting through the pid  and getAccel functions
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
  Serial.begin(9600);  // Starts serial comm thru USB for debugging purposes
  pinMode(accvcc, OUTPUT);
  pinMode(accgnd, OUTPUT);
  digitalWrite(accvcc, HIGH); //establishing 5v to the accel breakout
  digitalWrite(accgnd, LOW); //And sinking it, too
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  xcontrol(); // runs xcontrol, then ycontrol
  delay(10);
  ycontrol();
  delay(10);
 motorSettingFL = 255; //and resets
 motorSettingFR = 255;
 motorSettingBL = 255;
 motorSettingBR = 255;
 delay(10);
  
}
