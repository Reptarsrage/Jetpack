/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "NonSolidThing.h"
#include "Enums.h"

NonSolidThing::NonSolidThing(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

NonSolidThing::NonSolidThing(const Rectangle r, const Sprites *s){
	Init(r, s);
}

void NonSolidThing::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "NonSolidThing";
	sprites = s;
	type = TYPE_PILLAR;
	def_sprite = SPRITE_PILLAR;
}

NonSolidThing::~NonSolidThing(){
	delete bounds;
}

const char *NonSolidThing::ToString() const{
	return name;
}

void NonSolidThing::draw(){
	glBindTexture(GL_TEXTURE_2D, sprites->getSprite(def_sprite));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}