#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <FL/Fl_Gl_Window.H>
#include <stdlib.h>

#ifdef __APPLE__
#include "OpenGL/glew.h"
#else
#include "GL/glew.h"
#endif

class JetpackDoc;

class PaintView : public Fl_Gl_Window
{
public:
	PaintView(int x, int y, int w, int h, const char* l);
	void draw();
	int handle(int event);

	void refresh();

	void resizeWindow(int width, int height);

	void SaveCurrentContent();
	void SaveCurrentBackContent();
	void RestoreContent();

	JetpackDoc *m_pDoc;
private:
	void handleEventKeys();
	void drawBackGround();
	void drawMovingThings();
	void moveThings();
	float checkBoundsX(float delta);
	float checkBoundsY(float delta);

private:
	int InitScene();
	void glEnable2D();
	void glDisable2D();
	GLvoid* m_pPaintBitstart;
	int		m_nDrawWidth,
			m_nDrawHeight,
			m_nWindowWidth, 
			m_nWindowHeight,
			bounds_right,
			bounds_left,
			bounds_top,
			bounds_bottom;
			

	float	row_w, 
			col_h,
			pos_x,
			pos_y,
			velocity_x,
			velocity_y,
			velocity_jump,
			force_x,
			force_y,
			mass,
			max_velocity,
			jump_restitution,
			force_gravity,
			jetpack_thrust;

	bool	hold_left,
			hold_right,
			hold_up,
			hold_down,
			background_drawn;

};

#endif