/* Justin Robb
 * 3-27-14
 * Gem
*/

#ifndef GEM_H_
#define GEM_H_

#include "Collectable.h"

/*
 * A gem is an integral part of the game, for the her must collect
 * all gems before he can win the level by exiting through the door.
 */
class Gem : public Collectable{

// Functions
public:
	Gem(float x, float y, float w, float h, const Sprites *s);
	Gem(const Rectangle r, const Sprites *s);
	~Gem();

	/* Collects this thing, and returns the points for doing so. */
	virtual int Collect();
	
private:
	/* initializes this thing */
	void Init(const Rectangle r, const Sprites *s);
};

#endif // GEM_H_