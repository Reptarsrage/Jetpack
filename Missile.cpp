#include "Missile.h"
#include "Enums.h"

const float SPEED = 2.f;
const float EPSILON = 0.1f;
const float WIDTH_RATIO = 1.f;
const float HEIGHT_RATIO = 1.f;
const float D_WIDTH_RATIO = 1.f;
const float D_HEIGHT_RATIO = 1.f;
const int SWITCH_SPEED = 4;

Missile::Missile(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Missile::Missile(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Missile::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	
	// set bounds and adjust
	width_ratio = WIDTH_RATIO;
	height_ratio = HEIGHT_RATIO;
	d_width_ratio = D_WIDTH_RATIO;
	d_height_ratio = D_HEIGHT_RATIO;
	adjustToBounds(r.position_x, r.position_y, r.width, r.height);

	name = "Missile";
	sprites = s;
	velocity_x = SPEED;
	velocity_y = 0;
	on_ladder = on_ground = hit_wall_bottom = hit_wall_left = hit_wall_right = hit_wall_top = false;
	hero_x = hero_y = 0;
	type = TYPE_MISSILE;
	def_sprite = SPRITE_MISSILELEFT1;
	gen_type = BADDIE;
	switch_time = SWITCH_SPEED;
}

Missile::~Missile(){
	delete bounds;
}

float Missile::applyGravity(float force_gravity, float max_velocity_grav) {
	return 0;
}

float Missile::getIntendedY() {
	if (hit_wall_top && hit_wall_bottom){
		hit_wall_top = hit_wall_bottom = false;
		return 0;
	}
	if (hit_wall_bottom) {
		hit_wall_bottom = false;
		velocity_y = 0;
		velocity_x = -SPEED;
		def_sprite = SPRITE_MISSILELEFT1;
	} else if (hit_wall_top) {
		hit_wall_top = false;
		velocity_y = 0;
		velocity_x = SPEED;
		def_sprite = SPRITE_MISSILERIGHT1;
	} 
	return velocity_y;

	if (switch_time > 0){
		switch_time--;
	} else {
		switch_time = SWITCH_SPEED;
		switch (def_sprite) {
			case SPRITE_MISSILERIGHT1:
				def_sprite = SPRITE_MISSILERIGHT2;
				break;
			case SPRITE_MISSILERIGHT2:
				def_sprite = SPRITE_MISSILERIGHT1;
				break;
			case SPRITE_MISSILELEFT1:
				def_sprite = SPRITE_MISSILELEFT2;
				break;
			case SPRITE_MISSILELEFT2:
				def_sprite = SPRITE_MISSILELEFT1;
				break;
			case SPRITE_MISSILEUP1:
				def_sprite = SPRITE_MISSILEUP2;
				break;
			case SPRITE_MISSILEUP2:
				def_sprite = SPRITE_MISSILEUP1;
				break;
			case SPRITE_MISSILEDOWN1:
				def_sprite = SPRITE_MISSILEDOWN2;
				break;
			case SPRITE_MISSILEDOWN2:
				def_sprite = SPRITE_MISSILEDOWN1;
				break;
		}
	}
}

float Missile::getIntendedX() {
	if (hit_wall_left && hit_wall_right) {
		hit_wall_left = hit_wall_right = false;
		return 0;
	}
	
	if (hit_wall_left) {
		hit_wall_left = false;
		velocity_y = -SPEED;
		velocity_x = 0;
		def_sprite = SPRITE_MISSILEUP1;
	} else if (hit_wall_right) {
		hit_wall_right = false;
		velocity_y = SPEED;
		velocity_x = 0;
		def_sprite = SPRITE_MISSILEDOWN1;
	} 
	
	return SPEED * velocity_x;
}
