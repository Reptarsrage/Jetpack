#include "Maestro.h"
#include "jetpackUI.h"
#include "Rectangle.h"
#include "Enums.h"
#include <string>
#include <sstream> 

const float MENU_HEIGHT = 50.f;
const float MARGIN_BOTTOM = 0.f;
const float MARGIN_LEFT = 0.f;
const float MARGIN_RIGHT = 0.f;
const float FUEL_WIDTH = .5f;

Maestro::Maestro(float			x, 
					 float			y, 
					 float			w, 
					 float			h,
					 JetpackUI *ui, 
					 const char*	l) : Fl_Group(x,y,w,h,l) {
	// Dimensions
	float width = (w - (MARGIN_LEFT + MARGIN_RIGHT) ) * FUEL_WIDTH;
	fuel_gage = new FuelGage(MARGIN_LEFT, y + h - MARGIN_BOTTOM - MENU_HEIGHT, width, MENU_HEIGHT, "Fuel");
	fuel_gage->m_UI = ui;	 
	game = new Game(x, y, w, h - MENU_HEIGHT - MARGIN_BOTTOM, l);
	m_UI = ui;
	game->m_UI = ui;
	height = h;
	img = NULL;
	img = new Fl_BMP_Image("Resources/background.bmp");
	assert(img);
}

Maestro::~Maestro() {
	delete game;
	delete fuel_gage;
	delete img;
}

void Maestro::loadLevel(std::list<AbstractThing *> level) {
	game->loadLevel(level);
}

void Maestro::draw() {
	std::stringstream ss;
	ss << "Score: ";
	ss << game->score;
	std::string str = ss.str();
	
	fuel_gage->game_fuel = game->fuel_percentage;
	fuel_gage->redraw();
	game->redraw();
	fl_color(FL_RED);
	fl_font(FL_COURIER_BOLD, 26);
	img->draw(x() + fuel_gage->w() + (MARGIN_LEFT + MARGIN_RIGHT), y() + height - MARGIN_BOTTOM - MENU_HEIGHT, fuel_gage->w(), fuel_gage->h());
	fl_draw(	str.c_str(), 
				x() + fuel_gage->w() + (MARGIN_LEFT + MARGIN_RIGHT) + 40, 
				y() + height - MARGIN_BOTTOM - MENU_HEIGHT, 
				fuel_gage->w(), 
				fuel_gage->h() / 2.f, 
				FL_ALIGN_LEFT_TOP);
}