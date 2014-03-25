// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "jetpack_main.h"

class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int     clearCanvas();                  // called by the UI to clear the drawing canvas

	char*	getImageName();					// get the current image name
	

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

	// Used by the filtering code so that we can
	// preview filters before applying.
	unsigned char*	m_ucPreviewBackup;

	// The current active brush.

	// Size of the brush.
	int m_nSize;							

	ImpressionistUI*	m_pUI;

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// get the color of the source buffer at the specified point	
	GLubyte* GetPixel( const unsigned char* sourceBuffer,
		int srcBufferWidth, int srcBufferHeight, int x, int y );

private:
	char			m_imageName[256];

};

extern void MessageBox(char *message);

#endif
