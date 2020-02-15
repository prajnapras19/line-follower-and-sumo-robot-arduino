/***************************************************************************************
* ARDUINO LINE FOLLOWER AND SUMO (BLUETOOTH CONTROLLED) ROBOT                          *
* CODERS:                                                                              *
* ALMER RASHAD                                                                         *
* PRAJNA                                                                               *
* R. W. ANDHIKA                                                                        *
* WAHIB ADIYATMA                                                                       *
*                                                                                      *
* Reference:                                                                           *
* https://www.instructables.com/id/How-to-use-the-L293D-Motor-Driver-Arduino-Tutorial/ *
* https://create.arduino.cc/projecthub/robocircuits/line-follower-robot-arduino-299bae *
* https://www.youtube.com/watch?v=Q36NbjPMV5k                                          *
* https://www.youtube.com/watch?v=t7k9D1jDEtk                                          *
* https://create.arduino.cc/projecthub/samanfern/bluetooth-controlled-car-d5d9ca       *
****************************************************************************************/

//Note for Prajna: to upload the code to arduino, write this permission in terminal $sudo chmod a+rw /dev/ttyUSB0

//Motor A (right)
#define motor_pin_1 5  // Pin 14 of L293
#define motor_pin_2 6  // Pin 10 of L293
//Motor B (left)
#define motor_pin_3 10 // Pin  7 of L293
#define motor_pin_4 9  // Pin  2 of L293

//photosensor IR
#define left_sensor_pin A0
#define right_sensor_pin A1

//baud_rate
#define baud_rate 9600

void setup(){
    //Set pins as inputs
    pinMode(left_sensor_pin, INPUT);
    pinMode(right_sensor_pin,INPUT);
    
    //Set pins as outputs
    pinMode(motor_pin_1, OUTPUT);
    pinMode(motor_pin_2, OUTPUT);
    pinMode(motor_pin_3, OUTPUT);
    pinMode(motor_pin_4, OUTPUT);
    Serial.begin(baud_rate);
}

void motorAClockwise(int speed){
    analogWrite(motor_pin_1,0);
    analogWrite(motor_pin_2,speed);
}

void motorACounterClockwise(int speed){
    analogWrite(motor_pin_1,speed);
    analogWrite(motor_pin_2,0);
}

void motorBClockwise(int speed){
    analogWrite(motor_pin_3,0);
    analogWrite(motor_pin_4,speed);
}
void motorBCounterClockwise(int speed){
    analogWrite(motor_pin_3,speed);
    analogWrite(motor_pin_4,0);
}

void stop(){
    motorAClockwise(0);
    motorBClockwise(0);
}

void forward(int speed){
    motorAClockwise(speed);
    motorBCounterClockwise(speed);
}

void backward(int speed){
    motorACounterClockwise(speed);
    motorBClockwise(speed);
}

void turnLeft(int speed){
    motorAClockwise(speed);
    motorBClockwise(speed);
}

void turnRight(int speed){
    motorACounterClockwise(speed);
    motorBCounterClockwise(speed);
}

void forwardRight(int speed){
    motorAClockwise(speed/2);
    motorBCounterClockwise(speed);
}

void forwardLeft(int speed){
    motorAClockwise(speed);
    motorBCounterClockwise(speed/2);
}

void backwardRight(int speed){
    motorACounterClockwise(speed/2);
    motorBClockwise(speed);
}

void backwardLeft(int speed){
    motorACounterClockwise(speed);
    motorBClockwise(speed/2);
}

bool isBlack(int sensor){
    return sensor<500;
}

void lineFollower(){
    //speed is from 0 to 255
    int left_sensor=analogRead(left_sensor_pin);
    int right_sensor=analogRead(right_sensor_pin);
    if (!isBlack(left_sensor) && !isBlack(right_sensor)){
        forward(180);
    }
    else if (isBlack(left_sensor) && !isBlack(right_sensor)){
        turnLeft(100);
    }
    else if (!isBlack(left_sensor) && isBlack(right_sensor)){
        turnRight(100);
    }
    else{
        stop();
    }
}

bool isNumber(char c){
    if (((int)c)<48 || ((int)c)>57){
        return 0;
    }
    return 1;
}

int num(char c){
    return ((int)c) - 48;
}

int speed_now=0;
void sumo(char command){
    //speed is from 0 to 255
    if (isNumber(command)){
        speed_now=25*num(command)+5;
    }
    else{
        switch(command){
            case 'F':
                forward(speed_now);
                break;
            case 'B':
                backward(speed_now);
                break;
            case 'L':
                turnLeft(speed_now);
                break;
            case 'R':
                turnRight(speed_now);
                break;
            case 'G':
                forwardLeft(speed_now);
                break;
            case 'I':
                forwardRight(speed_now);
                break;
            case 'H':
                backwardLeft(speed_now);
                break;
            case 'J':
                backwardRight(speed_now);
                break;
            case 'q':
                speed_now=255;
                break;
            default:
                stop();
        }
    }
}

char tmp = 'x';
bool is_X = 0;
void play(){
    //if you use the robot as sumo robot, call sumo(char $command)
    //if you use the robot as line follower robot, call lineFollower()
    if (Serial.available()){
        tmp = Serial.read();
    }
    if (tmp=='x'){
        is_X=0;
    }
    if (tmp=='X'){
        is_X=1;
    }
    if (is_X){
        lineFollower();
    }
    else{
        sumo(tmp);
    }
}

void loop(){
    play();
}
