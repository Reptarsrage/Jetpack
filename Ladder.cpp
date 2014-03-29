/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "Ladder.h"
#include "Enums.h"

Ladder::Ladder(float x, float y, float w, float h, const Sprites *s) {
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Ladder::Ladder(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Ladder::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Ladder";
	sprites = s;
	def_sprite = SPRITE_LADDER;
}

Ladder::~Ladder(){
	delete bounds;
}

const char *Ladder::ToString() const{
	return name;
}

void Ladder::draw(){
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