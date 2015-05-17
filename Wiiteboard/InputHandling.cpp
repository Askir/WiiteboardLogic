#include "stdafx.h"
#include <iostream>
#include "InputHandling.h"
#include <array>


std::array<bool, 4> LEFT_CLICK_DOWN_NIBBLE = { 0, 0, 0, 1 };
std::array<bool, 4> LEFT_CLICK_UP_NIBBLE = { 0, 1, 0, 0 };
std::array<bool, 4> RIGHT_CLICK_DOWN_NIBBLE = { 0, 0, 1, 0 };
std::array<bool, 4> RIGHT_CLICK_UP_NIBBLE = { 0, 0, 1, 1 };
std::array<bool, 4> MOUSE_DISCONNECT_NIBBLE = { 0, 0, 0, 0 };

//returns true if the 8 Bit limit is reached
bool InputHandling::receiveBit(bool bit) {
	if (!startBitReceived) {
		startBitReceived = !bit;
	}
	if (startBitReceived) {
		byte[bitCounter] = bit;
		if (bitCounter >= 7) {
			bitCounter = 0;
			startBitReceived = false;
			readFrame();
			return true;
		}
		bitCounter++;
		return false;
	}
	return false;
}

void InputHandling::readFrame() {
	bool lastBit = byte[0];
	int counter = 0;
	int byteIndex = 0;
	int index = 0;
	for (bool b : byte) {
		if (b == lastBit && byteIndex < 7) {
			counter++;
		}
		else {
			if (byteIndex == 7) {
				counter++;
			}
			if (lastBit) {
				counter = (counter - (counter % 2)) / 2;
			}
			else {
				counter = (counter + (counter % 2)) / 2;
			}
			int curIndex = index;
			for (; index < curIndex + counter; ++index) {
				std::cout << "Index: " << index;
				nibble[index] = lastBit;
			}
			if (lastBit && byteIndex % 2 == 1) {
				counter = 1;
			}
			else if (byteIndex % 2 == 1) {
				counter = 0;
			}
			else {
				counter = 1;
			}
		}
		byteIndex++;
		lastBit = b;
	}
}

PenAction InputHandling::analyzePenAction() {
	for (bool b : nibble) {
		std::cout << "\n" << "Nibble: " << b << "\n";
	}
	if (nibble == LEFT_CLICK_DOWN_NIBBLE) {
		penAction = LEFT_CLICK_DOWN;
	}
	else if (nibble == LEFT_CLICK_UP_NIBBLE) {
		penAction = LEFT_CLICK_UP;
	}
	else if (nibble == RIGHT_CLICK_DOWN_NIBBLE) {
		penAction = RIGHT_CLICK_DOWN;
	}
	else if (nibble == RIGHT_CLICK_UP_NIBBLE) {
		penAction = RIGHT_CLICK_UP;
	}
	else if (nibble == MOUSE_DISCONNECT_NIBBLE) {
		penAction = MOUSE_DISCONNECT;
	}
	else {
		penAction = MOVE_MOUSE;
	}
	return penAction;
}

PenAction InputHandling::getPenAction() {
	return analyzePenAction();
}



InputHandling::~InputHandling()
{}