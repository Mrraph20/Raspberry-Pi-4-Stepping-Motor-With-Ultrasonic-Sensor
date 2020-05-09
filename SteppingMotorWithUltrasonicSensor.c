/*
Made by: Christopher Milian 
Purpose: To control Stepping Motor Rotation Direction with Ultrasonic Sensor
Started: 5/8/2020
Completed: 
*/

#include <stdio.h>
#include <wiringPi.h>
#include <sys/time.h>

#define trigPin 4 // GPIO 23      
#define echoPin 5  //GPIO 24
#define MAX_DISTANCE 220        // Define the maximum measured distance
#define timeOut MAX_DISTANCE*60 // Calculate timeout according to the maximum measured distance

const int motorPins[]={1,0,4,6};  // GPIO 18,17,23,25 // Define pins connected to four phase ABCD of stepper motor 
const int CCWStep[]={0x01,0x02,0x04,0x08};  // Define power supply order for coil for rotating anticlockwise 
const int CWStep[]={0x08,0x04,0x02,0x01};   // Define power supply order for coil for rotating clockwise

// Movement per Power Supply Direction
void moveOnePeriod(int dir,int ms){  // Motor: For four phase step motor, four steps is a cycle. 
    int i=0,j=0;                        // The function is used to drive the stepping motor clockwise or anticlockwise to take four steps.
    for (j=0;j<4;j++){      // Cycle according to power supply order 
        for (i=0;i<4;i++){  // Assigning to each pin, a total of 4 pins
            if(dir == 1)    
                digitalWrite(motorPins[i],(CCWStep[j] == (1<<i)) ? HIGH : LOW);  // Power supply order clockwise
            else  
                digitalWrite(motorPins[i],(CWStep[j] == (1<<i)) ? HIGH : LOW);  // Power supply order anticlockwise
        }
        if(ms<3)  // The delay cannot be less than 3ms, otherwise it will exceed speed limit of the motor
            ms=3;
        delay(ms);
    }
}
// Movement
void moveSteps(int dir, int ms, int steps){  // Motor: Continuous rotation function, 
    int i;                                     // the parameter steps specifies the rotation cycles, every four steps is a cycle
    for(i=0;i<steps;i++){
        moveOnePeriod(dir,ms);
    }
}
// Movement
void motorStop(){  // Motor: Function used to stop rotating
    int i;
    for(i=0;i<4;i++){
        digitalWrite(motorPins[i],LOW);
    }   
}
// Calculations
int pulseIn(int pin, int level, int timeout)  // Sensor: Function pulseIn: obtain pulse time of a pin
{
   struct timeval tn, t0, t1;
   long micros;
   gettimeofday(&t0, NULL);
   micros = 0;
   while (digitalRead(pin) != level)
   {
      gettimeofday(&tn, NULL);
      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;
      micros += (tn.tv_usec - t0.tv_usec);
      if (micros > timeout) return 0;
   }
   gettimeofday(&t1, NULL);
   while (digitalRead(pin) == level)
   {
      gettimeofday(&tn, NULL);
      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;
      micros = micros + (tn.tv_usec - t0.tv_usec);
      if (micros > timeout) return 0;
   }
   if (tn.tv_sec > t1.tv_sec) micros = 1000000L; else micros = 0;
   micros = micros + (tn.tv_usec - t1.tv_usec);
   return micros;
}
// Calculations
float getSonar(){   // Sensor: Get the measurement result of ultrasonic module with unit: cm
    long pingTime;
    float distance;
    digitalWrite(trigPin,HIGH); // Send 10us high level to trigPin 
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);
    pingTime = pulseIn(echoPin,HIGH,timeOut);   // Read plus time of echoPin
    distance = (float)pingTime * 340.0 / 2.0 / 10000.0; // Calculate distance with sound speed 340m/s
    return distance;
}

int main(){
    int i;
    float distance = 0;
    wiringPiSetup();
    pinMode(trigPin,OUTPUT); 
    pinMode(echoPin,INPUT);

    for(i=0;i<4;i++){
        pinMode(motorPins[i],OUTPUT);
    } 

    printf("Stepping motor and sensor are initializing.\n");

    /*
    while(1){
        distance = getSonar();
        printf("The distance is : %.2f cm\n",distance);
    
        moveSteps(1,3,512);  // Rotating 360° clockwise, a total of 2048 steps in a circle, namely, 512 cycles. 2048/4 = 512
        delay(500);
        moveSteps(0,3,512);  // Rotating 360° anticlockwise
        delay(500);
    }
    */

    while(1){

        if ((distance < 20) && (distance > 0)){  //Motor stops
            printf("The distance is : %.2f cm\n",distance);
            printf("Too close, stopping motor.\n");
            motorStop();
        }
        else{                //Motor goes clockwise
            printf("The distance is : %.2f cm\n",distance);
            printf("Good distance, resuming motor.\n");
            moveOnePeriod(1,3);
        }
    }
    return 0;
}