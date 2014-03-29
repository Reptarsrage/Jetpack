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
	void Init(const Rectangle r, const Sprites *s);
	
	/* Returns the name of this thing */
	virtual const char *ToString() const;
	
	/* Draws this thing */
	virtual void draw();
	
	/* Moves this thing by one step*/
	virtual void move(float x, float y);

	/* Makes this hero jump */
	virtual void Jump(float restitution);

	/* Attempts to apply gravity to the object, returns the value dropped due to gravity */
	virtual float applyGravity(float delta_y);

// Attributes
public:
	float velocity_x,		// veloxity in x-dir
		  velocity_y,		// veloxity in y-dir
		  force_x,			// force in x-dir
		  force_y,			// force in y-dir
		  mass,				// Mass of hero
		  velocity_jump,	// veloxity of jump
		  on_ground,
		  on_ladder;
};


#endif // HERO_H_