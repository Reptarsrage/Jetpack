/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "SolidThing.h"
#include "Enums.h"

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
	name = "SolidThing";
	sprites = s;
	type = TYPE_SOLID;
	def_sprite = SPRITE_NONPSOLID;
}

SolidThing::~SolidThing(){
	delete bounds;
}

const char *SolidThing::ToString() const{
	return name;
}

void SolidThing::draw(){
	glBindTexture(GL_TEXTURE_2D, sprites->getSprite(def_sprite));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}