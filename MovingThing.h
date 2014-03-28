/* Justin Robb
 * 3-27-14
 * JetPack
 * A moving thing
*/

#ifndef MOVING_THING_H_
#define MOVING_THING_H_

#include "AbstractThing.h"
#include "paintView.h"

class Rectangle;
class Sprites;

/*
 * Base class for all things moving in the game, i.e. hero and baddies.
 */
class MovingThing : public AbstractThing{

// Functions
public:

	~MovingThing();
	MovingThing(float x, float y, float w, float h, const Sprites *s);
	MovingThing(const Rectangle r, const Sprites *s);
	
	/* Returns the name of this thing */
	virtual const char *ToString() const;
	
	/* Draws this thing */
	virtual void draw();
	
	/* Moves this thing by one */
	virtual void move(float x, float y);

	/* Ensures the bounds lie within the drawing board */
	virtual float checkBoundsX(float delta, const Rectangle bounds) const;
	
	/* Ensures the bounds lie within the drawing board */
	virtual float checkBoundsY(float delta, const Rectangle bounds) const;

	/* Makes the hero jump (soon to be moved to hero) */
	void Jump(float restitution) { velocity_jump = restitution; }

	/* Sets heros' x velocity (soon to be moved to hero) */
	void SetVelocityX(float v);

	/* Sets heros' y velocity (soon to be moved to hero) */
	void SetVelocityY(float v);

// Attributes
public:
	float velocity_x,		// veloxity in x-dir
		  velocity_y,		// veloxity in y-dir
		  force_x,			// force in x-dir
		  force_y,			// force in y-dir
		  velocity_jump,	// veloxity of jump
		  mass;				// Mass of hero
};


#endif // MOVING_THING_H_