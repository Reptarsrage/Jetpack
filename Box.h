/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef BOX_H_
#define BOX_H_

#include "SolidThing.h"

class Rectangle;
class Sprites;

/*
 * Base class for all things which do not move in the game, i.e. blocks, collectables.
 */
class Box : public SolidThing {
// Functions
public:
	Box(float x, float y, float w, float h, const Sprites *s);
	Box(const Rectangle r, const Sprites *s);
	~Box();
	
	/* Initialization for multiple cnstrs */
	virtual void Init(const Rectangle r, const Sprites *s);
};

#endif // BOX_H_