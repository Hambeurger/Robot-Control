//mySharpIR.h
#ifndef mySharpIR_h
#define mySharpIR_h

#include<Arduino.h>

class SharpIR{
  private:
    int ir_pin;
    long sensor_model;
  public:
  	//constructor
    SharpIR(int irPin,long sensor_model);
    //get distance mm
    float distance(int sensor_num,float med_voltage);
};

#endif
