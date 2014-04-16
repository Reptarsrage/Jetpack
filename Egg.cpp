#include "Egg.h"
#include "Enums.h"

const float SPEED = 1.8f;
const float EPSILON = 0.1f;
const float HERO_WIDTH_RATIO = .9f;
const float HERO_HEIGHT_RATIO = .9f;

Egg::Egg(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Egg::Egg(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Egg::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width * HERO_WIDTH_RATIO, r.height * HERO_HEIGHT_RATIO);
	name = "Egg";
	sprites = s;
	velocity_x = SPEED;
	velocity_y = 0;
	on_ground = on_ladder = hit_wall_bottom = hit_wall_left = hit_wall_right = hit_wall_top = false;
	hero_x = hero_y = 0;
	type = TYPE_EGG;
	def_sprite = SPRITE_EGG;
	gen_type = BADDIE;
}

Egg::~Egg(){
	delete bounds;
}

void Egg::move(float x, float y) {
	if (on_ground)
		bounds->position_x += x;
	bounds->position_y += y;
}

void Egg::Grounded(bool b) {
	if (on_ground && !b) {
		velocity_y = 0;
	}
	on_ground = b;
}

float Egg::applyGravity(float force_gravity, float max_velocity_grav) {
	if (!on_ground) {
		velocity_y += force_gravity;
	} else
		velocity_y = 1.f;
	if (velocity_y > max_velocity_grav)
		velocity_y = max_velocity_grav;

	return velocity_y;
}

float Egg::getIntendedY() {
	return velocity_y;
}

float Egg::getIntendedX() {
	if (!on_ground) {
		return 0;
	}

	if (hit_wall_left) {
		hit_wall_left = false;
		velocity_x = SPEED;
	}

	if (hit_wall_right) {
		hit_wall_right = false;
		velocity_x = -SPEED;
	}
	return velocity_x;
}