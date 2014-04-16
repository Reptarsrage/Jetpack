#include "Spring.h"
#include "Enums.h"

const float SPEED = 2.f;

Spring::Spring(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Spring::Spring(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Spring::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Spring";
	sprites = s;
	velocity_x = 0;
	velocity_y = SPEED;
	on_ground = on_ladder = hit_wall_bottom = hit_wall_left = hit_wall_right = hit_wall_top = false;
	type = TYPE_SPRING;
	def_sprite = SPRITE_SPRING1;
	gen_type = BADDIE;
}

Spring::~Spring(){
	delete bounds;
}

float Spring::applyGravity(float force_gravity, float max_velocity_grav) {
	return 0;
}

float Spring::getIntendedY() {
	if (hit_wall_bottom) {
		hit_wall_bottom = false;
		velocity_y = -SPEED;
	}

	if (hit_wall_top) {
		hit_wall_top = false;
		velocity_y = SPEED;
	}
	return velocity_y;
}

float Spring::getIntendedX() {
	return velocity_x;
}
