#include "Hero.h"
#include "Enums.h"

const float HERO_WIDTH_RATIO = .6f;
const float HERO_HEIGHT_RATIO = .9f;

void Hero::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width * HERO_WIDTH_RATIO, r.height * HERO_HEIGHT_RATIO);
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

void Hero::move(float x, float y){
	bounds->position_x += x;
	bounds->position_y += y;
}

void Hero::Jump(float restitution) {
	on_ladder = false;
	if (on_ground || on_ladder)
		velocity_jump = restitution;
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
