#include <iostream>
#define NDEBUG
#include <GL/freeglut.h>
#include "cScene.h"

cScene scena;

void resize_binding(int width, int height) {
	scena.resize(width, height);
}

void key_binding(unsigned char key, int x, int y) {
	scena.key(key, x, y);
}

void idle_binding() {
	scena.idle();
}

void display_binding() {
	scena.display();
}

void mouse_binding(int button, int state, int x, int y)
{
	scena.mouse(button, state, x, y);
}

void mouse_move_binding(int x, int y) {
	scena.mouse_move(x, y);
}

int main(int argc, char *argv[])
{
	scena.set_disks();
	scena.add_disks();
	scena.init(argc, argv, "Hanoi");

	return 0;
}