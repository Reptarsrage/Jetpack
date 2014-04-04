/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "SolidThing.h"
#include "Enums.h"

SolidThing::SolidThing(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

SolidThing::SolidThing(const Rectangle r, const Sprites *s){
	Init(r, s);
}

void SolidThing::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "SolidThing";
	sprites = s;
	type = TYPE_SOLID;
	def_sprite = SPRITE_NONPSOLID;
}

SolidThing::~SolidThing(){
	delete bounds;
}

const char *SolidThing::ToString() const{
	return name;
}

void SolidThing::draw(){
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