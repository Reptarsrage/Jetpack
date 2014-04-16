/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "Teleporter.h"
#include "Enums.h"

Teleporter::Teleporter(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Teleporter::Teleporter(const Rectangle r, const Sprites *s){
	Init(r, s);
}

void Teleporter::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	draw_bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Teleporter";
	sprites = s;
	type = TYPE_PURPLETELEPORTER;
	def_sprite = SPRITE_PURPLETELEPORTER;
	is_solid = true;
	is_collectable = false;
	attribute = -1;
	gen_type = SOLID;
}

Teleporter::~Teleporter(){
	delete bounds;
	delete draw_bounds;
}

void Teleporter::bindTeleporter(int code) {
	assert(code >= 0);
	assert(code < TELE_COUNT);
	if (code == TELE_GREEN) {
		type = TYPE_GREENTELEPORTER;
		def_sprite = SPRITE_GREENTELEPORTER;
	} else if (code == TELE_PURPLE) {
		type = TYPE_PURPLETELEPORTER;
		def_sprite = SPRITE_PURPLETELEPORTER;
	} else if (code == TELE_YELLOW) {
		type = TYPE_YELLOWTELEPORTER;
		def_sprite = SPRITE_YELLOWTELEPORTER;
	}
}

void Teleporter::draw() {
	glBindTexture(GL_TEXTURE_2D, sprites->getSprite(def_sprite));
	draw_bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Teleporter::SetBounds(float x, float y, float width, float height){
	if (bounds) 
		delete bounds; 
	if(draw_bounds)
		delete draw_bounds;
	bounds = new Rectangle(x, y , width, height * 0.1f);
	draw_bounds = new Rectangle(x, y, width, height);
}