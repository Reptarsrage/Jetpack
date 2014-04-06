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
	Collectable() {}	// default constructure for inherited items

	/* Returns the name of this thing */
	virtual const char *ToString() const;

	/* Collects this thing, and returns the points for doing so. */
	virtual int Collect();

	/* Is this thing already collected? */
	virtual bool Collected();

	/* Draws this thing */
	virtual void draw();
	
private:
	/* initializes this baddie */
	void Init(const Rectangle r, const Sprites *s);

// Attributes
protected:
	
	/* Is this still up for grabs? */
	bool collected;

	/* How many points is this worth? */
	int point_value;
};

#endif // COLLECTABLE_H_