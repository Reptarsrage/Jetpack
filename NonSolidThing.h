/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef NONSOLID_THING_H_
#define NONSOLID_THING_H_

#include "StationaryThing.h"

class Rectangle;
class Sprites;

/*
 * Base class for all things which do not move in the game, i.e. blocks, collectables.
 */
class NonSolidThing : public StationaryThing {
// Functions
public:
	NonSolidThing(float x, float y, float w, float h, const Sprites *s);
	NonSolidThing(const Rectangle r, const Sprites *s);
	~NonSolidThing();
	
	/* Returns the name of this thing */
	virtual const char *ToString() const;

	/* Draws this thing */
	virtual void draw();

	/* sets the sprite to draw */
	virtual void setInfo(int code, int sprite, char * name);
	
private:
	/* initializes this thing */
	void Init(const Rectangle r, const Sprites *s);

};

#endif // NONSOLID_THING_H_