#define PWM_L 9 //motor 1 speed control,analog
#define DIR_L 6 //motor 1 direction control,digital
#define PWM_R 4 //motor 2 speed control,analog
#define DIR_R 5 //motor 2 direction control,digital

#define SPEED 255 //Max speed

int option;

void setup()
{
  pinMode(PWM_L,OUTPUT);
  pinMode(DIR_L,OUTPUT);
  pinMode(PWM_R,OUTPUT);
  pinMode(DIR_R,OUTPUT);

  Serial.begin(9600);

  Serial.println("Go forward-1; Go back-2; Turn left-3; Turn right-4");
  
  while (Serial.available()==0){
    option=Serial.parseInt();
  }
}

void loop()
{
  switch(option){
    case 1:
      Serial.println("Go forward.");
      analogWrite(PWM_L,SPEED);
      digitalWrite(DIR_L,LOW);
      analogWrite(PWM_R,SPEED);
      digitalWrite(DIR_R,LOW);
      delay(10000);
      break;
    case 2:
      Serial.println("Go back.");
      analogWrite(PWM_L,SPEED);
      digitalWrite(DIR_L,HIGH);
      analogWrite(PWM_R,SPEED);
      digitalWrite(DIR_R,HIGH);
      delay(10000);
      break;
    case 3:
      Serial.println("Turn left.");
      analogWrite(PWM_L,SPEED);
      digitalWrite(DIR_L,HIGH);
      analogWrite(PWM_R,SPEED);
      digitalWrite(DIR_R,LOW);
      delay(10000);
      break;
    case 4:
      Serial.println("Turn right.");
      analogWrite(PWM_L,SPEED);
      digitalWrite(DIR_L,LOW);
      analogWrite(PWM_R,SPEED);
      digitalWrite(DIR_R,HIGH);
      delay(10000);
      break;
    default:
      Serial.println("Input error.");
      break;
    Serial.println("Program end.");
  }

  /*This was the previous test code
   * 
  Serial.println("Forward fast.");
  digitalWrite(DIR1,LOW);
  digitalWrite(DIR2,LOW);
  analogWrite(PWM1,value_fast);   
  analogWrite(PWM2,value_fast);   

  
  Serial.println(digitalRead(encoder_a_1));
  Serial.println(digitalRead(encoder_a_2));
  Serial.println(digitalRead(encoder_b_1));
  Serial.println(digitalRead(encoder_b_2));
  delay(3000);
  
  Serial.println("Backward fast.");
  digitalWrite(DIR1,HIGH);
  digitalWrite(DIR2,HIGH);
  analogWrite(PWM1,value_fast);   
  analogWrite(PWM2,value_fast);   

  Serial.println(digitalRead(encoder_a_1));
  Serial.println(digitalRead(encoder_a_2));
  Serial.println(digitalRead(encoder_b_1));
  Serial.println(digitalRead(encoder_b_2));
  
  delay(3000);

  Serial.println("Turn.");
  digitalWrite(DIR1,HIGH);
  digitalWrite(DIR2,HIGH);
  analogWrite(PWM1,255);
  analogWrite(PWM2,0);

  Serial.println(digitalRead(encoder_a_1));
  Serial.println(digitalRead(encoder_a_2));
  Serial.println(digitalRead(encoder_b_1));
  Serial.println(digitalRead(encoder_b_2));
  
  delay(3000);
  */
}
