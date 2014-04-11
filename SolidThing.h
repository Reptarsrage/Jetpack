/* Justin Robb
 * 3-27-14
 * Solid Thing
*/

#ifndef SOLID_THING_H_
#define SOLID_THING_H_

#include "StationaryThing.h"

/*
 * Base class (abstract )for all solid things which do not move in the game, i.e. blocks.
 */
class SolidThing : public StationaryThing {
// Functions
public:

	/* gets the grounds attribute */
	virtual int getAttribute() { return attribute; }

	/* Sets an additional property of the block */
	/* should be called immediately afer construction, if there is an attribute! */
	virtual void setAttribute(int code) = 0;

	/* can this be phased from a certain diretion? */
	virtual bool phaseable(int dir) const { return false; }

	/* handles being phased */
	virtual void phase() { is_solid = false; }

protected:
	int attribute;				// a solid thing may have one attribute, i.e. ice, moss.
	GLuint attribute_sprite;	// Sprite for attribute to draw on top of this thing
};

#endif // SOLID_THING_H_