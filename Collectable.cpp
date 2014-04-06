/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "Collectable.h"
#include "Enums.h"

Collectable::Collectable(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Collectable::Collectable(const Rectangle r, const Sprites *s){
	Init(r, s);
}

void Collectable::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Collectable";
	sprites = s;
	collected = false;
	type = TYPE_GEM;
	def_sprite = SPRITE_GEM;
	is_solid = false;
	is_collectable = true;
}

Collectable::~Collectable(){
	delete bounds;
}

bool Collectable::Collected() {
	return collected;
}

int Collectable::Collect() {
	collected = true;
	def_sprite = SPRITE_GEMCOLLECTED;
	return point_value;
}

const char *Collectable::ToString() const{
	return name;
}

void Collectable::draw(){
	glBindTexture(GL_TEXTURE_2D, sprites->getSprite(def_sprite));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}