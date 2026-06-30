/**
   TODO
   Finish state machine
   define interrupt routine, when we want to track steps taken
   add debug printouts
   have a sensor calibration function, on start. y = (x - Min) * 1000 / (Max - Min) to normalise reading accross all sensors.

*/

#include "main.h"

int state = S_STOP; //init the state machine

int sensor_val[5] = {0, 0, 0, 0, 0};
int sensor_last_val[5] = {0, 0, 0, 0, 0};
int sensor_pins[5] = {IR_LL, IR_LM, IR_M, IR_RM, IR_RR};
bool monitoring = true; //locks the state of sesnor_state so it can be used for moving
int sensor_state = '0';

int mmove(int direction); //done
int readSensor(int* store, int* pins, int * store_last);
int processSensor(int* store, int* store_last);
void isr_motor_1();
void isr_motor_2();

int mmove(int direction) {
  switch (direction) {
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

// do rudementry an A --> D converstion based on a threashold
int readSensor(int* store, int* pins, int * store_last) {

  // store a reading, and move current reading to last reading
  int tmp[NUM_SENSORS];
  for (int i = 0; i < NUM_SENSORS; i++) {
    tmp[i] = analogRead(sensor_pins[i]);
    store_last[i] = store[i];
  }
  // assign on Black or not on Black
  for (int i = 0; i < NUM_SENSORS; i++) {
    if (tmp[i] > SEN_READ_B) {
      store[i] = ON_BLACK;
    } else if (tmp[i] > SEN_READ_W) {
      store[i] = OFF_BLACK;
    }

  }
  return 0;
}

// 
int processSensor(int* store, int* store_last) {

  //#define ROBOT_FORE 'F'
  //#define ROBOT_STOP 'S'
  //#define ROBOT_LEFT 'L'
  //#define ROBOT_RIGHT 'R'

  // if ![0], left
  // if ![4], right
  // if [2], go
  // if none, stop

    if (store[4] == ON_BLACK){ // right sensor
      return 'R';
    } else if (store[0] == ON_BLACK){ // left sensor
      return 'L';
    } else if (store[2] == ON_BLACK ){ // front sensor
      return 'F';
    } else{
      return 'S'; // all else fails, stop
    }
  }



void isr_motor_1() {

}


void isr_motor_2() {

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

  pinMode(IR_LL, INPUT);
  pinMode(IR_LM, INPUT);
  pinMode(IR_M, INPUT);
  pinMode(IR_RM, INPUT);
  pinMode(IR_RR, INPUT);

  attachInterrupt(digitalPinToInterrupt(0), isr_motor_1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(1), isr_motor_2, CHANGE);

  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(sensor_pins[i], INPUT);
  }

}

void loop() {

  delay(500); //gives us a chance to track it's thinking

  readSensor(sensor_val, sensor_pins, sensor_last_val);
  while (monitoring) {
    sensor_state = processSensor(sensor_val, sensor_last_val);
  }
  switch (state) {
    case S_STOP:
      mmove(ROBOT_STOP); //ensure its actually stopped
      if (sensor_state == ROBOT_FORE) {
        state = S_FORWARD;
        monitoring = false;
      }
      break;

    case S_FORWARD: //monitoring off
      mmove(sensor_state);
      state = S_MOVING;
      break;

    case S_MOVING: // hopefully, it stays here most of the time
      monitoring = true;
      // wait for L, R, S
      switch (sensor_state) {
        case ROBOT_LEFT: // LL Sensor On
          monitoring = false;
          state = S_TURN_LEFT;
          break;
        case ROBOT_RIGHT: // RR Sensor On
          monitoring = false;
          state = S_TURN_RIGHT;
          break;
        case ROBOT_STOP: // M Sensor Off
          monitoring = false;
          state = S_STOP;
          break;
        default:
          // LEFT, RIGHT, STOP not found
          break;
      }
      break;

    case S_TURN_LEFT:
      mmove(sensor_state);
      state = S_TURNING;
      break;

    case S_TURN_RIGHT:
      mmove(sensor_state);
      state = S_TURNING;
      break;

    case S_TURNING:
      monitoring = true;
      if (sensor_state == ROBOT_FORE) { // there is a chance it could get sticky here, might be able to hack with a forced delay after move. 
        mmove(sensor_state);
        state = S_MOVING;
      }
      break;

    default:
      mmove(ROBOT_STOP);
      break;

  }

}
