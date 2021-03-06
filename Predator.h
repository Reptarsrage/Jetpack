/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef PREDATOR_H_
#define PREDATOR_H_

#include "MovingThing.h"

class Rectangle;
class Sprites;

/*
 * Position and properties of the non-player controlled Predator baddie. 
 * The only baddie that ignores solid objects.
 * Eternally hunts the player, but should move slow enough to be fair.
 */
class Predator : public MovingThing {

// Functions
public:

	~Predator();
	Predator(float x, float y, float w, float h, const Sprites *s);
	Predator(const Rectangle r, const Sprites *s);

	/* Gets the intended y-dir change */
	virtual float getIntendedY();

	/* Gets the intended x-dir change */
	virtual float getIntendedX();

	/* Attempts to apply gravity to the object, returns the value dropped due to gravity */
	virtual float applyGravity(float force_gravity, float max_velocity_grav);

private:
	/* initializes this baddie */
	void Init(const Rectangle r, const Sprites *s);

// Attributes
private:

	int switch_time, switch_small;	// time in beween sprite switches
	float velocity_x,	// velocity in the x-dir
		  velocity_y;	// velocity in the y-dir
};


#endif // PREDATOR_H_