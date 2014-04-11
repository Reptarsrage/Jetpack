/* Justin Robb
 * 3-27-14
 * Box
*/

#ifndef BOX_H_
#define BOX_H_

#include "SolidThing.h"

/*
 * A solid box object.
 */
class Box : public SolidThing {
// Functions
public:
	Box(float x, float y, float w, float h, const Sprites *s);
	Box(const Rectangle r, const Sprites *s);
	~Box();
	
	// boxes can not have attributes 
	virtual void setAttribute(int code) {}

	/* can this be phased from a certain diretion? */
	virtual bool phaseable(int dir) const { return true; }

	/* handles being phased */
	virtual void phase();

	/* Draws this thing */
	virtual void draw();

private:
	/* initializes this thing */
	void Init(const Rectangle r, const Sprites *s);
};

#endif // BOX_H_