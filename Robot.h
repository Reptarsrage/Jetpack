/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef ROBOT_H_
#define ROBOT_H_

#include "MovingThing.h"

class Rectangle;
class Sprites;

/*
 * Position and properties of the non-player controlled Robot baddie. 
 */
class Robot : public MovingThing {

// Functions
public:

	~Robot();
	Robot(float x, float y, float w, float h, const Sprites *s);
	Robot(const Rectangle r, const Sprites *s);
	void Init(const Rectangle r, const Sprites *s);
	
	/* Moves this thing by one */
	virtual void move(float x, float y);

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

	/*  Sets whether this moving thing is on a solid surface */
	virtual void Grounded(bool b);

	/*  Sets whether this moving thing can climb a ladder */
	virtual void OnLadder(bool b, float ladder_x, float ladder_y);

	/*  Sets the x-velocity to match the direction to hunt the hero */
	virtual void SetDir();

// Attributes
private:

	float velocity_x,	// velocity in the x-dir
		  velocity_y;	// velocity in the y-dir
};


#endif // ROBOT_H_