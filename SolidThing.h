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

	/* Sets an additional property of the block */
	/* should be called immediately afer construction, if there is an attribute! */
	virtual void setAttribute(int code) = 0;
		
protected:
	int attribute;
	GLuint attribute_sprite;
	Rectangle * attribute_bounds;
};

#endif // SOLID_THING_H_