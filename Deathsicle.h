/* Justin Robb
 * 3-27-14
 * Deathly spikes
*/

#ifndef DEATHSICLE_H_
#define DEATHSICLE_H_

#include "MovingThing.h"

/*
 * Position and properties of Deathsicles, which are basically just spikes.
 * These do not move.
 */
class Deathsicle : public MovingThing {

// Functions
public:

	~Deathsicle();
	/* REMEMBER to call setDir() */
	Deathsicle(float x, float y, float w, float h, const Sprites *s);
	/* REMEMBER to call setDir() */
	Deathsicle(const Rectangle r, const Sprites *s);

	/* Gets the intended y-dir change */
	virtual float getIntendedY();

	/* Gets the intended x-dir change */
	virtual float getIntendedX();

	/* Attempts to apply gravity to the object, returns the value dropped due to gravity */
	virtual float applyGravity(float force_gravity, float max_velocity_grav);

	/* sets the direction of the deathly Stalactite/Stalacmite */
	/* this should always be called immediatetly after construction! */
	virtual void setDir(int dir);

protected:
	/* adjusts the bounds to match ratios and center thing */
	virtual void adjustToBounds(float x, float y, float width, float height);
	
private:
	/* initializes this baddie */
	void Init(const Rectangle r, const Sprites *s);

};


#endif // DEATHSICLE_H_