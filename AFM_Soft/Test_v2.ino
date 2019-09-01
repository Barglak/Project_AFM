#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define time_interval 700

const int dirPin_x = 7;
const int stepPin_x = 6;
const int dirPin_y = 5;
const int stepPin_y = 4;
const int dirPin_z = 3;
const int stepPin_z = 2;

const int x_button_forward = 38;
const int x_button_backward =36;
const int y_button_forward = 42;
const int y_button_backward = 40;
const int z_button = 44; 

const int x1_end = 32;
const int x2_end = 33;
const int y1_end = 30;
const int y2_end = 31;

int x_button_fstate = 0;  
int x_button_bstate = 0;
int y_button_fstate = 0; 
int y_button_bstate = 0;     
int z_button_state = 0;

int x1_end_state = 0;
int x2_end_state = 0;
int y1_end_state = 0;
int y2_end_state = 0;


void setup() {
  pinMode(dirPin_x,OUTPUT);
  pinMode(stepPin_x,OUTPUT);
  pinMode(dirPin_y,OUTPUT);
  pinMode(stepPin_y,OUTPUT);
  pinMode(dirPin_z,OUTPUT);
  pinMode(stepPin_z,OUTPUT);
  
  pinMode(x_button_forward,INPUT);
  pinMode(x_button_backward,INPUT);
  pinMode(y_button_forward,INPUT);
  pinMode(y_button_backward,INPUT);
  pinMode(z_button,INPUT);

  pinMode(x1_end,INPUT);
  pinMode(x2_end,INPUT);
  pinMode(y1_end,INPUT);
  pinMode(y2_end,INPUT);
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  lcd.init();
  lcd.backlight();
    
  lcd.setCursor(2,0);
  lcd.print("AFM..");
  
}

void loop() {

  x_button_fstate = digitalRead(x_button_forward);
  x_button_bstate = digitalRead(x_button_backward);
  y_button_fstate = digitalRead(y_button_forward);
  y_button_bstate = digitalRead(y_button_backward);
  z_button_state = digitalRead(z_button);

  x1_end_state = digitalRead(x1_end);
  x2_end_state = digitalRead(x2_end);
  y1_end_state = digitalRead(y1_end);
  y2_end_state = digitalRead(y2_end);
  
//******************************************* X MOTOR
 if((x_button_fstate == HIGH)&&(x2_end_state != HIGH)){
    move_forward(dirPin_x, stepPin_x);
 }

  if((x_button_bstate == HIGH)&&(x1_end_state != HIGH)){
    move_backward(dirPin_x, stepPin_x);
 }

 //****************************************** Y MOTOR
 if((y_button_fstate == HIGH)&&(y2_end_state != HIGH)){
    move_forward(dirPin_y, stepPin_y);
 }

  if((y_button_bstate == HIGH)&&(y1_end_state != HIGH)){
    move_backward(dirPin_y, stepPin_y);
 }

  //***************************************** Z MOTOR
 if(z_button_state == HIGH){
    move_forward(dirPin_z, stepPin_z);
 }
// Koniec loop 
}

 void move_forward(int dirPin, int stepPin){
  digitalWrite(dirPin,LOW);
  
  for(int x = 0;x<50; x++){
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(time_interval);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(time_interval);
     }
  }

 void move_backward(int dirPin, int stepPin){
  digitalWrite(dirPin,HIGH);
  
  for(int x = 0;x<50; x++){
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(time_interval);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(time_interval);
     }
  }

void blink(){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 
  
  }
