#include "Hero.h"
#include "Enums.h"

const int DEFAULT_SPRITE = SPRITE_FRONT;

Hero::Hero(float x, float y, float w, float h, const Sprites *s){
	assert(s);
	bounds = new Rectangle(x, y, w, h);
	name = "Hero";
	sprites = s;
	velocity_x = 0.0;
	velocity_y = 0.0;
	velocity_jump = 0.0;
	force_x = 0.0;
	force_y = 0.0,
	mass = 1.0;
}

Hero::Hero(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Hero";
	sprites = s;
	velocity_x = 0.0;
	velocity_y = 0.0;
	velocity_jump = 0.0;
	force_x = 0.0;
	force_y = 0.0,
	mass = 1.0;
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
