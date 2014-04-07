/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "BrickSolid.h"
#include "Enums.h"

BrickSolid::BrickSolid(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

BrickSolid::BrickSolid(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void BrickSolid::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "BrickSolid";
	sprites = s;
	type = TYPE_BRICKSOLID;
	def_sprite = SPRITE_SOLID;
	attribute = -1;
	is_solid = true;
	is_collectable = false;
}

BrickSolid::~BrickSolid(){
	delete bounds;
}

void BrickSolid::setAttribute(int code) {
	assert(code >= 0);
	attribute = code;
	switch (code){
		case MOSSY:
			attribute_sprite = SPRITE_MOSSSOLID;
			type = TYPE_BRICKSOLID_MOSSY;
			name = "Mossy Brics";
			break;
		case ICY:
			name = "Icy Bricks";
			attribute_sprite = SPRITE_ICESOLID;
			type = TYPE_BRICKSOLID_ICY;
			break;
		case SHIELDED_LEFT:
			name = "Left Shielded Bricks";
			attribute_sprite = SPRITE_L;
			type = TYPE_SHIELDED_BRICK_L;
			break;
		case  SHIELDED_RIGHT:
			name = "Right Shielded Bricks";
			attribute_sprite = SPRITE_R;
			type = TYPE_SHIELDED_BRICK_R;
			break;
		case SHIELDED_UP:
			name = "Top Shielded Bricks";
			attribute_sprite = SPRITE_U;
			type = TYPE_SHIELDED_BRICK_U;
			break;
		case SHIELDED_DOWN:
			name = "Bottom Shielded Bricks";
			attribute_sprite = SPRITE_D;
			type = TYPE_SHIELDED_BRICK_D;
			break;
		case CONVEYOR_LEFT:
		case CONVEYOR_RIGHT:
			name = "Conveyor Bricks";
			attribute_sprite = SPRITE_CONVEYORSOLID1;
			type = TYPE_BRICKSOLID_CONVEYOR_L;
			break;
		default:
			attribute = -1;
			printf("Unrecognized solid attribute, code: %d", code);
			break;
	}
}

void BrickSolid::draw(){
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