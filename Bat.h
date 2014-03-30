/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef BAT_H_
#define BAT_H_

#include "MovingThing.h"

class Rectangle;
class Sprites;

/*
 * Position and properties of the non-player controlled Bat baddie. 
 */
class Bat : public MovingThing {

// Functions
public:

	~Bat();
	Bat(float x, float y, float w, float h, const Sprites *s);
	Bat(const Rectangle r, const Sprites *s);
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

private:
	/* Calculates the ricochet */
	void calculate_dir(float norm_x, float norm_y);

	/* changes the direction ever so slightly */
	void randomize_dir();

	// Attributes
private:
	
	float velocity_x,	// velocity in the x-dir
		  velocity_y;	// velocity in the y-dir
};


#endif // BAT_H_