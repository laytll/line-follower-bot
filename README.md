# bot

[Line Sensor](https://thepihut.com/products/infrared-line-tracking-sensor)
[Motor + Encoder](https://thepihut.com/products/tt-motor-with-encoder-6v-160rpm-120-1)
[Motor Driver](https://thepihut.com/products/3a-4v-16v-2-channel-dc-motor-driver?srsltid=AfmBOooJRuBS1QQOaZZq5TR9B4TiwWkcg4vQccNKIH4ld3PLLN18atic)

# TODO
- [x] define pins
- [x] Sensor Implementation
- [x] implement code of the state machine
- [ ] Debug printouts

# pindef
```c
see main.h for pindef
```

## Interim Functionality
The robot will move forward only, handling left and right turns.  
No logging of track taken, but will give us a chance to check the data.  

|state      |action                             |next state |
|-----------|-----------------------------------|-----------|
|OFF        |Power applied                      | STOP      |
|STOP       |M or RM or LM  sensor on           | FORWARD   |
|FORWARD    |Both motors forward                | MOVING    |
|MOVING     |LL sensor on                       | TURN_LEFT |
|MOVING     |RR sensor on                       | TURN_RIGHT|
|MOVING     |M sensor off                       | STOP      |
|TURN_LEFT  |left motor off, right motor on     | TURNING   |
|TURN_RIGHT |right motor off, left motor on     | TURNING   |
|TURNING    |LL and RR off                      | STOP      |



