#include "Bat.h"
#include "Enums.h"

const int DEFAULT_SPRITE = SPRITE_BAT1;
const float SPEED = 2.f;
const float EPSILON = 0.1f;

Bat::Bat(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Bat::Bat(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Bat::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Bat";
	sprites = s;
	float dir_angle = fmod(m_randf(), 2*PI);
	velocity_x = 0;
	velocity_y = 0;
	on_ground = on_ladder = hit_wall_bottom = hit_wall_left = hit_wall_right = hit_wall_top = false;
	hero_x = hero_y = 0;
}

Bat::~Bat(){
	delete bounds;
}

float Bat::applyGravity(float force_gravity, float max_velocity_grav) {
	return 0;
}

const char *Bat::ToString() const{
	return name;
}

float Bat::getIntendedY() {
	// TODO
	return 0;
}

float Bat::getIntendedX() {
	//TODO
	return 0;
}

void Bat::draw(){
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
