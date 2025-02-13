//Control DC 2 motor with encoders,without using library
//Reference Website: https://www.mauroalfieri.it/elettronica/tinkercad-controlla-un-motore-con-encoder.html
#define t 100

#define enc_L_1 18 //motor 1 encoder 1
#define enc_L_2 19 //motor 1 encoder 2
#define PWM_L 9 //motor 1 speed control,analog
#define DIR_L 6 //motor 1 direction control,digital

#define enc_R_1 2 //motor 2 encoder 1
#define enc_R_2 3 //motor 2 encoder 2
#define PWM_R 4 //motor 2 speed control,analog
#define DIR_R 5 //motor 2 direction control,digital

volatile int lastEncoded=0;
volatile long encoderValue=0;
volatile long absEncoderValue=0,absEncoderValue_new;
 
long lastencoderValue=0;
 
int lastMSB=0;
int lastLSB=0;

void setup() {
   Serial.begin(9600);
   pinMode(enc_L_1,INPUT);
   pinMode(enc_L_2,INPUT); //put encoder to input
   
   digitalWrite(enc_L_1,HIGH); //turn pullup resistor on
   digitalWrite(enc_L_2,HIGH); //turn pullup resistor on
   
   attachInterrupt(digitalPinToInterrupt(enc_L_1),updateEncoder,CHANGE);
   attachInterrupt(digitalPinToInterrupt(enc_L_2),updateEncoder,CHANGE);
  
   pinMode(PWM_L,OUTPUT);
   pinMode(DIR_L,OUTPUT);
}

void loop() {
   absEncoderValue_new=fabs(encoderValue);
   
   Serial.print("Encoder value since last iteration:");
   Serial.println(absEncoderValue_new-absEncoderValue);
   Serial.print("Encoder pulse:");
   Serial.println(absEncoderValue_new);
   Serial.println();

   absEncoderValue=absEncoderValue_new;

  //The below code is used to control motor movement by using encoder value.
  //Encoder pulse only increase when wheel is not spinning.
   /*if (0<=absEncoderValue&&absEncoderValue<1000) {
    analogWrite(PWM_L,255);
    digitalWrite(DIR_L,LOW);
    analogWrite(PWM_R,255);
    digitalWrite(DIR_L,HIGH);
  } else {
    analogWrite(PWM_L,0);
    digitalWrite(DIR_L,LOW);
  }*/
  
   delay(t);
}

void updateEncoder(){
  int MSB = digitalRead(enc_L_1); //MSB = most significant bit
  int LSB = digitalRead(enc_L_2); //LSB = least significant bit
 
  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value
 
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;
 
  lastEncoded = encoded; //store this value for next time
}
