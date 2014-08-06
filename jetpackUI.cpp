/* Justin Robb
 * 3-30-14
 * JetPack
 * The user interface part for the program.
*/

#include <FL/fl_ask.H>
#include "JetpackUI.h"
#include "fileio.h"
#include <sstream>

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

void JetpackUI::loadLevel(string title) {	
	assert(m_current == m_editor);
	string filename = "test.level";
	level_cache = load(filename, sprites);
	for (struct Level *l : *level_cache) {
		if (l->title->compare(title) == 0) {
			m_editor->loadLevel(*l->data);
		}
	}
	switch_contexts(m_editor_group);
}

void JetpackUI::saveLevel(string t, string d, string p) {
	assert(m_current == m_editor);
	printf("Saving...\n");
	string filename = string("test.level");
	struct Level level;
	level.num_rows = 16;
	level.num_cols = 26;
	level.title = new string(t);
	level.description = new string(d);
	level.passcode = new string(p);
	level.data = m_editor->getLevel();
	level.screenshot_data = m_editor->getScreen();
	level.screenshot_w = m_editor->w();
	level.screenshot_h = m_editor->h();
	save(filename, level);
	printf("LEVEL SAVED!\n");
	delete level.title;
	delete level.description;
	delete level.passcode;

	switch_contexts(m_editor_group);
}

