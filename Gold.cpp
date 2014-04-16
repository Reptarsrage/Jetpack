/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "Gold.h"
#include "Enums.h"

Gold::Gold(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Gold::Gold(const Rectangle r, const Sprites *s){
	Init(r, s);
}

void Gold::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	sprites = s;
	collected = false;
	setValue(0);
	is_solid = false;
	is_collectable = true;
	gen_type = COLLECTABLE;
}

Gold::~Gold(){
	delete bounds;
}

void Gold::setValue(int value) {
	point_value = value;
	if (value <= 100) {
		type = TYPE_GOLD1;
		def_sprite = SPRITE_GOLD1;
		name = "Gold Small";
	} else if (value <= 250) {
		type = TYPE_GOLD2;
		def_sprite = SPRITE_GOLD2;
		name = "Gold Medium";
	} else if (value <= 500) {
		type = TYPE_GOLD3;
		def_sprite = SPRITE_GOLD3;
		name = "Gold Large";
	} else {
		type = TYPE_GOLD4;
		def_sprite = SPRITE_GOLD4;
		name = "Gold Extra Large";
	}
}

int Gold::Collect(){
	collected = true;
	bounds->height = 0;
	bounds->width = 0;
	return point_value;
}