#pragma once
#include "cRectangle.h"
#include "cCircle.h"
#include "cFigure.h"
#include <vector>

void resize_binding(int width, int height);
void idle_binding();
void display_binding();
void key_binding(unsigned char key, int x, int y);
void mouse_binding(int button, int state, int x, int y);
void mouse_move_binding(int x, int y);


class cScene {
	std::vector<cFigure*> figures;
	std::vector<cFigure*> first;
	std::vector<cFigure*> second;
	std::vector<cFigure*> third;
	int active_id_;
	int amount_of_disks_;
	std::pair<double , double> previous_coords_;
	int previous_position_;
	bool left_button_down;

public:
	cScene();
	void resize(int width, int height);
	void idle();
	void display();
	void init(int argc, char **argv, const char* window_name);
	void set_callbacks();
	void key(unsigned char key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void mouse_move(int x, int y);

	void conditions(double openglX, double openglY, cFigure* el, bool& block_moved_);

	void set_disks();
	void add_disks();
};