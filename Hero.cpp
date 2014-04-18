#include "Hero.h"

const float WIDTH_RATIO = .6f;
const float HEIGHT_RATIO = .85f;
const int WALK_SPEED = 5;

void Hero::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	float margin_l = (r.width - (WIDTH_RATIO * r.width)) / 2.f;
	float margin_t = (r.height - (HEIGHT_RATIO * r.height)) / 2.f;
	bounds = new Rectangle(margin_l + r.position_x, r.position_y - margin_t, WIDTH_RATIO * r.width, HEIGHT_RATIO * r.height);
	name = "Hero";
	sprites = s;
	velocity_x = 0.0;
	velocity_y = 0.0;
	velocity_jump = 0.0;
	force_x = 0.0;
	force_y = 0.0,
	mass = 1.0;
	on_ground = false;
	on_ladder = false;
	type = TYPE_HERO;
	def_sprite = SPRITE_FRONT;
	ground_type = -1;
	ladder_dir = -1;
	ladder_left = 0;
	gen_type = OTHER;
	walk_time = WALK_SPEED;
}

Hero::Hero(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Hero::Hero(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

Hero::~Hero(){
	delete bounds;
}

void Hero::SetBounds(float x, float y, float width, float height) { 
	if (bounds) 
		delete bounds;
	float margin_l = (width - (WIDTH_RATIO * width)) / 2.f;
	float margin_t = (height - (HEIGHT_RATIO * height)) / 2.f;
	bounds = new Rectangle(margin_l + x, y - margin_t, WIDTH_RATIO * width, HEIGHT_RATIO * height); 
}

void Hero::move(float x, float y){
	bounds->position_x += x;
	bounds->position_y += y;
}

void Hero::phase(int dir) {
	if (dir == UP) {
		def_sprite = SPRITE_PHASINGUP1;
	} else if (dir == DOWN) {
		def_sprite = SPRITE_PHASEDOWN1;
	} else if (dir == LEFT) {
		def_sprite = SPRITE_PHASINGLEFT1;
	} else if (dir == RIGHT) {
		def_sprite = SPRITE_PHASINGRIGHT1;
	}
}

void Hero::step(int dir) {
	if (walk_time > 0) {
		walk_time--;
		if (def_sprite != SPRITE_LEFT1 && def_sprite != SPRITE_LEFT2) {
			if (dir == LEFT)
				def_sprite = SPRITE_LEFT1;
			else if (dir == RIGHT)
				def_sprite = SPRITE_RIGHT1;
		}
	} else if (def_sprite == SPRITE_LEFT1) {
		walk_time = WALK_SPEED;
		def_sprite = SPRITE_LEFT2;
	} else if (def_sprite == SPRITE_LEFT2) {
		walk_time = WALK_SPEED;
		def_sprite = SPRITE_LEFT1;
	} else if (def_sprite == SPRITE_RIGHT1) {
		walk_time = WALK_SPEED;
		def_sprite = SPRITE_RIGHT2;
	} else if (def_sprite == SPRITE_RIGHT2) {
		walk_time = WALK_SPEED;
		def_sprite = SPRITE_RIGHT1;
	} else {
		walk_time = WALK_SPEED;
		def_sprite = SPRITE_FRONT;
	}
}

void Hero::Jump(float restitution) {
	if (on_ground || on_ladder) {
		on_ladder = false;
		velocity_y = 0;
		velocity_jump = restitution;
	}
}

float Hero::applyGravity(float force_gravity) {
	velocity_x += force_x * mass;
	if (on_ladder) {
		velocity_jump = 0;
	}

	if (velocity_jump < 0.0)
		velocity_jump = 0.0;
	
	if (!on_ground && !on_ladder) {
		velocity_jump -=  force_gravity * mass;
		velocity_y += (force_y + force_gravity) * mass;
		return force_gravity;
	}
	
	return 0;
}

void Hero::draw(){
	glBindTexture(GL_TEXTURE_2D, sprites->getSprite(def_sprite));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}
