/* Justin Robb
 * 3-27-14
 * Spring baddie
*/

#ifndef SPRING_H_
#define SPRING_H_

#include "MovingThing.h"

/*
 * Position and properties of the non-player controlled Spring baddie.
 * The spring baddie moves up until it hits the veiling, then moves down 
 * until it hits the floor, then moves up.. and so on.
 */
class Spring : public MovingThing {

// Functions
public:

	~Spring();
	Spring(float x, float y, float w, float h, const Sprites *s);
	Spring(const Rectangle r, const Sprites *s);

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
	
	float velocity_x,	// velocity in the x-dir
		  velocity_y;	// velocity in the y-dir
};


#endif // SPRING_H_