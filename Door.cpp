/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "Door.h"
#include "Enums.h"

Door::Door(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Door::Door(const Rectangle r, const Sprites *s){
	Init(r, s);
}

void Door::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Door";
	sprites = s;
	type = DOOR_TYPE;
	def_sprite = SPRITE_DOORCLOSED;
	is_open = false;
}

Door::~Door(){
	delete bounds;
}

void Door::Open()  { 
	def_sprite = SPRITE_DOOROPEN;
	is_open = true;
}

const char *Door::ToString() const{
	return name;
}

void Door::draw(){
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