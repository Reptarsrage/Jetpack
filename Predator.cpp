#include "Predator.h"
#include "Enums.h"

const float SPEED = 5.f;
const int SWITCH_SPEED = 40;
const int SWITCH_SPEED_S = 10;
const float WIDTH_RATIO = .7f;
const float HEIGHT_RATIO = .7f;
const float D_WIDTH_RATIO = .7f;
const float D_HEIGHT_RATIO = .7f;

Predator::Predator(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Predator::Predator(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Predator::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	
	// set bounds and adjust
	width_ratio = WIDTH_RATIO;
	height_ratio = HEIGHT_RATIO;
	d_width_ratio = D_WIDTH_RATIO;
	d_height_ratio = D_HEIGHT_RATIO;
	adjustToBounds(r.position_x, r.position_y, r.width, r.height);

	name = "Predator";
	sprites = s;
	velocity_x = 0;
	velocity_y = 0;
	on_ground = on_ladder = hit_wall_bottom = hit_wall_left = hit_wall_right = hit_wall_top = false;
	type = TYPE_HUNTER;
	hero_x = hero_y = 0.f;
	def_sprite = SPRITE_HUNTERV1;
	gen_type = BADDIE;
	switch_time = SWITCH_SPEED;
	switch_small = SWITCH_SPEED_S;
}

Predator::~Predator(){
	delete bounds;
}

float Predator::applyGravity(float force_gravity, float max_velocity_grav) {
	return 0;
}

float Predator::getIntendedY() {
	if (hero_y > bounds->position_y){
		velocity_y = SPEED;
	} else {
		velocity_y = -SPEED;
	}

	if (switch_time > 0) {
		switch_time--;
		velocity_y = 0;
	} else if (def_sprite == SPRITE_HUNTERH1 || def_sprite == SPRITE_HUNTERH2) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_HUNTERV1;
	} else {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_HUNTERH1;
	}
	return velocity_y;
}

float Predator::getIntendedX() {
	if (hero_x > bounds->position_x){
		velocity_x =  SPEED;
	} else {
		velocity_x =  -SPEED;
	}
	if (switch_time > 0)
		velocity_x = 0;

	if (switch_small > 0)
		switch_small--;
	else if (def_sprite == SPRITE_HUNTERH1) {
		switch_small = SWITCH_SPEED_S;
		def_sprite = SPRITE_HUNTERH2;
	} else if (def_sprite == SPRITE_HUNTERH2) {
		switch_small = SWITCH_SPEED_S;
		def_sprite = SPRITE_HUNTERH1;
	} else if (def_sprite == SPRITE_HUNTERV1) {
		switch_small = SWITCH_SPEED_S;
		def_sprite = SPRITE_HUNTERV2;
	} else {
		switch_small = SWITCH_SPEED_S;
		def_sprite = SPRITE_HUNTERV1;
	}
	return velocity_x;
}