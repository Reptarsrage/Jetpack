/* Justin Robb
 * 3-27-14
 * A useful Item
*/

#ifndef ITEM_H_
#define ITEM_H_

#include "Collectable.h"

/*
 * Base class for all things which help the hero, invincibility, fuel, ect.
 */
class Item : public Collectable{
// Functions
public:
	Item(float x, float y, float w, float h, const Sprites *s);
	Item(const Rectangle r, const Sprites *s);
	~Item();

	/* Sets the type and sprite of this thing */
	virtual void setType(int code);

	/* Collects this thing, and returns the points for doing so. */
	virtual int Collect();

private:
	/* initializes this item */
	void Init(const Rectangle r, const Sprites *s);
};

#endif // ITEM_H_