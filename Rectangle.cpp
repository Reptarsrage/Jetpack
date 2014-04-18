/* Justin Robb
 * 3-27-14
 * JetPack
 * Abstract thing
*/

#include "rectangle.h"
const float OVERLAP_EPSILON = 0.0001f;

Rectangle::Rectangle(){
	position_x = 0;
	position_y = 0;
	width = 0;
	height = 0;
}

Rectangle::Rectangle(float x, float y, float w, float h){
	assert(w >= 0);
	assert(h >= 0);

	position_x = x;
	position_y = y;
	width = w;
	height = h;
}

bool Rectangle::Overlaps(const Rectangle other) const{
	
	return (left() + OVERLAP_EPSILON < other.right() && right() - OVERLAP_EPSILON > other.left() &&
			 bottom() + OVERLAP_EPSILON < other.top() && top() - OVERLAP_EPSILON > other.bottom());

}

/*  draws a filled-in rectangle */
void  Rectangle::draw() const{
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f( 0, 1 );                           
			glVertex2f( left(), top() );
			glTexCoord2f( 0, 0 );                           
			glVertex2f( left(), bottom() );
			glTexCoord2f( 1, 0 );                           
			glVertex2f( right(), bottom() );
			glTexCoord2f( 1, 1 );                           
			glVertex2f( right(), top() );
		glEnd();
	glPopMatrix();
}

bool Rectangle::ContainsPoint(float x, float y) const {
	return (x > left()) && 
		   (x < right()) && 
		   (y < top()) &&
		   (y > bottom());
}

float Rectangle::top() const {
	return position_y;
}

float Rectangle::bottom() const {
	return position_y - height;
}

float Rectangle::left() const {
	return position_x;
}

float Rectangle::right() const {
	return position_x + width;
}