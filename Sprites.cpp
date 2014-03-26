
#include "Sprites.h"
#include "Enums.h"

Sprites::Sprites() {
	linktex = new GLuint[SPRITE_COUNT];
	loaded = false;
}

Sprites::~Sprites() {
	delete[] linktex;
}

GLuint Sprites::getSprite(int code) const {
	return linktex[code];	
}

int Sprites::Load(char * directory) {
	if (loaded)
		return 1;
	for (int i = 0; i < SPRITE_COUNT; i++){
		std::string name = std::string(directory);
		name += SpriteNames[i];
		loadSprite(name.c_str(), i);
	}
	loaded = true;
	return 0;
}

void Sprites::loadSprite(const char *image_name, int index) {
	// Enable the texture rectangle extension
	glEnable( GL_TEXTURE_RECTANGLE_NV );


	// Generate one texture ID
	glGenTextures( 1, &linktex[index] );

	// Bind the texture using GL_TEXTURE_RECTANGLE_NV
	glBindTexture( GL_TEXTURE_RECTANGLE_NV, linktex[index] );

	// Enable bilinear filtering on this texture
	glTexParameteri( GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MAG_FILTER, GL_LINEAR );


	// load texture image
	int width, height;
	unsigned char* image =
	SOIL_load_image(image_name, &width, &height, 0, SOIL_LOAD_RGBA);

	// Write the 32-bit RGBA texture buffer to video memory
	glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA, width, height, 0, GL_RGBA,
				  GL_UNSIGNED_BYTE, image);
}