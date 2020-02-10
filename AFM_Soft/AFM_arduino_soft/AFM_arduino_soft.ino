#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define push 48
#define time_interval 40

const int PinA = 3;
const int PinB = 2;
 int k;

const int dirPin_x = 6;
const int stepPin_x = 7;
const int dirPin_y = 4;
const int stepPin_y = 5;
const int dirPin_z = 9;
const int stepPin_z = 8;

const int x2_end = 40;
const int x1_end = 38;
const int y2_end = 36;
const int y1_end = 34;

volatile int lastCount = 0;
volatile int last_counter = 0;
volatile int page = 1;
volatile int pushed = 0;
volatile int menu = 0;
volatile int MENU = 0;
volatile int frame = 0;

volatile int counter = 0;
volatile int x_length_step = 5;
volatile int y_length_step = 5;
volatile int x_max = 50;
volatile int y_max = 50;
volatile bool direct = 0; // 0 forward, 1 backward

const int opto[12] = {A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11};

void isr () {
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  if (interruptTime - lastInterruptTime > 5) {
    if (digitalRead(PinB) == LOW)
    {
      counter-- ;
    }
    else {
      counter++ ; 
    }
  }
  lastInterruptTime = interruptTime;
  if (counter != lastCount) {
    lastCount = counter ;
  }
}


void setup() {
  Serial.begin(115200);

  randomSeed(analogRead(0));
  
  pinMode(dirPin_x, OUTPUT);
  pinMode(stepPin_x, OUTPUT);
  pinMode(dirPin_y, OUTPUT);
  pinMode(stepPin_y, OUTPUT);
  pinMode(dirPin_z, OUTPUT);
  pinMode(stepPin_z, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(x1_end, INPUT);
  pinMode(x2_end, INPUT);
  pinMode(y1_end, INPUT);
  pinMode(y2_end, INPUT);
  pinMode(PinA, INPUT);
  pinMode(PinB, INPUT);
  pinMode(push, INPUT);

  attachInterrupt(digitalPinToInterrupt(PinA), isr, LOW);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("      AFM ");
  lcd.setCursor(14, 1);
  lcd.print("DB");
}


void blink() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
}



