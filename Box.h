/* Justin Robb
 * 3-27-14
 * Box
*/

#ifndef BOX_H_
#define BOX_H_

#include "SolidThing.h"

class Rectangle;
class Sprites;

/*
 * A solid box object.
 */
class Box : public SolidThing {
// Functions
public:
	Box(float x, float y, float w, float h, const Sprites *s);
	Box(const Rectangle r, const Sprites *s);
	~Box();
		
private:
	/* initializes this thing */
	void Init(const Rectangle r, const Sprites *s);
};

#endif // BOX_H_