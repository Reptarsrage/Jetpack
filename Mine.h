/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef MINE_H_
#define MINE_H_

#include "MovingThing.h"

class Rectangle;
class Sprites;

/*
 * Position and properties of the non-player controlled Mine baddie. 
 */
class Mine : public MovingThing {

// Functions
public:

	~Mine();
	Mine(float x, float y, float w, float h, const Sprites *s);
	Mine(const Rectangle r, const Sprites *s);
	
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
	
private:
	/* initializes this baddie */
	void Init(const Rectangle r, const Sprites *s);

};


#endif // MINE_H_