/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "JetpackDoc.h"
#include "JetpackUI.h"
#include "paintView.h"
#include "Sprites.h"
#include "Enums.h"
#include "MovingThing.h"
#include "StationaryThing.h"
#include "Hero.h"
#include "Pinwheel.h"

static int eventToDo;
static int isAnEvent=0;
const int NUM_ROWS = 16;
const int NUM_COLS = 26;
const float MAX_VELOCITY = 0.12f;
const float FORCE_GRAVITY = 0.012f;
const float JETPACK_THRUST = 0.024f;
const float JUMP_RESTITUTION = 0.4f;
const float MARGIN = 20.f;

PaintView::PaintView(int			x, 
					 int			y, 
					 int			w, 
					 int			h, 
					 const char*	l)
						: Fl_Gl_Window(x,y,w,h,l)
{
	// Dimensions
	row_w = w / (NUM_COLS * 1.0f);
	col_h = h / (NUM_ROWS * 1.0f);
	bounds = new Rectangle(0, 0, w, h);
	m_nDrawWidth = w;
	m_nDrawHeight = h;

	// Controls
	hold_left = level_loaded = hold_right = hold_up = hold_down = false;

	// consts
	max_velocity = col_h * MAX_VELOCITY;
	jump_restitution = col_h * JUMP_RESTITUTION;
	force_gravity = col_h * FORCE_GRAVITY;
	jetpack_thrust = col_h * JETPACK_THRUST;

	// hero/env
	stat_things = NULL;
	dyn_things = NULL;
	hero = NULL;
}

PaintView::~PaintView() {
	delete hero;
	stat_things->clear();
}

void PaintView::handleEventKeys() {
	if (isAnEvent) {
		isAnEvent	= 0;	

		// This is the event handler
		switch (eventToDo) 
		{
		case LEFT_MOUSE_DOWN:
			break;
		case LEFT_MOUSE_DRAG:
			break;
		case LEFT_MOUSE_UP:
			break;
		case RIGHT_MOUSE_DOWN:
			break;
		case RIGHT_MOUSE_DRAG:
			break;
		case RIGHT_MOUSE_UP:
			break;
		case ARROW_UP_PRESS:
			hold_up = true;
			break;
		case ARROW_UP_RELEASE:
			hold_up = false;
			break;
		case ARROW_DOWN_PRESS:
			hold_down = true;
			break;
		case ARROW_DOWN_RELEASE:
			hold_down = false;
			break;
		case ARROW_LEFT_PRESS:
			hold_left = true;
			break;
		case ARROW_LEFT_RELEASE:
			hold_left = false;
			break;
		case ARROW_RIGHT_PRESS:
			hold_right = true;
			break;
		case ARROW_RIGHT_RELEASE:
			hold_right = false;
			break;
		case SPACEBAR_PRESS:
			hero->velocity_jump = jump_restitution;
			break;
		default:
			printf("Unknown event!!\n");		
			break;
		}
	}
}

void PaintView::loadLevel() {
	assert(stat_things);
	assert(dyn_things);
	stat_things->push_back(new StationaryThing(10 * row_w, 9 * col_h, row_w, col_h, m_pDoc->sprites));
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			if ( i % 5 == 0 && j != 0 && j != NUM_COLS - 1 && j != NUM_COLS - 2)
				stat_things->push_back(new StationaryThing(j * row_w, i * col_h, row_w, col_h, m_pDoc->sprites));
		}	
	}
	for (int j = 0; j < NUM_COLS; j++) {
		dyn_things->push_back(new Pinwheel(10 * row_w, 8 * col_h, row_w, col_h, m_pDoc->sprites));
	}
	for (int j = 0; j < NUM_COLS; j++) {
		dyn_things->push_back(new Pinwheel(j * row_w, col_h, row_w, col_h, m_pDoc->sprites));
	}
	for (int j = 0; j < NUM_COLS; j++) {
		dyn_things->push_back(new Pinwheel(j * row_w, 0 * col_h, row_w, col_h, m_pDoc->sprites));
	}
	
}

