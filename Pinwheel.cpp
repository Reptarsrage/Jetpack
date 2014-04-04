#include "Pinwheel.h"
#include "Enums.h"

const int DEFAULT_SPRITE = SPRITE_PINWHEEL1;
const float SPEED = 2.f;
const float EPSILON = 0.1f;

Pinwheel::Pinwheel(float x, float y, float w, float h, const Sprites *s){
	const Rectangle r = Rectangle(x, y, w, h);
	Init(r, s);
}

Pinwheel::Pinwheel(const Rectangle r, const Sprites *s) {
	Init(r, s);
}

void Pinwheel::Init(const Rectangle r, const Sprites *s) {
	assert(s);
	bounds = new Rectangle(r.position_x, r.position_y, r.width, r.height);
	name = "Pinwheel";
	sprites = s;
	float dir_angle = fmod(m_randf(), 2*PI);
	velocity_x = cosf(dir_angle);
	velocity_y = sinf(dir_angle);
	printf("Initial Pinwheel angle = %g\n", dir_angle);
	on_ladder = on_ground = hit_wall_bottom = hit_wall_left = hit_wall_right = hit_wall_top = false;
	hero_x = hero_y = 0;
	type = TYPE_PINWHEEL;
}

Pinwheel::~Pinwheel(){
	delete bounds;
}

float Pinwheel::applyGravity(float force_gravity, float max_velocity_grav) {
	return 0;
}

const char *Pinwheel::ToString() const{
	return name;
}

void Pinwheel::randomize_dir() {
	float sign_x = velocity_x / fabs(velocity_x);
	float sign_y = velocity_y / fabs(velocity_y);
	float velocity_x_old = velocity_x;
	float velocity_y_old = velocity_y;
	float angle = atanf(velocity_y / velocity_x);
	if (m_rand() % 3 == 0)
		angle += EPSILON;
	else
		angle -= EPSILON;
	velocity_x = sign_x * fabs(cosf(angle));
	velocity_y = sign_y * fabs(sinf(angle));
}

void Pinwheel::calculate_dir(float norm_x, float norm_y) {
	/*If you can get the normal of the surface where you're bouncing off of it 
	you can do a dot product with the velocity vector the projectile will have when it hits.
	Divide the dot product by the magnitude of the velocity, then double it and scale the 
	surface normal by that number and subtract the resulting vector from your velocity.*/
	
	float dot_prod = norm_x * velocity_x + norm_y* velocity_y;
	float res = dot_prod;
	float norm_res_x = (2.f * res) * norm_x;
	float norm_res_y = (2.f * res) * norm_y;
	velocity_x -= norm_res_x;
	velocity_y -= norm_res_y;
	randomize_dir();
}


float Pinwheel::getIntendedY() {
	if (hit_wall_top && hit_wall_bottom){
		hit_wall_top = hit_wall_bottom = false;
		return 0;
	}
	float norm_y = 0.f;
	if (hit_wall_bottom) {
		norm_y = -1.f;
		hit_wall_bottom = false;
		calculate_dir(0.f, norm_y);
	} else if (hit_wall_top) {
		norm_y = 1.f;
		hit_wall_top = false;
		calculate_dir(0.f, norm_y);
	} 
	return SPEED * velocity_y;
}

float Pinwheel::getIntendedX() {
	if (hit_wall_left && hit_wall_right) {
		hit_wall_left = hit_wall_right = false;
		return 0;
	}
	
	float norm_x = 0.f;
	if (hit_wall_left) {
		norm_x = 1.f;
		hit_wall_left = false;
		calculate_dir(norm_x, 0.f);
	} else if (hit_wall_right) {
		norm_x = -1.f;
		hit_wall_right = false;
		calculate_dir(norm_x, 0.f);
	} 
	
	return SPEED * velocity_x;
}

void Pinwheel::draw(){
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, sprites->getSprite(DEFAULT_SPRITE));
		glTranslatef(bounds->left(), bounds->bottom(), 0);
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
