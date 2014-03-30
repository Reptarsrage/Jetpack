/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef EGG_H_
#define EGG_H_

#include "MovingThing.h"

class Rectangle;
class Sprites;

/*
 * Position and properties of the non-player controlled Egg baddie. 
 */
class Egg : public MovingThing {

// Functions
public:

	~Egg();
	Egg(float x, float y, float w, float h, const Sprites *s);
	Egg(const Rectangle r, const Sprites *s);
	void Init(const Rectangle r, const Sprites *s);
	
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

// Attributes
private:
	
	float velocity_x,	// velocity in the x-dir
		  velocity_y;	// velocity in the y-dir
};


#endif // EGG_H_