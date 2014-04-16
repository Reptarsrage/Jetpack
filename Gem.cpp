/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "Gem.h"
#include "Enums.h"

Gem::Gem(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Gem::Gem(const Rectangle r, const Sprites *s){
	Init(r, s);
}


void Gem::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Gem";
	sprites = s;
	collected = false;
	type = TYPE_GEM;
	def_sprite = SPRITE_GEM;
	is_solid = false;
	is_collectable = true;
	point_value = 20;
	gen_type = COLLECTABLE;
}

Gem::~Gem(){
	delete bounds;
}

int Gem::Collect() {
	collected = true;
	def_sprite = SPRITE_GEMCOLLECTED;
	return point_value;
}