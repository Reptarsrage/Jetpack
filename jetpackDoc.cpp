/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include <FL/fl_ask.H>
#include <algorithm>
#include "JetpackDoc.h"
#include "JetpackUI.h"

#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } if ((sprites)!=NULL) {delete sprites; sprites=NULL; } }
const int FRAME_RATE = 100; //push it to the limit??


JetpackDoc::JetpackDoc() 
{
	m_nWidth		= -1;
	sprites = new Sprites();
	animating = false;
}

void JetpackDoc::setUI(JetpackUI* ui) 
{
	m_pUI	= ui;
	m_nPaintWidth = m_nWidth = DEFAULT_WIDTH;
	m_nPaintHeight = m_nHeight = DEFAULT_HEIGHT - DEFAULT_MARGIN;

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(m_nWidth, m_nHeight);	
	m_pUI->m_paintView->refresh();
	
	// imdediately start (change later)
	startAnimating();
}

void callback(void* o) {
		((JetpackDoc *)o)->m_pUI->m_paintView->refresh();
		Fl::repeat_timeout(1.0 / FRAME_RATE, callback, o);
    }

void JetpackDoc::startAnimating() {
	printf("ANIMATING\n");
	animating = true;
	Fl::add_timeout(1.0 / FRAME_RATE, callback, this);
}

void JetpackDoc::stopAnimating() {
	printf("STOPPING\n");
	Fl::remove_timeout(callback, this);
	animating = false;
}



