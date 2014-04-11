/* Justin Robb
 * 3-27-14
 * A brick block
*/

#ifndef BRICK_SOLID_THING_H_
#define BRICK_SOLID_THING_H_

#include "SolidThing.h"

/*
 * Solid brick object.
 */
class BrickSolid : public SolidThing {
// Functions
public:
	BrickSolid(float x, float y, float w, float h, const Sprites *s);
	BrickSolid(const Rectangle r, const Sprites *s);
	~BrickSolid();

	/* Sets an additional property of the block */
	virtual void setAttribute(int code);

	/* Draws this thing */
	virtual void draw();

	/* can this be phased from a certain diretion? */
	virtual bool phaseable(int dir) const;

	/* handles being phased */
	virtual void phase();
		
private:
	/* initializes this thing */
	void Init(const Rectangle r, const Sprites *s);

private:
	Rectangle * attribute_bounds;
	int phased_count;

};

#endif // BRICK_SOLID_THING_H_