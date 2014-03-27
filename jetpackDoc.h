// 
// JetpackDoc.h
//
// header file for Doc 
//

#ifndef JetpackDoc_h
#define JetpackDoc_h

#include "jetpack_main.h"
#include "Sprites.h"

class JetpackUI;

class JetpackDoc 
{
public:
	JetpackDoc();
	void	setUI(JetpackUI* ui);		// Assign the UI to use

	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	void	startAnimating();
	void	stopAnimating();

// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Images for original image and painting.
	unsigned char*	m_ucImage;
	unsigned char*	m_ucPainting;						

	JetpackUI*	m_pUI;
	Sprites *sprites;
	bool animating;
};

extern void MessageBox(char *message);

#endif