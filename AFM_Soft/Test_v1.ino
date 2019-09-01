const int stepPin = 3;
const int dirPin = 5;
const int button1 = 8;
const int button2 = 9;

int buttonState = 0;        
int buttonState2 = 0;

void setup() {
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  buttonState = digitalRead(button1);
  buttonState2 = digitalRead(button2);

 if(buttonState == HIGH){
    digitalWrite(dirPin,HIGH);
    
      for(int x = 0;x<200; x++){
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(800);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(800);
      }
 }

  if(buttonState2 == HIGH){
    digitalWrite(dirPin,LOW);
    
      for(int x = 0;x<200; x++){
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(800);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(800);
      }
 }
 
}

void blink(){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 
  
  }
