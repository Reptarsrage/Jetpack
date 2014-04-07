/* Justin Robb
 * 3-27-14
 * Stationary Thing
*/

#ifndef STATIONARY_THING_H_
#define STATIONARY_THING_H_

#include "AbstractThing.h"

/*
 * Base class ( abstract) for all things which do not move in the game, i.e. blocks, collectables.
 */
class StationaryThing : public AbstractThing{
// Functions
public:
	/* draws this thing */
	virtual void draw() {
		glBindTexture(GL_TEXTURE_2D, sprites->getSprite(def_sprite));
		bounds->draw();
		glBindTexture(GL_TEXTURE_2D, 0);
	}

// Attributes
public:
	bool is_solid,			// is this thing solid?
		 is_collectable;	// is this thing collectable by the hero?
};

#endif // STATIONARY_THING_H_