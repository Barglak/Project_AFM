#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define push 22
#define time_interval 750

const int PinA = 2;
const int PinB = 3;

const int dirPin_x = 7;
const int stepPin_x = 6;
const int dirPin_y = 5;
const int stepPin_y = 4;
const int dirPin_z = 9;
const int stepPin_z = 8;

const int x1_end = 32;
const int x2_end = 33;
const int y1_end = 30;
const int y2_end = 31;

int x1_end_state = 0;
int x2_end_state = 0;
int y1_end_state = 0;
int y2_end_state = 0;

int lastCount = 0;
int last_counter = 0;
int page = 1;
int subMenu = 0;
int pushed = 0;
int menu = 0;

volatile int counter = 0;
volatile int x_length_step = 0;
volatile int y_length_step = 0;

void isr (){
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  if (interruptTime - lastInterruptTime > 5) {
    if (digitalRead(PinB) == LOW)
    {
      counter-- ; // Could be -5 or -10
    }
    else {
      counter++ ; // Could be +5 or +10
    }
  }
  lastInterruptTime = interruptTime;
  if (counter != lastCount) {
    lastCount = counter ;
  }
}

void setup()
{
  Serial.begin(115200);
  
  pinMode(dirPin_x,OUTPUT);
  pinMode(stepPin_x,OUTPUT);
  pinMode(dirPin_y,OUTPUT);
  pinMode(stepPin_y,OUTPUT);
  pinMode(dirPin_z,OUTPUT);
  pinMode(stepPin_z,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
    
  pinMode(x1_end,INPUT);
  pinMode(x2_end,INPUT);
  pinMode(y1_end,INPUT);
  pinMode(y2_end,INPUT);
  pinMode(PinA, INPUT);
  pinMode(PinB, INPUT);
  pinMode(push,INPUT);
  
  attachInterrupt(digitalPinToInterrupt(PinA), isr, LOW);

  lcd.init();
  lcd.backlight(); 
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("  AFM Project");
  
}

void blink(){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100); 
  }

