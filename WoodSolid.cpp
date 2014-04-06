/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "WoodSolid.h"
#include "Enums.h"

WoodSolid::WoodSolid(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

WoodSolid::WoodSolid(const Rectangle r, const Sprites *s){
	Init(r, s);
}

void WoodSolid::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	attribute_bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "WoodSolid";
	sprites = s;
	type = TYPE_WOODSOLID;
	def_sprite = SPRITE_HARDERSOLID;
	attribute = -1;
	is_solid = true;
	is_collectable = false;
}

WoodSolid::~WoodSolid(){
	delete bounds;
	delete attribute_bounds;
}

void WoodSolid::setAttribute(int code) {
	attribute = code;
	switch (code){
		case MOSSY:
			attribute_sprite = SPRITE_MOSSSOLID;
			name = "Mossy Brics";
			break;
		case ICY:
			name = "Icy Wood";
			attribute_sprite = SPRITE_ICESOLID;
			break;
		case SHIELDED_LEFT:
			name = "Left Shielded Wood";
			attribute_sprite = SPRITE_L;
			break;
		case  SHIELDED_RIGHT:
			name = "Right Shielded Wood";
			attribute_sprite = SPRITE_R;
			break;
		case SHIELDED_UP:
			name = "Top Shielded Wood";
			attribute_sprite = SPRITE_U;
			break;
		case SHIELDED_DOWN:
			name = "Bottom Shielded Wood";
			attribute_sprite = SPRITE_D;
			break;
		case CONVEYOR_LEFT:
		case CONVEYOR_RIGHT:
			name = "Conveyor Wood";
			attribute_sprite = SPRITE_CONVEYORSOLID1;
			break;
		default:
			attribute = -1;
			attribute_bounds->height = 0;
			attribute_bounds->width = 0;
			printf("Unrecognized solid attribute, code: %d", code);
			break;
	}
}

void WoodSolid::draw(){
	glBindTexture(GL_TEXTURE_2D, sprites->getSprite(def_sprite));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	if (attribute >= 0) {
		glBindTexture(GL_TEXTURE_2D, sprites->getSprite(attribute_sprite));
		attribute_bounds->draw();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}