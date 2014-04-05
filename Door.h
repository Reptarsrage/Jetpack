/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef DOOR_H_
#define DOOR_H_

#include "StationaryThing.h"

class Rectangle;
class Sprites;

/*
 * Base class for all things which do not move in the game, i.e. blocks, collectables.
 */
class Door : public StationaryThing {
// Functions
public:
	Door(float x, float y, float w, float h, const Sprites *s);
	Door(const Rectangle r, const Sprites *s);
	~Door();
	
	/* Initialization for multiple cnstrs */
	virtual void Init(const Rectangle r, const Sprites *s);

	/* Returns the name of this thing */
	virtual const char *ToString() const;

	/* Draws this thing */
	virtual void draw();

	/* Open the door */
	virtual void Open();

	/* Draws this thing */
	virtual bool IsOpen() { return is_open; }

// Attributes

private:
	bool is_open;
};

#endif // DOOR_H_