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
#include <list>
#include <queue>
#include "OpenGl2DWindow.h"

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
class Editor : public OpenGl2DWindow
{
// Functions
public:
	Editor(float x, float y, float w, float h, const char* l);
	~Editor();
	
	/* Draws all the things */
	void draw();

	/* called when a key event happens in fltk */
	int handle(int event);

	/* loads the level from a file */
	void loadLevel(const std::list<AbstractThing *> level);

	/* saves the level to a file */
	const std::queue<AbstractThing *> *getLevel();

	/* removes all placed items */
	void Clear();

	/* Only can save/play a level with a hero and a door placed*/
	bool Playable();

private:
	/* places the hero */
	void placeHero();

	/* places the door */
	void placeDoor();

	/* handles the space key */
	void handleSpace();
	
	/* places the currently selected thing on the map, at the curser loacation*/
	void placeThing();

	/* Records the current thing to be placed, chosen by the user from the menu*/
	void chooseThing();

	/* Switches context to menu, and back again */
	void switchContext();

	/* Displays the menu for choosing a thing */
	void DrawMenu();

	/* Moves the curser */
	void advancePosition(bool up, bool down, bool left, bool right);

	/* handles user controls */
	void moveCurser();

// Attributes
public:
	float row_w,			// width of one thing
		  col_h;			// height of one thing
private:
	Rectangle *bounds;		// Current bounds for the map
	Rectangle *curser;		// Current curser position
	Rectangle *menu;		// bounds of the menu
	AbstractThing **menu_items;	// a container holding all menu items 
								// in the col-wise order in which they appear
	Hero *hero;					// our hero!
	Door *door;					// his destination.
	
	Rectangle *prev_curser;		// saved curser positino when switching contexts
	int selected;				// currently slected menu item
	std::list<AbstractThing *> *placed_items;	// all placed items

	int frame;					// current frame number, used to slow down controls

	float left,					// drawing bounds left
		  top,					// drawing bounds top
		  bottom,				// drawing bounds bottom
		  right;				// drawing bounds right

	bool	hold_left,		// Should our curser move left?
			hold_right,		// Should our curser move right?
			hold_up,		// Should our curser move up?
			hold_down,		// Should our curser move down?
			hold_place,		// Is the user trying to place/select a thing?
			choosing;		// Is the menu showing/user picking a thing?
};

#endif // EDITOR_H