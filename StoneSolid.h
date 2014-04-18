/* Justin Robb
 * 3-27-14
 * Stone Solid
*/

#ifndef STONE_SOLID_H_
#define STONE_SOLID_H_

#include "SolidThing.h"

/*
 * A non-phasable stone block.
 */
class StoneSolid : public SolidThing {
// Functions
public:
	StoneSolid(float x, float y, float w, float h, const Sprites *s);
	StoneSolid(const Rectangle r, const Sprites *s);
	~StoneSolid();

	/* Sets an additional property of the block */
	/* should be called immediately afer construction, if there is an attribute! */
	virtual void setAttribute(int code);

	/* returns the attribute value of this thing. */
	virtual int getAttribute() { return attribute; }

	/* Draws this thing */
	virtual void draw();
		
private:
	/* initializes this thing */
	void Init(const Rectangle r, const Sprites *s);

// Attributes
private:
	int switch_time;	// update conveyor sprite
};

#endif // STONE_SOLID_H_