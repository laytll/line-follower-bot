# bot

[Line Sensor](https://thepihut.com/products/infrared-line-tracking-sensor)
[Motor + Encoder](https://thepihut.com/products/tt-motor-with-encoder-6v-160rpm-120-1)
[Motor Driver](https://thepihut.com/products/3a-4v-16v-2-channel-dc-motor-driver?srsltid=AfmBOooJRuBS1QQOaZZq5TR9B4TiwWkcg4vQccNKIH4ld3PLLN18atic)

# TODO
- [x] define pins

# pindef
```c
#define MOTOR_1_FORE D11    // --> Cytron p.1 (M1A)
#define MOTOR_2_FORE D10    // --> Cytron p.5 (M2A)
#define MOTOR_1_BACK D9     // --> Cytron p.2 (M1B)
#define MOTOR_2_BACK D6     // --> Cytron p.6 (M2B)

#define MOTOR_1_ENC_A D4    // --> Motor 1 p.3
#define MOTOR_1_ENC_B D2    // --> Motor 1 p.4, int0 fixed to D2 on Uno
#define MOTOR_2_ENC_A D5    // --> Motor 2 p.3
#define MOTOR_2_ENC_B D3    // --> Motor 2 p.4, int1 fixed to D3 on Uno
                            
#define IR_LL D19           // --> Sensor p.3 (IR1)
#define IR_LM D18           // --> Sensor p.4 (IR2)
#define IR3_M D17           // --> Sensor p.5 (IR3)
#define IR4_RM D16          // --> Sensor p.6 (IR4)
#define IR5_RR D15          // --> Sensor p.7 (IR5)
```


