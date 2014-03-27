//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//

#include "jetpack_main.h"
#include "JetpackDoc.h"
#include "JetpackUI.h"
#include "paintView.h"
#include "Sprites.h"
#include "Enums.h"

#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif

static int		eventToDo;
static int		isAnEvent=0;

PaintView::PaintView(int			x, 
					 int			y, 
					 int			w, 
					 int			h, 
					 const char*	l)
						: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;
	m_control_y = -20;
	m_control_x = 20;
	hold_left = background_drawn = hold_right = hold_up = hold_down = false;
}


void PaintView::draw()
{

	if(!valid())
	{
		InitScene();
	}

	m_nWindowWidth	= w();
	m_nWindowHeight	= h();

	int drawWidth, drawHeight;
	drawWidth = m_pDoc->m_nPaintWidth;
	drawHeight = m_pDoc->m_nPaintHeight;

	m_pPaintBitstart = m_pDoc->m_ucPainting;

	m_nDrawWidth	= drawWidth;
	m_nDrawHeight	= drawHeight;

	if (isAnEvent) 
	{
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
		default:
			printf("Unknown event!!\n");		
			break;
		}
	}
	
	if (hold_left && !Fl::event_key(FL_Left))
		hold_left = false;
	else if (hold_left)
		m_control_x -= 5;

	if (hold_right && !Fl::event_key(FL_Right))
		hold_left = false;
	else if (hold_right)
		m_control_x += 5;

	if (hold_up && !Fl::event_key(FL_Up))
		hold_up = false;
	else if (hold_up)
		m_control_y += 5;

	if (hold_down && !Fl::event_key(FL_Down))
		hold_down = false;
	else if (hold_down)
		m_control_y -= 5;
	

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

	float h = m_nDrawHeight / 16.0;
	float w = m_nDrawWidth / 26.0;
	
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 26; j++){
			glPushMatrix();
				glBindTexture(GL_TEXTURE_RECTANGLE_NV, m_pDoc->sprites->getSprite((26*i + j) % SPRITE_COUNT - 1));
				glTranslatef(j*w, i*h, 0);
				glRotatef(180, 0,0, 1);
				glBegin(GL_QUADS);
					glTexCoord2i( 0, h );                           
					 glVertex2i( 0, 0 );
					 glTexCoord2i( w,h );     
					 glVertex2i( w, 0 );
					 glTexCoord2i( w, 0 );    
					 glVertex2i( w,h );
					 glTexCoord2i( 0, 0 );          
					 glVertex2i( 0, h );
				 glEnd();
			glPopMatrix();
		}
	}

	glBindTexture(GL_TEXTURE_RECTANGLE_NV, m_pDoc->sprites->getSprite(SPRITE_FRONT));
	glPushMatrix();
		glTranslatef(m_control_x, -m_control_y, 0);
		glRotatef(180, 0, 0, 1);	
			glBegin(GL_QUADS);
				glTexCoord2i( 0, h );                           
				glVertex2i( 0, 0 );
				glTexCoord2i( w,h );     
				glVertex2i( w, 0 );
				glTexCoord2i( w, 0 );    
				glVertex2i( w,h );
				glTexCoord2i( 0, 0 );          
				glVertex2i( 0, h );
			glEnd();
	glPopMatrix();

	glDisable2D();

	//glFlush();
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
		else
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