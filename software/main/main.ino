/**
 * TODO
 * Define how to infer position from array number sensor
 * Finish state machine
 * define interrupt routine
 * add debug printouts
 * Implement readSensor, the processSensor
 * have a sensor calibration, on start
 * 
 */

#include "main.h"

int state = S_STOP; //init the state machine

int sensor_val[5] = {0,0,0,0,0};
int sensor_last_val[5] {0,0,0,0,0};
int sensor_pins[5] = {IR_LL, IR_LM, IR_M, IR_RM, IR_RR};
bool monitoring = true; //locks the state of sesnor_state so it can be used for moving
int sensor_state = '0';

int move(int direction); //done
int readSensor(int* store, int* pins);
int processSensor(int* store, int* store_last);
void isr_motor_1();
void isr_motor_2();

int move(int direction){
    switch(direction){
      case 'F':
        analogWrite(MOTOR_1_FORE, MOTOR_ON);
        analogWrite(MOTOR_2_FORE, MOTOR_ON);
        break;
        
      case 'L': //left
        analogWrite(MOTOR_1_FORE, MOTOR_ON);
        analogWrite(MOTOR_2_FORE, MOTOR_OFF);
        break;
      
      case 'R': //right    
        analogWrite(MOTOR_1_FORE, MOTOR_OFF);
        analogWrite(MOTOR_2_FORE, MOTOR_ON);
        break;
      
      case 'S':
        analogWrite(MOTOR_1_FORE, MOTOR_OFF);
        analogWrite(MOTOR_2_FORE, MOTOR_OFF);
        break; 
        
      default:
        analogWrite(MOTOR_1_FORE, MOTOR_OFF);
        analogWrite(MOTOR_2_FORE, MOTOR_OFF);
        break;
    }
    return 0;
  }

// potentially do the A --> D conversion, and high~low conversion here before processSensor
// https://www.waveshare.com/wiki/Tracker_Sensor
int readSensor(int* store, int* pins){
  for(int i=0;i<NUM_SENSORS;i++){ sensor_val[i] = analogRead(sensor_pins[i]); }
  return 0;
}

// WIP
int processSensor(int* store, int* store_last){  

  //#define ROBOT_FORE 'F'
  //#define ROBOT_STOP 'S'
  //#define ROBOT_LEFT 'L'
  //#define ROBOT_RIGHT 'R'

  int ret = 0;
  int higher_last[NUM_SENSORS] = {0,0,0,0,0};

  // if [0], left
  // if [4], right
  // if [3], go
  // if none, stop
  
  //flag if the last value is higher or lower by SEN_DIFF_PER 
  for (int i=0; i < NUM_SENSORS; i++){
    }
  

  for (int i=0; i < NUM_SENSORS; i++){
  }
  
  return ret;
  }

void isr_motor_1(){
  
  }

 
void isr_motor_2(){
  
  }
  

void setup() {

  pinMode(MOTOR_1_FORE, OUTPUT);
  pinMode(MOTOR_2_FORE, OUTPUT);
  pinMode(MOTOR_1_BACK, OUTPUT);
  pinMode(MOTOR_2_BACK, OUTPUT);

  pinMode(MOTOR_1_ENC_A, INPUT);
  pinMode(MOTOR_1_ENC_B, INPUT); // isr0
  pinMode(MOTOR_2_ENC_A, INPUT);
  pinMode(MOTOR_2_ENC_B, INPUT); // isr1

  attachInterrupt(digitalPinToInterrupt(0), isr_motor_1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(1), isr_motor_2, CHANGE);

  for(int i=0;i<NUM_SENSORS;i++){ pinMode(sensor_pins[i], INPUT); }

}

void loop() {

  readSensor(sensor_val, sensor_pins);
  while (monitoring){
    sensor_state = processSensor(sensor_val, sensor_last_val);
  }
  switch(state){
    case S_STOP:
      move(ROBOT_STOP);
      if(sensor_state == ROBOT_FORE){
        state = S_FORWARD;
        monitoring = false;
      }
      break;
      
    case S_FORWARD: //monitoring off
      move(sensor_state);
      state = S_MOVING;
      break;
      
    case S_MOVING:
      monitoring = true;
      processSensor(sensor_val, sensor_last_val);
      // wait for L, R, S
      switch(sensor_state){
        case ROBOT_LEFT:
          monitoring = false;
          state = S_TURN_LEFT;
          break;
        case ROBOT_RIGHT:
          monitoring = false;
          state = S_TURN_RIGHT;
          break;
        case ROBOT_STOP:
          monitoring = false;
          state = S_STOP;
          break;          
      }
      break;
    
    case S_TURN_LEFT:
      move(sensor_state);
      state = S_TURNING;
      break;
    
    case S_TURN_RIGHT:
      move(sensor_state);
      state = S_TURNING;
      break;
    
    case S_TURNING:
      monitoring = true;
      if (sensor_state == ROBOT_FORE){
        move(sensor_state);
        state = S_MOVING;
      }
      break;
    
    default:
      move(ROBOT_STOP);
      break;
    
    }

}
