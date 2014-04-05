/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "SolidThing.h"
#include "Enums.h"

SolidThing::SolidThing() {
}

SolidThing::SolidThing(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

SolidThing::SolidThing(const Rectangle r, const Sprites *s){
	Init(r, s);
}

void SolidThing::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	attribute_bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "SolidThing";
	sprites = s;
	type = TYPE_STONESOLID;
	def_sprite = SPRITE_NONPSOLID;
	attribute = -1;
}

SolidThing::~SolidThing(){
	delete bounds;
	delete attribute_bounds;
}

const char *SolidThing::ToString() const{
	return name;
}


void SolidThing::setAttribute(int code) {
	attribute = code;
	if (code == MOSSY) {
		name = "Mossy Stone";
		attribute_sprite = SPRITE_MOSSSOLID;
	} else if (code == ICY) {
		attribute_sprite = SPRITE_ICESOLID;
		name = "Icy Stone";
	} else if (code == CONVEYOR_LEFT || code == CONVEYOR_RIGHT) {
		name = "Conveyor Stone";
		attribute_sprite = SPRITE_CONVEYORSOLID1;
	} else {
		attribute = -1;
		attribute_bounds->height = 0;
		attribute_bounds->width = 0;
		printf("Unrecognized solid attribute, code: %d", code);
	}
}

void SolidThing::draw(){
	glBindTexture(GL_TEXTURE_2D, sprites->getSprite(def_sprite));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	if (attribute >= 0) {
		glBindTexture(GL_TEXTURE_2D, sprites->getSprite(attribute_sprite));
		attribute_bounds->draw();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}