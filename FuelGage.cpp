#include "FuelGage.h"
#include "Rectangle.h"
#include "Enums.h"
#include "jetPackUI.h"

FuelGage::FuelGage(float x, float y, float w, float h, const char* l) : OpenGl2DWindow(x,y,w,h,l){
	bounds = new Rectangle(0, h, w, h);
}

FuelGage::~FuelGage() {
	delete bounds;
}

void FuelGage::draw() {
	if (!valid()) {
		InitScene();
		valid(1);
	}
	glEnable2D();
	glBindTexture(GL_TEXTURE_2D, m_UI->sprites->getSprite(SPRITE_FUELBACK));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// draw bar
	glPushMatrix();
		glColor3f(0,1,0);
		glTranslatef(bounds->position_x + bounds->width * .086f, bounds->position_y - bounds->height *.533f, 0 );
		glBegin(GL_QUADS);
			glVertex2f(0,0);
			glVertex2f(bounds->width * .86f,0);
			glVertex2f(bounds->width * .86f, bounds->height * .33f);
			glVertex2f(0,bounds->height * .33f);
		glEnd();
	glPopMatrix();
	
	glDisable2D();
}