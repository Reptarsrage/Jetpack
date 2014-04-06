/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef DEATHSICLE_H_
#define DEATHSICLE_H_

#include "MovingThing.h"

class Rectangle;
class Sprites;

/*
 * Position and properties of the non-player controlled Deathsicle baddie. 
 */
class Deathsicle : public MovingThing {

// Functions
public:

	~Deathsicle();
	Deathsicle(float x, float y, float w, float h, const Sprites *s);
	Deathsicle(const Rectangle r, const Sprites *s);
	
	/* Returns the name of this thing */
	virtual const char *ToString() const;
	
	/* Draws this thing */
	virtual void draw();

	/* Gets the intended y-dir change */
	virtual float getIntendedY();

	/* Gets the intended x-dir change */
	virtual float getIntendedX();

	/* Attempts to apply gravity to the object, returns the value dropped due to gravity */
	virtual float applyGravity(float force_gravity, float max_velocity_grav);

	/* sets the direction of the deathly Stalactite/Stalacmite */
	virtual void setDir(int dir);
	
private:
	/* initializes this baddie */
	void Init(const Rectangle r, const Sprites *s);

};


#endif // DEATHSICLE_H_