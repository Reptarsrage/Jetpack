#include "Hero.h"
#include "Enums.h"

const int DEFAULT_SPRITE = SPRITE_FRONT;
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

const char *Hero::ToString() const{
	return name;
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
	if (on_ladder) {
		velocity_jump = 0;
	}

	if (velocity_jump < 0.0)
		velocity_jump = 0.0;
	
	if (!on_ground && !on_ladder) {
		velocity_jump -=  force_gravity * mass;
		velocity_y += (force_y + force_gravity) * mass;
		velocity_x += force_x * mass;
		return force_gravity;
	}
	return 0;
}

void Hero::draw(){
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, sprites->getSprite(DEFAULT_SPRITE));
		glTranslatef(bounds->left(), bounds->bottom(), 0);
		glBegin(GL_QUADS);
			glTexCoord2f( 0, 0 );                           
			glVertex2f( 0, 0 );
			glTexCoord2f( 1, 0 );     
			glVertex2f( bounds->width, 0 );
			glTexCoord2f( 1, 1);    
			glVertex2f( bounds->width, bounds->height );
			glTexCoord2f( 0, 1 );          
			glVertex2f( 0, bounds->height );
		glEnd();
	glPopMatrix();
}
