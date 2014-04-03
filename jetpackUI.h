/* Justin Robb
 * 3-27-14
 * JetPack
 * User Interface Handler (doesn't do key events)
*/

#ifndef JetpackUI_h
#define JetpackUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Tabs.H>

#include "jetpack_main.h"
#include "paintView.h"
#include "Editor.h"
#include "Sprites.h"

const float DEFAULT_WIDTH = 800;		// Default window width
const float DEFAULT_HEIGHT = 400;		// Default window height
const float DEFAULT_MARGIN = 25;		// Default menu-bar height

/*
 * Handles all forms, windows, menus and UI related things.
 * While this handles UI, all key events should be handled by
 * the one who is in charge of painting.
 */
class JetpackUI {
// Member functions
public:
	JetpackUI();
	
	/* Draw the main window */
	void show();

		/* Begins animation counter */
	void	startAnimating();

	/* Stops animation counter */
	void	stopAnimating();

	/* Loads a level into the editor */
	void	loadLevel();

	/* Saves the current edited level */
	void	saveLevel();

// All callbacks here.  Callbacks are declared 
// static
private:
	/* Causes the Jetpack program to exit
	 * Called by the UI when the quit menu item is chosen
	 */
	static void	cb_exit(Fl_Menu_* o, void* v);
	
	/* Brings up an about dialog box
	 * Called by the UI when the about menu item is chosen 
	*/
	static void	cb_clear(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_switch1(Fl_Menu_* o, void* v);
	static void	cb_switch2(Fl_Menu_* o, void* v);
	static void	cb_load_level(Fl_Menu_* o, void* v);
	static void	cb_save_level(Fl_Menu_* o, void* v);

// Static Functions
private:

	// Static class members
	static Fl_Menu_Item	menuitems[];		// menu items for main menu bar
	
	/* This returns the UI, given the menu item.  It provides a
	 * link from the menu items to the UI 
	 */
	static JetpackUI* whoami(Fl_Menu_* o);

// Atributes and FLTK Widgets
public:
	Fl_Group* m_gamePlay_group;				// FLTK Group holding the game
	Fl_Group* m_editor_group;				// FLTK Group holding the level editor
	
	PaintView* m_gamePlay;				// In charge of painting/controlling the game
	Editor* m_editor;					// In charge of painting/controlling the level editor
	
	Fl_Gl_Window *m_current;			// Current thing being used (animated).
	
	Fl_Window* m_mainWindow;			// The main form
	Fl_Menu_Bar* m_menubar;				// menubar of main form
	int				m_nWidth,			// Dimensions of original window.
					m_nHeight;

	int				m_nPaintWidth,		// Dimensions of the paint window.
					m_nPaintHeight;						

	Sprites *sprites;				// Sprite manager (all sprites)
	bool animating;					// controller for animation callbacks

};

#endif