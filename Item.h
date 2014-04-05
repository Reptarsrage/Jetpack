/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef ITEM_H_
#define ITEM_H_

#include "Collectable.h"

class Rectangle;
class Sprites;

/*
 * Base class for all things which do not move in the game, i.e. blocks, Items.
 */
class Item : public Collectable{
// Functions
public:
	Item(float x, float y, float w, float h, const Sprites *s);
	Item(const Rectangle r, const Sprites *s);
	~Item();
	
	/* Initialization for multiple cnstrs */
	virtual void Init(const Rectangle r, const Sprites *s);

	/* Returns the name of this thing */
	virtual const char *ToString() const;

	/* Sets the type and sprite of this thing */
	virtual void setType(int code);

	/* Collects this thing, and returns the points for doing so. */
	virtual int Collect();
};

#endif // ITEM_H_