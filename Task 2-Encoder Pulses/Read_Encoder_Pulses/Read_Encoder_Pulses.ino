#include"myEncoder.h"

#define t 500
#define PWM_L 9 //motor 1 speed control,analog
#define DIR_L 6 //motor 1 direction control,digital
#define PWM_R 4 //motor 2 speed control,analog
#define DIR_R 5 //motor 2 direction control,digital

Encoder enc_L=Encoder(2,3);
//Encoder enc_R=Encoder(18,19);

void setup() {
  Serial.begin(9600);
  pinMode(PWM_L,OUTPUT);
  pinMode(DIR_L,OUTPUT);  
  pinMode(PWM_R,OUTPUT);
  pinMode(DIR_R,OUTPUT);
}

void loop() {
  int enc_val=enc_L.getEncUpdate(t);
  //int enc_val=enc_R.getEncUpdate(t);

  //The below code is used to control motor movement by using encoder value.
   /*if (0<=enc_val&&enc_val<1000) {
    analogWrite(PWM_L,250);
    digitalWrite(DIR_L,LOW);
  } else {
    analogWrite(PWM_L,0);
    digitalWrite(DIR_L,LOW);
  }

   if (0<=enc_val&&enc_val<1000) {
    analogWrite(PWM_R,250);
    digitalWrite(DIR_R,LOW);
  } else {
    analogWrite(PWM_R,0);
    digitalWrite(DIR_R,LOW);
  }*/
}