void loop() {
 if((last_counter > counter) || (last_counter < counter) || (pushed)) {
   menu = 1;
   
  //************************************** MENU = 0  
   if(MENU == 0){
     if(0 <= counter && counter < 1){
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("> Set steps length");
       lcd.setCursor(0, 1);
       lcd.print("  Set field size");
       page = 1;
       if(pushed){
         pushed = 0;
         }
       }

      if(1 <= counter && counter < 2){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  Set steps length");
        lcd.setCursor(0, 1);
        lcd.print("> Set field size");
        page = 2;
        if(pushed) {
          pushed = 0;
          }
        }
      
      if(2 <= counter && counter < 3){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("> Start");
        lcd.setCursor(0, 1);
        lcd.print("  Reset");
        page = 3;
        if(pushed){
          pushed = 0;
          }
        }

      if(3 <= counter && counter < 4){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  Start");
        lcd.setCursor(0, 1);
        lcd.print("> Reset");
        page = 4;
        if(pushed){
          pushed = 0;
          }
        }
      
      if(4 <= counter && counter < 5){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("> Back");
        page = 5;
        if(pushed){
          pushed = 0;
          }
        }
        
  if(counter > 5){
    counter = 5;
    }
  if(counter <= 0){
    counter = 0;
    }       
  }//if menu ==0

   if(MENU == 1){
     if((page == 1)){
       if(0 <= counter && counter < 1){
         lcd.clear();
         lcd.setCursor(0, 0);
         lcd.print("> Set X step");
         lcd.setCursor(0, 1);
         lcd.print("  Set Y step");
         frame = 1;
         if(pushed){
           pushed = 0;
           }
         }

       if(1 <= counter && counter < 2){
         lcd.clear();
         lcd.setCursor(0, 0);
         lcd.print("  Set X step");
         lcd.setCursor(0, 1);
         lcd.print("> Set Y step");
         frame = 2;
         if(pushed){
           pushed = 0;
           }
         }

       if(2 <= counter && counter < 3){
         lcd.clear();
         lcd.setCursor(0, 0);
         lcd.print("> Back");
         frame = 3;
         if(pushed){
           pushed = 0;
           }
         }      
       }
    
     if((page == 2)){
       if(0 <= counter && counter < 1){
         lcd.clear();
         lcd.setCursor(0, 0);
         lcd.print("> Set X_max");
         lcd.setCursor(0, 1);
         lcd.print("  Set Y_max");
         frame = 1;
         if(pushed){
           pushed = 0;
           }
         }

       if(1 <= counter && counter < 2){
         lcd.clear();
         lcd.setCursor(0, 0);
         lcd.print("  Set X_max");
         lcd.setCursor(0, 1);
         lcd.print("> Set Y_max");
         frame = 2;
         if(pushed){
           pushed = 0;
           }
         }

       if(2 <= counter && counter < 3){
         lcd.clear();
         lcd.setCursor(0, 0);
         lcd.print("> Back");
         frame = 3;
         if(pushed){
           pushed = 0;
           }
         }
       }
  if(counter > 3){
    counter = 3;
    }
  if(counter < 0){
    counter = 0;
    }       
  }//If menu==1

   if(MENU == 2){
     if(page == 1){
       lcd.clear();
       lcd.setCursor(7, 0);
       if(counter > 9){
         lcd.setCursor(6, 0);
         }
       lcd.print(counter);
       lcd.setCursor(8, 0);
       lcd.print("mm");
       
       if(counter > 19){
         counter = 19;
         }
       if(counter < 1){
         counter = 1;
         }
       }
      
     if(page == 2){
       lcd.clear();
       lcd.setCursor(7, 0);
       if(counter > 9){
         lcd.setCursor(6, 0);
         }
       lcd.print(counter);
       lcd.setCursor(8, 0);
       lcd.print("cm");

       if(counter > 18){
         counter = 18;
         }
       if(counter < 1){
         counter = 1;
         }
       }       
     }// end of MENU = 2
 }// end of 1 if
  last_counter = counter;

       
  if(digitalRead(push)){
    if(MENU == 1){
      if(page == 1){
        if(frame == 1){
          counter = 0;
          pushed = 0;
          menu = 0;
          MENU = 2;
          delay(300);
          }
          
         if(frame == 2){ 
           counter = 0;
           pushed = 0;
           menu = 0;
           MENU = 2;
           delay(300); 
           } 
           
         if(frame == 3){
           pushed = 1;
           MENU = 0;
           counter = 0;
           menu = 0;
           delay(200);
           }
         }
        
      if(page == 2){
        if(frame == 1){
          counter = 0;
          pushed = 0;
          menu = 0;
          MENU = 2;
          delay(300);
          }
          
        if(frame == 2){
          counter = 0;
          pushed = 0;
          menu = 0;
          MENU = 2;
          delay(300);
          } 
          
        if(frame == 3){
          pushed = 1;
          MENU = 0;
          counter = 0;
          menu = 0;
          delay(200);
          }
        } 
      }
      
    if(MENU == 2 &&  menu == 1){
      if(page == 1){      
        pushed = 0;
        MENU = 1;
        if(frame == 1){
          x_length_step = counter;
         // Serial.println("X_length_step:");
       // Serial.println(x_length_step);
          }
        if(frame == 2){
          y_length_step = counter;
          //Serial.println("Y_length_step:");
      ///  Serial.println(y_length_step);
          }
          counter = 0;
        delay(200);
        }

       if(page == 2){
         pushed = 0;
         MENU = 1;
         if(frame == 1){
           x_max = 10*counter;
         // Serial.println("X_max:");
       // Serial.println(x_max);
           }
         if(frame == 2){
           y_max = 10*counter;
        //  Serial.println("Y_max:");
     //   Serial.println(y_max);
           }
          counter = 0;
        delay(200);
        }
      }
      
    if(MENU == 0 && menu == 1){
      if(page == 1){
        pushed = 1;
        counter = 0;
        menu = 0;
        MENU = 1;
        delay(300);
        }

      if(page == 2){
        pushed = 1;
        counter = 0;
        menu = 0;
        MENU = 1;
        delay(300);
        }

      if(page == 3){             //*****************START
               /* Serial.println("X_max:");
        Serial.println(x_max);
                Serial.println("Y_max:");
        Serial.println(y_max);
                Serial.println("X_length_step:");
        Serial.println(x_length_step);
                Serial.println("Y_length_step:");
        Serial.println(y_length_step);*/
        
       lcd.clear();
       lcd.setCursor(1, 0);
       lcd.print("Progressing..");
       unsigned long time1 = millis();
       measure();
       unsigned long time2 = millis();
       lcd.clear();
       lcd.setCursor(2, 0);
       lcd.print("End measure");
       lcd.setCursor(0, 1);
       lcd.print("Time[s]:");
       lcd.setCursor(9, 1);
       lcd.print((time2-time1)/1000);
       MENU = 0;
       // counter = 1;
       pushed = 0;
       menu = 0;  
   
        }
      if(page == 4){
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Reseting..");
        while(digitalRead(x2_end) != HIGH){
             move_forward(dirPin_x, stepPin_x, 4);      
             }    
       
        while(digitalRead(y2_end) != HIGH){
             move_forward(dirPin_y, stepPin_y, 4);
             }
         
        move_backward(dirPin_x, stepPin_x, 5);    
        move_backward(dirPin_y, stepPin_y, 5); 

        MENU = 0;
        counter = 1;
        pushed = 0;
        menu = 0;
        }
  
      if(page == 5){
        counter = 0;
        last_counter = counter;
        pushed = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("      AFM ");
        lcd.setCursor(14, 1);
        lcd.print("DB");
        delay(2000);
        }
      }
    }// end if push
  

}//loop end

