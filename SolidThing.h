/* Justin Robb
 * 3-27-14
 * Solid Thing
*/

#ifndef SOLID_THING_H_
#define SOLID_THING_H_

#include "StationaryThing.h"

class Rectangle;
class Sprites;

/*
 * Base class for all solid things which do not move in the game, i.e. blocks.
 */
class SolidThing : public StationaryThing {
// Functions
public:
	SolidThing(float x, float y, float w, float h, const Sprites *s);
	SolidThing(const Rectangle r, const Sprites *s);
	SolidThing();
	~SolidThing();

	/* Returns the name of this thing */
	virtual const char *ToString() const;

	/* Sets an additional property of the block */
	virtual void setAttribute(int code);

	/* Draws this thing */
	virtual void draw();
		
private:
	/* initializes this thing */
	void Init(const Rectangle r, const Sprites *s);

private:
	int attribute;
	GLuint attribute_sprite;
	Rectangle * attribute_bounds;
};

#endif // SOLID_THING_H_