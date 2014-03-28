/* Justin Robb
 * 3-27-14
 * JetPack
 * Abstract thing
*/

#ifndef ABSTRACT_THING_H_
#define ABSTRACT_THING_H_

#include "Rectangle.h"
#include "Sprites.h"

/* 
 * An abstract thing is an object within the level.
 * Objects within the level can be moving things, or stationary things.
 */
class AbstractThing {
// Functions
public:
	/* Returns a rectangle representing the bounds of this object. */
	const Rectangle Bounds() const {return *bounds; }
	
	/* Returns true if this thing's bounds conflict with the other thing's bounds. */
	bool Overlaps(const AbstractThing *other) const { return bounds->Overlaps(other->Bounds()); }
	
	/* Returns true if this thing's bounds conflict with the rectangle. */
	bool Overlaps(const Rectangle other) const { return bounds->Overlaps(other); }

	/* Sets the bounds for this thing. */
	void SetBounds(float x, float y, float width, float height) 
		{ if (bounds) delete bounds; bounds = new Rectangle(x, y, width, height); }

// Pure Virtual Functions
public:
	/* Returns the name of this thing. */
	virtual const char *ToString() const = 0;

	/* Draws this thing in its bounds */
	virtual void draw() = 0;
	
// Atributes
protected:
	Rectangle *bounds;			// The bounds of this thing.
	char * name;				// The name of this thing.
	const Sprites *sprites;		// A pointer to the sprite manager (for drawing this thing).
};

#endif // ABSTRACT_THING_H_