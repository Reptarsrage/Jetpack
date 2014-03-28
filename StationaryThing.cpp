/* Justin Robb
 * 3-27-14
 * JetPack
 * Abstract thing
*/

#include "StationaryThing.h"
#include "Enums.h"

StationaryThing::StationaryThing(float x, float y, float w, float h, const Sprites *s){
	bounds = new Rectangle(x, y, w, h);
	name = "StationaryThing";
	sprites = s;
	def_sprite = std::rand() % SPRITE_COUNT;
}

StationaryThing::StationaryThing(const Rectangle r, const Sprites *s){
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "StationaryThing";
	sprites = s;
	def_sprite = std::rand() % SPRITE_COUNT;
}

StationaryThing::~StationaryThing(){
	delete bounds;
}

const char *StationaryThing::ToString() const{
	return name;
}

void StationaryThing::draw(){
	glPushMatrix();
		glBindTexture(GL_TEXTURE_RECTANGLE_NV, sprites->getSprite(def_sprite));
		glTranslatef(bounds->left(), bounds->top(), 0);
		glRotatef(180, 0,0, 1);
		glBegin(GL_QUADS);
			glTexCoord2f( 0, bounds->height );                           
			glVertex2f( 0, 0 );
			glTexCoord2f( bounds->width, bounds->height );     
			glVertex2f( bounds->width, 0 );
			glTexCoord2f( bounds->width, 0 );    
			glVertex2f( bounds->width, bounds->height );
			glTexCoord2f( 0, 0 );          
			glVertex2f( 0, bounds->height );
		glEnd();
	glPopMatrix();
}