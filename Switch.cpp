/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "Switch.h"
#include "Enums.h"

Switch::Switch(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Switch::Switch(const Rectangle r, const Sprites *s){
	Init(r, s);
}

void Switch::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	sprites = s;
	name = "Switch";
	def_sprite = SPRITE_REDSWITCH;
	type = TYPE_REDSWITCH;
}

Switch::~Switch(){
	delete bounds;
}

const char *Switch::ToString() const{
	return name;
}

void Switch::bindSwitch(int code){
	assert(code >= 0);
	assert(code < SWITCH_COUNT);
	switch (code) {
		case SWITCH_BLUE_H:
		case SWITCH_BLUE_V:
			type = TYPE_BLUESWITCH;
			def_sprite = SPRITE_BLUESWITCH;
			break;
		case SWITCH_RED_V:
		case SWITCH_RED_H:
			type = TYPE_REDSWITCH;
			def_sprite = SPRITE_REDSWITCH;
			break;
		case SWITCH_GOLD_V:
		case SWITCH_GOLD_H:
			type = TYPE_GOLDSWITCH;
			def_sprite = SPRITE_GOLDSWITCH;
			break;
	}
}

void Switch::draw(){
	glBindTexture(GL_TEXTURE_2D, sprites->getSprite(def_sprite));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}