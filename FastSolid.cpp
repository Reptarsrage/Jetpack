/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "FastSolid.h"
#include "Enums.h"

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
}

FastSolid::~FastSolid(){
	delete bounds;
}