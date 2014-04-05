/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef FAST_SOLID_THING_H_
#define FAST_SOLID_THING_H_

#include "SolidThing.h"

class Rectangle;
class Sprites;

/*
 * Base class for all things which do not move in the game, i.e. blocks, collectables.
 */
class FastSolid : public SolidThing {
// Functions
public:
	FastSolid(float x, float y, float w, float h, const Sprites *s);
	FastSolid(const Rectangle r, const Sprites *s);
	~FastSolid();
	
	/* Initialization for multiple cnstrs */
	virtual void Init(const Rectangle r, const Sprites *s);
};

#endif // FAST_SOLID_THING_H_