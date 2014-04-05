/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef GOLD_H_
#define GOLD_H_

#include "Collectable.h"

class Rectangle;
class Sprites;

/*
 * Base class for all things which do not move in the game, i.e. blocks, GOLDs.
 */
class Gold : public Collectable{
// Functions
public:
	Gold(float x, float y, float w, float h, const Sprites *s);
	Gold(const Rectangle r, const Sprites *s);
	~Gold();
	
	/* Initialization for multiple cnstrs */
	virtual void Init(const Rectangle r, const Sprites *s);

	/* Returns the name of this thing */
	virtual const char *ToString() const;

	/* Sets the value and sprite of this thing */
	/* 0 - 100 small */
	/* 101 - 250 medium */
	/* 251 - 500 larg */
	/* 501+ Extra large */
	virtual void setValue(int value);

	/* Collects this thing, and returns the points for doing so. */
	virtual int Collect();
};

#endif // GOLD_H_