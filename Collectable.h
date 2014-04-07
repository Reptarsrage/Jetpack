/* Justin Robb
 * 3-27-14
 * Collectable
*/

#ifndef COLLECTABLE_H_
#define COLLECTABLE_H_

#include "StationaryThing.h"

/*
 * Base class (abstract) for all collecable things in the game, i.e. gold, items, gems.
 */
class Collectable : public StationaryThing {
public:
	
	/* Is this thing already collected? */
	virtual bool Collected() { return collected; }

// Pure virtual Functions
public:

	/* Collects this thing, and returns the points for doing so. */
	virtual int Collect() = 0;

// Attributes
protected:
	
	/* Is this still up for grabs? */
	bool collected;

	/* How many points is this worth? */
	int point_value;
};

#endif // COLLECTABLE_H_