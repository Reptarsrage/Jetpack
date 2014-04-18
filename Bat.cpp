#include "Bat.h"
#include "Enums.h"

const float SPEED = 0.45f;
const float WIDTH_RATIO = .8f;
const float HEIGHT_RATIO = .9f;
const float D_WIDTH_RATIO = .8f;
const float D_HEIGHT_RATIO = .9f;
const int SWITCH_SPEED = 10;
int flap = DOWN;


Bat::Bat(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Bat::Bat(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Bat::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	
	// set bounds and adjust
	width_ratio = WIDTH_RATIO;
	height_ratio = HEIGHT_RATIO;
	d_width_ratio = D_WIDTH_RATIO;
	d_height_ratio = D_HEIGHT_RATIO;
	adjustToBounds(r.position_x, r.position_y, r.width, r.height);

	name = "Bat";
	sprites = s;
	float dir_angle = fmod(m_randf(), 2*PI);
	velocity_x = 0;
	velocity_y = 0;
	on_ground = false;
	on_ladder = false;
	hit_wall_bottom = false;
	hit_wall_left = false;
	hit_wall_right = false;
	hit_wall_top = false;
	hero_x = hero_y = 0.f;
	def_sprite = SPRITE_BAT1;
	type = TYPE_BAT;
	gen_type = BADDIE;
	switch_time = SWITCH_SPEED;
}

Bat::~Bat(){
	delete bounds;
}

float Bat::applyGravity(float force_gravity, float max_velocity_grav) {
	return 0;
}

float Bat::getIntendedY() {
	if (hero_y > bounds->position_y){
		velocity_y = SPEED;
	} else {
		velocity_y = -SPEED;
	}
	if (switch_time > 0)
		switch_time--;
	else if (def_sprite == SPRITE_BAT1 && flap == DOWN) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_BAT2;
	} else if (def_sprite == SPRITE_BAT2 && flap == DOWN) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_BAT3;
	} else if (def_sprite == SPRITE_BAT3 && flap == DOWN) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_BAT4;
	} else if (def_sprite == SPRITE_BAT4 && flap == DOWN) {
		switch_time = SWITCH_SPEED;
		flap = UP;
	} else if (def_sprite == SPRITE_BAT1 && flap == UP) {
		switch_time = SWITCH_SPEED;
		flap = DOWN;
	} else if (def_sprite == SPRITE_BAT2 && flap == UP) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_BAT1;
	} else if (def_sprite == SPRITE_BAT3 && flap == UP) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_BAT2;
	} else if (def_sprite == SPRITE_BAT4 && flap == UP) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_BAT3;
	}
	return velocity_y;
}

float Bat::getIntendedX() {
	if (hero_x > bounds->position_x){
		velocity_x = SPEED;
	} else {
		velocity_x = -SPEED;
	}
	return velocity_x;
}
