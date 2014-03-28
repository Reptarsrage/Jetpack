/* Justin Robb
 * 3-27-14
 * JetPack
 * File to be in charge of all the sprite resources
*/

#ifndef SPRITES_H_
#define SPRITES_H_

#include "GL/glew.h"
#include "SOIL.h"
#include <iostream>
#include <string>

/* Managaes all Sprites */
class Sprites {
public:
	Sprites();
	~Sprites();

	/* Returns opengl code for the specified bite. 
	 * This code can be used in bindTexture.
	 */
	GLuint getSprite(int code) const;

	/* loads all sprites into the program */
	int Load(const char * directory);

private:
	GLuint *linktex;									// Container for all the sprites
	void loadSprite(const char *image_name, int index);	// Loads one sprite from an image file into the program
	bool loaded;										// To avoid repeat loading
};

#endif //  SPRITES_H_