void PaintView::drawBackGround() {
	assert(stat_things);
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, m_pDoc->sprites->getSprite(SPRITE_BACKGROUND));
		glTranslatef(bounds->left(), bounds->bottom(), 0);
		glBegin(GL_QUADS);
			glTexCoord2f( 0, 0 );                           
			glVertex2f( 0, 0 );
			glTexCoord2f(1, 0 );     
			glVertex2f( bounds->width, 0 );
			glTexCoord2f( 1, 1 );    
			glVertex2f( bounds->width, bounds->height );
			glTexCoord2f( 0, 1 );          
			glVertex2f( 0, bounds->height );
		glEnd();
	glPopMatrix();
	
	for (StationaryThing *s : *stat_things) {
		s->draw();
	}
}

void PaintView::drawMovingThings() {
	assert(dyn_things);
	for (MovingThing *baddie : *dyn_things){
		baddie->draw();
	}
}

void PaintView::drawHero() {
	assert(hero);
	hero->draw();
}

void PaintView::moveThings() {
	assert(dyn_things);
	for (MovingThing *baddie : *dyn_things){
		advancePosition(baddie, baddie->getIntendedX(), baddie->getIntendedY());
	}
}

void PaintView::moveHero() {
	assert(hero);
	
	// move in x-dir
	if (hold_left && !Fl::event_key(FL_Left)) {
		hold_left = false;
	} else if (hold_left){
		hero->velocity_x = - max_velocity;
	} else if (hold_right && !Fl::event_key(FL_Right)) {
		hold_left = false;
	} else if (hold_right) {
		hero->velocity_x = max_velocity;
	} else
		hero->velocity_x = 0;

	// move in y-dir
	if (hold_up && !Fl::event_key(FL_Up)) {
		hold_up = false;
	} else if (hold_up) {
		hero->force_y = - jetpack_thrust;
	} else
		hero->force_y = 0.0;

	// apply forces
	hero->velocity_jump -=  force_gravity * hero->mass;
	hero->velocity_y += (hero->force_y + force_gravity) * hero->mass;
	hero->velocity_x += hero->force_x * hero->mass;
	
	// Check limits
	if (hero->velocity_jump < 0.0)
		hero->velocity_jump = 0.0;
	
	if (hero->velocity_x > max_velocity) 
		hero->velocity_x = max_velocity;
	else if (-hero->velocity_x > max_velocity)
		hero->velocity_x = - max_velocity;
	
	if (hero->velocity_y > max_velocity) 
		hero->velocity_y = max_velocity;
	else if (-hero->velocity_y > max_velocity)
		hero->velocity_y = - max_velocity;

	// set positions
	advanceHeroPosition(hero->velocity_x, hero->velocity_y - hero->velocity_jump);
}

void PaintView::advanceHeroPosition(float delta_x, float delta_y) const {
	assert(hero);
	
	// check world bounds
	const Rectangle hero_bounds = hero->Bounds();
	const Rectangle new_hero_bounds_y = Rectangle(hero_bounds.position_x,
		hero_bounds.position_y + delta_y, hero_bounds.width, hero_bounds.height);
	const Rectangle new_hero_bounds_x = Rectangle(hero_bounds.position_x + delta_x,
		hero_bounds.position_y, hero_bounds.width, hero_bounds.height);

	// in the x direction
	if (new_hero_bounds_x.right() > bounds->right())
		delta_x = bounds->right() - hero_bounds.right();
	else if (new_hero_bounds_x.left()  < bounds->left()) 
		delta_x = bounds->left() - hero_bounds.left();

	// and in the y direction
	if (new_hero_bounds_y.top() > bounds->top())
		delta_y = bounds->top() - hero_bounds.top();
	else if (new_hero_bounds_y.bottom() < bounds->bottom())
		delta_y =  bounds->bottom() - hero_bounds.bottom();

	// check solid objects in x and y directions (if we need to)
	if (delta_x == 0 && delta_y == 0)
		return;

	for (StationaryThing *s : *stat_things){
		const Rectangle s_bounds = s->Bounds();
		if (s->Overlaps(new_hero_bounds_x)) {
			if (hero_bounds.right() <= s_bounds.left())
				delta_x = s_bounds.left() - hero_bounds.right();
			else
				delta_x = s_bounds.right() - hero_bounds.left();
		}
		if (s->Overlaps(new_hero_bounds_y)) {
			if (hero_bounds.top() <= s_bounds.bottom())
				delta_y = s_bounds.bottom() - hero_bounds.top();
			else
				delta_y =  s_bounds.top() - hero_bounds.bottom();
		}
	}

	hero->move(delta_x, delta_y);
}

