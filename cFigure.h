#pragma once
#include <GL/freeglut.h>

class cFigure {
protected:
	double x_, y_;
	double v_x_, v_y_;
	float rgb_[3];
	bool static_;
public:
	cFigure(double x = 0.0, double y = 0.0, double v_x=0.0, double v_y = 0.0);
	virtual void draw() = 0;
	void move(double dx, double dy);
	void rotate_clockwise();
	void speed_up_x(const float& val);
	void speed_up_y(const float& val);
	void slow_down_x(const float& val);
	void slow_down_y(const float& val);
	virtual bool isClicked(double openglX, double openglY) = 0;
	virtual int isUnclicked(double openglX, double openglY) = 0;
	void follow (double dx, double dy);
	void set_color(double r, double g, double b);
	void set_static(bool x);
	void set_x_y(double x, double y);
	double get_x();
	double get_y();
	virtual double get_a() = 0;
};