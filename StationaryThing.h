/* Justin Robb
 * 3-27-14
 * JetPack
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
	/* Initialization for multiple cnstrs */
	virtual void Init(const Rectangle r, const Sprites *s) = 0;

// Attributes
public:
	bool is_solid,
		 is_collectable;

private:
	/* Which sprite to use to draw this thing */
	GLuint def_sprite;
};

#endif // STATIONARY_THING_H_