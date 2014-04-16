#include "Predator.h"
#include "Enums.h"

const float SPEED = 0.175f;

Predator::Predator(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Predator::Predator(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Predator::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Predator";
	sprites = s;
	velocity_x = 0;
	velocity_y = 0;
	on_ground = on_ladder = hit_wall_bottom = hit_wall_left = hit_wall_right = hit_wall_top = false;
	type = TYPE_HUNTER;
	hero_x = hero_y = 0.f;
	def_sprite = SPRITE_HUNTERV1;
	gen_type = BADDIE;
}

Predator::~Predator(){
	delete bounds;
}

float Predator::applyGravity(float force_gravity, float max_velocity_grav) {
	return 0;
}

float Predator::getIntendedY() {
	if (hero_y > bounds->position_y){
		return SPEED;
	} else {
		return -SPEED;
	}

}

float Predator::getIntendedX() {
	if (hero_x > bounds->position_x){
		return SPEED;
	} else {
		return -SPEED;
	}
}