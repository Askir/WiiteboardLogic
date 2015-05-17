// Wiiteboard.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "QuadrangleMorphing.h"
#include "Point.h"
#include <windows.h>
#include "Rectangle.h"
#include <MouseInputDLL.h>
#include "MorphingController.h"
#include "PenAction.h"
#include <array>
#include "InputHandling.h"
#include <random>
#include "WiimoteHandler.h"
#include <conio.h>
#include "MouseMovement.h"
#include "WiimoteMode.h"
WiimoteHandler wh;
unsigned connected;
MorphingController morphcon[8];
MouseMovement mouse;

void CALLBACK intervallMouseControl(
	_In_ PVOID   lpParameter,
	_In_ BOOLEAN TimerOrWaitFired
	){
	wh.refreshWiimotes();
	//int returnvalues[connected][2];
	//for (int i = 0; i < connected; i++){
		
	float data[2];	
	bool visible = wh.getIRData(0, 0, data);
	if (visible){
		Point point = morphcon[0].getNewIRPoint(data[0], data[1]);

		mouse.setMousePosition(point.getX(), point.getY());
		printf("an signal");
	}
		morphcon[0].getNewData(visible);
	//}
	

}

void startMouseControl(){
	HANDLE hTQ = CreateTimerQueue();
	if (hTQ == NULL){
		printf("%x\n", GetLastError());
	}
	else{
		HANDLE hnewTimer;
		CreateTimerQueueTimer(&hnewTimer,
			hTQ,
			&intervallMouseControl,
			NULL,
			500,
			10,
			WT_EXECUTEDEFAULT);
		std::cout << " press a to abort! ";
		char input = _getch();
		if (input == 'a'){
			DeleteTimerQueueTimer(hTQ, hnewTimer, NULL);
			DeleteTimerQueueEx(hTQ, NULL);
		}
	}

}



int _tmain(int argc, _TCHAR* argv[])
{
	//wh.connectFirstWiimote();
	connected = wh.connectWiimotes();
	_tprintf(_T("%u connected \n"), connected);
	WiimoteMode modes[8];
	for (unsigned i = 0; i < connected; i++){
		wh.setLED(i, i);
		bool defined = false;
		while (!defined){
			_tprintf(_T("choose mode for wiimote Number %u \n"), i);
			_tprintf(_T("[w] for wiitboard camera \n [p} for presentation tool \n"));
			char input = _getch();
			if (input == 'w'){
				modes[i] = CAMERA_MODE;
				defined = true;
			}
			else if (input == 'p'){
				modes[i] = PRESENTATION_MODE;
				defined = true;
			}
			else{
				_tprintf(_T("Wrong Button try again:"));
			}
		}

	}
	/**_tprintf(_T("to start calibrating press 'c'"));
	char input = _getch();
	if (input == 'c'){
		bool visible = false;
		while (!visible){
			visible = wh.getIRData
		}
	}**/
	morphcon[0].addCalibrationPoint(0.0, 0.0);
	morphcon[0].addCalibrationPoint(0.0, 1.0);
	morphcon[0].addCalibrationPoint(1.0, 1.0);
	morphcon[0].addCalibrationPoint(1.0, 0.0);
	morphcon[0].finalCalibration();
	wh.setLEDs(15);
	/**while (true){
		float data[2];
		wh.getIRData(0, 0, data);
	}**/
	startMouseControl();
	/**MorphingController morphCon = MorphingController();
	morphCon.addCalibrationPoint(0.0, 0.0);
	morphCon.addCalibrationPoint(0.0, 1.0);
	morphCon.addCalibrationPoint(1.0, 1.0);
	morphCon.addCalibrationPoint(1.0, 0.0);
	morphCon.finalCalibration();
	std::array<bool, 8> leftClickDown = { 0, 0, 0, 0, 0, 1, 1, 1 };
	//{0, 0, 0, 1}
	std::array<bool, 8> leftClickUp = { 0, 1, 1, 1, 0, 0, 0, 0 };
	//{0, 1, 0, 0}
	std::array<bool, 8> rightClickDown = { 0, 0, 0, 1, 1, 1, 0, 0 };
	//{0, 0, 1, 0}
	std::array<bool, 8> rightClickUp = { 0, 0, 0, 1, 1, 1, 1, 1 };
	//{0, 0, 1, 1}
	float x;
	float y;
	for (int i = 0; i < 15; ++i) {
		x = rand() / (float) RAND_MAX;
		std::cout << "X: " << x << "\n";
		y = rand() / (float) RAND_MAX;
		std::cout << "Y: " << y << "\n";
		morphCon.getNewIRPoint(x, y);
		for (int i = 0; i < 8; ++i) {
			std::cout << "RightClickDown@i -> " << rightClickDown.at(i) << "\n";
			morphCon.getNewData(rightClickDown.at(i));
		}
		Sleep(10);
		for (int j = 0; j < 8; ++j) {
			std::cout << "RightClickUp@i -> " << rightClickUp.at(j) << "\n";
			morphCon.getNewData(rightClickUp.at(j));
		}
		Sleep(1000);
		morphCon.getNewIRPoint(x, y);
		for (int i = 0; i < 8; ++i) {
			std::cout << "LeftClickDown@i -> " << leftClickDown.at(i) << "\n";
			morphCon.getNewData(leftClickDown.at(i));
		}
		Sleep(10);
		for (int i = 0; i < 8; ++i) {
			std::cout << "LeftClickUp@i -> " << leftClickUp.at(i) << "\n";
			morphCon.getNewData(leftClickUp.at(i));
		}
		Sleep(1000);
	}
	**\
	/**	InputHandling input = InputHandling();
	std::array<bool, 12> test = { 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1 };
	for (bool b : test) {
	if (input.receiveBit(b)) {
	std::cout << "InputHandling -> PenAction: " << input.analyzePenAction() << "\n";
	}
	} **/


	/**	PenAction penA = LEFT_CLICK_DOWN;
	if (penA == LEFT_CLICK_DOWN) {
	penA = MOUSE_DISCONNECT;
	}
	std::cout << penA;
	Point pointA = Point(27, 18, 0);
	Point pointB = Point(25, 381, 0);
	Point pointC = Point(1023, 50, 0);
	Point pointD = Point(700, 1, 0);
	uschi::Rectangle rectangle = uschi::Rectangle();
	rectangle.addPoint(pointA);
	rectangle.addPoint(pointB);
	rectangle.addPoint(pointC);
	rectangle.addPoint(pointD);
	QuadrangleMorphing morphingOfD00M = QuadrangleMorphing(rectangle);
	morphingOfD00M.startQuadrangleTransformation();
	std::cout << morphingOfD00M.getFinalSquare().getVector().at(2).getX();
	Point point = morphingOfD00M.startPointTransformation(Point(500, 19, 0));
	setPosition(point.getX() * 65565, (1 - point.getY()) * 65565);
	std::cout << point.getX() << " " << point.getY(); **/
	Sleep(30000);
}


