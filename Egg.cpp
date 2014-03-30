#include "Egg.h"
#include "Enums.h"

const int DEFAULT_SPRITE = SPRITE_EGG;
const float SPEED = 2.f;
const float EPSILON = 0.1f;

Egg::Egg(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Egg::Egg(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Egg::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Egg";
	sprites = s;
	velocity_x = SPEED;
	velocity_y = 0;
	on_ground = on_ladder = hit_wall_bottom = hit_wall_left = hit_wall_right = hit_wall_top = false;
	hero_x = hero_y = 0;
}

Egg::~Egg(){
	delete bounds;
}

float Egg::applyGravity(float force_gravity, float max_velocity_grav) {
	if (!on_ground) {
		velocity_y += force_gravity;
	}
	if (velocity_y > max_velocity_grav)
		velocity_y = max_velocity_grav;

	return velocity_y;
}

const char *Egg::ToString() const{
	return name;
}

float Egg::getIntendedY() {
	return velocity_y;
}

float Egg::getIntendedX() {
	if (!on_ground) {
		return 0;
	}
	on_ground = false;
	if (hit_wall_left) {
		hit_wall_left = false;
		velocity_x = SPEED;
	}

	if (hit_wall_right) {
		hit_wall_right = false;
		velocity_x = -SPEED;
	}
	return velocity_x;
}

void Egg::draw(){
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
