/* Justin Robb
 * 3-27-14
 * A brick block
*/

#ifndef BRICK_SOLID_THING_H_
#define BRICK_SOLID_THING_H_

#include "SolidThing.h"

class Rectangle;
class Sprites;

/*
 * Solid brick object.
 */
class BrickSolid : public SolidThing {
// Functions
public:
	BrickSolid(float x, float y, float w, float h, const Sprites *s);
	BrickSolid(const Rectangle r, const Sprites *s);
	~BrickSolid();

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

#endif // BRICK_SOLID_THING_H_