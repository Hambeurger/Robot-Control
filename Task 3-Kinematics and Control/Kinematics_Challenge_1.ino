//Kinematics: Challenge 1,2022.7.18
//Waiting for encUpdate()function,right now just simulating encoder data.
//Delete initial value of N_L,N_R,t,newEnc(int t)function afterwards.

#include<math.h>

#define pi 3.14
#define MAX_POSE 1

int t=2000; //delay time
double T=t/1000.00; //convert to m

typedef class Pose{
  public:
    double *x,*y,*theta;
}pose;

Pose pose_orig; //global variables
const double r=0.05,b=0.20,C=100.00; //Unit in m
//r=radius of wheels,b=wheel to wheel distance,C=encoder resolution(pulses per revolution)

double N_L=0.00,N_R=0.00; //Number of pulses

int count=1;

Pose createPose(double x,double y,double theta){
  Pose pose_c;
  pose_c.x=(double*)malloc(MAX_POSE*sizeof(double));
  pose_c.y=(double*)malloc(MAX_POSE*sizeof(double));
  pose_c.theta=(double*)malloc(MAX_POSE*sizeof(double));
  pose_c.x[0]=x;
  pose_c.y[0]=y;
  pose_c.theta[0]=theta;
  return pose_c;
}

Pose poseUpdate(double N_L,double N_R,double r,double b,double C){
  /*: Returns new pose of the robot based on current number of encoder pulses and the robot’s physical properties.*/
  double D_L,D_R,D; //Linear wheel and robot displacement
  double theta; //Change of rotation angle
  double delta_x,delta_y; //Change of horizontal and vertical distance
  
  //Displacement of each wheel since last iteration
  D_L=(2.00*pi*r)/C*N_L;
  D_R=(2.00*pi*r)/C*N_R;

  /*Serial.print("D_L:");
  Serial.println(D_L);
  Serial.print("D_R:");
  Serial.println(D_R);*/

  //Displacement of robot since last iteration
  D=(D_L+D_R)/2.00;

  /*Serial.print("D:");
  Serial.println(D);*/

  //Orientation(rotation angle) since last iteration
  theta=(D_R-D_L)/b;

  /*Serial.print("theta:");
  Serial.println(theta);*/

  //Change of linear distance since last iteration
  delta_x=D*cos(theta);
  delta_y=D*sin(theta);

  /*Serial.print("delta_x:");
  Serial.println(delta_x);
  Serial.print("delta_y:");
  Serial.println(delta_y)*/

  //Get new position of robot
  pose_orig.x[0]+=delta_x;
  pose_orig.y[0]+=delta_y;
  pose_orig.theta[0]+=theta;

  return pose_orig;
}

void printRobotPose(){
  int convert_angle;
  Serial.println("Right now the robot position is at:");
  
  Serial.print("x:");
  Serial.println(pose_orig.x[0]);
  Serial.print("y:");
  Serial.println(pose_orig.y[0]);
  
  convert_angle=int(pose_orig.theta[0]*180/pi)%360;
  if(convert_angle<0){
    convert_angle+=360;
  }
  Serial.print("Angle:");
  Serial.println(convert_angle);
  
  Serial.println();
}

void newEnc(int t){
  N_L+=200.00;
  N_R+=100.00;
  delay(t);
}

void printEnc(){
  Serial.print("N_L:");
  Serial.println(N_L);
  Serial.print("N_R:");
  Serial.println(N_R);
}

void setup() {
  pose_orig=createPose(0,0,0);
  Serial.begin(9600);
}

void loop() {
  //To be used later.
  //N_L=enc_L.encUpdate(t);
  //N_R=enc_R.encUpdate(t);
  
  Serial.print("Count:");
  Serial.println(count);
  count++;
  
  printEnc();
  
  pose_orig=poseUpdate(N_L,N_R,r,b,C); //substituite the last pose

  printRobotPose();

  newEnc(t);
}
