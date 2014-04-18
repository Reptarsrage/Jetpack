#include "Pinwheel.h"
#include "Enums.h"

const float SPEED = 2.f;
const float EPSILON = 0.1f;
const int SWITCH_SPEED = 5;
const float WIDTH_RATIO = .3f;
const float HEIGHT_RATIO = .3f;
const float D_WIDTH_RATIO = .5f;
const float D_HEIGHT_RATIO = .5f;

Pinwheel::Pinwheel(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Pinwheel::Pinwheel(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Pinwheel::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	width_ratio = WIDTH_RATIO;
	height_ratio = HEIGHT_RATIO;
	d_width_ratio = D_WIDTH_RATIO;
	d_height_ratio = D_HEIGHT_RATIO;
	adjustToBounds(r.position_x, r.position_y, r.width, r.height);

	name = "Pinwheel";
	sprites = s;
	float dir_angle = fmod(m_randf(), 2*PI);
	velocity_x = cosf(dir_angle);
	velocity_y = sinf(dir_angle);
	printf("Initial Pinwheel angle = %g\n", dir_angle);
	on_ladder = on_ground = hit_wall_bottom = hit_wall_left = hit_wall_right = hit_wall_top = false;
	hero_x = hero_y = 0;
	type = TYPE_PINWHEEL;
	def_sprite = SPRITE_PINWHEEL1;
	gen_type = BADDIE;
	switch_time = SWITCH_SPEED;
}

Pinwheel::~Pinwheel(){
	delete bounds;
	delete draw_bounds;
}

float Pinwheel::applyGravity(float force_gravity, float max_velocity_grav) {
	return 0;
}

void Pinwheel::SetBounds(float x, float y, float width, float height) { 
	if (bounds) 
		delete bounds; 
	if (draw_bounds)
		delete draw_bounds;

	adjustToBounds(x, y, width, height);
}

void Pinwheel::randomize_dir() {
	float sign_x = velocity_x / fabs(velocity_x);
	float sign_y = velocity_y / fabs(velocity_y);
	float velocity_x_old = velocity_x;
	float velocity_y_old = velocity_y;
	float angle = atanf(velocity_y / velocity_x);
	if (m_rand() % 3 == 0)
		angle += EPSILON;
	else
		angle -= EPSILON;
	velocity_x = sign_x * fabs(cosf(angle));
	velocity_y = sign_y * fabs(sinf(angle));
}

void Pinwheel::calculate_dir(float norm_x, float norm_y) {
	/*If you can get the normal of the surface where you're bouncing off of it 
	you can do a dot product with the velocity vector the projectile will have when it hits.
	Divide the dot product by the magnitude of the velocity, then double it and scale the 
	surface normal by that number and subtract the resulting vector from your velocity.*/
	
	float dot_prod = norm_x * velocity_x + norm_y* velocity_y;
	float res = dot_prod;
	float norm_res_x = (2.f * res) * norm_x;
	float norm_res_y = (2.f * res) * norm_y;
	velocity_x -= norm_res_x;
	velocity_y -= norm_res_y;
	randomize_dir();
}


float Pinwheel::getIntendedY() {
	if (hit_wall_top && hit_wall_bottom){
		hit_wall_top = hit_wall_bottom = false;
		return 0;
	}
	float norm_y = 0.f;
	if (hit_wall_bottom) {
		norm_y = -1.f;
		hit_wall_bottom = false;
		calculate_dir(0.f, norm_y);
	} else if (hit_wall_top) {
		norm_y = 1.f;
		hit_wall_top = false;
		calculate_dir(0.f, norm_y);
	} 
	return SPEED * velocity_y;
}

float Pinwheel::getIntendedX() {
	if (switch_time > 0) {
		switch_time--;
	} else if (def_sprite == SPRITE_PINWHEEL1) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_PINWHEEL2;
	} else if (def_sprite == SPRITE_PINWHEEL2) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_PINWHEEL3;
	} else if (def_sprite == SPRITE_PINWHEEL3) {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_PINWHEEL4;
	} else {
		switch_time = SWITCH_SPEED;
		def_sprite = SPRITE_PINWHEEL1;
	}
	
	if (hit_wall_left && hit_wall_right) {
		hit_wall_left = hit_wall_right = false;
		return 0;
	}
	
	float norm_x = 0.f;
	if (hit_wall_left) {
		norm_x = 1.f;
		hit_wall_left = false;
		calculate_dir(norm_x, 0.f);
	} else if (hit_wall_right) {
		norm_x = -1.f;
		hit_wall_right = false;
		calculate_dir(norm_x, 0.f);
	} 
	
	return SPEED * velocity_x;
}