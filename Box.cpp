/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "Box.h"
#include "Enums.h"

Box::Box(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Box::Box(const Rectangle r, const Sprites *s){
	Init(r, s);
}

void Box::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Box";
	sprites = s;
	type = TYPE_BOX;
	def_sprite = SPRITE_BOX;
	is_solid = true;
	is_collectable = false;
}

Box::~Box(){
	delete bounds;
}