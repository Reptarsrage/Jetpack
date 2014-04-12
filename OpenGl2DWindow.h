/* Justin Robb
 * 3-30-14
 * JetPack
 * The editing window
*/

#ifndef OpenGl2DWindow_H
#define OpenGl2DWindow_H

#include <FL/Fl_Gl_Window.H>
#include <stdlib.h>
#include <vector>
#include <list>

#ifdef __APPLE__
#include "OpenGL/glew.h"
#else
#include "GL/glew.h"
#endif

class JetpackUI;

/* Controls the animation and drawing */
class OpenGl2DWindow : public Fl_Gl_Window
{
// Functions
protected:
	OpenGl2DWindow(float x, float y, float w, float h, const char* l) : Fl_Gl_Window(x,y,w,h,l) {}

	/* Helper function to initialize opengl for drawing*/
	int InitScene();
	
	/* Helper function to enable 2d drawing in opengl */
	void glEnable2D();
	
	/* Helper function to disable 2d drawing in opengl */
	void glDisable2D();

// Attributes
public:
	JetpackUI *m_UI;

};

#endif // OpenGl2DWindow_H