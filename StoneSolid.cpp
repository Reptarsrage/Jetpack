/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "StoneSolid.h"
#include "Enums.h"

StoneSolid::StoneSolid(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

StoneSolid::StoneSolid(const Rectangle r, const Sprites *s){
	Init(r, s);
}

void StoneSolid::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "StoneSolid";
	sprites = s;
	type = TYPE_STONESOLID;
	def_sprite = SPRITE_NONPSOLID;
	attribute = -1;
	is_solid = true;
	is_collectable = false;
}

StoneSolid::~StoneSolid(){
	delete bounds;
}

void StoneSolid::setAttribute(int code) {
	assert(code >= 0);
	attribute = code;
	if (code == MOSSY) {
		name = "Mossy Stone";
		attribute_sprite = SPRITE_MOSSSOLID;
		type = TYPE_STONESOLID_MOSSY;
	} else if (code == ICY) {
		attribute_sprite = SPRITE_ICESOLID;
		name = "Icy Stone";
		type = TYPE_STONESOLID_ICY;
	} else if (code == CONVEYOR_LEFT || code == CONVEYOR_RIGHT) {
		name = "Conveyor Stone";
		attribute_sprite = SPRITE_CONVEYORSOLID1;
		type = TYPE_STONESOLID_CONVEYOR_L;
	} else {
		attribute = -1;
		printf("Unrecognized solid attribute, code: %d", code);
	}
}

void StoneSolid::draw(){
	glBindTexture(GL_TEXTURE_2D, sprites->getSprite(def_sprite));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	if (attribute >= 0) {
		assert(attribute_sprite >= 0);
		assert(attribute_sprite < SPRITE_COUNT);
		glBindTexture(GL_TEXTURE_2D, sprites->getSprite(attribute_sprite));
		bounds->draw();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}