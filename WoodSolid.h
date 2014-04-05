/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef WOOD_SOLID_THING_H_
#define WOOD_SOLID_THING_H_

#include "SolidThing.h"

class Rectangle;
class Sprites;

/*
 * Base class for all things which do not move in the game, i.e. blocks, collectables.
 */
class WoodSolid : public SolidThing {
// Functions
public:
	WoodSolid(float x, float y, float w, float h, const Sprites *s);
	WoodSolid(const Rectangle r, const Sprites *s);
	~WoodSolid();
	
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

#endif // WOOD_SOLID_THING_H_