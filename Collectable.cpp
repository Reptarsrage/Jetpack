/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "Collectable.h"
#include "Enums.h"

Collectable::Collectable(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Collectable::Collectable(const Rectangle r, const Sprites *s){
	Init(r, s);
}

void Collectable::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Collectable";
	sprites = s;
	collected = false;
	type = TYPE_GEM;
	def_sprite = SPRITE_GEM;
}

Collectable::~Collectable(){
	delete bounds;
}

bool Collectable::Collected() {
	return collected;
}

int Collectable::Collect() {
	collected = true;
	def_sprite = SPRITE_GEMCOLLECTED;
	return point_value;
}

const char *Collectable::ToString() const{
	return name;
}

void Collectable::draw(){
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, sprites->getSprite(def_sprite));
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