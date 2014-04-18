/* Justin Robb
 * 4-4-14
 * Switch Solid
*/

#ifndef SWITCH_SOLID_THING_H_
#define SWITCH_SOLID_THING_H_

#include "SolidThing.h"

/*
 * A solid thing which can be turned on and off by switches.
 * Ther are different colors representing which solids are turned on/off
 * when each switch is pressed. The solid can be either verticle or horizontal.
 */
class SwitchSolid : public SolidThing {
// Functions
public:
	SwitchSolid(float x, float y, float w, float h, const Sprites *s);
	SwitchSolid(const Rectangle r, const Sprites *s);
	~SwitchSolid();

	/* Draws this thing */
	virtual void draw();

	/* binds the color to a colored switch */
	virtual void bindSwitch(int code);

	/* turns this switch solid on and off */
	virtual void Switch();

	/* switches can't have attributes */
	virtual void setAttribute(int code) {}
	
private:
	/* initializes this thing */
	void Init(const Rectangle r, const Sprites *s);
};

#endif // SWITCH_SOLID_THING_H_