/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "Box.h"
#include "Enums.h"

Box::Box(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Box::Box(const Rectangle r, const Sprites *s){
	Init(r, s);
}

void Box::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Box";
	sprites = s;
	type = TYPE_BOX;
	def_sprite = SPRITE_BOX;
	is_solid = true;
	is_collectable = false;
	attribute = -1;
}

Box::~Box(){
	delete bounds;
}

void Box::phase() {
	is_solid = false;
}

void Box::draw(){
	glBindTexture(GL_TEXTURE_2D, sprites->getSprite(def_sprite));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	if (!is_solid) {
		glBindTexture(GL_TEXTURE_2D, sprites->getSprite(SPRITE_SOLIDPHASED));
		bounds->draw();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}