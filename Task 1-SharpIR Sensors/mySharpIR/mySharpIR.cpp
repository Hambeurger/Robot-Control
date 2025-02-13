//mySharpIR.cpp
/*Function of left sensor:
middle sensor:
right sensor:*/

#include<mySharpIR.h>
#include<math.h>


SharpIR::SharpIR(int ir_pin,long sensor_model){
	ir_pin=ir_pin;
	sensor_model=sensor_model;
	pinMode(ir_pin,INPUT);
	#ifdef ARDUINO
		analogReference(DEFAULT);
	#endif
}

float SharpIR::distance(int sensor_num,float med_voltage){
	float distance_mm;
	float e=2.7183;
	
	switch(sensor_num){
		case 1:
			distance_mm=10*37.143*pow(e,(-0.465)*med_voltage);
			break;
		case 2:
			distance_mm=10*35.534*pow(e,(-0.527)*med_voltage);
			break;
		case 3:
			distance_mm=10*38.177*pow(e,(-0.561)*med_voltage);
			break;
		default:
			Serial.println("Something is wrong.");
			exit(0);
	}
	
	return distance_mm;
}