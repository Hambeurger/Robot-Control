/*Use SharpIR library to get analogRead voltage, hand measure distance, make voltage-distance data chart, 
generate three new functions from graph (for each sensor)*/

//Position and sensor number check: IR1-A2-Left,IR2-A3-Middle,IR3-A4-Right

// Include the library:
#include<SharpIR.h>

// Define model and input pin:
#define IRPin1 A2
#define IRPin2 A3
#define IRPin3 A4
#define model 1080 //GP2Y0A21YK0F according to documentation

// Create variable to store distance and input number:
int distance_cm;
int sensor_num;
int sensor_value;
float voltage_output;

// Create new instance of the SharpIR class:
SharpIR mySensor1 = SharpIR(IRPin1, model);
SharpIR mySensor2 = SharpIR(IRPin2, model);
SharpIR mySensor3 = SharpIR(IRPin3, model);

//Function to convert analogRead and output voltage
void outputVoltage(int sensor_value)
{
  float voltage_output=sensor_value*(5.0/1023.0);
  Serial.print("Output voltage is:");
  Serial.println(voltage_output);
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
      // Get a distance measurement and store it as distance_cm:
      distance_cm = mySensor1.distance();

      // Print the measured distance to the serial monitor:
      Serial.print("Mean distance left sensor: ");
      Serial.print(distance_cm);
      Serial.println(" cm");

      //Output the voltage to serial monitor
      sensor_value=analogRead(A2);
      outputVoltage(sensor_value);

      break;
        
     case 2:
        // Apply same method to other two sensors.
        distance_cm = mySensor2.distance();
        Serial.print("Mean distance middle sensor: ");
        Serial.print(distance_cm);
        Serial.println(" cm");
        sensor_value=analogRead(A3);
        outputVoltage(sensor_value);
        break;

      case 3:
        distance_cm = mySensor3.distance();
        Serial.print("Mean distance right sensor: ");
        Serial.print(distance_cm);
        Serial.println(" cm");
        sensor_value=analogRead(A4);
        outputVoltage(sensor_value);
        break;

      default:
        Serial.println("Error.");
        break;
  }
        delay(1000);   
}
