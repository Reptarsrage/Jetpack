/* Justin Robb
 * 3-27-14
 * Stationary Thing
*/

#ifndef STATIONARY_THING_H_
#define STATIONARY_THING_H_

#include "AbstractThing.h"

class Rectangle;
class Sprites;

/*
 * Base class for all things which do not move in the game, i.e. blocks, collectables.
 */
class StationaryThing : public AbstractThing{
// Functions
public:

	/* Returns the name of this thing. */
	virtual const char *ToString() const { return name; }

// Attributes
public:
	bool is_solid,			// is this thing solid?
		 is_collectable;	// is this thing collectable by the hero?
};

#endif // STATIONARY_THING_H_