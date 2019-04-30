#include "cCircle.h"

cCircle::cCircle(double r = 2, double x = 0, double y = 0, double v_x = 0, double v_y = 0) :cFigure(x, y, v_x, v_y), r_(r) {

}

void cCircle::draw() {
	glPushMatrix();
	
	glTranslated(x_, y_, 0.0);
	glRotated(0, 1.0, 0.0, 0.0);
	glRotated(0, 0.0, 1.0, 0.0);
	glRotated(0, 0.0, 0.0, 1.0);

	glColor3d(rgb_[0], rgb_[1], rgb_[2]);


	glBegin(GL_LINE_LOOP);
	for (float kat = 0; kat < 360; kat += 10)
	{
		float x, y;
		x = r_ * cos(kat / 180 * 3.14);
		y = r_ * sin(kat / 180 * 3.14);
		glVertex2f(x, y);	
	}
	glEnd();

	glPopMatrix();
}

bool cCircle::isClicked(double openglX, double openglY) {
	if (sqrt(pow(openglX,2) + pow(openglY, 2)) <r_) {
		rgb_[0] = 0.0;
		rgb_[1] = 1.0;
		return true;
	}
	return false;
}

int cCircle::isUnclicked(double openglX, double openglY) {
		rgb_[0] = 1.0;
		rgb_[1] = 0.0;
		return 1;
}

double cCircle::get_a(){
	return r_;
}