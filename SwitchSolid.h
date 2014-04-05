/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef SWITCH_SOLID_THING_H_
#define SWITCH_SOLID_THING_H_

#include "SolidThing.h"

class Rectangle;
class Sprites;

/*
 * Base class for all things which do not move in the game, i.e. blocks, collectables.
 */
class SwitchSolid : public SolidThing {
// Functions
public:
	SwitchSolid(float x, float y, float w, float h, const Sprites *s);
	SwitchSolid(const Rectangle r, const Sprites *s);
	~SwitchSolid();
	
	/* Initialization for multiple cnstrs */
	virtual void Init(const Rectangle r, const Sprites *s);

	/* Draws this thing */
	virtual void draw();

	/* binds the color to a colored switch */
	virtual void bindSwitch(int code);

};

#endif // SWITCH_SOLID_THING_H_