void loop(){

  if((last_counter > counter)||(last_counter < counter)||(pushed)){ //1 if
    menu = 1;
    if(subMenu == 0){
      if(0 <= counter && counter < 2){
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("> X axis");
        lcd.setCursor(0,1);  
        lcd.print("  Y axis");
        page = 1;
          if(pushed){ 
            pushed = 0;
          }  
        }

      if(2 <= counter && counter < 3){
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("  X axis");
        lcd.setCursor(0,1);  
        lcd.print("> Y axis");
        page = 2;
          if(pushed){ 
              pushed = 0;
            } 
        }

       if(3 <= counter && counter < 4){
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("> Set X step");
        lcd.setCursor(0,1);  
        lcd.print("  Set Y step");
        page = 3;
          if(pushed){ 
              pushed = 0;
            } 
        }

      if(4 <= counter && counter < 5){
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("  Set X step");
        lcd.setCursor(0,1);  
        lcd.print("> Set Y step");
        page = 4;
          if(pushed){ 
              pushed = 0;
            } 
        } 
        
      if(5 <= counter && counter < 6){
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("> Back");
        page = 5;
          if(pushed){ 
              pushed = 0;
            } 
        } 
            
      }

// -------------------------- SECOND PAGE OF THE MENU 

    if(subMenu == 1){
      if(0 <= counter && counter < 1){
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("> Move X forward");
        lcd.setCursor(0,1);  
        lcd.print("  Move X backward");
        page = 1;
        pushed = 0;
        }

      if(1 <= counter && counter < 2){
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("  Move X forward");
        lcd.setCursor(0,1);  
        lcd.print("> Move X backward");
        page = 2;
        pushed = 0;
        }
        
      if(2 <= counter && counter < 3){
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("> Back");
        page = 3;
        pushed = 0;
        }    
      }

// -------------------------- THIRD PAGE OF THE MENU 
    if(subMenu == 2){
      if(0 <= counter && counter < 1){
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("> Move Y forward");
        lcd.setCursor(0,1);  
        lcd.print("  Move Y backward");
        page = 1;
        pushed = 0;
        }

      if(1 <= counter && counter < 2){
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("  Move Y forward");
        lcd.setCursor(0,1);  
        lcd.print("> Move Y backward");
        page = 2;
        pushed = 0;
        }
        
      if(2 <= counter && counter < 3){
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("> Back");
        page = 3;
        pushed = 0;
        }   
      }
      
// -------------------------- FOURTH PAGE OF THE MENU
    if(subMenu == 3){  // Set X step
        lcd.clear();
        lcd.setCursor(7,0); 
        if(counter>9){
          lcd.setCursor(6,0);
          }
        lcd.print(counter);
        lcd.setCursor(8,0);  
        lcd.print("mm");
      }


// -------------------------- FIFTH PAGE OF THE MENU 
    if(subMenu == 4){ // set y step
        lcd.clear();
        lcd.setCursor(7,0); 
        if(counter>9){
          lcd.setCursor(6,0);
          }
        lcd.print(counter);
        lcd.setCursor(8,0);  
        lcd.print("mm");
      }
    
    }// 1 if end, end Menu prints

  last_counter = counter;

  if(digitalRead(push)){
    
    if(subMenu == 1){
      if(page == 1){
        subMenu = 0;
        counter = 1;
        pushed = 0;
        menu = 0;
        while(digitalRead(x2_end) != HIGH){
          move_forward(dirPin_x, stepPin_x, x_length_step);
         
          }
        delay(300);  
        }
        
      if(page == 2){
        subMenu = 0;
        counter = 1;
        pushed = 0;
        menu = 0;
        while(digitalRead(x1_end) != HIGH){
          move_backward(dirPin_x, stepPin_x, x_length_step);
          
          }
        delay(300);
        }  

      if(page == 3){
        subMenu = 0;
        counter = 1;
        pushed = 0;
        menu = 0;
        delay(300);
        }  
      }

     if(subMenu == 2){
      if(page == 1){
        subMenu = 0;
        counter = 1;
        pushed = 0;
        menu = 0;
        while(digitalRead(y2_end) != HIGH){
          move_forward(dirPin_y, stepPin_y, y_length_step);
          
          }
        delay(300);  
        }
        
      if(page == 2){
        subMenu = 0;
        counter = 1;
        pushed = 0;
        menu = 0;
        while(digitalRead(y1_end) != HIGH){
          move_backward(dirPin_y, stepPin_y, y_length_step);
          
          }
        delay(300);  
        }  

      if(page == 3){
        subMenu = 0;
        counter = 2;
        pushed = 0;
        menu = 0;
        delay(300);
        }  
      }
      
     if(subMenu == 3){
        x_length_step = counter;
        subMenu = 0;
        counter = 1;
        pushed = 0;
        menu = 0;
        delay(300);
      } 
          
     if(subMenu == 4){
        y_length_step = counter;
        subMenu = 0;
        counter = 1;
        pushed = 0;
        menu = 0;
        delay(300);
      }     

if(subMenu == 0 && menu == 1){
      if(page == 1){
        subMenu = 1;
        counter = 0;
        pushed = 1;
        delay(300);
        }
        
      if(page == 2){
        subMenu = 2;
        counter = 0;
        pushed = 1;
        delay(300);
        }
        
      if(page == 3){
        subMenu = 3;
        counter = 0;
        pushed = 0;
        delay(300);
        }
        
      if(page == 4){
        subMenu = 4;
        counter = 0;
        pushed = 1;
        delay(300);        
        }    

      if(page == 5){
        counter = 0;
        last_counter = counter;
        pushed = 0; 
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("  AFM Project");    
        delay(2000);   
        }    
        
      } // end of subMenu == 0

    }// end of if(push)

// Limit for counter
if(((subMenu != 3)||(subMenu == 4))&&((subMenu == 3)||(subMenu != 4))){
   if(counter > 6){
     counter = 6;
     }
   if(counter < 0){
     counter=0;
     }      
  }else{
    if(counter > 30){
     counter = 30;
     }
   if(counter < 0){
     counter=0;
     }  
    
    }   
} // loop end

void move_forward(int dirPin, int stepPin, int angle){
  digitalWrite(dirPin,0);

  for(int x = 0;x<angle*25; x++){
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(time_interval);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(time_interval);
     }
     delay(100);
  }

void move_backward(int dirPin, int stepPin, int angle){
  digitalWrite(dirPin,HIGH);
 
  for(int x = 0;x<angle*25; x++){
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(time_interval);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(time_interval);
     }
     delay(100);
  }
