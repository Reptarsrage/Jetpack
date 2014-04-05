/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef BRICK_SOLID_THING_H_
#define BRICK_SOLID_THING_H_

#include "SolidThing.h"

class Rectangle;
class Sprites;

/*
 * Base class for all things which do not move in the game, i.e. blocks, collectables.
 */
class BrickSolid : public SolidThing {
// Functions
public:
	BrickSolid(float x, float y, float w, float h, const Sprites *s);
	BrickSolid(const Rectangle r, const Sprites *s);
	~BrickSolid();
	
	/* Initialization for multiple cnstrs */
	virtual void Init(const Rectangle r, const Sprites *s);

	/* Sets an additional property of the block */
	virtual void setAttribute(int code);

	/* Draws this thing */
	virtual void draw();

private:
	int attribute;
	GLuint attribute_sprite;
	Rectangle * attribute_bounds;

};

#endif // BRICK_SOLID_THING_H_