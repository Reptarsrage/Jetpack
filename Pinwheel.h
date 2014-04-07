/* Justin Robb
 * 3-27-14
 * JetPack
 * Pinwheel baddie
*/

#ifndef PINWHEEL_H_
#define PINWHEEL_H_

#include "MovingThing.h"

/*
 * Position and properties of the non-player controlled Pinwheel baddie. 
 * Bounces around the level forever, doesn't care where hero is.
 */
class Pinwheel : public MovingThing {

// Functions
public:

	~Pinwheel();
	Pinwheel(float x, float y, float w, float h, const Sprites *s);
	Pinwheel(const Rectangle r, const Sprites *s);

	/* Gets the intended y-dir change */
	virtual float getIntendedY();

	/* Gets the intended x-dir change */
	virtual float getIntendedX();

	/* Attempts to apply gravity to the object, returns the value dropped due to gravity */
	virtual float applyGravity(float force_gravity, float max_velocity_grav);

private:
	/* Calculates the ricochet off of walls*/
	void calculate_dir(float norm_x, float norm_y);

	/* changes the direction ever so slightly, pretty cool effect */
	void randomize_dir();
	
	/* initializes this baddie */
	void Init(const Rectangle r, const Sprites *s);

// Attributes
private:
	
	float velocity_x,	// velocity in the x-dir
		  velocity_y;	// velocity in the y-dir
};


#endif // PINWHEEL_H_