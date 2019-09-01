int opto1 = A0;
int opto2 = A1;
int opto3 = A2;
int opto4 = A3;
int opto5 = A4;
int value1 = 0;
int value2 = 0;
int value3 = 0;
int value4 = 0;
int value5 = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  
value1 = analogRead(opto1);
value2 = analogRead(opto2);
value3 = analogRead(opto3);
value4 = analogRead(opto4);
value5 = analogRead(opto5);

Serial.print("value1 = ");
//Serial.print(value1);
Serial.print(value1>470 ? 1 : 0);
Serial.print("  value2 = ");
//Serial.print(value2);
Serial.print(value2>470 ? 1 : 0);
Serial.print("  value3 = ");
//Serial.print(value3);
Serial.print(value3>470 ? 1 : 0);
Serial.print("  value4 = ");
//Serial.print(value4);
Serial.print(value4>470 ? 1 : 0);
Serial.print("  value5 = ");
//Serial.println(value5);
Serial.println(value5>470 ? 1 : 0);
delay(300);

}
