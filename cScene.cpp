#include "cScene.h"
#include <iostream>

cScene::cScene() {
	active_id_ = 0;
	left_button_down = 0;
	cFigure *k1 = new cRectangle(1, 12, -6, -2, 0, 0, 0);
	k1->set_color(0.7, 0.3, 0.0);
	k1->set_static(1);
	figures.push_back(k1);
	cFigure *k2 = new cRectangle(1, 12, 0, -2, 0, 0, 0);
	k2->set_color(0.7, 0.3, 0.0);
	k2->set_static(1);
	figures.push_back(k2);
	cFigure *k3 = new cRectangle(1, 12, 6, -2, 0, 0, 0);
	k3->set_color(0.7, 0.3, 0.0);
	k3->set_static(1);
	figures.push_back(k3);
	cFigure *k4 = new cRectangle(18, 1, 0, -8, 0, 0, 0);
	k4->set_color(0.7, 0.3, 0.0);
	k4->set_static(1);
	figures.push_back(k4);
}

void cScene::resize(int width, int height) {
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
	//gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	glOrtho(-10, 10, -10, 10, -1, 1);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void cScene::idle() {
	glutPostRedisplay();
}

void cScene::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	{
		for (int i = 0; i<4;i++)
			figures[i]->draw();
		for (auto& el : first)
			el->draw();
		for (auto& el : second)
			el->draw();
		for (auto& el : third)
			el->draw();
	}
	glPopMatrix();
	glutSwapBuffers();
}

void cScene::set_callbacks() {
	glutDisplayFunc(display_binding);
	glutReshapeFunc(resize_binding);
	glutMotionFunc(mouse_move_binding);
	glutMouseFunc(mouse_binding);
	glutKeyboardFunc(key_binding);
	glutIdleFunc(idle_binding);
}

void cScene::init(int argc, char **argv, const char *window_name) {

	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(40, 40);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glutCreateWindow(window_name);
	glClearColor(1, 1, 1, 1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	set_callbacks();

	glutMainLoop();
}

void cScene::key(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		figures[active_id_]->move(0, 0.1);
		break;
	case 's':
		figures[active_id_]->move(0, -0.1);
		break;
	case 'a':
		figures[active_id_]->move(-0.1, 0.0);
		break;
	case 'd':
		figures[active_id_]->move(0.1, 0.0);
		break;
	case '+':
		if (figures.size() - 1 > active_id_) active_id_++;
		break;
	case '-':
		if (0 < active_id_) active_id_--;
		break;
	case 'o': {
		cFigure *o = new cCircle(0.5, 0, 0, 0, 0);
		figures.push_back(o);
		break;
	}
	case 'p': {
		cFigure *k = new cRectangle(2, 1, 0, 0, 0, 0, 0);
		figures.push_back(k);
		break;
	}
	case 'l': {
		glPushMatrix();
		figures[active_id_]->rotate_clockwise();
		glPopMatrix();
		break;
	}
	case 'm' :{
		figures[active_id_]->speed_up_x(0.001);
		break;
	}
	case 'n': {
		figures[active_id_]->speed_up_y(0.001);
		break;
	}
	case 'b': {
		figures[active_id_]->slow_down_x(0.001);
		break;
	}
	case 'v': {
		figures[active_id_]->slow_down_y(0.001);
		break;
	}
	}
}

void cScene::conditions(double openglX, double openglY, cFigure* el, bool& block_moved_) {
	/*switch (el->isUnclicked(openglX, openglY)) {
	case 1: {
		if (!first.empty())
			if (el->get_a() < first.back()->get_a()) {
				el->set_x_y(-6, -5);
				first.push_back(el);
				switch (previous_position_) {
				case 1:
					first.pop_back();
					break;
				case 2:
					second.pop_back();
					break;
				case 3:
					third.pop_back();
					break;
				}
				if (!second.empty())
					second.back()->set_static(0);
				if (!third.empty())
					third.back()->set_static(0);

			}
		block_moved_ = true;
		break;
	}
	case 2: {
		if (!second.empty())
			if (el->get_a() < second.back()->get_a()) {
				el->set_x_y(0, -7);
				second.push_back(el);
				switch (previous_position_) {
				case 1:
					first.pop_back();
					break;
				case 2:
					second.pop_back();
					break;
				case 3:
					third.pop_back();
					break;
				}
				if (!first.empty())
					first.back()->set_static(0);
				if (!third.empty())
					third.back()->set_static(0);
			}
		block_moved_ = true;
		break;
	}
	case 3: {
		if (!third.empty())
			if (el->get_a() < third.back()->get_a()) {
				el->set_x_y(6, -7);
				third.push_back(el);
				switch (previous_position_) {
				case 1:
					first.pop_back();
					break;
				case 2:
					second.pop_back();
					break;
				case 3:
					third.pop_back();
					break;
				}
				if (!second.empty())
					second.back()->set_static(0);
				if (!first.empty())
					first.back()->set_static(0);
			}
		block_moved_ = true;
		break;
	}
	case 4: {
		el->set_x_y(previous_coords_.first, previous_coords_.second);

		if (!first.empty())
			first.back()->set_static(0);
		if (!second.empty())
			second.back()->set_static(0);
		if (!third.empty())
			third.back()->set_static(0);
		break;
	}
	}
	left_button_down = 0;*/
}

