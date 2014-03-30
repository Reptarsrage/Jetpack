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
 * Base class for all things moving in the game, i.e. baddies.
 */
class MovingThing : public AbstractThing{

// Functions
public:
	
	/* Moves this thing by one */
	virtual void move(float x, float y) { bounds->position_x += x;  bounds->position_y += y;}

	/* Gets the intended y-dir change */
	virtual float getIntendedY() = 0;

	/* Gets the intended x-dir change */
	virtual float getIntendedX() = 0;

	/* Attempts to apply gravity to the object, returns the value dropped due to gravity */
	virtual float applyGravity(float force_gravity, float max_velocity_grav) = 0;

// Attributes
public:
	float hit_wall_top,		// Baddies must know a little about there environment to hunt the hero
		  hit_wall_bottom,
		  hit_wall_left,
		  hit_wall_right,
		  hero_x,
		  hero_y;

	bool on_ground,
		 on_ladder;
};


#endif // MOVING_THING_H_