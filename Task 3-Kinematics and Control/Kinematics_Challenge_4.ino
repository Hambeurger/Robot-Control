//Kinematics Challenge 4: PID Control Test

#include<math.h>

#define pi 3.14
#define MAX_POSE 1

int t=100; //delay time
double T=t/1000.00; //convert to m

typedef class Pose{
  public:
    double *x,*y,*theta,*w_L,*w_R;
}pose;

typedef struct Dest_vel{
  double dest_V,dest_W; //Desired linear and angular velocity to reach given pose
};

typedef struct W_wheels{
  double w_L,w_R; //Angular velocity of two wheels
};

Pose pose_orig; //global variables
Pose pose_dest;
const double r=0.05,b=0.20,C=100.00; //Unit in m
//r=radius of wheels,b=wheel to wheel distance,C=encoder resolution(pulses per revolution)

Dest_vel dest_vel;
W_wheels w_wheels,w_wheels_dest;

//Just a simulation
double eps_P,eps_P_new,eps_D,eps_I=0;
double KP=1.00,KD=0.025,KI=0.00;
double G;

double N_L=0.00,N_R=0.00; //Number of pulses

long int count=1;

Pose createPose(double x,double y,double theta){
  Pose pose_c;
  pose_c.x=(double*)malloc(MAX_POSE*sizeof(double));
  pose_c.y=(double*)malloc(MAX_POSE*sizeof(double));
  pose_c.theta=(double*)malloc(MAX_POSE*sizeof(double));
  pose_c.w_L=(double*)malloc(MAX_POSE*sizeof(double));
  pose_c.w_R=(double*)malloc(MAX_POSE*sizeof(double));
  pose_c.x[0]=x;
  pose_c.y[0]=y;
  pose_c.theta[0]=theta;
  pose_c.w_L[0]=0;
  pose_c.w_R[0]=0;
  return pose_c;
}

Dest_vel cmd_vel(){
  //Returns the desired linear and angular velocities
  double alpha_dest,theta_dest;
  
  //The objective orientation
  alpha_dest=atan((pose_dest.y[0]-pose_orig.y[0])/(pose_dest.x[0]-pose_orig.x[0]));
  Serial.print("Alpha_dest:");
  Serial.println(alpha_dest);
  
  //The necessary rotation in order to put robot in the goal orientation(limit above pi/2)
  theta_dest=alpha_dest-pose_orig.theta[0];
  Serial.print("Theta_dest:");
  Serial.println(theta_dest);
  
  //How to calculate the necessary robot's linear and angular velocity??? ppt p.38 step 4
  dest_vel.dest_V=theta_dest*2.00;
  dest_vel.dest_W=theta_dest*3.00;

  return dest_vel;
}

W_wheels cmd_vel2wheels(double V,double W){
  //Converts the linear and angular velocities to wheels angular velocities
  w_wheels.w_L=(V-b/2.00*W)/r;
  w_wheels.w_R=(V+b/2.00*W)/r;
  return w_wheels;
}

Pose poseUpdate(double N_L,double N_R,double r,double b,double C){
  /*: Returns new pose of the robot based on current number of encoder pulses and the robot’s physical properties.*/
  double D_L,D_R,D; //Linear wheel and robot displacement
  double V,W; //Angular and linear velocity of robot
  double theta; //Change of rotation angle
  
  //Displacement of each wheel since last iteration
  D_L=(2.00*pi*r)/C*N_L;
  D_R=(2.00*pi*r)/C*N_R;

  //Displacement of robot since last iteration
  D=(D_L+D_R)/2.00;

  //Calculate real linear and angular velocity of robot
  V=D/T;
  W=(D_L-D_R)/(b*T);

  //Calculate change in position and orientation
  theta=atan2(sin(theta+W*t),cos(theta+W*t));

  //Calculate angular velocity of two wheels
  w_wheels=cmd_vel2wheels(V,W);

  //Get new position of robot
  pose_orig.x[0]+=V*cos(theta)*T;
  pose_orig.y[0]+=V*sin(theta)*T;
  pose_orig.theta[0]=theta;
  pose_orig.w_L[0]=w_wheels.w_L;
  pose_orig.w_R[0]=w_wheels.w_R;

  Serial.println(pose_orig.w_L[0]);
  Serial.println(pose_orig.w_R[0]);

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

void encFunc()
{
  count++;
}

void newEnc(int t){
  N_L=2.00;
  N_R=5.00;
  delay(t);
}

double pid_controller(W_wheels w_wheels_dest,W_wheels w_wheels){
  eps_P_new=w_wheels_dest.w_L*(-w_wheels.w_R)-w_wheels_dest.w_R*(-w_wheels.w_L);
  Serial.println(eps_P_new);
  eps_D=eps_P_new-eps_P;
  Serial.println(eps_D);
  eps_I=eps_I+eps_P_new;
  Serial.println(eps_I);
  eps_P=eps_P_new;

  G=KP*eps_P+KI*eps_I*T+KD*eps_D/T;

  return G;
}

void setup() {
  pose_orig=createPose(0,0,0);
  pose_dest=createPose(5,8,26); //use a random destination pose for test

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(3),encFunc,CHANGE);
  
  dest_vel=cmd_vel(); //Give the robot a desired linear and angular velocities

  Serial.print("Desired robot V:");
  Serial.println(dest_vel.dest_V);
  Serial.print("Desired robot W:");
  Serial.println(dest_vel.dest_W);
  

  w_wheels_dest=cmd_vel2wheels(dest_vel.dest_V,dest_vel.dest_W); //Calculate the desired angular velocities of the wheels,
  
  Serial.print("Desired left wheel w:");
  Serial.println(w_wheels_dest.w_L);
  Serial.print("Desired right wheel w:");
  Serial.println(w_wheels_dest.w_R);
  Serial.println();
}

void loop() {
  if(millis()%t==0){
    pose_orig=poseUpdate(N_L,N_R,r,b,C); //Calculate the real angular velocities of the wheels and update robot pose

    float g=pid_controller(w_wheels_dest,w_wheels);
    
    Serial.print("This is G:");
    Serial.println(g);
    Serial.println();
    //printRobotPose();
    
    newEnc(t);
  }
  /*while(pose_orig.x[0]!=pose_dest.x[0]&&pose_orig.y[0]!=pose_dest.y[0]){
    poseUpdate(N_L,N_R,r,b,C);
    
    printRobotPose();
    
    newEnc(t);
  }
  Serial.println("Destination reached.");*/
}
