#pragma once
#include <GL/freeglut.h>
#include"cFigure.h"

class cRectangle : public cFigure {
	double a_, b_;
	double angle_;
	bool taken_;
public:
	cRectangle(double a, double b, double x, double y, double v_x, double v_y, double angle);
	void draw();
	bool isClicked(double openglX, double openglY);
	int isUnclicked(double openglX, double openglY);
	double get_a();
};


