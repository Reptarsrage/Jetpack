#include "Missile.h"
#include "Enums.h"

const float SPEED = 2.f;
const float EPSILON = 0.1f;

Missile::Missile(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Missile::Missile(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Missile::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Missile";
	sprites = s;
	velocity_x = SPEED;
	velocity_y = 0;
	on_ladder = on_ground = hit_wall_bottom = hit_wall_left = hit_wall_right = hit_wall_top = false;
	hero_x = hero_y = 0;
	type = TYPE_MISSILE;
	def_sprite = SPRITE_MISSILELEFT1;
}

Missile::~Missile(){
	delete bounds;
}

float Missile::applyGravity(float force_gravity, float max_velocity_grav) {
	return 0;
}

const char *Missile::ToString() const{
	return name;
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
	} else if (hit_wall_top) {
		hit_wall_top = false;
		velocity_y = 0;
		velocity_x = SPEED;
	} 
	return velocity_y;
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
	} else if (hit_wall_right) {
		hit_wall_right = false;
		velocity_y = SPEED;
		velocity_x = 0;
	} 
	
	return SPEED * velocity_x;
}

void Missile::draw(){
	glBindTexture(GL_TEXTURE_2D, sprites->getSprite(def_sprite));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}
