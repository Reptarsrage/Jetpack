/* Justin Robb
 * 3-30-14
 * JetPack
 * The editing window
*/

#ifndef EDITOR_H
#define EDITOR_H

#include <FL/Fl_Gl_Window.H>
#include <stdlib.h>
#include <vector>
#include "Rectangle.h"

#ifdef __APPLE__
#include "OpenGL/glew.h"
#else
#include "GL/glew.h"
#endif

class Rectangle;
class MovingThing;
class Hero;
class StationaryThing;
class JetpackUI;
class Collectable;
class Door;
class Bounds;
class AbstractThing;

/* Controls the animation and drawing for
 * the level editor.
*/
class Editor : public Fl_Gl_Window
{
// Functions
public:
	Editor(float x, float y, float w, float h, const char* l);
	~Editor();
	
	/* Draws all the things */
	void draw();

	/* called when a key event happens in fltk */
	int handle(int event);

private:
	
	/* Switches context to menu, and back again */
	void switchContext();

	/* Displays the menu for choosing a thing */
	void DrawMenu();

	/* Moves the curser */
	void advancePosition(bool up, bool down, bool left, bool right);

	/* handles user controls */
	void moveCurser();

	/* Helper function to initialize opengl for drawing*/
	int InitScene();
	
	/* Helper function to enable 2d drawing in opengl */
	void glEnable2D();
	
	/* Helper function to disable 2d drawing in opengl */
	void glDisable2D();

// Attributes
public:
	JetpackUI *m_UI;		// Pointer to handler

private:
	Rectangle *bounds;		// Current bounds for the map
	Rectangle *curser;		// Current curser position
	Rectangle *menu;		// bounds of the menu
	AbstractThing **menu_items;
	Rectangle prev_curser;

	float row_w,
		  col_h,
		  left,
		  top,
		  bottom,
		  right;

	bool	hold_left,		// Should our hero move left?
			hold_right,		// Should our hero move right?
			hold_up,		// Should our hero move up?
			hold_down,		// Should our hero move down?
			choosing;		// Is the menu showing/user picking a thing?
};

#endif // EDITOR_H