#ifndef MAIN_H
#define MAIN_H

#define MOTOR_1_FORE 11    // --> Cytron p.1 (M1A)
#define MOTOR_2_FORE 10    // --> Cytron p.5 (M2A)
#define MOTOR_1_BACK 9     // --> Cytron p.2 (M1B)
#define MOTOR_2_BACK 6     // --> Cytron p.6 (M2B)

#define MOTOR_1_ENC_A 4    // --> Motor 1 p.3
#define MOTOR_1_ENC_B 2    // --> Motor 1 p.4, int0 fixed to D2 on Uno
#define MOTOR_2_ENC_A 5    // --> Motor 2 p.3
#define MOTOR_2_ENC_B 3    // --> Motor 2 p.4, int1 fixed to D3 on Uno

#define IR_LL A1           // --> Sensor p.3 (IR1)
#define IR_LM A2           // --> Sensor p.4 (IR2)
#define IR_M A3           // --> Sensor p.5 (IR3)
#define IR_RM A4          // --> Sensor p.6 (IR4)
#define IR_RR A5          // --> Sensor p.7 (IR5)

#define S_STOP 1
#define S_FORWARD 2
#define S_MOVING 3
#define S_TURN_LEFT 4
#define S_TURN_RIGHT 5
#define S_TURNING 6

#define MOTOR_ON 128
#define MOTOR_OFF 0

#define ROBOT_FORE 'F'
#define ROBOT_STOP 'S'
#define ROBOT_LEFT 'L'
#define ROBOT_RIGHT 'R'

#define NUM_SENSORS 5

#define SEN_READ_B 600
#define SEN_READ_W 300
#define SEN_DIFF_PER 25

#define ON_BLACK 1
#define OFF_BLACK 0

#endif