void PaintView::advancePosition(MovingThing *thing, float delta_x, float delta_y) const {
	assert(thing);
	
	// check world bounds
	const Rectangle thing_bounds = thing->Bounds();
	const Rectangle new_thing_bounds_y = Rectangle(thing_bounds.position_x,
		thing_bounds.position_y + delta_y, thing_bounds.width, thing_bounds.height);
	const Rectangle new_thing_bounds_x = Rectangle(thing_bounds.position_x + delta_x,
		thing_bounds.position_y, thing_bounds.width, thing_bounds.height);

	// in the x direction
	if (new_thing_bounds_x.right() > bounds->right()) {
		delta_x = bounds->right() - thing_bounds.right();
		thing->hit_wall_right = true;
	} else if (new_thing_bounds_x.left() < bounds->left()) {
		delta_x = bounds->left() - thing_bounds.left();
		thing->hit_wall_left = true;
	}


	// and in the y direction
	if (new_thing_bounds_y.top() > bounds->top()) {
		delta_y = bounds->top() - thing_bounds.top();
		thing->hit_wall_top = true;
	} else if (new_thing_bounds_y.bottom() < bounds->bottom()) {
		delta_y = bounds->bottom() - thing_bounds.bottom();
		thing->hit_wall_bottom = true;
	}

	// check solid objects in x and y directions (if we need to)
	if (delta_x == 0 && delta_y == 0)
		return;

	for (StationaryThing *s : *stat_things){
		const Rectangle s_bounds = s->Bounds();
		if (s->Overlaps(new_thing_bounds_x)) {
			if (thing_bounds.right() <= s_bounds.left()) {
				delta_x = s_bounds.left() - thing_bounds.right();
				thing->hit_wall_right = true;
			} else {
				delta_x = s_bounds.right() - thing_bounds.left();
				thing->hit_wall_left = true;
			}
		}
		if (s->Overlaps(new_thing_bounds_y)) {
			if (thing_bounds.top() <= s_bounds.bottom()) {
				delta_y = s_bounds.bottom() - thing_bounds.top();
				thing->hit_wall_top = true;
			} else {
				delta_y =  s_bounds.top() - thing_bounds.bottom();
				thing->hit_wall_bottom = true;
			}
		}
	}
	thing->move(delta_x, delta_y);
}

