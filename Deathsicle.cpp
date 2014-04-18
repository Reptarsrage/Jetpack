#include "Deathsicle.h"
#include "Enums.h"

// for the down & top pos
// reversed for other posits
const float WIDTH_RATIO = 1.f;
const float HEIGHT_RATIO = .2f;
const float D_WIDTH_RATIO = 1.f;
const float D_HEIGHT_RATIO = 1.f;

Deathsicle::Deathsicle(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Deathsicle::Deathsicle(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Deathsicle::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	
	// set bounds and adjust
	width_ratio = WIDTH_RATIO;
	height_ratio = HEIGHT_RATIO;
	d_width_ratio = D_WIDTH_RATIO;
	d_height_ratio = D_HEIGHT_RATIO;
	adjustToBounds(r.position_x, r.position_y, r.width, r.height);

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
		width_ratio = HEIGHT_RATIO;
		height_ratio = WIDTH_RATIO; 
	} else if (dir == RIGHT) {
		type = TYPE_DEATHRIGHT;
		def_sprite = SPRITE_DEATHRIGHT;
		width_ratio = HEIGHT_RATIO;
		height_ratio = WIDTH_RATIO; 
	} else if (dir == UP) {
		type = TYPE_DEATHUP;
		def_sprite = SPRITE_DEATHUP;
		width_ratio = WIDTH_RATIO;
		height_ratio = HEIGHT_RATIO;
	} else if (dir == DOWN) {
		type = TYPE_DEATHDOWN;
		def_sprite = SPRITE_DEATHDOWN;
		width_ratio = WIDTH_RATIO;
		height_ratio = HEIGHT_RATIO;
	}
}

void Deathsicle::adjustToBounds(float x, float y, float width, float height) {
	float margin_l;
	float margin_t;
	if (type == TYPE_DEATHLEFT) {
		margin_l = 0;
		margin_t = (height - (height_ratio * height)) / 2.f;
	} else if (type == TYPE_DEATHRIGHT) {
		margin_l = width - (width_ratio * width);
		margin_t = (height - (height_ratio * height)) / 2.f;
	} else if (type == TYPE_DEATHUP) {
		margin_l = (width - (width_ratio * width)) / 2.f;
		margin_t = height - (height_ratio * height);
	} else {
		// down
		margin_l = (width - (width_ratio * width)) / 2.f;
		margin_t = 0;
	}

	bounds = new Rectangle(margin_l + x, y - margin_t, width_ratio * width, height_ratio * height);
		
	margin_l = (width - (d_width_ratio * width)) / 2.f;
	margin_t = (height - (d_height_ratio * height)) / 2.f;
	draw_bounds = new Rectangle(margin_l + x, y - margin_t, d_width_ratio * width, d_height_ratio * height);
}