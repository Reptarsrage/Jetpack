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
	SolidThing();
	~SolidThing();

	/* Initialization for multiple cnstrs */
	virtual void Init(const Rectangle r, const Sprites *s);

	/* Returns the name of this thing */
	virtual const char *ToString() const;

	/* Sets an additional property of the block */
	virtual void setAttribute(int code);

	/* Draws this thing */
	virtual void draw();

private:
	int attribute;
	GLuint attribute_sprite;
	Rectangle * attribute_bounds;
};

#endif // SOLID_THING_H_