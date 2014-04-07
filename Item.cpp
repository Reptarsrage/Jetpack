/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "Item.h"
#include "Enums.h"

Item::Item(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Item::Item(const Rectangle r, const Sprites *s){
	Init(r, s);
}

void Item::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Item";
	sprites = s;
	collected = false;
	point_value = 0;
	setType(TYPE_FULLFUEL);
	is_solid = false;
	is_collectable = true;
}

Item::~Item(){
	delete bounds;
}

void Item::setType(int code) {
	assert(code > 0);
	assert(code < TYPE_COUNT);
	type = code;
	switch (code) {
		case TYPE_HALFFUEL:
			def_sprite = SPRITE_HALFFUEL;
			name = "Half Fuel Tank";
			break;
		case TYPE_FULLFUEL:
			def_sprite = SPRITE_FULLFUEL;
			name = "Full Fuel Tank";
			break;
		case TYPE_TIMER:
			def_sprite = SPRITE_TIMER;
			name = "Timer";
			break;
		case TYPE_INVINCIBILITY:
			def_sprite = SPRITE_INVINCIBILITY;
			name = "Invincibility";
			break;
		default:
			printf("Unkown type for an Item, code: %d", code);
			break;
	}
}

int Item::Collect(){
	collected = true;
	bounds->height = 0;
	bounds->width = 0;
	return 0;
}