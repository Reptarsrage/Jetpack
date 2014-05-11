/* Justin Robb
 * 4-37-14
 * JetPack
 * The Saving a level window
*/

#ifndef SAVING_MENU_H
#define SAVING_MENU_H

#include <stdlib.h>
#include <vector>
#include <list>
#include "FL\Fl_Hold_Browser.H"
#include "FL\Fl_Multiline_Input.H"
#include "FL\Fl_Text_Buffer.H"
#include "FL\Fl_Image.H"
#include "FL\Fl_Button.H"
#include "FL\Fl_Box.H"
#include "jetpackUI.h"
#include "FL\Fl_RGB_Image.H"

#ifdef __APPLE__
#include "OpenGL/glew.h"
#else
#include "GL/glew.h"
#endif

class Rectangle;
class JetpackUI;
class Sprites;

class SavingMenu : public Fl_Group {

// Functions
public:
	SavingMenu(float x, float y, float w, float h, const char* l, JetpackUI *ui);
	~SavingMenu();
	static void	cb_sel(Fl_Widget* o, void* v);
	static void	cb_confirm(Fl_Widget* o, void* v);
	void setTexts(const char * title, const char * description,  const char *password);
	void update(std::string filename);
	void addImage();
	unsigned char * Resample(unsigned char *buf, int width, int height, int newWidth, int newHeight);
	
	/* This returns the UI, given the browser item.  It provides a
	 * link from the browser items to the UI 
	 */
	static SavingMenu* whoami(Fl_Widget* o);
	
public:
	Fl_Hold_Browser *browser;
	Fl_Multiline_Input *title, *description;//, *pass;
	Fl_Button *confirm;
	std::list<struct Level *> *level_cache;
	JetpackUI *m_UI;
	Fl_Box  *img_box;
	Fl_RGB_Image *img;
};

#endif // SAVING_MENU_H