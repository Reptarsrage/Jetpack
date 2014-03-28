/* Justin Robb
 * 3-27-14
 * JetPack
 * The user interface part for the program.
*/

#include <string>
#include <FL/fl_ask.H>
#include <algorithm>
#include <math.h>
#include "JetpackUI.h"
#include "JetpackDoc.h"

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

JetpackDoc* JetpackUI::getDocument()
{
	return m_pDoc;
}

void JetpackUI::show() {
	m_mainWindow->show();
	m_paintView->show();
}

void JetpackUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
}

void JetpackUI::setDocument(JetpackDoc* doc)
{
	m_pDoc = doc;
	m_paintView->m_pDoc = doc;
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
	// Create the main window
	m_mainWindow = new Fl_Window(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Jetpack");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, DEFAULT_WIDTH, DEFAULT_MARGIN);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT - DEFAULT_MARGIN);

			// install paint view window
		m_paintView = new PaintView(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT - DEFAULT_MARGIN, "This is the paint view");
			m_paintView->box(FL_DOWN_FRAME);

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();
}



