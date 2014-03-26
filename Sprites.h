// File to be in charge of all the sprite resources

#ifndef SPRITES_H_
#define SPRITES_H_

#include "GL/glew.h"
#include "SOIL.h"
#include <iostream>
#include <string>

class Sprites {
public:
	Sprites();
	~Sprites();
	GLuint getSprite(int code) const;
	int Load(char * directory);

private:
	GLuint *linktex;
	void Sprites::loadSprite(const char *image_name, int index);
	bool loaded;
};


#endif //  SPRITES_H_