void move_forward(int dirPin, int stepPin, int angle) {
  digitalWrite(dirPin, HIGH);

  for (int x = 0; x < angle * 25*16; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(time_interval);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(time_interval);
  }
}

void move_backward(int dirPin, int stepPin, int angle) {
  digitalWrite(dirPin, LOW);

  for (int x = 0; x < angle * 25*16; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(time_interval);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(time_interval);
  }
}

void move(int dirPin, int stepPin, int angle, int value) {
  digitalWrite(dirPin, value); // direct 0 forward, 1 backward

  for (int x = 0; x < angle * 25*16; x++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(time_interval);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(time_interval);
  }
}

void move_z() {
  digitalWrite(dirPin_z, HIGH);

  for (int x = 0; x<1600; x++) {
    digitalWrite(stepPin_z, HIGH);
    delayMicroseconds(30);
    digitalWrite(stepPin_z, LOW);
    delayMicroseconds(30);
  }
}
void measure() {
    for( k = 0; k < x_max/x_length_step + 1; k++){    
        for(int j = 0; j < y_max/y_length_step; j++){    
          Serial.print((j + direct*(y_max/y_length_step  -(j*2)))*x_length_step);// dac ewentualnie -1
          Serial.print(" ");
          Serial.print(k*y_length_step);
          Serial.print(" ");
          
           Read();
           
           if((digitalRead(y1_end) == HIGH) || (digitalRead(y2_end) == HIGH)){
             break;
             }
           move(dirPin_y, stepPin_y, y_length_step, direct);
           }

        direct = !direct;
        if(digitalRead(x1_end) != HIGH){
          move_backward(dirPin_x, stepPin_x, x_length_step);
          }
        if(digitalRead(push)){
          break;
          }
        }   
  } // end void measure

void Read(){
     move_z();
     delay(20);
     //delay(500);
     int a = 1;
     for(int i=1;i<13;i++){
       if(analogRead(opto[i-1])>700){
         Serial.print((i-1)*4);
         a = 0;
         break;    
         }
        }

       if(a){
        Serial.print("0");
        }
        
     Serial.print('\n');
     move_z();
     delay(20);
  }
