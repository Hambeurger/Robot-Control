//myEncoder.h

#ifndef myEncoder_h
#define myEncoder_h

#include<Arduino.h>

class Encoder{
  private:
    int enc_1,enc_2; //Assign the two encoder pins
  public:
  	//Constructor
    Encoder(int enc_1,int enc_2);
    
    //Get the current number of encoder pulses, at iteration t
    int getEncUpdate(int t);
    //Use the return value of this function to control motor movement
};

#endif