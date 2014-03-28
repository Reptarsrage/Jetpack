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

#include "jetpack_main.h"
#include "paintView.h"

const int DEFAULT_WIDTH = 600;		// Default window width
const int DEFAULT_HEIGHT = 300;		// Default window height
const int DEFAULT_MARGIN = 25;		// Default menu-bar height

/*
 * Handles all forms, windows, menus and UI related things.
 * While this handles UI, all key events should be handled by
 * the one who is in charge of painting.
 */
class JetpackUI {
// Member functions
public:
	JetpackUI();
	
	/* Sets the animation/state handler for communication */
	void setDocument(JetpackDoc* doc);
	
	/* Returns the animation/state handler */
	JetpackDoc*	getDocument();
	
	/* Draw the main window */
	void show();
	
	/* Change the paint and original window sizes to w by h */
	void resize_windows(int w, int h);	

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
	static void	cb_about(Fl_Menu_* o, void* v);

// Atributes and FLTK Widgets
public:
	PaintView* m_paintView;		// In charge of painting
	Fl_Window* m_mainWindow;	// The main form
	Fl_Menu_Bar* m_menubar;		// menubar of main form
private:
	JetpackDoc*	m_pDoc;			// pointer to document to communicate with the document

	// Static class members
	static Fl_Menu_Item	menuitems[];		// menu items for main menu bar
	
	/* This returns the UI, given the menu item.  It provides a
	 * link from the menu items to the UI 
	 */
	static JetpackUI* whoami(Fl_Menu_* o);

};

#endif