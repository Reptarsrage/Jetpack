/* Justin Robb
 * 3-30-14
 * JetPack
 * The user interface part for the program.
*/

#include <FL/fl_ask.H>
#include "JetpackUI.h"
#include "fileio.h"

const int CYCLE_RATE = 100; // times per second

void callback(void* o) {
		((JetpackUI *)o)->m_current->redraw();
		Fl::repeat_timeout(1.0 / CYCLE_RATE, callback, o);
    }

void JetpackUI::startAnimating() {
	if (!animating) {
		printf("ANIMATING\n");
		animating = true;
		Fl::add_timeout(1.0 / CYCLE_RATE, callback, this);
	}
}

void JetpackUI::stopAnimating() {
	if (animating){
		printf("STOPPING\n");
		Fl::remove_timeout(callback, this);
		animating = false;
	}
}

void JetpackUI::loadLevel() {
	assert(m_current == m_editor);
	string filename = "test.level";
	int num_rows;
	int num_cols;
	string *title;
	string *description;
	string *passcode;
	std::list<AbstractThing *> *l = new std::list<AbstractThing *>();
	load(filename, m_editor->row_w, 
				m_editor->col_h, 
				&num_rows, 
				&num_cols,
				&title,
				&description,
				&passcode,
				l,
				sprites);
	m_editor->loadLevel(*l);
	if (l->empty())
		delete l;
	delete title;
	delete description;
	delete passcode;
}

void JetpackUI::saveLevel() {
	assert(m_current == m_editor);
	if (!m_editor->Playable()){
		printf("You must place both a hero and a door before you save.\n");
		return;
	}
	printf("Saving...\n");
	string filename = string("test.level");
	int num_rows = 16;
	int num_cols = 26;
	string title = string("Test");
	string description = string("Test level, file I/O.");
	string passcode = string("Justin is super awesome.");
	const std::queue<AbstractThing *> *q = m_editor->getLevel();

	save( filename, 
		  title, 
		  description, 
		  passcode, 
		  *q,
		  num_rows, 
		  num_cols);
	delete q;
	printf("LEVEL SAVED!\n");
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

void JetpackUI::cb_clear(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_editor->Clear();
}

void JetpackUI::cb_switch_to_editor(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_gamePlay_group->hide();
	whoami(o)->m_editor_group->show();
	whoami(o)->m_current = whoami(o)->m_editor;
}

void JetpackUI::cb_switch_to_game(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_editor_group->hide();
	whoami(o)->m_gamePlay_group->show();
	whoami(o)->m_current = whoami(o)->m_gamePlay;
}

void JetpackUI::cb_load_level(Fl_Menu_* o, void* v) 
{
	whoami(o)->loadLevel();
}


void JetpackUI::cb_save_level(Fl_Menu_* o, void* v) 
{
	whoami(o)->saveLevel();
}

void JetpackUI::playLoaded() {
	assert(m_gamePlay);
	string filename = "test.level";
	int num_rows;
	int num_cols;
	string *title;
	string *description;
	string *passcode;
	std::list<AbstractThing *> *l = new std::list<AbstractThing *>();
	load(filename, m_gamePlay->getRowWidth(), 
				m_gamePlay->getColHeight(), 
				&num_rows, 
				&num_cols,
				&title,
				&description,
				&passcode,
				l,
				sprites);
	m_gamePlay->loadLevel(*l);
	if (l->empty())
		delete l;
	delete title;
	delete description;
	delete passcode;
	m_editor_group->hide();
	m_gamePlay_group->show();
	m_current = m_gamePlay;

}


void JetpackUI::show() {
	m_mainWindow->show();
}

void JetpackUI::cb_play_loaded(Fl_Menu_* o, void* v) {
	whoami(o)->playLoaded();
}

// Main menu definition
Fl_Menu_Item JetpackUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Quit",			FL_CTRL + 'w', (Fl_Callback *)JetpackUI::cb_exit },
		{ 0 },
	{ "&Game",		0, 0, 0, FL_SUBMENU },
		{ "&Switch to this",	0, (Fl_Callback *)JetpackUI::cb_switch_to_game },
		{ "&Play a loaded level",	0, (Fl_Callback *)JetpackUI::cb_play_loaded },
		{ 0 },
	{ "&Editor",		0, 0, 0, FL_SUBMENU },
		{ "&Switch to this",	0, (Fl_Callback *)JetpackUI::cb_switch_to_editor},
		{ "&Load Level",	FL_CTRL + 'w', (Fl_Callback *)JetpackUI::cb_load_level},
		{ "&Save Level",	FL_CTRL + 'l', (Fl_Callback *)JetpackUI::cb_save_level},
		{ "&Clear current level",	0, (Fl_Callback *)JetpackUI::cb_clear},
		{ 0 },
	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	0, (Fl_Callback *)JetpackUI::cb_about },
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
	
	m_mainWindow = new Fl_Double_Window(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Jetpack");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, DEFAULT_WIDTH, DEFAULT_MARGIN);
		m_menubar->menu(menuitems);
		
		Fl_Group* group_g = new Fl_Group(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT);
				// install editor view window
		Maestro *game = new Maestro(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT - DEFAULT_MARGIN, this, "");
			group_g->end();
			Fl_Group* group_e = new Fl_Group(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT);
				// install gameplay view window
				Editor *editor = new Editor(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT - DEFAULT_MARGIN, "");
				editor->m_UI = this;
			group_e->end();
			group_e->hide();
    m_mainWindow->end();

	// Set dimensions
	m_nPaintWidth = m_nWidth = DEFAULT_WIDTH;
	m_nPaintHeight = m_nHeight = DEFAULT_HEIGHT - DEFAULT_MARGIN;
	m_editor_group = group_e;
	m_gamePlay_group = group_g;
	m_editor = editor;
	m_gamePlay = game;
	m_current = game;
	m_mainWindow->iconize(); // IMPORTANT
	startAnimating();
}



