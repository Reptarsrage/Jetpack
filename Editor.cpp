/* Justin Robb
 * 3-27-14
 * JetPack
*/
#include "JetpackUI.h"
#include "Editor.h"
#include "Sprites.h"
#include "Enums.h"
#include "MovingThing.h"
#include "StationaryThing.h"
#include "SolidThing.h"
#include "NonSolidThing.h"
#include "Collectable.h"
#include "Ladder.h"
#include "Hero.h"
#include "Pinwheel.h"
#include "Door.h"
#include "Bat.h"
#include "Predator.h"
#include "Spring.h"
#include "Egg.h"
#include "Robot.h"

const int NUM_ROWS = 16;
const int NUM_COLS = 26;
const float MARGIN_TOP = 5.f;
const float MARGIN_BOTTOM = 40.f;
const float MARGIN_LEFT = 5.f;
const float MARGIN_RIGHT = 15.f;

Editor::Editor(	float			x, 
				float			y, 
				float			w, 
				float			h, 
				const char*	l)
				: Fl_Gl_Window(x,y,w,h,l)
{	
	
	// Dimensions
	float width = w - (MARGIN_LEFT + MARGIN_RIGHT);
	float height = h - (MARGIN_BOTTOM + MARGIN_TOP);
	row_w = width / (NUM_COLS * 1.0f);
	col_h = height / (NUM_ROWS * 1.0f);
	bounds = new Rectangle(MARGIN_LEFT, h - MARGIN_BOTTOM, width, height);

	// better bounds
	left = bounds->left();
	top = bounds->bottom() + col_h;
	bottom = bounds->top();
	right = bounds->right() - row_w;

	// Controls
	choosing = hold_left = hold_right = false;
	hold_up = hold_down = false;

	// curser
	curser = new Rectangle(left, top, row_w, col_h);
	menu = new Rectangle(left, bottom, bounds->width, 2.f*col_h);
	menu_items = NULL;
	prev_curser = Rectangle(left, top, row_w, col_h);
}

Editor::~Editor() {
}

void Editor::draw()
{
	if(!valid())
	{
		// initialize opengl
		valid(1);
		InitScene();
		printf("INITIALIZED\n");

		if (!menu_items) {
			// populate menu items
			int rows = menu->height / col_h;
			int cols = menu->width / row_w;
			int item_count = 0;
			Rectangle menu_ptr = Rectangle(menu->left(), menu->bottom() + col_h, row_w, col_h);
			menu_items = new AbstractThing*[rows * cols];
			for (int j = 0; j < rows; j++) {
				for (int i = 0; i < cols; i++) {	                      
					menu_items[item_count] = getThingFromCode(item_count, menu_ptr.position_x, menu_ptr.position_y,
															  row_w, col_h, m_UI->sprites);
					item_count++;
					menu_ptr.position_x += row_w;
				}
				menu_ptr.position_y += col_h;
				menu_ptr.position_x = menu->left();
			}
		}
	}
	
	// move
	moveCurser();
	
	
	// Draw Scene
	glEnable2D();

	// clear screen and initialize things
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clean the screen and the depth buffer
	glLoadIdentity();
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glColor3f(1,1,1);
	
	// Draw Backdrop
	glBindTexture(GL_TEXTURE_2D, m_UI->sprites->getSprite(SPRITE_BACKGROUND));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	// draw menu
	if (choosing) {
		DrawMenu();
	}
	
	// draw curser
	glPushMatrix();
		glColor4f(1,0,0, 1);
		glLineWidth(3);	     
		glBegin(GL_LINES);                                         
			glVertex2f( curser->left(), curser->top() );                           
			glVertex2f( curser->left(), curser->bottom() ); 
			glVertex2f( curser->left(), curser->bottom() );
			glVertex2f( curser->right(), curser->bottom() );
			glVertex2f( curser->right(), curser->bottom() );  
			glVertex2f( curser->right(), curser->top() );
			glVertex2f( curser->right(), curser->top() );
			glVertex2f( curser->left(), curser->top() ); 
		glEnd();
		glColor4f(1,1,1, 1);
	glPopMatrix();
	glDisable2D();
}

void Editor::switchContext() {
	if (choosing) {
		// turn off menu, restore curser
		choosing = false;
		delete curser;
		curser = new Rectangle(prev_curser);
	} else {
		// turn menu on
		choosing = true;
		prev_curser = Rectangle(curser->position_x, curser->position_y, curser->width, curser->height);
		curser->position_y = menu->bottom() + col_h;
		curser->position_x = menu->left();
	}
}

void Editor::advancePosition(bool upf, bool downf, bool leftf, bool rightf) {
	if ((choosing && upf && curser->top() > menu->bottom() + col_h)
		|| (!choosing && upf && curser->top() > top)) {
		curser->position_y -= col_h;
	}
	if (downf && curser->top() < bottom) {
		curser->position_y += col_h;
	}
	if (leftf && curser->left() > left) {
		curser->position_x -= row_w;
	}
	if (rightf && curser->left() < right) {
		curser->position_x += row_w;
	}
}

