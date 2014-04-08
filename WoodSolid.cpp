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
}

void WoodSolid::setAttribute(int code) {
	assert(code >= 0);
	attribute = code;
	switch (code){
		case MOSSY:
			attribute_sprite = SPRITE_MOSSSOLID;
			name = "Mossy Wood";
			type = TYPE_WOODSOLID_MOSSY;
			break;
		case ICY:
			name = "Icy Wood";
			attribute_sprite = SPRITE_ICESOLID;
			type = TYPE_WOODSOLID_ICY;
			break;
		case SHIELDED_LEFT:
			name = "Left Shielded Wood";
			attribute_sprite = SPRITE_L;
			type = TYPE_SHIELDED_WOOD_L;
			break;
		case  SHIELDED_RIGHT:
			name = "Right Shielded Wood";
			attribute_sprite = SPRITE_R;
			type = TYPE_SHIELDED_WOOD_R;
			break;
		case SHIELDED_UP:
			name = "Top Shielded Wood";
			attribute_sprite = SPRITE_U;
			type = TYPE_SHIELDED_WOOD_U;
			break;
		case SHIELDED_DOWN:
			name = "Bottom Shielded Wood";
			attribute_sprite = SPRITE_D;
			type = TYPE_SHIELDED_WOOD_D;
			break;
		case CONVEYOR_LEFT:
			name = "Conveyor Left Wood";
			attribute_sprite = SPRITE_CONVEYORSOLID1;
			type = TYPE_WOODSOLID_CONVEYOR_L;
			break;
		case CONVEYOR_RIGHT:
			name = "Conveyor Right Wood";
			attribute_sprite = SPRITE_CONVEYORSOLID2;
			type = TYPE_WOODSOLID_CONVEYOR_R;
			break;
		default:
			attribute = -1;
			printf("Unrecognized solid attribute, code: %d", code);
			break;
	}
}

void WoodSolid::draw(){
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