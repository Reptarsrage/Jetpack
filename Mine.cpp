#include "Mine.h"
#include "Enums.h"

const float WIDTH_RATIO = .2f;
const float HEIGHT_RATIO = .01f;
const float D_WIDTH_RATIO = 1.f;
const float D_HEIGHT_RATIO = 1.f;

Mine::Mine(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Mine::Mine(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Mine::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	
	// set bounds and adjust
	width_ratio = WIDTH_RATIO;
	height_ratio = HEIGHT_RATIO;
	d_width_ratio = D_WIDTH_RATIO;
	d_height_ratio = D_HEIGHT_RATIO;
	adjustToBounds(r.position_x, r.position_y, r.width, r.height);

	name = "Land Mine";
	sprites = s;
	on_ground = on_ladder = hit_wall_bottom = hit_wall_left = hit_wall_right = hit_wall_top = false;
	type = TYPE_MINE;
	def_sprite = SPRITE_MINE;
	gen_type = BADDIE;
}

Mine::~Mine(){
	delete bounds;
}

float Mine::applyGravity(float force_gravity, float max_velocity_grav) {
	return 0;
}

float Mine::getIntendedY() {
	return 0;
}

float Mine::getIntendedX() {
	return 0;
}
