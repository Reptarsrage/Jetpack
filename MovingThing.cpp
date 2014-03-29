/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "MovingThing.h"
#include "Enums.h"

const int DEFAULT_SPRITE = SPRITE_FRONT;

const char *MovingThing::ToString() const{
	return name;
}

void MovingThing::draw(){
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, sprites->getSprite(DEFAULT_SPRITE));
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

void MovingThing::move(float x, float y) {
	// set positions
	bounds->position_x += x;
	bounds->position_y += y;
}