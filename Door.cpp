/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "Door.h"
#include "Enums.h"

Door::Door(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Door::Door(const Rectangle r, const Sprites *s){
	Init(r, s);
}

void Door::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Door";
	sprites = s;
	type = TYPE_DOOR;
	def_sprite = SPRITE_DOORCLOSED;
	is_open = false;
	gen_type = OTHER;
}

Door::~Door(){
	delete bounds;
}

void Door::Open()  { 
	def_sprite = SPRITE_DOOROPEN;
	is_open = true;
}