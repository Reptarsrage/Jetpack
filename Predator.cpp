#include "Predator.h"
#include "Enums.h"

const int DEFAULT_SPRITE = SPRITE_HUNTERV1;
const float SPEED = 0.175f;

Predator::Predator(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Predator::Predator(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Predator::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Predator";
	sprites = s;
	velocity_x = 0;
	velocity_y = 0;
	on_ground = on_ladder = hit_wall_bottom = hit_wall_left = hit_wall_right = hit_wall_top = false;
	type = TYPE_HUNTER;
	hero_x = hero_y = 0.f;
}

Predator::~Predator(){
	delete bounds;
}

float Predator::applyGravity(float force_gravity, float max_velocity_grav) {
	return 0;
}

const char *Predator::ToString() const{
	return name;
}

float Predator::getIntendedY() {
	if (hero_y > bounds->position_y){
		return SPEED;
	} else {
		return -SPEED;
	}

}

float Predator::getIntendedX() {
	if (hero_x > bounds->position_x){
		return SPEED;
	} else {
		return -SPEED;
	}
}

void Predator::draw(){
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
