#pragma once
#include <GL/freeglut.h>
#include <cmath>
#include"cFigure.h"

class cCircle : public cFigure {
	double r_;
public:
	cCircle(double r, double x, double y, double v_x, double v_y);
	void draw();
	bool isClicked(double openglX, double openglY);
	int isUnclicked(double openglX, double openglY);
	double get_a();
};