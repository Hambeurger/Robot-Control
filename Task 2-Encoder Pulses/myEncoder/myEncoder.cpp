//Control DC 2 motor with encoders.

#include"myEncoder.h"

int enc_1,enc_2; //encoder pin is also the interrupt pin

volatile int lastEncoded=0;
volatile long encoderValue=0;
volatile long correctEncoderValue=0;
 
long lastencoderValue=0;
 
int lastMSB=0;
int lastLSB=0;

void updateEncoder();

Encoder::Encoder(int enc_1,int enc_2){
	enc_1=enc_1;
	enc_2=enc_2;
	
	pinMode(enc_1,INPUT);
	pinMode(enc_2,INPUT); //put encoder to input
   
	digitalWrite(enc_1,HIGH); //turn pullup resistor on
	digitalWrite(enc_2,HIGH); //turn pullup resistor on
	
	attachInterrupt(digitalPinToInterrupt(enc_1),updateEncoder,CHANGE);
	attachInterrupt(digitalPinToInterrupt(enc_2),updateEncoder,CHANGE);
}

int Encoder::getEncUpdate(int t){
	correctEncoderValue=encoderValue/4;
	
	Serial.print("Encoder value is:");
	Serial.println(correctEncoderValue);

	/*The below code is used to control motor movement by using encoder value.
	if (0<=correctEncoderValue && correctEncoderValue<5000) {
		analogWrite(PWM_L,127);
		digitalWrite(DIR_L,LOW);
	} 
	else {
    	analogWrite(PWM_L,0);
    	digitalWrite(DIR_L,LOW);
  }*/
  	delay(t);
	return encoderValue;
}

void updateEncoder(){
	int MSB=digitalRead(enc_1); //MSB = most significant bit
	int LSB=digitalRead(enc_2); //LSB = least significant bit
	int encoded=(MSB << 1) |LSB; //converting the 2 pin value to single number
	int sum=(lastEncoded << 2) | encoded; //adding it to the previous encoded value
 
	if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011){
  		encoderValue++;
  	}
	if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000){
  		encoderValue--;
  	}
  	lastEncoded=encoded; //store this value for next time
}