#include "Robot.h"
#include "Enums.h"

const int DEFAULT_SPRITE = SPRITE_ROBOLEFT1;
const float SPEED = 1.8f;
const float EPSILON = 1.f;

Robot::Robot(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Robot::Robot(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Robot::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Robot";
	sprites = s;
	velocity_x = SPEED;
	velocity_y = 0;
	on_ground = on_ladder = hit_wall_bottom = hit_wall_left = hit_wall_right = hit_wall_top = false;
	hero_x = hero_y = 0;
	type = ROBOT_TYPE;
}

Robot::~Robot(){
	delete bounds;
}

void Robot::SetDir() {
	if (hero_x > bounds->position_x)
		velocity_x = SPEED;
	else
		velocity_x = -SPEED;
}

void Robot::move(float x, float y) {
	if (on_ground)
		bounds->position_x += x;
	bounds->position_y += y;
}

void Robot::Grounded(bool b) {
	if (on_ladder)
		// not applicable when on a ladder
		return;
	
	if (on_ground && !b) {
		// Just left solid ground
		velocity_y = 0;
	}

	if (!on_ground && b) {
		// touched down on solid ground
		SetDir();
	}

	on_ground = b;
}

void Robot::OnLadder(bool b, float ladder_x, float ladder_y) {
	if (on_ladder && b ) {
		// already on a ladder
		return;
	}
	if (!on_ladder && !b){ 
		// already not on a ladder
		return;
	}

	if (on_ladder && !b) {
		// no longer on a ladder!
		velocity_y = 0;
		on_ladder = false;
		SetDir();
	}

	if (!on_ladder && b) {
		// should we climb?
		if (hero_y > bounds->position_y + EPSILON) {
			// climb down
			bounds->position_x = ladder_x;
			bounds->position_y = ladder_y + EPSILON;
			velocity_y = SPEED;
			velocity_x = 0;
			on_ladder = true;
			hit_wall_top = false;
			hit_wall_bottom = false;
		} else if (hero_y < bounds->position_y - EPSILON){
			// climb up
			bounds->position_x = ladder_x;
			bounds->position_y = ladder_y - EPSILON;
			velocity_y = -SPEED;
			velocity_x = 0;
			on_ladder = true;
			hit_wall_top = false;
			hit_wall_bottom = false;
		}
	}
}

float Robot::applyGravity(float force_gravity, float max_velocity_grav) {
	if (on_ladder)
		// no gravity on a ladder
		return 0;
	
	if (!on_ground)
		// only apply gravity when falling
		velocity_y += force_gravity;
	else
		// apply a little bit while on ground to stay on ground, and register being on ground
		velocity_y = 1.f;
	
	if (velocity_y > max_velocity_grav)
		// bound falling speed
		velocity_y = max_velocity_grav;

	return velocity_y;
}

const char *Robot::ToString() const{
	return name;
}

float Robot::getIntendedY() {
	if (hit_wall_top && on_ladder) {
		// We've reached the top of the ladder, move sideways
		velocity_y = 0;
		SetDir();
	} 
	hit_wall_top = false;

	if (hit_wall_bottom && on_ladder) {
		// We've reached the bottom of the ladder, move sideways
		velocity_y = 0;
		SetDir();
	} 
	hit_wall_bottom = false;
	
	return velocity_y;
}

float Robot::getIntendedX() {
	if (!on_ground) {
		// falling? can't move at all
		return 0;
	}

	if (hit_wall_left) {
		// hit a wall to the left, switch directions
		hit_wall_left = false;
		velocity_x *= -1;
	}

	if (hit_wall_right) {
		// hit a wall to the left, switch directions
		hit_wall_right = false;
		velocity_x *= -1;
	}
	return velocity_x;
}

void Robot::draw(){
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);//sprites->getSprite(DEFAULT_SPRITE));
		glTranslatef(bounds->left(), bounds->bottom(), 0);
		glColor3f(1,0,0);
		glBegin(GL_QUADS);
			glTexCoord2f( 0, 0 );                           
			glVertex2f( 0, 0 );
			glTexCoord2f( 1, 0 );     
			glVertex2f( bounds->width, 0 );
			glTexCoord2f( 1, 1);    
			glVertex2f( bounds->width, bounds->height );
			glTexCoord2f( 0, 1 );          
			glVertex2f( 0, bounds->height );
		glEnd();
	glPopMatrix();
}
