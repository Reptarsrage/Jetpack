/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "FastSolid.h"
#include "Enums.h"


const int PHASE_RESISTANCE = 10; // how many ticks does it take to phase through this?
const int PHASE_RECOVERY = 50;   // how many ticks does it take to recover from being phased?

FastSolid::FastSolid(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

FastSolid::FastSolid(const Rectangle r, const Sprites *s){
	Init(r, s);
}

void FastSolid::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "FastSolid";
	sprites = s;
	type = TYPE_FASTSOLID;
	def_sprite = SPRITE_FASTSOLID;
	is_solid = true;
	is_collectable = false;
	attribute = -1;
	phased_count = PHASE_RESISTANCE;
}

FastSolid::~FastSolid(){
	delete bounds;
}

void FastSolid::phase() {
	if (phased_count < 0) {
		is_solid = false;
		phased_count = PHASE_RECOVERY;
	} else
		phased_count -= 2;
}

void FastSolid::draw(){
	glBindTexture(GL_TEXTURE_2D, sprites->getSprite(def_sprite));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	if (!is_solid && phased_count > 0) {
		glBindTexture(GL_TEXTURE_2D, sprites->getSprite(SPRITE_SOLIDPHASED));
		bounds->draw();
		glBindTexture(GL_TEXTURE_2D, 0);
		phased_count--;
	} else if (!is_solid) {
		is_solid = true;
		phased_count = PHASE_RESISTANCE;
	} else if (phased_count < PHASE_RESISTANCE)
		phased_count++;
}