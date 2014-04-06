/* Justin Robb
 * 4-5-14
 * Teleporter
*/

#ifndef TELEPORTER_H_
#define TELEPORTER_H_

#include "SolidThing.h"

class Rectangle;
class Sprites;

/*
 * Teleports the hero and certain other baddies to other teleporters around the map.
 */
class Teleporter : public SolidThing {
// Functions
public:
	Teleporter(float x, float y, float w, float h, const Sprites *s);
	Teleporter(const Rectangle r, const Sprites *s);
	~Teleporter();

	/* binds this teleporter to a color group */
	virtual void bindTeleporter(int code);

	/* Draws this thing in its bounds */
	virtual void draw();

	/* Sets the bounds for this thing. */
	void SetBounds(float x, float y, float width, float height);
		
private:
	/* initializes this baddie */
	void Init(const Rectangle r, const Sprites *s);

// Attributes
protected:
	Rectangle *draw_bounds;	// the bounds to draw the sprite in (different from actual bounds)
};

#endif // TELEPORTER_H_