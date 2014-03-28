/* Justin Robb
 * 3-27-14
 * JetPack
 * The painting window
*/

#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <FL/Fl_Gl_Window.H>
#include <stdlib.h>
#include <vector>

#ifdef __APPLE__
#include "OpenGL/glew.h"
#else
#include "GL/glew.h"
#endif

class JetpackDoc;
class Rectangle;
class MovingThing;
class StationaryThing;

/* Controls the animation and drawing */
class PaintView : public Fl_Gl_Window
{
// Functions
public:
	PaintView(int x, int y, int w, int h, const char* l);
	~PaintView();
	
	/* Draws all the things */
	void draw();

	/* called when a key event happens in fltk */
	int handle(int event);

	/* Forces a redraw */
	void refresh();

	/* Resizes the painting window */
	void resizeWindow(int width, int height);

private:
	/* Helper function to handle key events */
	void handleEventKeys();
	
	/* Helper function to draw all non moving things */
	void drawBackGround();
	
	/* Helper function to draw all moving things */
	void drawMovingThings();
	
	/* Helper function to move all moving things (by telling them to move) */
	void moveThings();
	
	/* Helper function to make sure hero's position stays valid in the x-direction */
	float checkBoundsX(float delta) const;
	
	/* Helper function to make sure hero's position stays valid  n the y-direction */
	float checkBoundsY(float delta) const;
	
	/* Helper function to load in all things to be drawn */
	void loadLevel();
	
	/* Helper function to initialize opengl for drawing*/
	int InitScene();
	
	/* Helper function to enable 2d drawing in opengl */
	void glEnable2D();
	
	/* Helper function to disable 2d drawing in opengl */
	void glDisable2D();

// Attributes
public:
	JetpackDoc *m_pDoc;							// Pointer to handler

private:
	Rectangle *bounds;							// Current bounds for the hero
	MovingThing *hero;
	std::vector<StationaryThing *> *stat_things;// Holds all non moving things
	
	int		m_nWindowWidth,		// Width of enire window
			m_nWindowHeight,	// Height of entire window
			m_nDrawHeight,		// Height of our painting section
			m_nDrawWidth;		// Width of our painting section
			

	float	row_w,				// width of one column in our painting grid
			col_h,				// height of one row in our painting grid
			max_velocity,		// scalable maximum velocity of things
			jump_restitution,	// scalable jump power of hero
			force_gravity,		// scalable force of gravity on moving things
			jetpack_thrust;		// scalable thrust of hero's jetpack 

	bool	hold_left,		// Should our hero move left?
			hold_right,		// Should our hero move right?
			hold_up,		// Should our hero move up?
			hold_down,		// Should our hero move down?
			level_loaded;	// Should we load the sprites of the level?
};

#endif