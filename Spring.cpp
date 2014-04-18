#include "Spring.h"
#include "Enums.h"

const float SPEED = 2.f;
const int BOUNCE_FRAMES = 10;
const int SWITCH_SPEED = 6;
const float WIDTH_RATIO = .6f;
const float HEIGHT_RATIO = .7f;
const float D_WIDTH_RATIO = .6f;
const float D_HEIGHT_RATIO = .7f;

Spring::Spring(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Spring::Spring(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Spring::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	width_ratio = WIDTH_RATIO;
	height_ratio = HEIGHT_RATIO;
	d_width_ratio = D_WIDTH_RATIO;
	d_height_ratio = D_HEIGHT_RATIO;
	adjustToBounds(r.position_x, r.position_y, r.width, r.height);
	
	name = "Spring";
	sprites = s;
	velocity_x = 0;
	velocity_y = SPEED;
	on_ground = on_ladder = hit_wall_bottom = hit_wall_left = hit_wall_right = hit_wall_top = false;
	type = TYPE_SPRING;
	def_sprite = SPRITE_SPRING1;
	gen_type = BADDIE;
	bounce_time = BOUNCE_FRAMES;
	switch_time = SWITCH_SPEED;
}

Spring::~Spring(){
	delete bounds;
}

float Spring::applyGravity(float force_gravity, float max_velocity_grav) {
	return 0;
}

float Spring::getIntendedY() {
	if (hit_wall_bottom) {
		velocity_y = 0;
		if (bounce_time > 0) {
			def_sprite = SPRITE_SPRINGSMALL;
			bounce_time--;
		} else {
			def_sprite = SPRITE_SPRING2;
			bounce_time = BOUNCE_FRAMES;
			hit_wall_bottom = false;
			velocity_y = -SPEED;
		}
	} else if (hit_wall_top) {
		velocity_y = 0;
		if (bounce_time > 0) {
			def_sprite = SPRITE_SPRINGSMALL;
			bounce_time--;
		} else {
			def_sprite = SPRITE_SPRING1;
			bounce_time = BOUNCE_FRAMES;
			hit_wall_top = false;
			velocity_y = SPEED;
		}
	} else if (switch_time > 0) {
		switch_time--;
	} else if (def_sprite == SPRITE_SPRING1) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_SPRING2;
	} else {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_SPRING1;
	}
	return velocity_y;
}

float Spring::getIntendedX() {
	return velocity_x;
}
