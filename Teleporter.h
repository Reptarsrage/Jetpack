/* Justin Robb
 * 3-27-14
 * JetPack
*/

#ifndef TELEPORTER_H_
#define TELEPORTER_H_

#include "SolidThing.h"

class Rectangle;
class Sprites;

class Teleporter : public SolidThing {
// Functions
public:
	Teleporter(float x, float y, float w, float h, const Sprites *s);
	Teleporter(const Rectangle r, const Sprites *s);
	~Teleporter();
	
	/* Initialization for multiple cnstrs */
	virtual void Init(const Rectangle r, const Sprites *s);

	/* binds this teleporter to a color group */
	virtual void bindTeleporter(int code);
};

#endif // TELEPORTER_H_