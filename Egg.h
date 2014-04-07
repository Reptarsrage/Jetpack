/* Justin Robb
 * 3-27-14
 * Egg baddie
*/

#ifndef EGG_H_
#define EGG_H_

#include "MovingThing.h"

/*
 * Position and properties of the non-player controlled Egg baddie.
 * Moves left and right, gravity effects it, doesn't care where hero is.
 */
class Egg : public MovingThing {

// Functions
public:

	~Egg();
	Egg(float x, float y, float w, float h, const Sprites *s);
	Egg(const Rectangle r, const Sprites *s);
	
	/* Moves this thing by one */
	virtual void move(float x, float y);

	/* Gets the intended y-dir change */
	virtual float getIntendedY();

	/* Gets the intended x-dir change */
	virtual float getIntendedX();

	/* Attempts to apply gravity to the object, returns the value dropped due to gravity */
	virtual float applyGravity(float force_gravity, float max_velocity_grav);

	/*  Sets whether this moving thing is on a solid surface */
	virtual void Grounded(bool b);
	
private:
	/* initializes this baddie */
	void Init(const Rectangle r, const Sprites *s);

// Attributes
private:

	float velocity_x,	// velocity in the x-dir
		  velocity_y;	// velocity in the y-dir
};


#endif // EGG_H_