void cScene::mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		double openglX = ((double)x - 400) / 800 * 20;
		double openglY = (-(double)y + 300) / 600 * 20;
		for (auto& el : first) {
			if (el->isClicked(openglX, openglY) == 1) {
				this->left_button_down = el->isClicked(openglX, openglY);
				previous_coords_ = std::make_pair(el->get_x(), el->get_y());
				previous_position_ = 1;
				el->isClicked(openglX, openglY);
				if (!second.empty())
				second.back()->set_static(1);
				if (!third.empty())
				third.back()->set_static(1);
			}
		}
		for (auto& el : second) {
			if (el->isClicked(openglX, openglY) == 1) {
				this->left_button_down = el->isClicked(openglX, openglY);
				previous_coords_ = std::make_pair(el->get_x(), el->get_y());
				previous_position_ = 2;
				el->isClicked(openglX, openglY);
				if (!first.empty())
				first.back()->set_static(1);
				if (!third.empty())
				third.back()->set_static(1);
			}
		}
		for (auto& el : third) {
			if (el->isClicked(openglX, openglY) == 1) {
				this->left_button_down = el->isClicked(openglX, openglY);
				previous_coords_ = std::make_pair(el->get_x(), el->get_y());
				previous_position_ = 3;
				el->isClicked(openglX, openglY);
				if (!second.empty())
				second.back()->set_static(1);
				if (!first.empty())
				first.back()->set_static(1);
			}
		}
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		double openglX = ((double)x - 400) / 800 * 20;
		double openglY = (-(double)y + 300) / 600 * 20;
		bool block_moved = false;
		for (auto& el : first) {
			switch (el->isUnclicked(openglX, openglY)) {
			case 1: {
				float top_block_width = 1000;
				if (!first.empty())
					top_block_width = first.back()->get_a();
				if (el->get_a() < top_block_width) {
					int capacity = first.size();
					el->set_x_y(-7, capacity - 7);
					first.push_back(el);
					switch (previous_position_) {
					case 1:
						first.pop_back();
						break;
					case 2:
						second.pop_back();
						break;
					case 3:
						third.pop_back();
						break;
					}
					if (!second.empty())
						second.back()->set_static(0);
					if (!third.empty())
						third.back()->set_static(0);

				}
				else {
					el->set_x_y(previous_coords_.first, previous_coords_.second);

					if (!first.empty())
						first.back()->set_static(0);
					if (!second.empty())
						second.back()->set_static(0);
					if (!third.empty())
						third.back()->set_static(0);
				}
				block_moved = true;
				break;
			}
			case 2: {
				float top_block_width = 1000;
				if (!second.empty())
					top_block_width = second.back()->get_a();
				if (el->get_a() < top_block_width) {
					int capacity = second.size();
						el->set_x_y(0, capacity - 7);
						second.push_back(el);
						switch (previous_position_) {
						case 1:
							first.pop_back();
							break;
						case 2:
							second.pop_back();
							break;
						case 3:
							third.pop_back();
							break;
						}
						if (!first.empty())
							first.back()->set_static(0);
						if (!third.empty())
							third.back()->set_static(0);
					}
				else {
					el->set_x_y(previous_coords_.first, previous_coords_.second);

					if (!first.empty())
						first.back()->set_static(0);
					if (!second.empty())
						second.back()->set_static(0);
					if (!third.empty())
						third.back()->set_static(0);
				}
				block_moved = true;
				break;
			}
			case 3: {
				float top_block_width = 1000;
				if (!third.empty())
					top_block_width = third.back()->get_a();
				if (el->get_a() < top_block_width) {
					int capacity = third.size();
					el->set_x_y(6, capacity - 7);
					third.push_back(el);
					switch (previous_position_) {
					case 1:
						first.pop_back();
						break;
					case 2:
						second.pop_back();
						break;
					case 3:
						third.pop_back();
						break;
					}
					if (!second.empty())
						second.back()->set_static(0);
					if (!first.empty())
						first.back()->set_static(0);
					}
				else {
					el->set_x_y(previous_coords_.first, previous_coords_.second);

					if (!first.empty())
						first.back()->set_static(0);
					if (!second.empty())
						second.back()->set_static(0);
					if (!third.empty())
						third.back()->set_static(0);
				}
				block_moved = true;
				break;
			}
			case 4: {
				el->set_x_y(previous_coords_.first, previous_coords_.second);

				if (!first.empty())
					first.back()->set_static(0);
				if (!second.empty())
					second.back()->set_static(0);
				if (!third.empty())
					third.back()->set_static(0);
				block_moved = true;
				break;
			}
			}
			left_button_down = 0;
		}
		if (!block_moved)
		for (auto& el : second) {
			switch (el->isUnclicked(openglX, openglY)) {
			case 1: {
				float top_block_width = 1000;
				if (!first.empty())
					top_block_width = first.back()->get_a();
				if (el->get_a() < top_block_width) {
					int capacity = first.size();
					el->set_x_y(-6, capacity - 7);
					first.push_back(el);
					switch (previous_position_) {
					case 1:
						first.pop_back();
						break;
					case 2:
						second.pop_back();
						break;
					case 3:
						third.pop_back();
						break;
					}
					if (!second.empty())
						second.back()->set_static(0);
					if (!third.empty())
						third.back()->set_static(0);
				}
				else {
					el->set_x_y(previous_coords_.first, previous_coords_.second);

					if (!first.empty())
						first.back()->set_static(0);
					if (!second.empty())
						second.back()->set_static(0);
					if (!third.empty())
						third.back()->set_static(0);
				}
				block_moved = true;
				break;
			}
			case 2: {
				float top_block_width = 1000;
				if (!second.empty())
					top_block_width = second.back()->get_a();
				if (el->get_a() < top_block_width) {
					int capacity = second.size();
					el->set_x_y(0, capacity - 7);
					second.push_back(el);
					switch (previous_position_) {
					case 1:
						first.pop_back();
						break;
					case 2:
						second.pop_back();
						break;
					case 3:
						third.pop_back();
						break;
					}
					if (!first.empty())
						first.back()->set_static(0);
					if (!third.empty())
						third.back()->set_static(0);
				}
				else {
					el->set_x_y(previous_coords_.first, previous_coords_.second);

					if (!first.empty())
						first.back()->set_static(0);
					if (!second.empty())
						second.back()->set_static(0);
					if (!third.empty())
						third.back()->set_static(0);
				}
				block_moved = true;
				break;
			}
			case 3: {
				float top_block_width = 1000;
				if (!third.empty())
					top_block_width = third.back()->get_a();
				if (el->get_a() < top_block_width) {
					int capacity = third.size();
					el->set_x_y(6, capacity - 7);
					third.push_back(el);
					switch (previous_position_) {
					case 1:
						first.pop_back();
						break;
					case 2:
						second.pop_back();
						break;
					case 3:
						third.pop_back();
						break;
					}
					if (!second.empty())
						second.back()->set_static(0);
					if (!first.empty())
						first.back()->set_static(0);
				}
				else {
					el->set_x_y(previous_coords_.first, previous_coords_.second);

					if (!first.empty())
						first.back()->set_static(0);
					if (!second.empty())
						second.back()->set_static(0);
					if (!third.empty())
						third.back()->set_static(0);
				}
				block_moved = true;
				break;
			}
			case 4: {
				el->set_x_y(previous_coords_.first, previous_coords_.second);

				if (!first.empty())
					first.back()->set_static(0);
				if (!second.empty())
					second.back()->set_static(0);
				if (!third.empty())
					third.back()->set_static(0);
				block_moved = true;
				break;
			}
			}
			left_button_down = 0;
		}
		if (!block_moved)
		for (auto& el : third) {
			switch (el->isUnclicked(openglX, openglY)) {
			case 1: {
				float top_block_width = 1000;
				if (!first.empty())
					top_block_width = first.back()->get_a();
				if (el->get_a() < top_block_width) {
					int capacity = first.size();
					el->set_x_y(-6, capacity - 7);
					first.push_back(el);
					switch (previous_position_) {
					case 1:
						first.pop_back();
						break;
					case 2:
						second.pop_back();
						break;
					case 3:
						third.pop_back();
						break;
					}
					if (!second.empty())
						second.back()->set_static(0);
					if (!third.empty())
						third.back()->set_static(0);
				}
				else {
					el->set_x_y(previous_coords_.first, previous_coords_.second);

					if (!first.empty())
						first.back()->set_static(0);
					if (!second.empty())
						second.back()->set_static(0);
					if (!third.empty())
						third.back()->set_static(0);
				}
				block_moved = true;
				break;
			}
			case 2: {
				float top_block_width = 1000;
				if (!second.empty())
					top_block_width = second.back()->get_a();
				if (el->get_a() < top_block_width) {
					int capacity = second.size();
					el->set_x_y(0, capacity - 7);
					second.push_back(el);
					switch (previous_position_) {
					case 1:
						first.pop_back();
						break;
					case 2:
						second.pop_back();
						break;
					case 3:
						third.pop_back();
						break;
					}
					if (!first.empty())
						first.back()->set_static(0);
					if (!third.empty())
						third.back()->set_static(0);
				}
				else {
					el->set_x_y(previous_coords_.first, previous_coords_.second);

					if (!first.empty())
						first.back()->set_static(0);
					if (!second.empty())
						second.back()->set_static(0);
					if (!third.empty())
						third.back()->set_static(0);
				}
				block_moved = true;
				break;
			}
			case 3: {
				float top_block_width = 1000;
				if (!third.empty())
					top_block_width = third.back()->get_a();
				if (el->get_a() < top_block_width) {
					int capacity = third.size();
					el->set_x_y(6, capacity - 7);
					third.push_back(el);
					switch (previous_position_) {
					case 1:
						first.pop_back();
						break;
					case 2:
						second.pop_back();
						break;
					case 3:
						third.pop_back();
						break;
					}
					if (!second.empty())
						second.back()->set_static(0);
					if (!first.empty())
						first.back()->set_static(0);
				}
				else {
					el->set_x_y(previous_coords_.first, previous_coords_.second);

					if (!first.empty())
						first.back()->set_static(0);
					if (!second.empty())
						second.back()->set_static(0);
					if (!third.empty())
						third.back()->set_static(0);
				}
				block_moved = true;
				break;
			}
			case 4: {
				el->set_x_y(previous_coords_.first, previous_coords_.second);

				if (!first.empty())
					first.back()->set_static(0);
				if (!second.empty())
					second.back()->set_static(0);
				if (!third.empty())
					third.back()->set_static(0);
				block_moved = true;
				break;
			}
			}
			left_button_down = 0;
		}
		if (!first.empty()) first.back()->set_static(0); 
		if (!second.empty()) second.back()->set_static(0);
		if (!third.empty()) third.back()->set_static(0);

		if (third.size() == amount_of_disks_) {
			glutDestroyWindow(1);
		}
	}
}

