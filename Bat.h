/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef BAT_H_
#define BAT_H_

#include "MovingThing.h"

/*
 * Position and properties of the non-player controlled Bat baddie. 
 * Bats have undefined behavior. As of now, they hunt the hero.
 */
class Bat : public MovingThing {

// Functions
public:
	~Bat();
	Bat(float x, float y, float w, float h, const Sprites *s);
	Bat(const Rectangle r, const Sprites *s);

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
	int switch_time;	// time in beween sprite switches
	float velocity_x,	// velocity in the x-dir
		  velocity_y;	// velocity in the y-dir
};


#endif // BAT_H_