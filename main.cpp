/*this Program acts as a prototype. it dosn't include any PWM modulation nor cours-correcten.
It is built as Step after Step programm, if any step fails the Program feils it shoud proof the concept of the pland roboter
*/


#include "AnalogIn.h"
#include "DigitalIn.h"
#include "DigitalOut.h"
#include "PinNames.h"
#include "mbed.h"
#include "pinmap.h"
#include <cwchar>



//arbitrary allocation of pins -> for testing this has to be adjusted
AnalogIn ch0(PA_15); //IR TOF sensor at the front
AnalogIn RearSensor(PC_9); //IR TOF sensor at the back facing down
DigitalOut FleftMotor(PC_10);
DigitalOut FrightMotor(PC_11);
DigitalOut BrightMotor(PB_15);
DigitalOut BleftMotor(PB_14);
DigitalOut armMotor(PC_12);
// main() runs in its own thread in the OS
    // Enable the ADC, 12MHz,  the final term should be (2**BURST_CHANNELS - 1)
int ToNextFunction;
float trigerValueRearSensor = 0.0f;
float trigerValueFrontSensor = 0.0f;


//only moves the arm in to the starting position
int StartPosition(void){
    if(true){
        return 1;
    }
    return NULL;
}

//Drives forward into the next step
int DriveForward(void){
    if (true) {    
        return 1;
    }
    return 0;
}

//only turns the arm until the robot is on the next step
int LiftUp(void){
    if (true) {
    return 1;
    }
    return 0;
}

//Drives Back until the robot dosn't see a step with the rear senor
int DriveBack(void){
    if(true){
        return 1;
    }
    return 0;
}




    
int main()
{
    while (true) {
        ToNextFunction = StartPosition();
        if(NULL != ToNextFunction){
            ToNextFunction = DriveForward();
            if(NULL != ToNextFunction){
                ToNextFunction = LiftUp();
                if(NULL != ToNextFunction){
                    ToNextFunction = DriveBack();

                }
            }
        }
        

    }
}

