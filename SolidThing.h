/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef SOLID_THING_H_
#define SOLID_THING_H_

#include "StationaryThing.h"

class Rectangle;
class Sprites;

/*
 * Base class for all things which do not move in the game, i.e. blocks, collectables.
 */
class SolidThing : public StationaryThing {
// Functions
public:
	SolidThing(float x, float y, float w, float h, const Sprites *s);
	SolidThing(const Rectangle r, const Sprites *s);
	~SolidThing();
	
	/* Returns the name of this thing */
	virtual const char *ToString() const;

	/* Draws this thing */
	virtual void draw();

// Attributes
private:
	/* Which sprite to use to draw this thing */
	GLuint def_sprite;
};

#endif // SOLID_THING_H_