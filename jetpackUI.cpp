/* Justin Robb
 * 3-27-14
 * JetPack
 * The user interface part for the program.
*/

#include <FL/fl_ask.H>
#include "JetpackUI.h"

#define DESTROY(p)	{  if ((sprites)!=NULL) {delete sprites; sprites=NULL; } }
const int FRAME_RATE = 100; //push it to the limit??

void callback(void* o) {
		((JetpackUI *)o)->m_paintView->refresh();
		Fl::repeat_timeout(1.0 / FRAME_RATE, callback, o);
    }

void JetpackUI::startAnimating() {
	printf("ANIMATING\n");
	animating = true;
	Fl::add_timeout(1.0 / FRAME_RATE, callback, this);
}

void JetpackUI::stopAnimating() {
	printf("STOPPING\n");
	Fl::remove_timeout(callback, this);
	animating = false;
}


JetpackUI* JetpackUI::whoami(Fl_Menu_* o)	
{
	return ( (JetpackUI*)(o->parent()->user_data()) );
}

void JetpackUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
}

void JetpackUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Jetpack");
}

void JetpackUI::show() {
	m_mainWindow->show();
	m_paintView->show();

}

// Main menu definition
Fl_Menu_Item JetpackUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)JetpackUI::cb_exit },
		{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)JetpackUI::cb_about },
		{ 0 },

	{ 0 }
};

//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
JetpackUI::JetpackUI() {
	// Initialize
	sprites = new Sprites();
	animating = false;
	
	// Create the main window
	m_mainWindow = new Fl_Window(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Jetpack");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, DEFAULT_WIDTH, DEFAULT_MARGIN);
		m_menubar->menu(menuitems);

		// Create a group that will hold one sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT - DEFAULT_MARGIN);

			// install paint view window
		m_paintView = new PaintView(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT - DEFAULT_MARGIN, "This is the paint view");
		m_paintView->box(FL_DOWN_FRAME);

		group->end();
		Fl_Group::current()->resizable(group);
		// group->resizable(m_paintView);
    m_mainWindow->end();

	// Set dimensions
	m_nPaintWidth = m_nWidth = DEFAULT_WIDTH;
	m_nPaintHeight = m_nHeight = DEFAULT_HEIGHT - DEFAULT_MARGIN;

	// refresh paint view as well
	m_paintView->m_UI = this;
	m_paintView->refresh();
	
	// imdediately start (change later)
	startAnimating();
}



