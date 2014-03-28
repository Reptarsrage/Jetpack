/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "MovingThing.h"
#include "Enums.h"

const int DEFAULT_SPRITE = SPRITE_FRONT;

MovingThing::MovingThing(float x, float y, float w, float h, const Sprites *s){
	assert(s);
	bounds = new Rectangle(x, y, w, h);
	name = "MovingThing";
	sprites = s;
	velocity_x = 0.0;
	velocity_y = 0.0;
	velocity_jump = 0.0;
	force_x = 0.0;
	force_y = 0.0,
	mass = 1.0;
}

MovingThing::MovingThing(const Rectangle r, const Sprites *s){
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "MovingThing";
	sprites = s;
	velocity_x = 0.0;
	velocity_y = 0.0;
	velocity_jump = 0.0;
	force_x = 0.0;
	force_y = 0.0,
	mass = 1.0;
}

MovingThing::~MovingThing(){
	delete bounds;
}

const char *MovingThing::ToString() const{
	return name;
}

void MovingThing::draw(){
	glPushMatrix();
		glBindTexture(GL_TEXTURE_RECTANGLE_NV, sprites->getSprite(DEFAULT_SPRITE));
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

float MovingThing::checkBoundsX(float delta, const Rectangle world_bounds) const{
	if (bounds->position_x + delta > world_bounds.right())
		return world_bounds.right() - bounds->position_x;
	if (bounds->position_x + delta  < world_bounds.left())
		return bounds->position_x - world_bounds.left();
	return delta;
}

float MovingThing::checkBoundsY(float delta, const Rectangle world_bounds) const{
	if (bounds->position_y + delta > world_bounds.top())
		return world_bounds.top() - bounds->position_y;
	if (bounds->position_y + delta  < world_bounds.bottom())
		return bounds->position_y - world_bounds.bottom();
	return delta;
}