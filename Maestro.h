/* Justin Robb
 * 4-10-14
 * JetPack
 * Game coordinator
*/

#ifndef MAESTRO_H_
#define MAESTRO_H_

#include "Game.h"
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_BMP_Image.H>
#include <FL/Fl_Double_Window.H>
#include <stdlib.h>
#include <vector>
#include <list>
#include "FuelGage.h"

#ifdef __APPLE__
#include "OpenGL/glew.h"
#else
#include "GL/glew.h"
#endif

class Rectangle;
class JetpackUI;
class AbstractThing;
class Game;
class FuelGage;

/*
 * Works closely with the game to coordinate important things like
 * level progression, score, deaths, displaying info, ect.
  */
class Maestro : public Fl_Group
{
// Functions
public:
	Maestro(float x, float y, float w, float h, JetpackUI *ui, const char* l);
	~Maestro();



	/* loads a level from a file */
	void loadLevel(std::list<AbstractThing *> level);

	/* redraws and updates the game */
	void draw();

	/* for loading/saving a level at the UI level */
	float getColHeight() { return game->col_h; }
	
	/* for loading/saving a level at the UI level */
	float getRowWidth() { return game->row_w; }

private:

// Attributes
private:
	int level;
	float height;
	Game *game;
	FuelGage *fuel_gage;
	JetpackUI *m_UI;
	Fl_BMP_Image *img;
};

#endif // MAESTRO_H_