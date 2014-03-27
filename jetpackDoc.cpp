// It basically maintain the Image for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)


#include <FL/fl_ask.H>
#include <algorithm>
#include "JetpackDoc.h"
#include "JetpackUI.h"

#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } if ((sprites)!=NULL) {delete sprites; sprites=NULL; } }

JetpackDoc::JetpackDoc() 
{
	// Set NULL image name as init. 
	m_nWidth		= -1;
	m_ucImage		= NULL;
	m_ucPainting	= NULL;
	sprites = new Sprites();
	animating = false;
}

//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void JetpackDoc::setUI(JetpackUI* ui) 
{
	m_pUI	= ui;
	m_nPaintWidth = m_nWidth = DEFAULT_WIDTH;
	m_nPaintHeight = m_nHeight = DEFAULT_HEIGHT - DEFAULT_MARGIN;
	
	// allocate space for draw view
	m_ucPainting		= new unsigned char [m_nWidth* m_nHeight*4];
	memset(m_ucPainting, 0, m_nWidth* m_nHeight*4);

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(m_nWidth, m_nHeight);	
	m_pUI->m_paintView->refresh();
}

void callback(void* o) {
		((JetpackDoc *)o)->m_pUI->m_paintView->flush();
		Fl::repeat_timeout(1.0 / 30.0, callback, o);
    }

void JetpackDoc::startAnimating() {
	printf("ANIMATING\n");
	animating = true;
	Fl::add_timeout(1.0 / 30.0, callback, this);
}

void JetpackDoc::stopAnimating() {
	printf("STOPPING\n");
	Fl::remove_timeout(callback, this);
	animating = false;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int JetpackDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}



