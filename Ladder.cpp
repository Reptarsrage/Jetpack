/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "Ladder.h"
#include "Enums.h"
const int SWITCH_SPEED = 2;

Ladder::Ladder(float x, float y, float w, float h, const Sprites *s) {
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Ladder::Ladder(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Ladder::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Ladder";
	type = TYPE_LADDER;
	sprites = s;
	def_sprite = SPRITE_LADDER;
	is_solid = false;
	is_collectable = false;
	direction = -1;
	gen_type = NONSOLID;
	switch_time = SWITCH_SPEED;
}

Ladder::~Ladder(){
	delete bounds;
}

void Ladder::setDirection(int code) {
	if (code == UP) {
		direction = UP;
		type = TYPE_LADDERUP;
		def_sprite = SPRITE_LADDER3;
		name = "Ladder moving up";
	} else if (code == DOWN) {
		direction = DOWN;
		type = TYPE_LADDERDOWN;
		def_sprite = SPRITE_LADDER2;
		name = "Ladder moving down";
	}
}

void Ladder::draw() {
	if (switch_time > 0) {
		switch_time--;
	} else if (direction == DOWN && def_sprite == SPRITE_LADDER) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_LADDER2;
	} else if (direction == DOWN && def_sprite == SPRITE_LADDER2) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_LADDER3;
	} else if (direction == DOWN && def_sprite == SPRITE_LADDER3) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_LADDER4;
	} else if (direction == DOWN && def_sprite == SPRITE_LADDER4) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_LADDER;
	} else if (direction == UP && def_sprite == SPRITE_LADDER) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_LADDER4;
	} else if (direction == UP && def_sprite == SPRITE_LADDER2) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_LADDER;
	} else if (direction == UP && def_sprite == SPRITE_LADDER3) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_LADDER2;
	} else if (direction == UP && def_sprite == SPRITE_LADDER4) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_LADDER3;
	}
	
	glBindTexture(GL_TEXTURE_2D, sprites->getSprite(def_sprite));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}