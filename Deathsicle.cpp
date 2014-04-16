#include "Deathsicle.h"
#include "Enums.h"

Deathsicle::Deathsicle(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Deathsicle::Deathsicle(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Deathsicle::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Deathsicle";
	sprites = s;
	on_ground = on_ladder = hit_wall_bottom = hit_wall_left = hit_wall_right = hit_wall_top = false;
	type = TYPE_DEATHDOWN;
	def_sprite = SPRITE_DEATHDOWN;
	gen_type = BADDIE;
}

Deathsicle::~Deathsicle(){
	delete bounds;
}

float Deathsicle::applyGravity(float force_gravity, float max_velocity_grav) {
	return 0;
}

float Deathsicle::getIntendedY() {
	return 0;
}

float Deathsicle::getIntendedX() {
	return 0;
}

void Deathsicle::setDir(int dir){
	assert (dir >= 0);
	assert (dir < 4);
	
	if (dir == LEFT) {
		type = TYPE_DEATHLEFT;
		def_sprite = SPRITE_DEATHLEFT;
	} else if (dir == RIGHT) {
		type = TYPE_DEATHRIGHT;
		def_sprite = SPRITE_DEATHRIGHT;
	} else if (dir == UP) {
		type = TYPE_DEATHUP;
		def_sprite = SPRITE_DEATHUP;
	} else if (dir == DOWN) {
		type = TYPE_DEATHDOWN;
		def_sprite = SPRITE_DEATHDOWN;
		
	}
}