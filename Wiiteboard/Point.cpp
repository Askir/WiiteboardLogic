#include "stdafx.h"
#include "Point.h"

class Point {
	private:
		double x;
		double y;
		double z;

	Point::Point() {}
	Point::Point(double x, double y, double z)
	{
			this->x = x;
			this->y = y;
			this->z = z;
	}

	void setX(double x) {
		this->x = x;
	}

	double getX() {
		return this->x;
	}

	void setY(double y) {
		this->y = y;
	}

	double getY() {
		return this->y;
	}

	void setZ(double z) {
		this->z = z;
	}

	double getZ() {
		return this->z;
	}

	Point::~Point()
	{
	}
};