void JetpackUI::switch_contexts(Fl_Group *display) {
	if (display == m_load_group) {
		stopAnimating();
		m_menubar_editor->hide();
		m_menubar_gamePlay->hide();
		m_loader->update("test.level");
		m_gamePlay_group->hide();
		m_editor_group->hide();
		m_save_group->hide();
		m_load_group->show();
	} else if (display == m_save_group) {
		stopAnimating();
		m_menubar_editor->hide();
		m_menubar_gamePlay->hide();
		m_saver->update("test.level");
		m_gamePlay_group->hide();
		m_editor_group->hide();
		m_save_group->show();
		m_load_group->hide();
	} else if (display == m_editor_group) {
		m_current = m_editor;
		m_menubar_editor->show();
		m_menubar_gamePlay->hide();
		m_gamePlay_group->hide();
		m_editor_group->show();
		m_save_group->hide();
		m_load_group->hide();
		startAnimating();
	} else if (display == m_gamePlay_group) {
		m_current = m_gamePlay;
		m_menubar_editor->hide();
		m_menubar_gamePlay->show();
		m_gamePlay_group->show();
		m_editor_group->hide();
		m_save_group->hide();
		m_load_group->hide();
		startAnimating();
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

void JetpackUI::cb_about_editor(Fl_Menu_* o, void* v) 
{
	fl_message("Jetpack (Early alpha)\n\n"
				"Controls\n"
				"\tArrow Keys......Move Curser.\n"
				"\tEnter...........Show/Hide menu of placable items.\n"
				"\tSpace...........Place the selected Item, choose an item from the menu.\n"
				"\tShift...........Delete an item.\n"
				"\tJ...............Place the hero.\n"
				"\tD...............Place the door.\n\n\n"
				"Use the menu bar to save, load, or try out your new level or any saved level.\n"
				"This has always been the most fun part of the game for me, hope you enjoy!\n"
				"\t-Justin\n\n\n\n\n");
}

void JetpackUI::cb_about_gameplay(Fl_Menu_* o, void* v) 
{
	fl_message("Jetpack  (Early alpha)\n\n"
				"Controls\n"
				"\tArrow Keys.....Move hero.\n"
				"\tSpace..........Jump.\n"
				"\tZ..............Use Jetpack.\n"
				"\tX..............Use Phaser.\n\n\n"
				"The goal of the game is to collect all the gems, avoid enemys, and make it to the door.\n"
				"You can accomplish this by using your handy jetpack (which runs on a rare fuel), and by using your\n"
				"trusty phaser, which can vaporize certain blocks temporarily. Note: The device, however, has not.\n"
				"Do not touch the operational end of the device. Do not look directly at the operational end of the\n"
				"device. Do not submerge the device in liquid, even partially. Most importantly, under no circumstances\n"
				"should you.. use it as a weapon.\n\n "
				"\tGood Luck and Enjoy!\n "
				"\t-Justin\n\n\n\n\n");
}

void JetpackUI::cb_clear(Fl_Menu_* o, void* v) 
{
	if (fl_ask("Are you sure you want to clear the current level?") == 0) { // NO
			return;
	}
	whoami(o)->m_editor->Clear();
}

void  JetpackUI::cb_switch_to_loader(Fl_Menu_* o, void* v) 
{
	whoami(o)->switch_contexts(whoami(o)->m_load_group);
}

void  JetpackUI::cb_switch_to_saver(Fl_Menu_* o, void* v) 
{
	if (!whoami(o)->m_editor->Playable()){
		fl_alert("You must place both a hero and a door before you save.\n");
		return;
	}
	whoami(o)->m_saver->addImage();
	whoami(o)->switch_contexts(whoami(o)->m_save_group);
}

void JetpackUI::cb_switch_to_editor(Fl_Menu_* o, void* v) 
{
	whoami(o)->switch_contexts(whoami(o)->m_editor_group);
}

void JetpackUI::cb_switch_to_game(Fl_Menu_* o, void* v) 
{
	whoami(o)->switch_contexts(whoami(o)->m_gamePlay_group);
}

void JetpackUI::playLoaded() {
	assert(m_editor == m_current);
	
	if (m_editor->Playable()) {
		m_gamePlay->loadLevel(*m_editor->getLevelForTest());
		switch_contexts(m_gamePlay_group);
	} else {
		fl_alert("You must place both a hero and a door before you can play.\n");
	}
}


void JetpackUI::show() {
	m_mainWindow->show();
}

void JetpackUI::cb_play_loaded(Fl_Menu_* o, void* v) {
	whoami(o)->playLoaded();
}

// Main menu definition
Fl_Menu_Item JetpackUI::menuitems_g[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Quit",			0, (Fl_Callback *)JetpackUI::cb_exit },
		{ 0 },
	{ "&Game",		0, 0, 0, FL_SUBMENU },
		{ "&Switch to Editor",	0, (Fl_Callback *)JetpackUI::cb_switch_to_editor },
		{ 0 },
	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	0, (Fl_Callback *)JetpackUI::cb_about_gameplay },
		{ 0 },

	{ 0 }
};

// Main menu definition
Fl_Menu_Item JetpackUI::menuitems_e[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Quit",			0, (Fl_Callback *)JetpackUI::cb_exit },
		{ 0 },
	{ "&Editor",		0, 0, 0, FL_SUBMENU },
		{ "&Switch to Game",	0, (Fl_Callback *)JetpackUI::cb_switch_to_game},
		{ "&Try out level",	0, (Fl_Callback *)JetpackUI::cb_play_loaded },
		{ "&Load Level",	0, (Fl_Callback *)JetpackUI::cb_switch_to_loader},
		{ "&Save Level",	0, (Fl_Callback *)JetpackUI::cb_switch_to_saver},
		{ "&Clear current level",	0, (Fl_Callback *)JetpackUI::cb_clear},
		{ 0 },
	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	0, (Fl_Callback *)JetpackUI::cb_about_editor },
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
	level_cache = NULL;
	
	// Create the main window
	
	m_mainWindow = new Fl_Double_Window(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Jetpack");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar_editor = new Fl_Menu_Bar(0, 0, DEFAULT_WIDTH, DEFAULT_MARGIN);
		m_menubar_editor->menu(menuitems_e);
		m_menubar_gamePlay = new Fl_Menu_Bar(0, 0, DEFAULT_WIDTH, DEFAULT_MARGIN);
		m_menubar_gamePlay->menu(menuitems_g);
		m_menubar_gamePlay->hide();
		m_menubar_editor->show();
		
		Fl_Group* group_f = new Fl_Group(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT);
			LoadingMenu *loader = new LoadingMenu(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, "Load Level", this);
		group_f->end();
		group_f->hide();

		Fl_Group* group_h = new Fl_Group(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT);
			SavingMenu *saver = new SavingMenu(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, "Save Level", this);
		group_h->end();
		group_h->hide();

		Fl_Group* group_g = new Fl_Group(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT);
			// install editor view window
			Maestro *game = new Maestro(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT - DEFAULT_MARGIN, this, "");
		group_g->end();
		group_g->hide();
		Fl_Group* group_e = new Fl_Group(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT);
			// install gameplay view window
			Editor *editor = new Editor(0, DEFAULT_MARGIN, DEFAULT_WIDTH, DEFAULT_HEIGHT - DEFAULT_MARGIN, "");
			editor->m_UI = this;
		group_e->end();
		//group_e->hide();
    m_mainWindow->end();

	//// Set dimensions
	m_nPaintWidth = m_nWidth = DEFAULT_WIDTH;
	m_nPaintHeight = m_nHeight = DEFAULT_HEIGHT - DEFAULT_MARGIN;
	m_editor_group = group_e;
	m_gamePlay_group = group_g;
	m_load_group = group_f;
	m_save_group = group_h;
	m_editor = editor;
	m_gamePlay = game;
	m_loader = loader;
	m_saver = saver;
	m_current = editor;
	m_mainWindow->iconize(); // IMPORTANT
	startAnimating();
	Fl_Widget * icon = fl_message_icon();
	icon->hide();
}



