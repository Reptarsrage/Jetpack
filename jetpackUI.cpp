/* Justin Robb
 * 3-30-14
 * JetPack
 * The user interface part for the program.
*/

#include <FL/fl_ask.H>
#include "JetpackUI.h"

const int FRAME_RATE = 30; // not sure if this is right...

void callback(void* o) {
		((JetpackUI *)o)->m_current->redraw();
		Fl::repeat_timeout(1.0 / FRAME_RATE, callback, o);
    }

void JetpackUI::startAnimating() {
	if (!animating) {
		printf("ANIMATING\n");
		animating = true;
		Fl::add_timeout(1.0 / FRAME_RATE, callback, this);
	}
}

void JetpackUI::stopAnimating() {
	if (animating){
		printf("STOPPING\n");
		Fl::remove_timeout(callback, this);
		animating = false;
	}
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

void JetpackUI::cb_switch1(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_gamePlay_group->hide();
	whoami(o)->m_editor_group->show();
	whoami(o)->m_current = whoami(o)->m_editor;
}

void JetpackUI::cb_switch2(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_editor_group->hide();
	whoami(o)->m_gamePlay_group->show();
	whoami(o)->m_current = whoami(o)->m_gamePlay;
}

void JetpackUI::show() {
	m_mainWindow->show();
}

// Main menu definition
Fl_Menu_Item JetpackUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Editor",			FL_ALT + 'e', (Fl_Callback *)JetpackUI::cb_switch1 },
		{ "&Gameplay",			FL_ALT + 'g', (Fl_Callback *)JetpackUI::cb_switch2 },
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
		
		//Fl_Tabs* tabs = new Fl_Tabs(20, 20, 350, 350);
		Fl_Group* group_g = new Fl_Group(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT);
				// install editor view window
				PaintView *game = new PaintView(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT, "Game");
				game->m_UI = this;
			group_g->end();
			group_g->hide();
			Fl_Group* group_e = new Fl_Group(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT);
				// install gameplay view window
				Editor *editor = new Editor(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT, "Level Editor");
				editor->m_UI = this;
			group_e->end();
		//tabs->end();
    m_mainWindow->end();

	// Set dimensions
	m_nPaintWidth = m_nWidth = DEFAULT_WIDTH;
	m_nPaintHeight = m_nHeight = DEFAULT_HEIGHT - DEFAULT_MARGIN;
	m_editor_group = group_e;
	m_gamePlay_group = group_g;
	m_editor = editor;
	m_gamePlay = game;
	m_current = editor;
	startAnimating();
}



