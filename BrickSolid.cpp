/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "BrickSolid.h"
#include "Enums.h"

const int PHASE_RESISTANCE = 50; // how many ticks does it take to phase through this?
const int PHASE_RECOVERY = 250;   // how many ticks does it take to recover from being phased?
const int CONVEYOR_SPEED = 1;

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
	phased_count = PHASE_RESISTANCE;
	gen_type = SOLID;
	switch_time = CONVEYOR_SPEED;
}

BrickSolid::~BrickSolid(){
	delete bounds;
}

bool BrickSolid::phaseable(int dir) const {
	if (dir == UP && attribute == SHIELDED_DOWN)
		return false;
	if (dir == DOWN && attribute == SHIELDED_UP) // TODO: do we want to phase thu conveyors, ect?
		return false;
	if (dir == RIGHT && attribute == SHIELDED_LEFT)
		return false;
	if (dir == LEFT && attribute == SHIELDED_RIGHT)
		return false;
	return true;
}

void BrickSolid::phase() {
	if (phased_count < 0) {
		is_solid = false;
		phased_count = PHASE_RECOVERY;
	} else
		phased_count -= 2;
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
			name = "Conveyor Left Bricks";
			attribute_sprite = SPRITE_CONVEYORSOLID2;
			type = TYPE_BRICKSOLID_CONVEYOR_L;
			break;
		case CONVEYOR_RIGHT:
			name = "Conveyor Right Bricks";
			attribute_sprite = SPRITE_CONVEYORSOLID1;
			type = TYPE_BRICKSOLID_CONVEYOR_R;
			break;
		default:
			attribute = -1;
			printf("Unrecognized solid attribute, code: %d", code);
			break;
	}
}

void BrickSolid::draw(){ 
	if (switch_time > 0)
		switch_time--;
	else if (attribute == CONVEYOR_RIGHT && attribute_sprite == SPRITE_CONVEYORSOLID1) {
		switch_time = CONVEYOR_SPEED;
		attribute_sprite = SPRITE_CONVEYORSOLID5;
	} else if (attribute == CONVEYOR_RIGHT && attribute_sprite == SPRITE_CONVEYORSOLID2) {
		switch_time = CONVEYOR_SPEED;
		attribute_sprite = SPRITE_CONVEYORSOLID1;
	} else if (attribute == CONVEYOR_RIGHT && attribute_sprite == SPRITE_CONVEYORSOLID3) {
		switch_time = CONVEYOR_SPEED;
		attribute_sprite = SPRITE_CONVEYORSOLID2;
	} else if (attribute == CONVEYOR_RIGHT && attribute_sprite == SPRITE_CONVEYORSOLID4) {
		switch_time = CONVEYOR_SPEED;
		attribute_sprite = SPRITE_CONVEYORSOLID3;
	} else if (attribute == CONVEYOR_RIGHT && attribute_sprite == SPRITE_CONVEYORSOLID5) {
		switch_time = CONVEYOR_SPEED;
		attribute_sprite = SPRITE_CONVEYORSOLID4;
	} else if (attribute == CONVEYOR_LEFT && attribute_sprite == SPRITE_CONVEYORSOLID1) {
		switch_time = CONVEYOR_SPEED;
		attribute_sprite = SPRITE_CONVEYORSOLID2;
	} else if (attribute == CONVEYOR_LEFT && attribute_sprite == SPRITE_CONVEYORSOLID2) {
		switch_time = CONVEYOR_SPEED;
		attribute_sprite = SPRITE_CONVEYORSOLID3;
	} else if (attribute == CONVEYOR_LEFT && attribute_sprite == SPRITE_CONVEYORSOLID3) {
		switch_time = CONVEYOR_SPEED;
		attribute_sprite = SPRITE_CONVEYORSOLID4;
	} else if (attribute == CONVEYOR_LEFT && attribute_sprite == SPRITE_CONVEYORSOLID4) {
		switch_time = CONVEYOR_SPEED;
		attribute_sprite = SPRITE_CONVEYORSOLID5;
	} else if (attribute == CONVEYOR_LEFT && attribute_sprite == SPRITE_CONVEYORSOLID5) {
		switch_time = CONVEYOR_SPEED;
		attribute_sprite = SPRITE_CONVEYORSOLID1;
	} else 
		switch_time = CONVEYOR_SPEED;
	
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