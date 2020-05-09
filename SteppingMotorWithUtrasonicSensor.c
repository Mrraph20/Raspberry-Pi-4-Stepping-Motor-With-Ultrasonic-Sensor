
#include <stdio.h>
#include <wiringPi.h>

const int motorPins[]={1,4,5,6};            // Define pins connected to four phase ABCD of stepper motor 
const int CCWStep[]={0x01,0x02,0x04,0x08};  // Define power supply order for coil for rotating anticlockwise 
const int CWStep[]={0x08,0x04,0x02,0x01};   // Define power supply order for coil for rotating clockwise

// As for four phase stepping motor, four steps is a cycle. the function is used to drive the stepping motor clockwise or anticlockwise to take four steps
void moveOnePeriod(int dir,int ms){
    int i=0,j=0;
    for (j=0;j<4;j++){      // Cycle according to power supply order 
        for (i=0;i<4;i++){  // Assign to each pin, a total of 4 pins
            if(dir == 1)    // Power supply order clockwise
                digitalWrite(motorPins[i],(CCWStep[j] == (1<<i)) ? HIGH : LOW);
            else  // Power supply order anticlockwise
                digitalWrite(motorPins[i],(CWStep[j] == (1<<i)) ? HIGH : LOW);
            printf("motorPin %d, %d \n",motorPins[i],digitalRead(motorPins[i]));
        }
        printf("Step cycle!\n");
        if(ms<3)  // The delay can not be less than 3ms, otherwise it will exceed speed limit of the motor
            ms=3;
        delay(ms);
    }
}


void moveSteps(int dir, int ms, int steps){  // Continuous rotation function, 
    int i;                                     // the parameter steps specifies the rotation cycles, every four steps is a cycle
    for(i=0;i<steps;i++){
        moveOnePeriod(dir,ms);
    }
}

void motorStop(){  // Function used to stop rotating
    int i;
    for(i=0;i<4;i++){
        digitalWrite(motorPins[i],LOW);
    }   
}

int main(void){
    int i;

    printf("Stepping motor is initializing.\n");

    wiringPiSetup();
    
    for(i=0;i<4;i++){
        pinMode(motorPins[i],OUTPUT);
    } 

    while(1){
        moveSteps(1,3,512);  // Rotating 360° clockwise, a total of 2048 steps in a circle, namely, 512 cycles.
        delay(500);
        moveSteps(0,3,512);  // Rotating 360° anticlockwise
        delay(500);
    }
    return 0;
}

