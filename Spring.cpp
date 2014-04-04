#include "Spring.h"
#include "Enums.h"

const int DEFAULT_SPRITE = SPRITE_SPRING1;
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
}

Spring::~Spring(){
	delete bounds;
}

float Spring::applyGravity(float force_gravity, float max_velocity_grav) {
	return 0;
}

const char *Spring::ToString() const{
	return name;
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

void Spring::draw(){
	glBindTexture(GL_TEXTURE_2D, sprites->getSprite(DEFAULT_SPRITE));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}
