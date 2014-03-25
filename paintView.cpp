//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//

#include "jetpack_main.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "paintView.h"


#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6
#define ARROW_UP_PRESS		7
#define ARROW_UP_RELEASE	8
#define ARROW_LEFT_PRESS	9
#define ARROW_LEFT_RELEASE	10
#define ARROW_RIGHT_PRESS	11
#define ARROW_RIGHT_RELEASE	12
#define ARROW_DOWN_PRESS	13
#define ARROW_DOWN_RELEASE	14


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
	m_control_y = 0;
	m_control_x = 0;
	hold_left = hold_right = hold_up = hold_down = false;
}


void PaintView::draw()
{
	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
	#endif // !MESA

	if(!valid())
	{

		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		ortho();

		int	cx	= m_nWindowWidth = w();
		int	cy	= m_nWindowHeight = h();

		// Tell openGL to read from the front buffer when capturing
		// out paint strokes 
		glReadBuffer( GL_FRONT );

		glViewport( 0, 0, cx, cy );

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluOrtho2D( 0, cx, 0, cy );

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();

		// This translation is needed to make the image pixels line up with
		// the screen's pixels.  For details, visit:
		// http://www.opengl.org/resources/faq/technical/transformations.htm#tran0030
		glTranslatef( 0.375, 0.375, 0.0 );

		glClear( GL_COLOR_BUFFER_BIT );
	}

	m_nWindowWidth	= w();
	m_nWindowHeight	= h();

	int drawWidth, drawHeight;
	drawWidth = min( m_nWindowWidth, m_pDoc->m_nPaintWidth );
	drawHeight = min( m_nWindowHeight, m_pDoc->m_nPaintHeight );

	int startrow = m_pDoc->m_nPaintHeight - (drawHeight);
	if ( startrow < 0 ) startrow = 0;

	m_pPaintBitstart = m_pDoc->m_ucPainting + 
		3 * ((m_pDoc->m_nPaintWidth * startrow));

	m_nDrawWidth	= drawWidth;
	m_nDrawHeight	= drawHeight;

	m_nStartRow		= startrow;
	m_nEndRow		= startrow + drawHeight;
	m_nStartCol		= 0;
	m_nEndCol		= m_nStartCol + drawWidth;

	if (!isAnEvent) 
	{
		//RestoreContent();
	}

	if (isAnEvent) 
	{
		RestoreContent();
		// Clear it after processing.
		isAnEvent	= 0;	

		// This is the event handler
		switch (eventToDo) 
		{
		case LEFT_MOUSE_DOWN:
			glBegin( GL_POINTS );
				glVertex2d( Fl::event_x(), m_nWindowHeight - Fl::event_y());
			glEnd();
			break;
		case LEFT_MOUSE_DRAG:
			glBegin( GL_POINTS );
				glColor3f(1.0, 0.0, 0.0);
				glVertex2d( Fl::event_x(), m_nWindowHeight - Fl::event_y() );
			glEnd();
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
		default:
			printf("Unknown event!!\n");		
			break;
		}
	}
	if (hold_up)
		m_control_y += 5;
	if (hold_down)
		m_control_y -= 5;
	if (hold_left)
		m_control_x -= 5;
	if (hold_right)
		m_control_x += 5;

	glPushMatrix();
		glTranslatef(m_control_x, m_control_y, 0);
		glBegin( GL_QUADS );
			glColor3f(0,1,0);	
			glVertex2d( 0, 0);
			glVertex2d( 0, 20);
			glVertex2d( 20, 20);
			glVertex2d( 20, 0);
		glEnd();
	glPopMatrix();
	SaveCurrentBackContent();
	glFlush();

	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
	#endif // !MESA
}


int PaintView::handle(int event)
{
	int key;
	switch(event)
	{
	case FL_SHORTCUT:
	case FL_KEYBOARD:
		key = Fl::event_key();
		if (key == FL_Left)
			eventToDo = ARROW_LEFT_PRESS;
		else if (key == FL_Right)
			eventToDo = ARROW_RIGHT_PRESS;
		else if (key == FL_Up)
			eventToDo = ARROW_UP_PRESS;
		else if (key == FL_Down)
			eventToDo = ARROW_DOWN_PRESS;
		else
			break;
		isAnEvent=1;
		redraw();
		break;
	case FL_KEYUP:
		key = Fl::event_key();
		if (key == FL_Left)
			eventToDo = ARROW_LEFT_RELEASE;
		else if (key == FL_Right)
			eventToDo = ARROW_RIGHT_RELEASE;
		else if (key == FL_Up)
			eventToDo = ARROW_UP_RELEASE;
		else if (key == FL_Down)
			eventToDo = ARROW_DOWN_RELEASE;
		else
			break;
		isAnEvent=1;
		redraw();
		break;
	case FL_ENTER:
	    redraw();
		break;
	case FL_PUSH:
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DOWN;
		else
			eventToDo=LEFT_MOUSE_DOWN;
		isAnEvent=1;
		redraw();
		break;
	case FL_DRAG:
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DRAG;
		else
			eventToDo=LEFT_MOUSE_DRAG;
		isAnEvent=1;
		redraw();
		break;
	case FL_RELEASE:
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_UP;
		else
			eventToDo=LEFT_MOUSE_UP;
		isAnEvent=1;
		redraw();
		break;
	case FL_MOVE:
		break;
	case FL_FOCUS:
	case FL_UNFOCUS:
		return 1;
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

void PaintView::SaveCurrentContent()
{
	// Tell OpenGL to read pixels from the front buffer
	glReadBuffer(GL_FRONT);

	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	
	glReadPixels( 0, 
				  m_nWindowHeight - m_nDrawHeight, 
				  m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart );
}

void PaintView::SaveCurrentBackContent()
{
	glReadBuffer(GL_BACK);

	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	
	glReadPixels( 0, 
				  m_nWindowHeight - m_nDrawHeight, 
				  m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart );

	glReadBuffer(GL_FRONT);
}

void PaintView::RestoreContent()
{
	glDrawBuffer(GL_BACK);

	glClear( GL_COLOR_BUFFER_BIT );

	glRasterPos2i( 0, m_nWindowHeight - m_nDrawHeight );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	glDrawPixels( m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart);

//	glDrawBuffer(GL_FRONT);
}