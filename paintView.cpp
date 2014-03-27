#include "jetpack_main.h"
#include "JetpackDoc.h"
#include "JetpackUI.h"
#include "paintView.h"
#include "Sprites.h"
#include "Enums.h"

static int eventToDo;
static int isAnEvent=0;
const int NUM_ROWS = 26;
const int NUM_COLS = 16;
const float MAX_VELOCITY = 0.12;
const float FORCE_GRAVITY = 0.012;
const float JETPACK_THRUST = 0.024;
const float JUMP_RESTITUTION = 0.4;

PaintView::PaintView(int			x, 
					 int			y, 
					 int			w, 
					 int			h, 
					 const char*	l)
						: Fl_Gl_Window(x,y,w,h,l)
{
	// Dimensions
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;
	row_w = w / (NUM_ROWS * 1.0f);
	col_h = h / (NUM_COLS * 1.0f);
	bounds_right = m_nDrawWidth - row_w;
	bounds_left = row_w;
	bounds_top = m_nDrawHeight - col_h;
	bounds_bottom = col_h;
	
	// Hero
	pos_y = 50.0;
	pos_x = 50.0;
	velocity_x = 0.0;
	velocity_y = 0.0;
	velocity_jump = 0.0;
	force_x = 0.0;
	force_y = 0.0,
	mass = 1.0;

	// Controls
	hold_left = background_drawn = hold_right = hold_up = hold_down = false;

	// consts
	max_velocity = col_h * MAX_VELOCITY;
	jump_restitution = col_h * JUMP_RESTITUTION;
	force_gravity = col_h * FORCE_GRAVITY;
	jetpack_thrust = col_h * JETPACK_THRUST;
}


void PaintView::handleEventKeys() {
	if (isAnEvent) {
		isAnEvent	= 0;	

		// This is the event handler
		switch (eventToDo) 
		{
		case LEFT_MOUSE_DOWN:
			m_pDoc->startAnimating();
			break;
		case LEFT_MOUSE_DRAG:
			break;
		case LEFT_MOUSE_UP:
			break;
		case RIGHT_MOUSE_DOWN:
			m_pDoc->stopAnimating();
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
			velocity_jump = jump_restitution;
			break;
		default:
			printf("Unknown event!!\n");		
			break;
		}
	}
}

void PaintView::drawBackGround() {
	for (int i = 0; i < NUM_COLS; i++) {
		for (int j = 0; j < NUM_ROWS; j++){
			glPushMatrix();
				glBindTexture(GL_TEXTURE_RECTANGLE_NV, m_pDoc->sprites->getSprite((26*i + j) % SPRITE_COUNT - 1));
				glTranslatef(j*row_w, i*col_h, 0);
				glRotatef(180, 0,0, 1);
				glBegin(GL_QUADS);
					glTexCoord2i( 0, col_h );                           
					 glVertex2i( 0, 0 );
					 glTexCoord2i( row_w, col_h );     
					 glVertex2i( row_w, 0 );
					 glTexCoord2i( row_w, 0 );    
					 glVertex2i( row_w, col_h );
					 glTexCoord2i( 0, 0 );          
					 glVertex2i( 0, col_h );
				 glEnd();
			glPopMatrix();
		}
	}
}

void PaintView::drawMovingThings() {
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, m_pDoc->sprites->getSprite(SPRITE_FRONT));
	glPushMatrix();
		glTranslatef(pos_x, pos_y, 0);
		glRotatef(180, 0, 0, 1);	
			glBegin(GL_QUADS);
				glTexCoord2i( 0, col_h );                           
				glVertex2i( 0, 0 );
				glTexCoord2i( row_w, col_h );     
				glVertex2i( row_w, 0 );
				glTexCoord2i( row_w, 0 );    
				glVertex2i( row_w, col_h );
				glTexCoord2i( 0, 0 );          
				glVertex2i( 0, col_h );
			glEnd();
	glPopMatrix();
}

float PaintView::checkBoundsX(float delta) {
	if (pos_x + delta > bounds_right)
		return bounds_right - pos_x;
	if (pos_x + delta  < bounds_left)
		return pos_x - bounds_left;
	return delta;
}

float PaintView::checkBoundsY(float delta) {
	if (pos_y + delta > bounds_top)
		return bounds_top - pos_y;
	if (pos_y + delta  < bounds_bottom)
		return pos_y - bounds_bottom;
	return delta;
}

void PaintView::moveThings() {
	// move in x-dir
	if (hold_left && !Fl::event_key(FL_Left)) {
		hold_left = false;
	} else if (hold_left){
		velocity_x = - max_velocity;
	} else if (hold_right && !Fl::event_key(FL_Right)) {
		hold_left = false;
	} else if (hold_right) {
		velocity_x = max_velocity;
	} else
		velocity_x = 0;

	// move in y-dir
	if (hold_up && !Fl::event_key(FL_Up)) {
		hold_up = false;
	} else if (hold_up) {
		force_y = - jetpack_thrust;
	} else
		force_y = 0.0;

	// apply forces
	velocity_jump -=  force_gravity * mass;
	velocity_y += (force_y + force_gravity) * mass;
	velocity_x += force_x * mass;
	
	// Check limits
	if (velocity_jump < 0.0)
		velocity_jump = 0.0;
	
	if (velocity_x > max_velocity) 
		velocity_x = max_velocity;
	else if (-velocity_x > max_velocity)
		velocity_x = - max_velocity;
	
	if (velocity_y > max_velocity) 
		velocity_y = max_velocity;
	else if (-velocity_y > max_velocity)
		velocity_y = - max_velocity;

	// set positions
	pos_x += checkBoundsX(velocity_x);
	pos_y += checkBoundsY(velocity_y - velocity_jump);
}

void PaintView::draw()
{

	if(!valid())
	{
		InitScene();
		printf("INITIALIZED\n");
		// get/set bounds
		m_nWindowWidth	= w();
		m_nWindowHeight	= h();
		int drawWidth, drawHeight;
		drawWidth = m_pDoc->m_nPaintWidth;
		drawHeight = m_pDoc->m_nPaintHeight;
		m_pPaintBitstart = m_pDoc->m_ucPainting;
		m_nDrawWidth = drawWidth;
		m_nDrawHeight = drawHeight;
		row_w = m_nDrawWidth / (NUM_ROWS * 1.0f);
		col_h = m_nDrawHeight / (NUM_COLS * 1.0f);
		bounds_right = m_nDrawWidth - row_w;
		bounds_left = row_w;
		bounds_top = m_nDrawHeight - col_h;
		bounds_bottom = col_h;
		max_velocity = col_h * MAX_VELOCITY;
		jump_restitution = col_h * JUMP_RESTITUTION;
		force_gravity = col_h * FORCE_GRAVITY;
		jetpack_thrust = col_h * JETPACK_THRUST;
	}

	// handle any events (keys)
	handleEventKeys();
	
	// move things
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