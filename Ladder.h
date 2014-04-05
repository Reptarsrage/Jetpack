/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef LADDER_H_
#define LADDER_H_

#include "StationaryThing.h"

class Rectangle;
class Sprites;

/*
 * Base class for all things which do not move in the game, i.e. blocks, Ladders.
 */
class Ladder : public StationaryThing {
// Functions
public:
	Ladder(float x, float y, float w, float h, const Sprites *s);
	Ladder(const Rectangle r, const Sprites *s);
	~Ladder();
	void Init(const Rectangle r, const Sprites *s);

	/* Returns the name of this thing */
	virtual const char *ToString() const;

	/* Draws this thing */
	virtual void draw();
};

#endif // LADDER_H_