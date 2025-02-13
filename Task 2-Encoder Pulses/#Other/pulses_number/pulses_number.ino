byte pin = 2;
volatile float elapsed;
volatile float previous;
float rpm;
volatile int pulses;
volatile bool flag;

void setup() {
  Serial.begin(9600);
  pinMode(pin, INPUT);
  attachInterrupt(0, periodically, RISING); 
  previous = millis();
}

void loop() {
  pulses = 0; // reset pulses counter

  attachInterrupt(0, periodically, RISING); // attach interrupt for rpm counter
  delay(500); 
  detachInterrupt(0); // detach interrupt for rpm counter

  if (flag == true) {
    attachInterrupt(1, count, RISING); // attach interrupt for pulses counter
    delay(elapsed);
    detachInterrupt(1); // detach interrupt for pulses counter
    flag = false; // reset flag
  }

  rpm = 1000 / elapsed * 60;

  Serial.print("elapsed: "); // print resuslts
  Serial.println(elapsed);
  Serial.print("rpm: ");
  Serial.println(rpm);
  Serial.print("pulses: ");
  Serial.println(pulses);
}

void periodically() { 
  elapsed = millis() - previous;
  previous = millis(); 
  flag = true; // set flag to activate pulses counter
} 

void count() {
  pulses++;
}
