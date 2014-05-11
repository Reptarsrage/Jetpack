// must have title, description, row_c, col_c, password, data, picture?
#ifndef LEVEL_H_
#define LEVEL_H_

#include <string>
#include <list>
#include "AbstractThing.h"
#include "FL\Fl_RGB_Image.H"
using namespace std;

struct Level {
	string *title, *description, *passcode;
	int num_rows, num_cols;
	list<AbstractThing *> *data;
	unsigned char * screenshot_data;
	int screenshot_w, screenshot_h;
};

#endif // LEVEL_H_