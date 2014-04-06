/* Justin Robb
 * 3-27-14
 * Switch
*/

#ifndef SWITCH_H_
#define SWITCH_H_

#include "StationaryThing.h"

class Rectangle;
class Sprites;

/*
 * Switches in the game can turn certain solid blocks on and off.
 * These blocks are called switchsolids
 */
class Switch : public StationaryThing {
// Functions
public:
	Switch(float x, float y, float w, float h, const Sprites *s);
	Switch(const Rectangle r, const Sprites *s);
	~Switch();
	
	/* Returns the name of this thing */
	virtual const char *ToString() const;

	/* Draws this thing */
	virtual void draw();

	/* binds the switch to a switch color group */
	virtual void bindSwitch(int code);
	
private:
	/* initializes this baddie */
	void Init(const Rectangle r, const Sprites *s);
};

#endif // SWITCH_H_