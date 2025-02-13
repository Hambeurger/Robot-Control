/*Use the three new functions to write customized library, use the new library to convert analog data to distance.
This is the code that reads the three IR sensors and converts their measurements in millimetres*/

//Position and sensor number check: IR1-A2-Left,IR2-A3-Middle,IR3-A4-Right

// Include the custom library:
#include"mySharpIR.h"

// Define model and input pin:
#define IRPin1 A2
#define IRPin2 A3
#define IRPin3 A4
#define model 1080 //GP2Y0A21YK0F
#define voltage_sample 10

// Create variable to store distance and input number:
float distance_mm;
int sensor_num;
float med_voltage;

/* Model: GP2Y0A21YK0F --> 1080 */

// Create new instance of the SharpIR class:
SharpIR mySensor1=SharpIR(IRPin1, model);
SharpIR mySensor2=SharpIR(IRPin2, model);
SharpIR mySensor3=SharpIR(IRPin3, model);

float getMedVoltage(int ir_pin)
//Function to convert analogRead and output voltage
{
  float med_voltage;
  int sensor_value[voltage_sample],med_sensor_value;
  
  for(int i=0;i<voltage_sample;i++){
    sensor_value[i]=analogRead(ir_pin);
    med_sensor_value+=sensor_value[i];
  }

  med_sensor_value=med_sensor_value/voltage_sample;
  med_voltage=med_sensor_value*(5.0/1023.0);
  
  return med_voltage;
}

void setup() {
  // Begin serial communication at a baudrate of 9600:
  Serial.begin(9600);
  
  Serial.println("Enter test sensor number(range 1-3):");
  Serial.println("Note:1,2,3-left,middle,right");
  
  while (Serial.available()==0) //waiting for user input
  {
    sensor_num=Serial.parseInt();
  }
}

void loop() {
  Serial.print("Testing sensor n.");
  Serial.println(sensor_num);
  
  switch(sensor_num)
  {
    case 1:
        med_voltage=getMedVoltage(A2);
        distance_mm = mySensor1.distance(sensor_num,med_voltage);
  
        // Print the measured distance to the serial monitor:
        Serial.print("Mean distance left sensor: ");
        Serial.print(distance_mm);
        Serial.println(" mm");

        //these two lines are for test
        Serial.print("Medium Voltage is:");
        Serial.print(med_voltage);
        Serial.println("");
        break;
        
     case 2:
        med_voltage=getMedVoltage(A3);
        distance_mm = mySensor2.distance(sensor_num,med_voltage);
  
        Serial.print("Mean distance middle sensor: ");
        Serial.print(distance_mm);
        Serial.println(" mm");
  
        Serial.print("Medium Voltage is:");
        Serial.print(med_voltage);
        Serial.println("");
        break;

      case 3:
        med_voltage=getMedVoltage(A4);
        distance_mm = mySensor3.distance(sensor_num,med_voltage);
  
        Serial.print("Mean distance right sensor: ");
        Serial.print(distance_mm);
        Serial.println(" mm");
  
        Serial.print("Medium Voltage is:");
        Serial.print(med_voltage);
        Serial.println("");
        break;

      default:
        Serial.println("Error.");
        break;
  }
        delay(1000);   
}