void PaintView::draw()
{
	if(!valid())
	{
		// initialize opengl
		InitScene();
		printf("INITIALIZED\n");
		
		// draw bounds
		m_nDrawWidth = m_pDoc->m_nPaintWidth;
		m_nDrawHeight = m_pDoc->m_nPaintHeight;
		
		// row/column
		row_w = m_nDrawWidth / (NUM_COLS * 1.0f);
		col_h = m_nDrawHeight / (NUM_ROWS * 1.0f);
		
		// player bounds
		if (bounds)
			delete bounds;
		bounds = new Rectangle(0, m_nDrawHeight - MARGIN, m_nDrawWidth, m_nDrawHeight - MARGIN);
		
		// constants
		max_velocity = col_h * MAX_VELOCITY;
		jump_restitution = col_h * JUMP_RESTITUTION;
		force_gravity = col_h * FORCE_GRAVITY;
		jetpack_thrust = col_h * JETPACK_THRUST;
		
		// Hero
		if (hero)
			delete hero;
		hero = new Hero(50.f, 50.f, row_w, col_h, m_pDoc->sprites);

		// environment
		if (stat_things){
			stat_things->clear();
		}
		stat_things = new std::vector<StationaryThing *>();

		// baddies
		if (dyn_things){
			dyn_things->clear();
		}
		dyn_things = new std::vector<MovingThing *>();

		loadLevel();
	}

	// handle any events (keys)
	handleEventKeys();
	
	// move things
	moveHero();
	moveThings();
	
	// Draw Scene
	glEnable2D();

	// Make the sprite 2 times bigger (optional)
	glScalef( 2.0f, 2.0f, 0.0f );
	
	// clear screen and initialize things
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clean the screen and the depth buffer
	glLoadIdentity();
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glColor3f(1,1,1);
	
	// draw background
	drawBackGround();
	
	// draw everything else
	drawHero();
	drawMovingThings();

	glDisable2D();
}


int PaintView::handle(int event)
{
	int key;
	switch(event)
	{
	case FL_SHORTCUT:
	case FL_KEYBOARD:
		key = Fl::event_key();
		if (key == FL_Left){
			eventToDo = ARROW_LEFT_PRESS;
			hold_left = true;
			hold_right = false;
		} else if (key == FL_Right){
			eventToDo = ARROW_RIGHT_PRESS;
			hold_right= true;
			hold_left = false;
		} else if (key == FL_Up){
			eventToDo = ARROW_UP_PRESS;
			hold_up = true;
			hold_down = false;
		} else if (key == FL_Down){
			eventToDo = ARROW_DOWN_PRESS;
			hold_down = true;
			hold_up = false;
		} else if (key == 'a')
			m_pDoc->startAnimating();
		else if (key == 's')
			m_pDoc->stopAnimating();
		else if (key == ' ') {
			eventToDo = SPACEBAR_PRESS;
		} else
			break;
		isAnEvent=1;
		redraw();
		break;
	case FL_KEYUP:
		key = Fl::event_key();
		if (key == FL_Left) {
			hold_left = false;
			eventToDo = ARROW_LEFT_RELEASE;
			if (Fl::event_key(FL_Right))
				hold_right = true;
		} else if (key == FL_Right){
			eventToDo = ARROW_RIGHT_RELEASE;
			hold_right = false;
			if (Fl::event_key(FL_Left))
				hold_left = true;
		} else if (key == FL_Up){
			eventToDo = ARROW_UP_RELEASE;
			hold_up = false;
			if (Fl::event_key(FL_Down))
				hold_down = true;
		} else if (key == FL_Down){
			eventToDo = ARROW_DOWN_RELEASE;
			hold_down = false;
			if (Fl::event_key(FL_Up))
				hold_up = true;
		} else
			break;
		isAnEvent=1;
		redraw();
		break;
	case FL_ENTER:
	    redraw();
		break;
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

void PaintView::refresh()
{
	redraw();
}

void PaintView::resizeWindow(int width, int height)
{
	resize(x(), y(), width, height);
}

void PaintView::glEnable2D()
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

void PaintView::glDisable2D()
{
    glPopAttrib();
    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();
}

int PaintView::InitScene()

{
        // Disable lighting
        glDisable( GL_LIGHTING );

        // Disable dithering
        glDisable( GL_DITHER );

        // Disable blending (for now)
        glDisable( GL_BLEND );

        // Disable depth testing
        glDisable( GL_DEPTH_TEST );
		m_pDoc->sprites->Load("Resources/");
		return 1;
}