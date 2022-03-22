#include "AnalogIn.h"
#include "DigitalOut.h"
#include "PinNames.h"
#include "mbed.h"
AnalogIn ch0(PA_15);
DigitalOut FleftMotor(PC_10);
DigitalOut FrightMotor(PC_11);
DigitalOut BrightMotor(PB_15);
DigitalOut BleftMotor(PB_14);
DigitalOut armMotor(PC_12);
// main() runs in its own thread in the OS
    // Enable the ADC, 12MHz,  the final term should be (2**BURST_CHANNELS - 1)
int ToNextFunction;

int StartPosition(void);
int DriveForward(void);
int LiftUp(void);
int DriveBack(void);




    
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