void cScene::mouse_move(int x, int y) {
	double openglX = ((double)x - 400) / 800 * 20;
	double openglY = (-(double)y + 300) / 600 * 20;
	for (auto& el : figures)
		if (left_button_down) {
			if (el->isClicked(openglX, openglY) == true) {
				el->follow(openglX, openglY);
				el->set_color(0.0, 1.0, 0.0);
			}
		}
}

void cScene::set_disks() {
	std::cout << "How many disks do you want (3, 4 or 5 disks):" << std::endl;
	std::cin >>amount_of_disks_;
	/*amount_of_disks_ = 3;*/
}

void cScene::add_disks() {
	if (amount_of_disks_ == 3 || amount_of_disks_ == 4 || amount_of_disks_ == 5) {
		int a = 0;
		for (int i = amount_of_disks_; i > 0; i--) {
			cFigure *k1 = new cRectangle(1 + i, 1, -6, -7 + a, 0, 0, 0);
			k1->set_color(1.0, 0.0, 0.0);
			if (i!=1) k1->set_static(1);
			figures.push_back(k1);
			first.push_back(k1);
			a++;
		}
	}
	else {
		system("cls");
		std::cout << "PODAJ PRAWIDLOWA LICZBE!!!" << std::endl << "\a";
		this->set_disks();
		this->add_disks();
	}
}
