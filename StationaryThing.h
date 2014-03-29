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
	StationaryThing(float x, float y, float w, float h, const Sprites *s);
	StationaryThing(const Rectangle r, const Sprites *s);
	~StationaryThing();
	
	/* Returns the name of this thing */
	virtual const char *ToString() const;

	/* Draws this thing */
	virtual void draw();

// Attributes
private:
	/* Which sprite to use to draw this thing */
	GLuint def_sprite;
};

#endif // STATIONARY_THING_H_