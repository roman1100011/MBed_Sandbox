/*this Program acts as a prototype. it dosn't include any PWM modulation nor cours-correcten.
It is built as Step after Step programm, if any step fails the Program feils it shoud proof the concept of the pland roboter
*/
#include "AnalogIn.h"
#include "DigitalIn.h"
#include "DigitalOut.h"
#include "PinNames.h"
#include "mbed.h"
#include "pinmap.h"
#include <cstdint>
#include <cwchar>
#include "PM2_Libary.h"


//arbitrary allocation of pins -> for testing this has to be adjusted
AnalogIn ch0(PA_15); //IR TOF sensor at the front
AnalogIn RearSensor(PC_9); //IR TOF sensor at the back facing down

DigitalOut armMotor(PC_12);
// main() runs in its own thread in the OS
    // Enable the ADC, 12MHz,  the final term should be (2**BURST_CHANNELS - 1)
int ToNextFunction;
float trigerValueRearSensor = 0.0f;
float trigerValueFrontSensor = 0.0f;


//-----------------------------------------actors Definition----------------------------------------------------

//Encoder pin 
EncoderCounter  encoder_M_right(PA_0, PA_1);
EncoderCounter  encoder_M_left(PA_2, PA_3);  //Pin zuweisung Provisorisch!!!

//motor pin
FastPWM pwm_M_right(PA_10);              
FastPWM pwm_M_left(PA_9); 

// create SpeedController and PositionController objects, default parametrization is for 78.125:1 gear box
float max_voltage = 12.0f;                  // define maximum voltage of battery packs, adjust this to 6.0f V if you only use one batterypack
float counts_per_turn = 20.0f * 78.125f;    // define counts per turn at gearbox end: counts/turn * gearratio
float kn = 180.0f / 12.0f;                  // define motor constant in rpm per V
float k_gear = 100.0f / 78.125f;            // define additional ratio in case you are using a dc motor with a different gear box, e.g. 100:1
float kp = 0.1f;                            // define custom kp, this is the default speed controller gain for gear box 78.125:1

//motors for tracks
PositionController positionController_M_right(counts_per_turn * k_gear, kn / k_gear, kp * k_gear, max_voltage, pwm_M_right, encoder_M_right); // parameters adjusted to 100:1 gear, we need a different speed controller gain here
PositionController positionController_M_left(counts_per_turn * k_gear, kn / k_gear, kp * k_gear, max_voltage, pwm_M_left, encoder_M_left); // parameters adjusted to 100:1 gear, we need a different speed controller gain here

//Arm Motor
PositionController positionController_M_Arm(counts_per_turn * k_gear, kn / k_gear, kp * k_gear, max_voltage, pwm_M_right, encoder_M_right); // parameters adjusted to 100:1 gear, we need a different speed controller gain here

//-----------------------------------------Functions----------------------------------------------------------
//only moves the arm in to the starting position
int StartPosition(void){
    if(true){
        return 1;
    }
    return NULL;
}

//Drives forward into the next step
int Drive(int8_t dist){
    int8_t i = 0;         //prov condition variable


    int8_t distance = dist; //distance which will be driven in [mm]
    float factor = 1.0f; //factor for calculating the value in to the float which will be given to the setDesiredRotation function
    float distanceValue = float(distance)*factor;
    do{
        positionController_M_right.setDesiredRotation(distanceValue);
        positionController_M_left.setDesiredRotation(distanceValue);
        i++;
    }while(i < 1);
    return 0;
    
}

//only turns the arm until the robot is on the next step
//not yet clear if the motor controler function drives to a absolute poition or if it drives the given distance relative to the current position
int LiftUp(int8_t deg){
    int8_t rotation = deg;
    int8_t i = 0;         //prov condition variable
    do{
        positionController_M_right.setDesiredRotation(deg);
        
        i++;
    }while(i < 1);
    return 0;
}



    
int main()
{
    while (true) {
        ToNextFunction = StartPosition();
        if(NULL != ToNextFunction){
            ToNextFunction = Drive(3);
            if(NULL != ToNextFunction){
                ToNextFunction = LiftUp(5);
                if(NULL != ToNextFunction){
                    ToNextFunction = Drive(-1);

                }
            }
        }
        
thread_sleep_for(10);
    }
}

