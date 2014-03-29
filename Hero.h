/* Justin Robb
 * 3-27-14
 * JetPack
 * Player controlled hero
*/

#ifndef HERO_H_
#define HERO_H_

#include "AbstractThing.h"
#include "paintView.h"

class Rectangle;
class Sprites;

/*
 * Position and properties of the player controlled charcter.
 */
class Hero : public AbstractThing {

// Functions
public:

	~Hero();
	Hero(float x, float y, float w, float h, const Sprites *s);
	Hero(const Rectangle r, const Sprites *s);
	
	/* Returns the name of this thing */
	virtual const char *ToString() const;
	
	/* Draws this thing */
	virtual void draw();
	
	/* Moves this thing by one step*/
	virtual void move(float x, float y);

// Attributes
public:
	float velocity_x,		// veloxity in x-dir
		  velocity_y,		// veloxity in y-dir
		  force_x,			// force in x-dir
		  force_y,			// force in y-dir
		  mass,				// Mass of hero
		  velocity_jump;	// veloxity of jump
};


#endif // HERO_H_