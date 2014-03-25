//
// JetpackUI.h
//
// The header file for the UI part
//

#ifndef JetpackUI_h
#define JetpackUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_File_Chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Color_Chooser.H>

#include "jetpack_main.h"
#include "paintView.h"

const int DEFAULT_WIDTH = 600;
const int DEFAULT_HEIGHT = 300;
const int DEFAULT_MARGIN = 25;

class JetpackUI {
public:
	JetpackUI();
	~JetpackUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
								
	PaintView*			m_paintView;

	// Member functions
	void				setDocument(JetpackDoc* doc);
	JetpackDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

private:
	JetpackDoc*	m_pDoc;		// pointer to document to communicate with the document

	// Static class members
	static Fl_Menu_Item		menuitems[];

	static JetpackUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);

};

#endif

