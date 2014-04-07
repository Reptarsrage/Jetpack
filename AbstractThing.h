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
	virtual const Rectangle Bounds() const {return *bounds; }
	
	/* Returns true if this thing's bounds conflict with the other thing's bounds. */
	virtual bool Overlaps(const AbstractThing *other) const { return bounds->Overlaps(other->Bounds()); }
	
	/* Returns true if this thing's bounds conflict with the rectangle. */
	virtual bool Overlaps(const Rectangle other) const { return bounds->Overlaps(other); }

	/* Sets the bounds for this thing. */
	virtual void SetBounds(float x, float y, float width, float height) 
		{ if (bounds) delete bounds; bounds = new Rectangle(x, y, width, height); }

	/* returns a descriptive integer to what this thing is */
	/* See TypeEnum in Enums.h for more info */
	virtual int getType() const { return type; }

	/* Returns the name of this thing. */
	virtual const char *ToString() const { return name; }

// Pure Virtual Functions
public:

	/* Draws this thing in its bounds */
	virtual void draw()= 0;
	
// Atributes
protected:
	Rectangle *bounds;			// The bounds of this thing.
	char * name;				// The name of this thing.
	const Sprites *sprites;		// A pointer to the sprite manager (for drawing this thing).
	int type;					// What kind of thing?
	GLuint def_sprite;			// Which sprite to use to draw this thing
};

#endif // ABSTRACT_THING_H_