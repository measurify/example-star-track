#include <pigpio.h>
#include <stdlib.h>
#include <unistd.h>

//Define motor pins
#define PIN_1 1
#define PIN_2 7
#define PIN_3 8
#define PIN_4 25

//Define switch pins
#define SWITCH 24

//Define camera button pin
#define BUTTON 6

//Define led pin
#define LED 16

//Define boolean variables to move motor
#define TRACK 1
#define REWIND 0

void controlMotor();
void controlCamera();
void doStep(int step);
void moveMotor(int direction); //Direction: 1 counterclockwise (track), 0 clockwise (reset)

int step = 0; //(can assume 0 to 7 values)
	      //Keeps track of motor steps,
	      //motor has 4096 steps per revolutions

int main(){
	gpioInitialise();

	//Defining pin modes
	gpioSetMode(PIN_1, PI_OUTPUT);
	gpioSetMode(PIN_2, PI_OUTPUT);
	gpioSetMode(PIN_3, PI_OUTPUT);
	gpioSetMode(PIN_4, PI_OUTPUT);
	gpioSetMode(SWITCH, PI_INPUT);
	gpioSetMode(BUTTON, PI_INPUT);
	gpioSetMode(LED, PI_OUTPUT);

	if(fork() == 0)
		controlMotor();
	else
		controlCamera();

	gpioTerminate();
	return 0;
}

void controlMotor(){

	int countStep = 0; //Counts steps done while tracking
			   //to reset motor later
	int trackDelay = 15723; //Almost 64 steps per second (15723 us per step)
	int rewindDelay = 900;	//max velocity

	while(1){
		//if switch button is on move motor to track.
		if(gpioRead(SWITCH)){
			moveMotor(TRACK);
			countStep++;
			gpioDelay(trackDelay);
		}
		//if switch button is off move motor to rewind,
		//then wait to track again
		else if(countStep > 0){
			moveMotor(REWIND);
			countStep--;
			gpioDelay(rewindDelay);
		}
	}
}

void controlCamera(){
	while(1){
		int button_state = gpioRead(BUTTON);
		gpioWrite(LED, 0); //Turn off led when finished shooting

		if(button_state == 0){
			gpioWrite(LED, 1); //Turn on led while shooting photos
			system("sudo /home/pi/Desktop/StarTrackercode/setupCamera.sh");
			system("sudo /home/pi/Desktop/StarTrackerCode/setParameters.sh");

			for(int i=0; i<10; i++){ //To make 5 photos in a row
				system("sudo /home/pi/Desktop/StarTrackerCode/capture.sh"); //Shoot a photo and wait for it to be saved on the camera
			}
		}
	}
}

void moveMotor(int direction){
	if(direction){
		doStep(step);
		step--; //to move counterclockwise
		if(step < 0)
			step = 7;
	}
	else{
		doStep(step);
		step++; //to move clockwise
		if(step > 7)
			step = 0;
	}

}

void doStep(int step){
	switch(step){
	case 0:
		gpioWrite(PIN_1, 1);
		gpioWrite(PIN_2, 0);
		gpioWrite(PIN_3, 0);
		gpioWrite(PIN_4, 1);
		break;

	case 1:
		gpioWrite(PIN_1, 1);
		gpioWrite(PIN_2, 0);
		gpioWrite(PIN_3, 0);
		gpioWrite(PIN_4, 0);
		break;

	case 2:
		gpioWrite(PIN_1, 1);
		gpioWrite(PIN_2, 1);
		gpioWrite(PIN_3, 0);
		gpioWrite(PIN_4, 0);
		break;

	case 3:
		gpioWrite(PIN_1, 0);
		gpioWrite(PIN_2, 1);
		gpioWrite(PIN_3, 0);
		gpioWrite(PIN_4, 0);
		break;

	case 4:
		gpioWrite(PIN_1, 0);
		gpioWrite(PIN_2, 1);
		gpioWrite(PIN_3, 1);
		gpioWrite(PIN_4, 0);
		break;

	case 5:
		gpioWrite(PIN_1, 0);
		gpioWrite(PIN_2, 0);
		gpioWrite(PIN_3, 1);
		gpioWrite(PIN_4, 0);
		break;

	case 6:
		gpioWrite(PIN_1, 0);
		gpioWrite(PIN_2, 0);
		gpioWrite(PIN_3, 1);
		gpioWrite(PIN_4, 1);
		break;

	case 7:
		gpioWrite(PIN_1, 0);
		gpioWrite(PIN_2, 0);
		gpioWrite(PIN_3, 0);
		gpioWrite(PIN_4, 1);
		break;

	default:
		gpioWrite(PIN_1, 0);
		gpioWrite(PIN_2, 0);
		gpioWrite(PIN_3, 0);
		gpioWrite(PIN_3, 0);
		break;
	}
	return;
}
