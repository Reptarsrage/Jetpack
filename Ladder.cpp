/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "Ladder.h"
#include "Enums.h"

Ladder::Ladder(float x, float y, float w, float h, const Sprites *s) {
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Ladder::Ladder(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Ladder::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Ladder";
	type = TYPE_LADDER;
	sprites = s;
	def_sprite = SPRITE_LADDER;
	is_solid = false;
	is_collectable = false;
}

Ladder::~Ladder(){
	delete bounds;
}