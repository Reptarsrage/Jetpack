/* Justin Robb
 * 3-30-14
 * JetPack
 * The editing window
*/

#ifndef GAME_H
#define GAME_H

#include <FL/Fl_Gl_Window.H>
#include <stdlib.h>
#include <vector>
#include <list>

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
class AbstractThing;
class Teleporter;
class SolidThing;

/* Controls the animation and drawing */
class Game : public Fl_Gl_Window
{
// Functions
public:
	Game(float x, float y, float w, float h, const char* l);
	~Game();
	
	/* Draws all the things */
	void draw();

	/* called when a key event happens in fltk */
	int handle(int event);

	/* called when a key event happens in fltk */
	void loadLevel(std::list<AbstractThing *> level);

	/* clear the current map of things */
	void Clear();

private:
	/* handles phasing through solid objects */
	void Game::heroPhase(int dir) ;

	/* teleports hero */
	void teleport(const Teleporter *src);

	/* switches switchblocks on/off */
	void switchSolids(int code);

	/* Handles what to do whenever the down key is pressed, not held */
	void handleDownPress();

	/* Helper function to test if hero can collect anything*/
	bool heroGetSwag();
	
	/* Helper function to draw all non moving things */
	void drawBackGround();
	
	/* Helper function to draw all moving things */
	void drawMovingThings();

	/* Helper function to draw all moving things */
	void drawHero();
	
	/* Helper function to move all moving things (by telling them to move) */
	void moveThings();

	/* Helper function to move all moving things (by telling them to move) */
	void moveHero();
	
	/* Helper function to advance the position of a moving thing. Does bounds checking! */
	void advancePosition(MovingThing *thing, float delta_x, float delta_y) const;
	
	/* Helper function to advance the position of a moving thing. Does bounds checking! */
	void advanceHeroPosition(float delta_x, float delta_y) const;
	
	/* Helper function to initialize opengl for drawing*/
	int InitScene();
	
	/* Helper function to enable 2d drawing in opengl */
	void glEnable2D();
	
	/* Helper function to disable 2d drawing in opengl */
	void glDisable2D();

// Attributes
public:
	JetpackUI *m_UI;							// Pointer to handler
	float row_w,				// width of one column in our painting grid
		  col_h;				// height of one row in our painting grid
private:
	Rectangle *bounds;							// Current bounds for the hero
	Hero *hero;
	Door *door;
	std::vector<SolidThing *> *solid_things;       // Holds all solid things
	std::vector<StationaryThing *> *nonsolid_things;    // Holds all non-solid, un-interactable things
	std::vector<StationaryThing *> *special_things;     // Holds all non-solid, interactable things (ladders, teleporters)
	std::vector<Collectable *> *collectable_things;		// Holds all collectable things
	std::vector<MovingThing *> *dyn_things;				// Holds all baddies

	int		gem_count;			// Number of gems left in the level 
								// (hero must collect all gems to open door and beat level)
			
	float	max_velocity,		// scalable maximum velocity of things
			jump_restitution,	// scalable jump power of hero
			force_gravity,		// scalable force of gravity on moving things
			max_velocity_grav,  // scalable maximum drop speed due to gravity
			jetpack_thrust,		// scalable thrust of hero's jetpack 
			ladder_velocity,	// how fast to go on ladders
			force_ice,			// how slippery ice is
			conveyor_speed;		// how fast conveyors move

	float left,					// drawing bounds left
		  top,					// drawing bounds top
		  bottom,				// drawing bounds bottom
		  right;				// drawing bounds right

	bool	hold_left,		// Should our hero move left?
			hold_right,		// Should our hero move right?
			hold_up,		// Should our hero move up?
			hold_down,		// Should our hero move down?
			hold_jet_pack,	// Should our hero activate his jetpack?
			hold_phase,		// Should our hero activate his phaser?
			phasing_in_air;	// special flag to handle phasing while jetpacking in air
							// which is really difficult for the user unless we help
};

#endif // GAME_H