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
const float MARGIN_BOTTOM = 5.f;
const float MARGIN_LEFT = 5.f;
const float MARGIN_RIGHT = 5.f;
const int FRAME_SKIP = 3;

Editor::Editor(	float			x, 
				float			y, 
				float			w, 
				float			h, 
				const char*	l)
				: OpenGl2DWindow(x,y,w,h,l)
{	
	
	// Dimensions
	float width = w - (MARGIN_LEFT + MARGIN_RIGHT);
	float height = h - (MARGIN_BOTTOM + MARGIN_TOP);
	row_w = width / (NUM_COLS * 1.0f);
	col_h = height / (NUM_ROWS * 1.0f);
	bounds = new Rectangle(x + MARGIN_LEFT, h - MARGIN_BOTTOM, width, height);

	// better bounds
	left = bounds->left();
	top = bounds->bottom() + col_h;
	bottom = bounds->top();
	right = bounds->right() - row_w;

	// Controls
	choosing = hold_left = hold_right = hold_del = false;
	hold_up = hold_down = hold_place = false;

	// curser
	curser = new Rectangle(left, top, row_w, col_h);
	menu = new Rectangle(left, bottom, bounds->width, ((TYPE_COUNT / NUM_COLS) + 1)*col_h);
	menu_items = NULL;
	prev_curser = NULL;
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
		bounds = new Rectangle(MARGIN_LEFT, h() - MARGIN_BOTTOM, bounds->width,  bounds->height);

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
					menu_items[item_count]->SetBounds(menu_ptr.position_x, menu_ptr.position_y,row_w, col_h);
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
	glDrawBuffer(GL_BACK);

	// Draw Backdrop
	glBindTexture(GL_TEXTURE_2D, m_UI->sprites->getSprite(SPRITE_BACKGROUND));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);

	// draw placed items
	for (AbstractThing *thing : *placed_items) {
		if (thing->gen_type != NONSOLID && thing->gen_type != COLLECTABLE)
		thing->draw();
	}
	if (hero)
		hero->draw();
	if (door)
		door->draw();

	// draw placed collectables
	for (AbstractThing *thing : *placed_items) {
		if (thing->gen_type == COLLECTABLE)
		thing->draw();
	}

	// draw placed non solids
	for (AbstractThing *thing : *placed_items) {
		if (thing->gen_type == NONSOLID)
		thing->draw();
	}


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
	removeThing();
	hero = new Hero(curser->left(), curser->top(), row_w, col_h, m_UI->sprites);

}

void Editor::placeDoor() {
	if (choosing)
		return;
	if (door)
		door = NULL;
	removeThing();
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
		thing->SetBounds(bounds->left() + b.position_x * row_w, top + b.position_y*col_h, row_w, col_h);
		if (thing->getType() == TYPE_HERO) {
			hero = reinterpret_cast<Hero *>(thing);
			printf("Loading hero at col %d and row %d\n", col, row);
		}
		else if (thing->getType() == TYPE_DOOR){
			door = reinterpret_cast<Door *>(thing);
			printf("Loading door at col %d and row %d\n", col, row);
		}
		else {
			placed_items->push_back(thing);
			printf("Loading %s at col %d and row %d\n", thing->ToString(), col, row);
		}
	}
}

bool Editor::Playable() {
	return hero && door;
}

unsigned char * Editor::getScreen() {
	unsigned char *screenshot = (unsigned char *)malloc(w()*h()*3);
	unsigned char *flipped = (unsigned char *)malloc(w()*h()*3);
	glReadBuffer(GL_BACK);
	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ROW_LENGTH, w());
	glReadPixels( 0, 0, w(), h(), GL_RGB, GL_UNSIGNED_BYTE, screenshot );
	for (int i = 0; i < h(); i++) {
		for (int j = 0; j < w()*3; j++) {
			flipped[i*w()*3 + j] = screenshot[(h() - i - 1)*w()*3 + j];
		}
	}
	delete[] screenshot;
	return flipped;
}


std::list<AbstractThing *>* Editor::getLevelForTest() {
	assert(hero);
	assert(door);

	std::list<AbstractThing *> *q = new std::list<AbstractThing *>();
	Rectangle ptr = Rectangle(left, top, row_w, col_h);
	for (int row = 0; row < NUM_ROWS; row++){
		for (int col = 0; col < NUM_COLS; col++) {
			if (hero->Overlaps(ptr)) {
				printf("Saving hero at col %d and row %d\n", col, row);
				q->push_back(getThingFromCode(hero->getType(), col, row, hero->Bounds().width, hero->Bounds().height, m_UI->sprites));
			}
			if (door->Overlaps(ptr)) {
				printf("Saving door at col %d and row %d\n", col, row);
				q->push_back(getThingFromCode(door->getType(), col, row, door->Bounds().width, door->Bounds().height, m_UI->sprites));
			}
			for (AbstractThing *thing : *placed_items) {
				if (ptr.Overlaps(thing->Bounds())) {
					printf("Saving %s at col %d and row %d\n", thing->ToString(), col, row);
					q->push_back(getThingFromCode(thing->getType(), col, row, thing->Bounds().width, thing->Bounds().height, m_UI->sprites));
				}
			}
			ptr.position_x += row_w;
		}
		ptr.position_x = left;
		ptr.position_y += col_h;
	}
	return q;
}

