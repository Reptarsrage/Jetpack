/* Justin Robb
 * 3-27-14
 * Door
*/

#ifndef DOOR_H_
#define DOOR_H_

#include "StationaryThing.h"

/*
 * Base class for the door, whch acts as a goal in the game.
 */
class Door : public StationaryThing {
// Functions
public:
	Door(float x, float y, float w, float h, const Sprites *s);
	Door(const Rectangle r, const Sprites *s);
	~Door();

	/* Open the door */
	virtual void Open();

	/* Draws this thing */
	virtual bool IsOpen() { return is_open; }
	
private:
	/* initializes this door */
	void Init(const Rectangle r, const Sprites *s);

// Attributes
private:
	bool is_open;
};

#endif // DOOR_H_