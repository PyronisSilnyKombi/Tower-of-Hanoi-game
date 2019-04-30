#include "cRectangle.h"

cRectangle::cRectangle(double a=2, double b=2, double x=0, double y=0, double v_x = 0, double v_y = 0, double angle= 0) :cFigure(x, y, v_x, v_y), a_(a), b_(b), angle_(angle) {
	taken_ = 0;
}

void cRectangle::draw() {
	glPushMatrix();

	glTranslated(x_, y_, 0.0);
	glRotated(angle_, 1.0, 0.0, 0.0);
	glRotated(angle_, 0.0, 1.0, 0.0);
	glRotated(angle_, 0.0, 0.0, 1.0);

	glColor3d(rgb_[0], rgb_[1], rgb_[2]);

	glBegin(GL_POLYGON);
	{
		glVertex3d(-a_ / 2, b_ / 2, 0);
		glVertex3d(a_ / 2, b_ / 2, 0);
		glVertex3d(a_ / 2, -b_ / 2, 0);
		glVertex3d(-a_ / 2, -b_ / 2, 0);
	}
	glEnd();
	glPopMatrix();
}

bool cRectangle::isClicked(double openglX, double openglY) {	
	if (static_) return false;
	if (openglX <(x_ + (a_ / 2)) && openglX >(x_ - (a_ / 2)) && openglY < (y_ + (b_ / 2)) && openglY >(y_ - (b_ / 2))) {
		rgb_[0] = 0.0;
		rgb_[1] = 1.0;
		return true;
	}
	taken_ = 1;
	return false;
}

int cRectangle::isUnclicked(double openglX, double openglY) {
	if (static_) return 0;
	if (openglX <(x_ + (a_ / 2)) && openglX >(x_ - (a_ / 2)) && openglY < (y_ + (b_ / 2)) && openglY >(y_ - (b_ / 2))) {
		rgb_[0] = 1.0;
		rgb_[1] = 0.0;
		/*return true;*/
	}
	if (/*taken_ = 1 && */ openglX > -1 && openglX < 1 && openglY > - 8 && openglY < 4) {
		static_ = 0;
		return 2;
		/*x_ = 0;
		y_ = -7;*/
	}
	if (/*taken_ = 1 &&*/ openglX > 5 && openglX < 7 && openglY > -8 && openglY < 4) {
		static_ = 0;
		return 3;
		/*x_ = 6;
		y_ = -7;*/
	}
	if (/*taken_ = 1 && */openglX < -5 && openglX > -7 && openglY > -8 && openglY < 4) {
		static_ = 0;
		return 1;
		/*x_ = -6;
		y_ = -5;*/
	}
	if (/*taken_ = 1 && */!((openglX > -1 && openglX < 1 && openglY > -8 && openglY < 4) || (openglX > 5 && openglX < 7 && openglY > -8 && openglY < 4) || (openglX < -5 && openglX > -7 && openglY > -8 && openglY < 4))) {
		static_ = 0;
		return 4;
		/*x_ = -6;
		y_ = -5;*/
	}
	taken_ = 0;
	return 0;
}

double cRectangle::get_a() {
	return a_;
}