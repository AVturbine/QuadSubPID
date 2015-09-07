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
float pid(float actual) {
  float olddiff;
  float diff = actual - 1; // 1g is our setpoint
  float sum = sum + diff; // Making the sum for the "
  float deltadiff = diff - olddiff;
  olddiff = diff
  float output = kp*diff + ki*sum + kd*deltadiff ;
  
}
  

void setup() {
  Serial.begin(9600);
  pinMode(accvcc, OUTPUT);
  pinMode(accgnd, OUTPUT);
  digitalWrite(accvcc, HIGH); //establishing 5v to the accel breakout
  digitalWrite(accgnd, LOW); //And sinking it, too

}

void loop() {
  // put your main code here, to run repeatedly:
  float x = getAccel('x');
  Serial.println(x);
  delay(500);
}
