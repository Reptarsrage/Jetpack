/* Justin Robb
 * 3-30-14
 * JetPack
 * The editing window
*/

#ifndef FuelGage_H
#define FuelGage_H

#include "OpenGl2DWindow.h"
#include <stdlib.h>
#include <vector>
#include <list>

#ifdef __APPLE__
#include "OpenGL/glew.h"
#else
#include "GL/glew.h"
#endif

class Rectangle;
class JetpackUI;

/* Controls the animation and drawing */
class FuelGage : public OpenGl2DWindow
{
// Functions
public:
	FuelGage(float x, float y, float w, float h, const char* l);
	~FuelGage();
	
	/* Draws all the things */
	void draw();

// Attributes
public:
	float game_fuel;

private:
	Rectangle *bounds;							// Current bounds
};

#endif // FuelGage_H