std::list<AbstractThing *>* Editor::getLevel() {
	assert(hero);
	assert(door);

	std::list<AbstractThing *> *q = new std::list<AbstractThing *>();
	Rectangle ptr = Rectangle(left, top, row_w, col_h);
	for (int row = 0; row < NUM_ROWS; row++){
		for (int col = 0; col < NUM_COLS; col++) {
			if (hero->Overlaps(ptr)) {
				printf("Saving hero at col %d and row %d\n", col, row);
				q->push_back(hero);
			}
			if (door->Overlaps(ptr)) {
				printf("Saving door at col %d and row %d\n", col, row);
				q->push_back(door);
			}
			for (AbstractThing *thing : *placed_items) {
				if (ptr.Overlaps(thing->Bounds())) {
					printf("Saving %s at col %d and row %d\n", thing->ToString(), col, row);
					q->push_back(thing);
				}
			}
			q->push_back(NULL);
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
		Rectangle *temp = curser;
		curser = prev_curser;
		prev_curser = temp;
	} else {
		// turn menu on
		choosing = true;
		if (prev_curser != NULL) {
			Rectangle *temp = curser;
			curser = prev_curser;
			prev_curser = temp;
		} else {
			prev_curser = new Rectangle(*curser);
			curser->position_y = menu->bottom() + col_h;
			curser->position_x = menu->left();
		}
	}
}

void Editor::placeThing() {
	assert(!choosing);
	if (selected < 0)
		return;

	AbstractThing *item = getThingFromCode(selected, curser->position_x, curser->position_y,
		row_w, col_h, m_UI->sprites);
	item->SetBounds(curser->position_x, curser->position_y, row_w, col_h);

	int type = item->gen_type;
	
	if (type == SOLID) {
		removeThing();
	}
	
	if (hero && item->Overlaps(hero))
		hero = NULL;
	
	if (door && item->Overlaps(door))
		door = NULL;

	std::list<AbstractThing *>::iterator it = placed_items->begin();
	while (it != placed_items->end()) {
		if ((type == NONSOLID && (*it)->gen_type == NONSOLID ||
			type == COLLECTABLE && (*it)->gen_type == COLLECTABLE ||
			type == BADDIE && (*it)->gen_type == BADDIE) &&
			curser->Overlaps((*it)->Bounds())) {
			printf("Replacing! ");
			
			placed_items->erase(it++);
		} else
			++it;
	}
	printf("Pacing %dth item.\n", placed_items->size() + 1);
	placed_items->push_back(item);
}

void Editor::chooseThing(){
	assert(choosing);
	
	int row = (curser->position_y - (menu->bottom() + col_h)) / col_h;
	int col = (curser->position_x - menu->position_x + row_w / 2.f) / row_w;
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
	printf("chose %s at row %d and col %d\n", t->ToString(), row, col);
	delete t;
	selected = special_case + col + row*NUM_COLS;
}

void Editor::advancePosition(bool upf, bool downf, bool leftf, bool rightf) {
	if ((choosing && upf && curser->top() > menu->bottom() + col_h * 1.5f)
		|| (!choosing && upf && curser->top() > top + col_h / 2.f)) {
		curser->position_y -= col_h;
	}
	if (downf && curser->top() < bottom - col_h / 2.f) {
		curser->position_y += col_h;
	}
	if (leftf && curser->left() > left + row_w / 2.f) {
		curser->position_x -= row_w;
	}
	if (rightf && curser->left() < right - row_w / 2.f) {
		curser->position_x += row_w;
	}
}

void Editor::moveCurser() {
	assert(curser);
	
	//place/choose/ delete
	if (hold_place && !Fl::event_key(' ')) {
		hold_place = false;
	} else if (hold_place) {
   		handleSpace();
	} else if (hold_del && !Fl::event_key(FL_Shift_L) && !Fl::event_key(FL_Shift_R)) {
		hold_del = false;
	} else if (hold_del)
		removeThing();


	
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

void Editor::removeThing() {
	std::list<AbstractThing *>::iterator it = placed_items->begin();
	while (it != placed_items->end()) {
		if ((*it)->Overlaps(*curser)) {
			placed_items->erase(it++);
			printf("Replacing! ");
		} else
			++it;
	}
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
					hold_del = false;
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
				case FL_Shift_L:
				case FL_Shift_R:
					hold_del = true;
					hold_place = false;
					break;
			}
			break;
		case FL_KEYUP:
			switch(key) {
				case ' ':
					hold_place = false;
					if (Fl::event_key(FL_Shift_L) || Fl::event_key(FL_Shift_R))
						hold_del = true;
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
				case FL_Shift_L:
				case FL_Shift_R:
					hold_del = false;
					if (Fl::event_key(' '))
						hold_place = true;
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