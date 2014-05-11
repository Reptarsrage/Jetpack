/* Justin Robb
 * 4-37-14
 * JetPack
 * The loading a level window
*/

#ifndef LOADING_MENU_H
#define LOADING_MENU_H

#include <stdlib.h>
#include <vector>
#include <list>
#include "FL\Fl_Hold_Browser.H"
#include "FL\Fl_Text_Display.H"
#include "FL\Fl_Text_Buffer.H"
#include "FL\Fl_RGB_Image.H"
#include "FL\Fl_Button.H"
#include "FL\Fl_Box.H"
#include "Level.h"
#include "jetpackUI.h"

#ifdef __APPLE__
#include "OpenGL/glew.h"
#else
#include "GL/glew.h"
#endif

class Rectangle;
class JetpackUI;
class Sprites;

class LoadingMenu : public Fl_Group {

// Functions
public:
	LoadingMenu(float x, float y, float w, float h, const char* l, JetpackUI *ui);
	~LoadingMenu();
	static void	cb_sel(Fl_Widget* o, void* v);
	static void	cb_confirm(Fl_Widget* o, void* v);
	void setTexts(const char * title, const char * description,  const char *password);
	void update(std::string filename);
	void addImage(const unsigned char *img_data, int width, int height);
	unsigned char * Resample(unsigned char *buf, int width, int height, int newWidth, int newHeight);
	void Reset();

	/* This returns the UI, given the browser item.  It provides a
	 * link from the browser items to the UI 
	 */
	static LoadingMenu* whoami(Fl_Widget* o);
	static void	cb_cancel(Fl_Widget* o, void* v);
	
public:
	Fl_Hold_Browser *browser;
	Fl_Text_Buffer *tit_buf, *desc_buf;//, *pass_buf;
	Fl_Text_Display *title, *description;//, *pass;
	Fl_Button *confirm, *cancel;
	std::list<struct Level *> *level_cache;
	JetpackUI *m_UI;
	Fl_Box  *img_box;
	Fl_RGB_Image *img;
};

#endif // LOADING_MENU_H