#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define push 22

const int PinA = 2;
const int PinB = 3;

volatile int counter = 0;
int lastCount = 0;
int last_counter = 0;
int page = 1;
int subMenu = 0;
int pushed = 0;
int menu = 0;
int clk_state;
bool last_state;
bool data_state;

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

  pinMode(push,INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
    
  Serial.begin(115200);

  pinMode(PinA, INPUT);
  pinMode(PinB, INPUT);

  attachInterrupt(digitalPinToInterrupt(PinA), isr, LOW);

  lcd.init();
  lcd.backlight();

//  last_state = digitalRead(clk);
  
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("  AFM Project");
  
}

void blink(){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500); 
  }

void loop(){
   /*state = digitalRead(clk);
   
   if(state!=last_state){
      if(digitalRead(data) != state){
          counter ++;
         }else{
          counter --;
        }
      }      
      last_state = state;
*/

  if((last_counter > counter)||(last_counter < counter)||(pushed)){ //1 if
    menu = 1;
    if(subMenu == 0){
      if(0 <= counter && counter < 2){
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("> Option 1");
        lcd.setCursor(0,1);  
        lcd.print("  Option 2");
        page = 1;
          if(pushed){ 
            pushed = 0;
          }  
        }

      if(2 <= counter && counter < 3){
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("  Option 1");
        lcd.setCursor(0,1);  
        lcd.print("> Option 2");
        page = 2;
          if(pushed){ 
              pushed = 0;
            } 
        }

       if(3 <= counter && counter < 4){
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("> Option 3");
        lcd.setCursor(0,1);  
        lcd.print("  Option 4");
        page = 3;
          if(pushed){ 
              pushed = 0;
            } 
        }

      if(4 <= counter && counter < 5){
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("  Option 3");
        lcd.setCursor(0,1);  
        lcd.print("> Option 4");
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
        lcd.print("> Option 1.1");
        lcd.setCursor(0,1);  
        lcd.print("  Option 1.2");
        page = 1;
        pushed = 0;
        }

      if(1 <= counter && counter < 2){
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("  Option 1.1");
        lcd.setCursor(0,1);  
        lcd.print("> Option 1.2");
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
        lcd.print("> Option 2.1");
        lcd.setCursor(0,1);  
        lcd.print("  Option 2.2");
        page = 1;
        pushed = 0;
        }

      if(1 <= counter && counter < 2){
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("  Option 2.1");
        lcd.setCursor(0,1);  
        lcd.print("> Option 2.2");
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
    if(subMenu == 3){
      if(0 <= counter && counter < 1){
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("> Option 3.1");
        lcd.setCursor(0,1);  
        lcd.print("  Option 3.2");
        page = 1;
        pushed = 0;
        }

      if(1 <= counter && counter < 2){
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("  Option 3.1");
        lcd.setCursor(0,1);  
        lcd.print("> Option 3.2");
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

// -------------------------- FIFTH PAGE OF THE MENU 
    if(subMenu == 4){
      if(0 <= counter && counter < 1){
        lcd.clear();
        lcd.setCursor(0,0); 
        lcd.print("> Option 4.1");
        lcd.setCursor(0,1);  
        lcd.print("  Option 4.2");
        page = 1;
        pushed = 0;
        }

      if(1 <= counter && counter < 2){
        lcd.clear();
        lcd.setCursor(0,0);  
        lcd.print("  Option 4.1");
        lcd.setCursor(0,1);  
        lcd.print("> Option 4.2");
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
    
    }// 1 if end, end Menu prints

  last_counter = counter;

  if(digitalRead(push)){
    
    if(subMenu == 1){
      if(page == 1){
        subMenu = 0;
        counter = 1;
        pushed = 0;
        menu = 0;
        blink();
        delay(1000);
        blink();
        }
        
      if(page == 2){
        subMenu = 0;
        counter = 1;
        pushed = 0;
        menu = 0;
        blink();
        blink();
        delay(1000);
        blink();
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
        blink();
        delay(1000);
        blink();
        blink();
        }
        
      if(page == 2){
        subMenu = 0;
        counter = 1;
        pushed = 0;
        menu = 0;
        blink();
        blink();
        delay(1000);
        blink();
        blink();
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
      if(page == 1){
        subMenu = 0;
        counter = 1;
        pushed = 0;
        menu = 0;
        blink();
        delay(1000);
        blink();
        blink();
        blink();
        }
       
      if(page == 2){
        subMenu = 0;
        counter = 1;
        pushed = 0;
        menu = 0;
        blink();
        blink();
        delay(1000);
        blink();
        blink();
        blink();
        }  

      if(page == 3){
        subMenu = 0;
        counter = 3;
        pushed = 0;
        menu = 0;
        delay(300);
        }  
      } 
          
     if(subMenu == 4){
      if(page == 1){
        subMenu = 0;
        counter = 1;
        pushed = 0;
        menu = 0;
        blink();
        delay(1000);
        blink();
        blink();
        blink();
        blink();
        }
        
      if(page == 2){
        subMenu = 0;
        counter = 1;
        pushed = 0;
        menu = 0;
        blink();
        blink();
        delay(1000);
        blink();
        blink();
        blink();
        blink();
        } 

      if(page == 3){
        subMenu = 0;
        counter = 4;
        pushed = 0;
        menu = 0;
        delay(300);
        }  
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
        pushed = 1;
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
   if(counter > 6){
     counter = 6;
     }
   if(counter < 0){
     counter=0;
     }      
     
} // loop end
