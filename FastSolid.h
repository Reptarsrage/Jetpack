/* Justin Robb
 * 3-27-14
 * Fast Solid
*/

#ifndef FAST_SOLID_THING_H_
#define FAST_SOLID_THING_H_

#include "SolidThing.h"

/*
 * A solid thing which the hero can phase through quickly
 */
class FastSolid : public SolidThing {
// Functions
public:
	FastSolid(float x, float y, float w, float h, const Sprites *s);
	FastSolid(const Rectangle r, const Sprites *s);
	~FastSolid();

	// fastsolids can not have attributes 
	virtual void setAttribute(int code) {}

private:
	/* initializes this thing */
	void Init(const Rectangle r, const Sprites *s);
};

#endif // FAST_SOLID_THING_H_