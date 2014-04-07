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

private:
	/* initializes this thing */
	void Init(const Rectangle r, const Sprites *s);

};

#endif // LADDER_H_