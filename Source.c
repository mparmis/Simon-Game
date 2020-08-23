#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<DAQlib.h>
#include<Windows.h>
#include<time.h>

#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3 

#define SWITCH0 0
#define SWITCH1 1
#define SWITCH2 2
#define SWITCH3 3

#define TRUE 1
#define FALSE 0

#define ON 1
#define OFF 0

#define ONE_SEC 1000

#define MAX_SEQUENCE_LENGTH 5

void runSimon(void);
void displayThreeReds(void);
void displayThreeGreens(void);
int extendSequence(int color_sequence[], int index);
int getButtonPressed(void);

int main(void) {
	int systemsetup = 6;
	srand((unsigned)time(NULL));
	if (setupDAQ(systemsetup) == TRUE)
		runSimon();
	else
		printf("ERROR:cannot initialize the system");
	system("PAUSE");
	return 0;
}
void runSimon(void) {
	int game;
	int color_sequence[MAX_SEQUENCE_LENGTH] = { -1,-1,-1,-1,-1 };
	int currentProgress = 0;
	int ButtonPressed[MAX_SEQUENCE_LENGTH];

	while (continueSuperLoop() == TRUE) {

		if (currentProgress == 5) { 
			printf("YOU WON!!!!\n");
			currentProgress = 0;
			displayThreeGreens();
			Sleep(ONE_SEC * 2);
		}
		if (currentProgress == -1) {
			printf("YOU LOST...\n");
			currentProgress = 0;
			displayThreeReds();
			Sleep(ONE_SEC * 2); 
		}
		extendSequence(color_sequence, currentProgress);
		for (int i = 0; i <= currentProgress; i++) {
			Sleep(ONE_SEC / 2);
			digitalWrite(color_sequence[i], ON);
			Sleep(ONE_SEC / 2);
			digitalWrite(color_sequence[i], OFF);
		}
		int keyPress = 0;
		while (keyPress <= currentProgress) {
			if (color_sequence[keyPress] != getButtonPressed()) { 
				currentProgress = -2;
			}
			keyPress++;
		}
		currentProgress++;
	}
}

void displayThreeReds(void) {

	for (int i = 0; i < 3; i++) {
		Sleep(ONE_SEC / 2);
		digitalWrite(LED1, ON);
		Sleep(ONE_SEC / 2);
		digitalWrite(LED1, OFF);
	}
}

void displayThreeGreens() {
	
	for (int i = 0; i < 3; i++) {
		Sleep(ONE_SEC / 2);
		digitalWrite(LED0, ON);
		Sleep(ONE_SEC / 2);
		digitalWrite(LED0, OFF);
	}
}
int extendSequence(int color_sequence[], int index) {
	color_sequence[index] = rand() % 4;
}
int getButtonPressed(void) {
	int returnval = -1;
	while (TRUE) {
		int switch0 = digitalRead(SWITCH0);
		int switch1 = digitalRead(SWITCH1);
		int switch2 = digitalRead(SWITCH2);
		int switch3 = digitalRead(SWITCH3);
		if (switch0 == ON) {
			while (TRUE) {
				if (digitalRead(SWITCH0) == OFF) { return 0; }
			}
		}

		else if (switch1 == ON)
			while (TRUE) {
				if (digitalRead(SWITCH1) == OFF) { return 1; }
			}

		else if (switch2 == ON)
			while (TRUE) {
				if (digitalRead(SWITCH2) == OFF) { return 2; }
			}

		else if (switch3 == ON)
			while (TRUE) {
				if (digitalRead(SWITCH3) == OFF) { return 3; }
			}
	}
	return returnval;
}