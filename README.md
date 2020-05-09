# Control Stepping Motor Rotation with Ultrasonic Sensor Using C and a Raspberry Pi 4B

###### This project is not complete yet. Repo set up for file transfer convenience. 

A project based on C that uses a Raspberry Pi 4B Rev. 1.2 board to make a stepping motor move clockwise or stop entirely depending on the distance calculated from the ultrasonic sensor. 
For GPIO pin mapping, I used WiringPi (Made by Gordon Henderson under GNU-LGPL) to simplify. 
Link: http://wiringpi.com/

**WiringPi Note: The author has discontinued public releases of WiringPi. The last update was 2.52 for the Raspberry Pi 4B.** 
Although WiringPi is preinstalled on Raspbian systems, the code for installation is as follows:
```
sudo apt-get install wiringpi
```
Use:
```
gpio -v
```
to check if your version is 2.52.

For more details visit http://wiringpi.com/download-and-install/

To upgrade, visit http://wiringpi.com/wiringpi-updated-to-2-52-for-the-raspberry-pi-4b/

Hardware components used:
- (1) 4 pin Ultrasonic Sensor 5VDC (HC-SR04) 
- (1) Step Motor 28BYJ-48 5VDC
- (1) ULN2003 Stepping motorDriver
- (10) Female to Male Jumper Cable
- (1) Male to Male Jumper Cable 
- (1) Breadboard powersupply 
- (1) Breadboard
- (1) 12V 2.5A AC Adapter (Used for the breadboard power supply)
- Raspberry Pi 4B Rev. 1.2

When compiling the code, run the following commands in terminal at the location of the file:
```
sudo bash
gcc SteppingMotorWithUltrasonicSensor.c -o SteppingMotorWithUltrasonicSensor -lwiringPi 
./SteppingMotorWithUltrasonicSensor
```

This project was possible through an electronics kit I purchased from Freenove that provided me
with all of the components I used. If interested, it is the "Freenove Ultrasonic Starter Kit for Raspberry Pi" (FNK0024).