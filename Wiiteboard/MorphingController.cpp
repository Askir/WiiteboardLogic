#include "stdafx.h"
#include "MorphingController.h"
#include "MouseMovement.h"
#include <iostream>




MorphingController::MorphingController()
{
	quadrangleMorphing = QuadrangleMorphing();
	mouseMovement = MouseMovement();
	inputHandling = InputHandling();
	calibrationRectangle = Rectangle();
}

bool MorphingController::addCalibrationPoint(float x, float y) {
	if (calibrationRectangle.getVector().size() <= 4) {
		calibrationRectangle.addPoint(Point(x * MorphingController::WIIMOTE_CAMERA_WIDTH, y * MorphingController::WIIMOTE_CAMERA_HEIGHT, 0));
		return true;
	}
	return false;
}

void MorphingController::resetCalibration() {
	calibrationRectangle = Rectangle();
}

bool MorphingController::deleteLastCalibrationPoint() {
	std::vector<Point> rectanglePoints = calibrationRectangle.getVector();
	if (rectanglePoints.size() > 0) {
		calibrationRectangle.getVector().pop_back();
		return true;
	}
	return false;
}

bool MorphingController::finalCalibration() {
	if (calibrationRectangle.getVector().size() == 4) {
		quadrangleMorphing.setMorphableQuadrangle(calibrationRectangle);
		quadrangleMorphing.startQuadrangleTransformation();
		return true;
	} 
	return false;

}

void MorphingController::getNewData(bool bitValue) {
	PenAction penAction = MOVE_MOUSE;
	if (inputHandling.receiveBit(bitValue)) {
		penAction = inputHandling.getPenAction();
	} 
	executeMouseAction(lastPoint, penAction);
}

void MorphingController::getNewIRPoint(float x, float y) {
	Point point = quadrangleMorphing.startPointTransformation(Point(x * MorphingController::WIIMOTE_CAMERA_WIDTH, y * MorphingController::WIIMOTE_CAMERA_HEIGHT, 0));
	std::cout << quadrangleMorphing.getFinalSquare().isInsideOf(point);
	if (quadrangleMorphing.getFinalSquare().isInsideOf(point)) {
		lastPoint = point;
	}

}

void MorphingController::executeMouseAction(Point mousePoint, PenAction penAction) {
	mouseMovement.setMousePosition(mousePoint.getX() * 65665, mousePoint.getY() * 65665);
	mouseMovement.executePenAction(penAction);
}

MorphingController::~MorphingController()
{
}
