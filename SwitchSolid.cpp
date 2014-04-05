/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "SwitchSolid.h"
#include "Enums.h"

SwitchSolid::SwitchSolid(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

SwitchSolid::SwitchSolid(const Rectangle r, const Sprites *s){
	Init(r, s);
}

void SwitchSolid::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "SwitchSolid";
	sprites = s;
	type = TYPE_REDSWITCHSOLID;
	def_sprite = SPRITE_REDSWITCHSOLID;
}

SwitchSolid::~SwitchSolid(){
	delete bounds;
}

void SwitchSolid::draw(){
	glBindTexture(GL_TEXTURE_2D, sprites->getSprite(def_sprite));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SwitchSolid::bindSwitch(int code) {
	assert(code >= 0);
	assert(code < SWITCH_COUNT);
	switch (code) {
		case SWITCH_BLUE_V:
			type = TYPE_BLUESWITCHSOLID;
			def_sprite = SPRITE_BLUESWITCHSOLID;
			break;
		case SWITCH_RED_V:
			type = TYPE_REDSWITCHSOLID;
			def_sprite = SPRITE_REDSWITCHSOLID;
			break;
		case SWITCH_GOLD_V:
			type = TYPE_GOLDSWITCHSOLID;
			def_sprite = SPRITE_GOLDSWITCHSOLID;
			break;
		case SWITCH_BLUE_H:
			type = TYPE_HBLUESWITCHSOLID;
			def_sprite = SPRITE_HBLUESWITCHSOLID;
			break;
		case SWITCH_RED_H:
			type = TYPE_HREDSWITCHSOLID;
			def_sprite = SPRITE_HREDSWITCHSOLID;
			break;
		case SWITCH_GOLD_H:
			type = TYPE_HGOLDSWITCHSOLID;
			def_sprite = SPRITE_HGOLDSWITCHSOLID;
			break;
	}
}