void Editor::moveCurser() {
	assert(curser);
	bool up, down, left, right;
	up = down = left = right = false;

	// move in x-dir
	if (hold_left && !Fl::event_key(FL_Left)) {
		hold_left = false;
	} else if (hold_left){
		left = true;
	} else if (hold_right && !Fl::event_key(FL_Right)) {
		hold_right = false;
	} else if (hold_right) {
		right = true;
	}

	// move in y-dir
	if (hold_up && !Fl::event_key(FL_Up)) {
		hold_up = false;
	} else if (hold_up) {
			up = true;
	} else if (hold_down && !Fl::event_key(FL_Down)) 
		hold_down = false;
	else if (hold_down)
		down = true;

	// set positions
	advancePosition(up, down, left, right);
}

void Editor::DrawMenu() {
	// calculate positions
	int sprite = 0;
	int rows = menu->height / col_h;
	int cols = menu->width / row_w;
	int item_count = 0;
	Rectangle menu_ptr = Rectangle(menu->left(), menu->bottom() + col_h, row_w, col_h);
	
	// draw backdrop for menu
	glColor4f(.7f,.7f,.7f,1);
	menu->draw();
	
	// draw all menu items
	glPushMatrix();
		glColor3f(1,1,1);	
		while (menu_items[item_count] != NULL) {
			menu_items[item_count]->draw();
			item_count++;
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();

	// draw grid
	glPushMatrix();
		glColor3f(0,1,0);
		for (int j = 0; j < rows; j++) {
			for (int i = 0; i < cols; i++) {	                      
				glLineWidth(3);	     
				glBegin(GL_LINES);                                         
					glVertex2f( menu_ptr.left(), menu_ptr.top() );                           
					glVertex2f( menu_ptr.left(), menu_ptr.bottom() ); 
					glVertex2f( menu_ptr.left(), menu_ptr.bottom() );
					glVertex2f( menu_ptr.right(), menu_ptr.bottom() );
					glVertex2f( menu_ptr.right(), menu_ptr.bottom() );  
					glVertex2f( menu_ptr.right(), menu_ptr.top() );
					glVertex2f( menu_ptr.right(), menu_ptr.top() );
					glVertex2f( menu_ptr.left(), menu_ptr.top() ); 
				glEnd();
				menu_ptr.position_x += row_w;
			}
			menu_ptr.position_y += col_h;
			menu_ptr.position_x = menu->left();
		}
	glPopMatrix();
}


int Editor::handle(int event)
{
	if (Fl_Gl_Window::handle(event) != 0)
		return 1;
	int key = Fl::event_key();
	switch(event) {
		case FL_SHORTCUT:
		case FL_KEYBOARD:
			switch(key) {
				case FL_Enter:
					switchContext();
					break;
				case FL_Left:
					hold_left = true;
					hold_right = false;
					break;
				case FL_Right:
					hold_right= true;
					hold_left = false;
					break;
				case FL_Up:
					hold_up = true;
					hold_down = false;
					break;
				case FL_Down:
					hold_down = true;
					hold_up = false;
					break;
				case 'a':
					m_UI->startAnimating();
					break;
				case 's':
					m_UI->stopAnimating();
					break;
			}
			break;
		case FL_KEYUP:
			switch(key) {
				case FL_Left:
					hold_left = false;
					if (Fl::event_key(FL_Right))
						hold_right = true;
					break;
				case FL_Right:
					hold_right = false;
					if (Fl::event_key(FL_Left))
						hold_left = true;
					break;
				case FL_Up:
					hold_up = false;
					if (Fl::event_key(FL_Down))
						hold_down = true;
					break;
				case FL_Down:
					hold_down = false;
					if (Fl::event_key(FL_Up))
						hold_up = true;
					break;
			}
			break;
		case FL_ENTER:
		case FL_MOVE:
		case FL_FOCUS:
		case FL_UNFOCUS:
			break;
		default:
			return 0;
			break;
		}
	return 1;
}

void Editor::glEnable2D()
{

    GLint iViewport[4];

    // Get a copy of the viewport
    glGetIntegerv( GL_VIEWPORT, iViewport );

    // Save a copy of the projection matrix so that we can restore it 
    // when it's time to do 3D rendering again.
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();

    // Set up the orthographic projection
    glOrtho( iViewport[0], iViewport[0]+iViewport[2],
                        iViewport[1]+iViewport[3], iViewport[1], -1, 1 );

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();

    // Make sure depth testing and lighting are disabled for 2D rendering until
    // we are finished rendering in 2D
    glPushAttrib( GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT );
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_LIGHTING );

}

void Editor::glDisable2D()
{
    glPopAttrib();
    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();
}

int Editor::InitScene()

{
        // Disable lighting
        glDisable( GL_LIGHTING );

        // Disable dithering
        glDisable( GL_DITHER );

        // Disable blending (for now)
        glDisable( GL_BLEND );

        // Disable depth testing
        glDisable( GL_DEPTH_TEST );

		m_UI->sprites->Load("Resources/");

		return 1;
}