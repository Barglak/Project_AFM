const int stepPin = 3;
const int dirPin = 5;


void setup() {
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
}

void loop() {
    digitalWrite(dirPin,LOW);

  for(int i = 0; i< 10; i++){
    for(int x = 0;x<200; x++){
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(1000);
     
         }
  delay(1000);
  }
   delay(1000);
}
