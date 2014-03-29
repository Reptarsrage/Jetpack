/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef COLLECTABLE_H_
#define COLLECTABLE_H_

#include "StationaryThing.h"

class Rectangle;
class Sprites;

/*
 * Base class for all things which do not move in the game, i.e. blocks, collectables.
 */
class Collectable : public StationaryThing{
// Functions
public:
	Collectable(float x, float y, float w, float h, const Sprites *s);
	Collectable(const Rectangle r, const Sprites *s);
	~Collectable();
	
	/* Initialization for multiple cnstrs */
	virtual void Init(const Rectangle r, const Sprites *s);

	/* Returns the name of this thing */
	virtual const char *ToString() const;

	/* Draws this thing */
	virtual void draw();

// Attributes
private:
	/* Which sprite to use to draw this thing */
	GLuint def_sprite;
};

#endif // COLLECTABLE_H_