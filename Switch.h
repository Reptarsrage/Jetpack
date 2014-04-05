/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef SWITCH_H_
#define SWITCH_H_

#include "StationaryThing.h"

class Rectangle;
class Sprites;

class Switch : public StationaryThing {
// Functions
public:
	Switch(float x, float y, float w, float h, const Sprites *s);
	Switch(const Rectangle r, const Sprites *s);
	~Switch();

	/* Initialization for multiple cnstrs */
	virtual void Init(const Rectangle r, const Sprites *s);
	
	/* Returns the name of this thing */
	virtual const char *ToString() const;

	/* Draws this thing */
	virtual void draw();

	/* binds the switch to a switch color group */
	virtual void bindSwitch(int code);
};

#endif // SWITCH_H_