/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef LADDER_H_
#define LADDER_H_

#include "StationaryThing.h"

/*
 * Base class for all Ladders.
 */
class Ladder : public StationaryThing {
// Functions
public:
	Ladder(float x, float y, float w, float h, const Sprites *s);
	Ladder(const Rectangle r, const Sprites *s);
	~Ladder();

	/* Sets the direction for moving ladders */
	void setDirection(int code);

	/* draws this ladder */
	void draw();

private:
	/* initializes this thing */
	void Init(const Rectangle r, const Sprites *s);

// Attributes
public:
	int direction;

private:
	int switch_time;
};

#endif // LADDER_H_