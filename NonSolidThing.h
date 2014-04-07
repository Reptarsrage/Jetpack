/* Justin Robb
 * 3-27-14
 * Non solid
*/

#ifndef NONSOLID_THING_H_
#define NONSOLID_THING_H_

#include "StationaryThing.h"

/*
 * Base class for all things which do not move in the game, and
 * do not contribute except for decoration, i.e. pillars, ivy.
 */
class NonSolidThing : public StationaryThing {
// Functions
public:
	/* REMEMBER call setInfo() */
	NonSolidThing(float x, float y, float w, float h, const Sprites *s);
	/* REMEMBER call setInfo() */
	NonSolidThing(const Rectangle r, const Sprites *s);
	~NonSolidThing();

	/* sets the sprite to draw 
	 * this should always be called immediatyle after construction!
	 */
	virtual void setInfo(int code, int sprite, char * name);
	
private:
	/* initializes this thing */
	void Init(const Rectangle r, const Sprites *s);

};

#endif // NONSOLID_THING_H_