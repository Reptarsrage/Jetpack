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
#include "Gem.h"
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
const int FRAME_SKIP = 3;

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
	hold_up = hold_down = hold_place = false;

	// curser
	curser = new Rectangle(left, top, row_w, col_h);
	menu = new Rectangle(left, bottom, bounds->width, ((TYPE_COUNT / NUM_COLS) + 1)*col_h);
	menu_items = NULL;
	prev_curser = Rectangle(left, top, row_w, col_h);
	frame = FRAME_SKIP;
	selected = -1;
	placed_items = new std::list<AbstractThing *>();
	hero = NULL;
	door = NULL;
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
			for (int i = 0; i < rows * cols; i++){
				menu_items[i] = NULL;
			}
			
			for (int j = 0; j < rows; j++) {
				for (int i = 0; i < cols; i++) {	                      
					if (item_count >= TYPE_COUNT)
						break;
					
					while (item_count == TYPE_DOOR || item_count == TYPE_HERO)
						item_count++;
					
					menu_items[item_count] = getThingFromCode(item_count, menu_ptr.position_x, menu_ptr.position_y,
															  row_w, col_h, m_UI->sprites);
					printf("added menu item %d, %s.\n", item_count, menu_items[item_count]->ToString());
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

	// draw placed items
	for (AbstractThing *thing : *placed_items) {
		thing->draw();
	}
	if (hero)
		hero->draw();
	if (door)
		door->draw();
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

void Editor::Clear() {
	delete placed_items;
	delete hero;
	delete door;
	hero = NULL;
	door = NULL;
	placed_items = new std::list<AbstractThing *>();
}

void Editor::placeHero() {
	if (choosing)
		return;
	if (hero)
		hero = NULL;

	hero = new Hero(curser->left(), curser->top(), row_w, col_h, m_UI->sprites);

}

void Editor::placeDoor() {
	if (choosing)
		return;
	if (door)
		door = NULL;

	door = new Door(curser->left(), curser->top(), row_w, col_h, m_UI->sprites);
}

void Editor::loadLevel(std::list<AbstractThing *> level) {
	Clear();
	if (level.empty())
		return;

	int row, col;
	for (AbstractThing *thing : level) {
		const Rectangle b = thing->Bounds();
		row = static_cast<int>(b.position_x);
		col = static_cast<int>(b.position_y);
		thing->SetBounds(left + b.position_x * row_w, top + b.position_y*col_h, b.width, b.height);
		if (thing->getType() == TYPE_HERO) {
			hero = reinterpret_cast<Hero *>(thing);
			printf("loading hero at col %d and row %d\n", col, row);
		}
		else if (thing->getType() == TYPE_DOOR){
			door = reinterpret_cast<Door *>(thing);
			printf("loading door at col %d and row %d\n", col, row);
		}
		else {
			placed_items->push_back(thing);
			printf("loading thing at col %d and row %d\n", col, row);
		}
	}
}

bool Editor::Playable() {
	return hero && door;
}

const std::queue<AbstractThing *>* Editor::getLevel() {
	assert(hero);
	assert(door);
	
	std::queue<AbstractThing *> *q = new std::queue<AbstractThing *>();
	Rectangle ptr = Rectangle(left, top, row_w, col_h);
	for (int row = 0; row < NUM_ROWS; row++){
		for (int col = 0; col < NUM_COLS; col++) {
			if (hero->Overlaps(ptr)) {
				printf("Saving hero at col %d and row %d\n", col, row);
				q->push(hero);
			}
			if (door->Overlaps(ptr)) {
				printf("Saving door at col %d and row %d\n", col, row);
				q->push(door);
			}
			for (AbstractThing *thing : *placed_items) {
				if (thing->Overlaps(ptr)) {
					printf("Saving thing at col %d and row %d\n", col, row);
					q->push(thing);
				}
			}
			q->push(NULL);
			ptr.position_x += row_w;
		}
		ptr.position_x = left;
		ptr.position_y += col_h;
	}
	return q;
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

void Editor::placeThing(){
	assert(!choosing);
	if (selected < 0)
		return;

	AbstractThing *item = getThingFromCode(selected, curser->position_x, curser->position_y,
		row_w, col_h, m_UI->sprites);
	std::list<AbstractThing *>::iterator it;
	for (it =  placed_items->begin(); it != placed_items->end(); ++it) {
		if ((*it)->Overlaps(item)) {
			placed_items->erase(it);
			break;
		} 
	}
	placed_items->push_back(item);
}

void Editor::chooseThing(){
	assert(choosing);
	
	int row = (curser->position_y - (menu->bottom() + col_h)) / col_h;
	int col = (curser->position_x - menu->position_x) / row_w;
	int special_case = 0;
	if (col + row*NUM_COLS >= TYPE_DOOR)
		special_case++;
	if (special_case + col + row*NUM_COLS >= TYPE_HERO)
		special_case++;
	if (special_case + col + row*NUM_COLS >= TYPE_COUNT){
		printf("Not a choosable thing!\n");
		return;
	}
	AbstractThing *t = getThingFromCode(special_case + col + row*NUM_COLS, 0, 0 ,0 ,0, m_UI->sprites);
	printf("chose %s\n", t->ToString());
	delete t;
	selected = special_case + col + row*NUM_COLS;
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
	
	//place/choose
	if (hold_place && !Fl::event_key(' ')) {
		hold_place = false;
	} else if (hold_place) {
   		handleSpace();
	}
	
	// skip some frames
	if (frame < 0)
		frame = FRAME_SKIP;
	else {
		frame--;
		return;
	}

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

void Editor::handleSpace() {
	if (choosing) {
		// select item
		chooseThing();
		hold_place = false;
	} else {
		// place item
		placeThing();
	}
}

void Editor::DrawMenu() {
	// calculate positions
	int sprite = 0;
	int rows = menu->height / col_h;
	int cols = menu->width / row_w;
	Rectangle menu_ptr = Rectangle(menu->left(), menu->bottom() + col_h, row_w, col_h);
	
	// draw backdrop for menu
	glColor4f(.7f,.7f,.7f,1);
	menu->draw();
	
	// draw all menu items
	glPushMatrix();
		glColor3f(1,1,1);	
		for (int i = 0; i < TYPE_COUNT; i++){
			if (menu_items[i] != NULL) {
				menu_items[i]->draw();
			}
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
				case 'j':
					placeHero();
					break;
				case 'd':
					placeDoor();
					break;
				case ' ':
					hold_place = true;
					handleSpace();
					break;
				case FL_Enter:
					switchContext();
					break;
				case FL_Left:
					advancePosition(false, false, true, false);
					frame = 20;
					hold_left = true;
					hold_right = false;
					break;
				case FL_Right:
					advancePosition(false, false, false, true);
					frame = 20;
					hold_right= true;
					hold_left = false;
					break;
				case FL_Up:
					advancePosition(true, false, false, false);
					frame = 20;
					hold_up = true;
					hold_down = false;
					break;
				case FL_Down:
					advancePosition(false, true, false, false);
					frame = 20;
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
				case ' ':
					hold_place = false;
					break;	
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