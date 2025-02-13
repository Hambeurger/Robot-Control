#define ENCA 18 // pin2 of the Arduino
#define ENCB 19 // Pin3 of the Arduino
int ENCA_DATA;
int ENCB_DATA;
 
void setup() {
  Serial.begin(9600); // Activates Serial communication
  pinMode(ENCA,INPUT); // sets pin2 as the input
  pinMode(ENCB,INPUT); // sets pin3 as the input
}
 
void loop() {
  ENCA_DATA = digitalRead(ENCA); 
  ENCB_DATA = digitalRead(ENCB); 
  Serial.print(ENCA_DATA); 
  Serial.print(" ");
  Serial.print(ENCB_DATA);
  Serial.println();
  delay(1000);
}
