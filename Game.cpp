/* Justin Robb
 * 3-27-14
 * JetPack
*/
#include "JetpackUI.h"
#include "Game.h"
#include "Sprites.h"
#include "Enums.h"
#include "MovingThing.h"
#include "StationaryThing.h"
#include "SolidThing.h"
#include "NonSolidThing.h"
#include "Gem.h"
#include "Ladder.h"
#include "Hero.h"
#include "Pinwheel.h"
#include "Door.h"
#include "Bat.h"
#include "Predator.h"
#include "Spring.h"
#include "Egg.h"
#include "Robot.h"
#include "SwitchSolid.h"
#include "Teleporter.h"


const int NUM_ROWS = 16;
const int NUM_COLS = 26;
const float MAX_VELOCITY = 0.12f;
const float MAX_VELOCITY_GRAV = 0.2f;
const float FORCE_GRAVITY = 0.012f;
const float JETPACK_THRUST = 0.028f;
const float JUMP_RESTITUTION = 0.33f;
const float MARGIN = 8.f;
const float MARGIN_TOP = 5.f;
const float MARGIN_BOTTOM = 5.f;
const float MARGIN_LEFT = 5.f;
const float MARGIN_RIGHT = 5.f;
const float LADDER_V_FACTOR = 1.f / 3.f;
const float ICE_FORCE_FACTOR = .06f;
const float CONVEYOR_V_FACTOR = .333f;
const float MOSS_DELAY = 0.5f;
const float FUEL_CONSMPT_RATE = 0.0005f;
const int INCINCIBILITY_LENGTH = 500;
const int FROZEN_LENGTH = 500;

Game::Game(float			x, 
					 float			y, 
					 float			w, 
					 float			h, 
					 const char*	l)
						: OpenGl2DWindow(x,y,w,h,l)
{
	// Dimensions
	float width = w - (MARGIN_LEFT + MARGIN_RIGHT);
	float height = h - (MARGIN_BOTTOM + MARGIN_TOP);
	row_w = width / (NUM_COLS * 1.0f);
	col_h = height / (NUM_ROWS * 1.0f);
	bounds = new Rectangle(MARGIN_LEFT, h - MARGIN_BOTTOM, width, height);

	// better bounds
	left = bounds->left();
	top = bounds->bottom();
	bottom = bounds->top();
	right = bounds->right();

	// Controls
	hold_left = hold_right = hold_phase = phasing_in_air = false;
	hold_up = hold_down = hold_jet_pack = false;

	// consts
	max_velocity = col_h * MAX_VELOCITY;
	jump_restitution = col_h * JUMP_RESTITUTION;
	force_gravity = col_h * FORCE_GRAVITY;
	jetpack_thrust = col_h * JETPACK_THRUST;
	max_velocity_grav = col_h * MAX_VELOCITY_GRAV;
	gem_count = 0;
	ladder_velocity = max_velocity * LADDER_V_FACTOR;
	force_ice = ICE_FORCE_FACTOR *max_velocity;
	conveyor_speed = max_velocity * CONVEYOR_V_FACTOR;
	frozen_timer = 0;
	invincible_timer = 0;

	// hero/env
	hero = NULL;
	door = NULL;
	solid_things = new std::vector<SolidThing *>();
	nonsolid_things = new std::vector<StationaryThing *>();
	collectable_things = new std::vector<Collectable *>();
	special_things = new std::vector<StationaryThing *>();
	dyn_things = new std::vector<MovingThing *>();
	alive = true;
	win = false;
	score = 0;
	fuel_percentage = 1;
}

Game::~Game() {
	delete hero;
	delete door;
	solid_things->clear();
	nonsolid_things->clear();
	collectable_things->clear();
	dyn_things->clear();
	special_things->clear();
}

void Game::Clear() {
	delete hero;
	delete door;
	solid_things->clear();
	nonsolid_things->clear();
	collectable_things->clear();
	dyn_things->clear();
	special_things->clear();
	solid_things = new std::vector<SolidThing *>();
	nonsolid_things = new std::vector<StationaryThing *>();
	collectable_things = new std::vector<Collectable *>();
	special_things = new std::vector<StationaryThing *>();
	dyn_things = new std::vector<MovingThing *>();
	gem_count = 0;
	score = 0;
	invincible_timer = 0;
	frozen_timer = 0;
	fuel_percentage = 1;
}

void Game::loadLevel(std::list<AbstractThing *> level) {
	Clear();
	assert(solid_things);
	assert(nonsolid_things);
	assert(collectable_things);
	assert(dyn_things);
	assert(special_things);
	
	if (level.empty())
		return;
	
	for (AbstractThing *thing : level) {
		const Rectangle b = thing->Bounds();
		thing->SetBounds(bounds->left() + b.position_x * row_w, bounds->bottom() + col_h + b.position_y*col_h, row_w, col_h);
		switch (thing->getType()){
			case TYPE_IVY:
			case TYPE_PILLAR:
			case TYPE_GOLDSWITCH:
			case TYPE_REDSWITCH:
			case TYPE_BLUESWITCH:
				nonsolid_things->push_back(reinterpret_cast<NonSolidThing *>(thing));
				break;
			case TYPE_BRICKSOLID:
			case TYPE_BRICKSOLID_ICY:
			case TYPE_BRICKSOLID_MOSSY:
			case TYPE_BRICKSOLID_CONVEYOR_L:
			case TYPE_BRICKSOLID_CONVEYOR_R:
			case TYPE_SHIELDED_BRICK_D:
			case TYPE_SHIELDED_BRICK_U:
			case TYPE_SHIELDED_BRICK_L:
			case TYPE_SHIELDED_BRICK_R:
			case TYPE_WOODSOLID:
			case TYPE_WOODSOLID_ICY:
			case TYPE_WOODSOLID_MOSSY:
			case TYPE_WOODSOLID_CONVEYOR_L:
			case TYPE_WOODSOLID_CONVEYOR_R:
			case TYPE_SHIELDED_WOOD_D:
			case TYPE_SHIELDED_WOOD_U:
			case TYPE_SHIELDED_WOOD_L:
			case TYPE_SHIELDED_WOOD_R:
			case TYPE_STONESOLID:
			case TYPE_STONESOLID_ICY:
			case TYPE_STONESOLID_MOSSY:
			case TYPE_STONESOLID_CONVEYOR_L:
			case TYPE_STONESOLID_CONVEYOR_R:
			case TYPE_GOLDSWITCHSOLID:
			case TYPE_FASTSOLID:
			case TYPE_BLUESWITCHSOLID:
			case TYPE_BOX:
			case TYPE_HBLUESWITCHSOLID:
			case TYPE_HGOLDSWITCHSOLID:
			case TYPE_HREDSWITCHSOLID:
			case TYPE_REDSWITCHSOLID:
			case TYPE_GREENTELEPORTER:
			case TYPE_YELLOWTELEPORTER:
			case TYPE_PURPLETELEPORTER:
				solid_things->push_back(reinterpret_cast<SolidThing *>(thing));
				break;
			case TYPE_SPRING:
			case TYPE_EGG:
			case TYPE_BAT:
			case TYPE_MINE:
			case TYPE_HUNTER:
			case TYPE_MISSILE:
			case TYPE_PINWHEEL:
			case TYPE_ROBOT:
			case TYPE_DEATHDOWN:
			case TYPE_DEATHLEFT:
			case TYPE_DEATHRIGHT:
			case TYPE_DEATHUP:
				dyn_things->push_back(reinterpret_cast<MovingThing *>(thing));
				break;
			case TYPE_GEM:
				gem_count++;
			case TYPE_FULLFUEL:
			case TYPE_GOLD1:
			case TYPE_GOLD2:
			case TYPE_GOLD3:
			case TYPE_GOLD4:
			case TYPE_HALFFUEL:
			case TYPE_INVINCIBILITY:
			case TYPE_TIMER:
				collectable_things->push_back(reinterpret_cast<Collectable *>(thing));
				break;
			case TYPE_LADDER:
			case TYPE_LADDERUP:
			case TYPE_LADDERDOWN:
				special_things->push_back(reinterpret_cast<Ladder *>(thing));
				break;
			case TYPE_DOOR:
				door = reinterpret_cast<Door *>(thing);
				break;
			case TYPE_HERO:
				hero = reinterpret_cast<Hero *>(thing);
				break;
			default:
				printf("UNIDENTIFIED THING! CODE:%d\n", thing->getType());
				break;
		}
	}
}

bool Game::heroGetSwag() {
	for (Collectable *s : *collectable_things){
		if (!s->Collected() && s->Overlaps(hero)){
			switch(s->getType()) {
			case TYPE_GEM:
				gem_count--;
				break;
			case TYPE_TIMER:
				frozen_timer = FROZEN_LENGTH;
				break;
			case TYPE_INVINCIBILITY:
				invincible_timer = INCINCIBILITY_LENGTH;
				break;
			case TYPE_FULLFUEL:
				fuel_percentage = 1;
				break;
			case TYPE_HALFFUEL:
				fuel_percentage = std::min(fuel_percentage + .5f, 1.f);
				break;
			default:
				printf("Unkown collected item!");
				break;
			}
			score += s->Collect();
			return true;
		}
	}
	return false;
}

void Game::drawBackGround() {
	assert(solid_things);
	assert(nonsolid_things);
	assert(collectable_things);
	assert(special_things);
	
	// Draw Backdrop
	glBindTexture(GL_TEXTURE_2D, m_UI->sprites->getSprite(SPRITE_BACKGROUND));
	bounds->draw();
	glBindTexture(GL_TEXTURE_2D, 0);
	
	for (StationaryThing *s : *solid_things) {
		s->draw();
	}

	for (StationaryThing *s : *collectable_things) {
		s->draw();
	}

	for (StationaryThing *s : *special_things) {
		s->draw();
	}
	
	drawMovingThings();

	door->draw();
	drawHero();
	for (StationaryThing *s : *nonsolid_things) {
		s->draw();
	}
}

void Game::drawMovingThings() {
	assert(dyn_things);
	for (MovingThing *baddie : *dyn_things){
		baddie->draw();
	}
}

void Game::drawHero() {
	assert(hero);
	hero->draw();
}

void Game::moveThings() {
	assert(dyn_things);
	for (MovingThing *baddie : *dyn_things){
		if (invincible_timer == 0 && baddie->Overlaps(hero)) {
			// HERO DIES
			alive = false;
		}
		
		const Rectangle r = hero->Bounds();
		baddie->updateHeroLoc(r.left(), r.top());
		
		// If we have a robot, check if it's on a ladder
		if (baddie->getType() == TYPE_ROBOT) {
			const Rectangle bb = baddie->Bounds();
			const Rectangle bbd = Rectangle(bb.position_x, bb.position_y + max_velocity, bb.width, bb.height);
			bool on_ladder = false;
			float x = 0;
			float y = 0;
			for (StationaryThing *s : *special_things) {
				if ((s->getType() == TYPE_LADDER || s->getType() == TYPE_LADDERUP || s->getType() == TYPE_LADDERDOWN) && 
					(s->Overlaps(baddie) || s->Overlaps(bbd))) {
					// touching a ladder! (or at least on top of one)
					const Rectangle sb = s->Bounds();
					x = sb.position_x;
					y = sb.position_y;
					on_ladder = true;
					break;
				}
			}
			baddie->OnLadder(on_ladder, x, y);
		}
		baddie->applyGravity(force_gravity, max_velocity_grav);
		advancePosition(baddie, baddie->getIntendedX(), baddie->getIntendedY());
	}
}

void Game::heroPhase(int dir) {
	if (dir < 0)
		return;

	const Rectangle h = hero->Bounds();
	const Rectangle vertical = Rectangle(h.position_x + h.width / 2.f, h.position_y, h.width / 20.f, h.height);
	const Rectangle horizontal = Rectangle(h.position_x, h.position_y - h.height / 2.f, h.width, h.height / 20.f);
	Rectangle r;
	if (dir == UP) {
		r = Rectangle(vertical.position_x, vertical.position_y - max_velocity, vertical.width, vertical.height);
	} else if (dir == DOWN) {
		r = Rectangle(vertical.position_x, vertical.position_y + max_velocity, vertical.width, vertical.height);
	} else if (dir == LEFT) {
		r = Rectangle(horizontal.position_x - max_velocity, horizontal.position_y, horizontal.width, horizontal.height);
	} else if (dir == RIGHT) {
		r = Rectangle(horizontal.position_x + max_velocity, horizontal.position_y, horizontal.width, horizontal.height);
	} else {
		assert("Unrecognized phase direction!" == "Error");
	}
	for (SolidThing *s : *solid_things) {
		if (s->is_solid && s->phaseable(dir) && s->Overlaps(r)) {
			// phase this block
			const Rectangle sb = s->Bounds();
			float x,y;
			x = y= 0;
			s->phase();
			if (dir == LEFT || dir == RIGHT){
				y = ((sb.position_y + (col_h - h.height) / 2.f)  - h.position_y) / 10.f;
				if (hold_jet_pack && !hero->on_ground)
					phasing_in_air = true;
			} else {
				x = ((sb.position_x + (row_w - h.width) / 2.f) - h.position_x) / 10.f;
			}
			hero->SetActualBounds(h.position_x + x, h.position_y + y, h.width, h.height);
			break;
		}
	}

}


void Game::moveHero() {
	assert(hero);
	
	// do things based on surroundings
	if (gem_count == 0)
		door->Open();
	
	if (door->IsOpen() && door->Overlaps(hero)){
		// TODO: WIN
		win = true;
	}
	
	// Phaser
	phasing_in_air = false;
	int dir = -1;
	if (hold_phase) {
		if (!Fl::event_key('x'))
			hold_phase = false;
		else if (hold_left) {
			dir = LEFT;
			heroPhase(LEFT);
		} else if (hold_right) {
			dir = RIGHT;
		} else if (hold_up) {
			dir = UP;
		} else if (hold_down) {
			dir = DOWN;
		} else {
			dir = UP;
		}
		heroPhase(dir);
	}
	hero->phase(dir);
	
	// collect things
	heroGetSwag();

	// move in x-dir
	if (hold_left && !Fl::event_key(FL_Left))
		hold_left = false;
	if (hold_right && !Fl::event_key(FL_Right))
		hold_right = false;
		
	if (hero->ground_type != ICY) {
		if (hold_left) {
			hero->velocity_x = - max_velocity;
		} else if (hold_right) {
			hero->velocity_x = max_velocity;
		} else
			hero->velocity_x = 0;
	}

	// move in y-dir
	const Rectangle h = hero->Bounds();
	if (hold_up && !Fl::event_key(FL_Up)) {
		hold_up = false;
	} else if (hold_up && hero->on_ladder) {
		hero->velocity_y = -max_velocity;
		if (hero->velocity_x == 0)
			hero->velocity_x = ((hero->ladder_left + (row_w - h.width) / 2.f) - h.position_x) / 10.f;
	} else if (hold_jet_pack && !Fl::event_key('z')) {
		hold_jet_pack = false;
	} else if (hold_jet_pack && !phasing_in_air && fuel_percentage > 0) {
		hero->on_ground = false;
		hero->force_y = - jetpack_thrust;
		fuel_percentage -= FUEL_CONSMPT_RATE;
	} else if (hold_jet_pack && phasing_in_air && fuel_percentage > 0) {
		hero->velocity_y = 0;
		hero->force_y = 0;
		fuel_percentage -= FUEL_CONSMPT_RATE;
	} else if (hold_down && !Fl::event_key(FL_Down)) 
		hold_down = false;
	else if (hold_down && hero->on_ladder) {
		hero->velocity_y = max_velocity;
		if (hero->velocity_x == 0)
			hero->velocity_x = ((hero->ladder_left + (row_w - h.width) / 2.f) - h.position_x) / 10.f;
	} else if (hero->on_ladder)
		hero->velocity_y = 0;
	else
		hero->force_y = 0.0;

	// climbing
	if (hero->on_ladder && hero->ladder_dir == UP)
		hero->velocity_y -= ladder_velocity;
	else if (hero->on_ladder && hero->ladder_dir == DOWN)
		hero->velocity_y += ladder_velocity;

	// ground attributes
	hero->force_x = 0;
	if (hero->on_ground){
		if (hero->ground_type == ICY && hold_left) {
			hero->force_x = -force_ice;
		} else if (hero->ground_type == ICY && hold_right) {
			hero->force_x = force_ice;
		} else if (hero->ground_type == MOSSY){
			hero->velocity_x *= MOSS_DELAY;
		} else if (hero->ground_type == CONVEYOR_LEFT) {
			hero->velocity_x -= conveyor_speed;
		} else if (hero->ground_type == CONVEYOR_RIGHT) {
			hero->velocity_x += conveyor_speed;
		}
	}
	// apply forces
	if (!phasing_in_air)
		hero->applyGravity(force_gravity);
	
	// update hero's sprite
	if (!hero->on_ladder && !hold_phase && invincible_timer == 0) {
		if (hero->velocity_jump > 0 && !hold_jet_pack)
			hero->setSprite(SPRITE_JUMPING);
		else if (hold_left && hold_jet_pack)
			hero->setSprite(SPRITE_LEFTJET);
		else if (hold_right && hold_jet_pack)
			hero->setSprite(SPRITE_RIGHTJET);
		else if (hold_left)
			hero->step(LEFT);
		else if (hold_right)
			hero->step(RIGHT);
		else 
			hero->setSprite(SPRITE_FRONT);
	} else if (invincible_timer > 0)
		hero->setSprite(SPRITE_INVINCIBILITY);

	// Check limits
	if (hero->on_ladder) {
		hero->velocity_jump = 0;
	}

	if (fuel_percentage < 0)
		fuel_percentage = 0;

	if (hero->velocity_jump < 0.0)
		hero->velocity_jump = 0.0;

	if (hero->velocity_x > max_velocity) 
		hero->velocity_x = max_velocity;
	else if (-hero->velocity_x > max_velocity)
		hero->velocity_x = - max_velocity;
	
	if (hero->velocity_y > max_velocity_grav) 
		hero->velocity_y = max_velocity_grav;
	else if (-hero->velocity_y > max_velocity)
		hero->velocity_y = - max_velocity;

	// set positions
	advanceHeroPosition(hero->velocity_x, hero->velocity_y - hero->velocity_jump);
}

void Game::advanceHeroPosition(float delta_x, float delta_y) const {
	assert(hero);

	// check world bounds
	const Rectangle hero_bounds = hero->Bounds();
	const Rectangle new_hero_bounds_y = Rectangle(hero_bounds.position_x,
		hero_bounds.position_y + delta_y, hero_bounds.width, hero_bounds.height);
	const Rectangle new_hero_bounds_x = Rectangle(hero_bounds.position_x + delta_x,
		hero_bounds.position_y, hero_bounds.width, hero_bounds.height);

	// in the x direction
	if (new_hero_bounds_x.right() > right)
		// hit right side
		delta_x = right - hero_bounds.right();
	else if (new_hero_bounds_x.left()  < left) 
		// hit left side
		delta_x = left - hero_bounds.left();

	// and in the y direction
	if (new_hero_bounds_y.top() > bottom) {
		// hit ground
		delta_y = bottom - hero_bounds.top();
		hero->on_ground = true;
	}
	else if (new_hero_bounds_y.bottom() < top)
		// hit ceiling
		delta_y =  top - hero_bounds.bottom();

	// handle ladders
	// stop on top of ladders, treat ladder tops as ground
	bool body_ladder, above_ladder;
	body_ladder = above_ladder = false;
	int ladder_att = -1;
	Rectangle s_bounds;
	const Rectangle vertical = Rectangle(hero_bounds.position_x + hero_bounds.width / 2.f, 
										 hero_bounds.position_y, 
										 hero_bounds.width / 20.f, 
										 hero_bounds.height);
	const Rectangle vertical_y = Rectangle(hero_bounds.position_x + hero_bounds.width / 2.f, 
										 hero_bounds.position_y + max_velocity, 
										 hero_bounds.width / 20.f, 
										 hero_bounds.height);
	for (StationaryThing *s : *special_things){
		if (s->getType() == TYPE_LADDER || s->getType() == TYPE_LADDERUP || s->getType() == TYPE_LADDERDOWN) {
			if (s->Overlaps(vertical_y)) {
				s_bounds = s->Bounds();
				above_ladder = true;
				ladder_att = reinterpret_cast<Ladder *>(s)->direction;
			}
			if (s->Overlaps(vertical)){
				s_bounds = s->Bounds();
				body_ladder = true;
				hero->ladder_left = s_bounds.left();
				ladder_att = reinterpret_cast<Ladder *>(s)->direction;
			}
		}
	}
	if (!body_ladder && above_ladder && hold_down) {
		hero->on_ladder = true;
		hero->ladder_dir = ladder_att;
		delta_y = max_velocity;
	} else if (!body_ladder && above_ladder && delta_y >= 0) {
		delta_y = s_bounds.bottom() - hero_bounds.top();
		hero->on_ground = true;
		hero->ground_type = -1;
	} else if (body_ladder && (hold_up || hold_down)){
		hero->on_ladder = true;
		hero->ladder_dir = ladder_att;
	}else if (!body_ladder && hero->on_ladder) {
		hero->velocity_y = 0;
		hero->on_ladder = false;
	} else if (hero->on_ladder && body_ladder)
		hero->ladder_dir = ladder_att;

	// check solid objects in x and y directions (if we need to)
	if (delta_x == 0 && delta_y == 0)
		return;

	bool x_conflict, y_conflict;
	x_conflict = y_conflict = false;
	for (SolidThing *s : *solid_things){
		if (s->is_solid && s->Overlaps(new_hero_bounds_x)) {
			const Rectangle s_bounds = s->Bounds();
			if (hero_bounds.right() <= s_bounds.left())
				delta_x = s_bounds.left() - hero_bounds.right();
			else
				delta_x = s_bounds.right() - hero_bounds.left();
			x_conflict = true;
		}
		if (s->is_solid && s->Overlaps(new_hero_bounds_y)) {
			const Rectangle s_bounds = s->Bounds();
			if (hero_bounds.bottom() <= s_bounds.bottom()) {
				delta_y = s_bounds.bottom() - hero_bounds.top();
				hero->on_ground = true;
				hero->ground_type = s->getAttribute();
			} else {
				delta_y =  s_bounds.top() - hero_bounds.bottom();
			}
			y_conflict = true;
		}
	}

	if (x_conflict && y_conflict)
		delta_x = 0;

	if (delta_y != 0) {
		hero->on_ground = false;
		hero->ground_type = -1;
	}
	hero->move(delta_x, delta_y);
}

void Game::advancePosition(MovingThing *thing, float delta_x, float delta_y) const {
	assert(thing);
	
	bool grounded = false;
	// check world bounds
	const Rectangle thing_bounds = thing->Bounds();
	const Rectangle new_thing_bounds_y = Rectangle(thing_bounds.position_x,
		thing_bounds.position_y + delta_y, thing_bounds.width, thing_bounds.height);
	const Rectangle new_thing_bounds_x = Rectangle(thing_bounds.position_x + delta_x,
		thing_bounds.position_y, thing_bounds.width, thing_bounds.height);
	
	// in the x direction
	if (new_thing_bounds_x.right() > right) {
		// hit right side
		delta_x = right - thing_bounds.right();
		thing->hit_wall_right = true;
	} else if (new_thing_bounds_x.left()  < left) {
		// hit left side
		delta_x = left - thing_bounds.left();
		thing->hit_wall_left = true;
	}

	// and in the y direction
	if (new_thing_bounds_y.top() > bottom) {
		// hit ground
		delta_y = bottom - thing_bounds.top();
		thing->hit_wall_bottom = true;
		grounded = true;
	}
	else if (new_thing_bounds_y.bottom() < top) {
		// hit ceiling
		delta_y =  top - thing_bounds.bottom();
		thing->hit_wall_top = true;
	}

	// not moving? good, exit without needing to check all objects
	if (delta_x == 0 && delta_y == 0)
		return;

	// check solid objects in x and y directions (except for predators which don't give no F@$!S)
	if (thing->getType() != TYPE_HUNTER) {
		for (SolidThing *s : *solid_things){
			const Rectangle s_bounds = s->Bounds();
			if (s->is_solid && s->Overlaps(new_thing_bounds_x)) {
				if (thing_bounds.right() <= s_bounds.left()) {
					delta_x = s_bounds.left() - thing_bounds.right();
					thing->hit_wall_right = true;
				} else {
					delta_x = s_bounds.right() - thing_bounds.left();
					thing->hit_wall_left = true;
				}
			}
			if (s->is_solid && s->Overlaps(new_thing_bounds_y)) {
				if (thing_bounds.top() <= s_bounds.bottom()) {
					delta_y = s_bounds.bottom() - thing_bounds.top();
					thing->hit_wall_bottom = true;
					grounded = true;
				} else {
					delta_y =  s_bounds.top() - thing_bounds.bottom();
					thing->hit_wall_top = true;
				}
			}
		}
	}

	thing->Grounded(grounded);
	thing->move(delta_x, delta_y);
}

void Game::draw()
{
	if(!valid())
	{
		valid(1);
		InitScene();
		// Hero
		if (!hero)
			hero = new Hero(bounds->left(), bounds->bottom() + col_h, row_w, col_h, m_UI->sprites);
		
		// Door
		if (!door)
			door = new Door(bounds->left() + 4*row_w, bounds->bottom() + col_h, row_w, col_h, m_UI->sprites);
	}
	assert(invincible_timer >= 0);
	assert(frozen_timer >= 0);

	if (invincible_timer > 0)
		invincible_timer--;

	// move things
	moveHero();
	
	if (frozen_timer == 0)
		moveThings();
	else
		frozen_timer--;

	glEnable2D();
	
	// draw everythingon 
	drawBackGround();

	if (win) {
		glColor4f(1,1,0,.2f);
		bounds->draw();
		win = false;
	}

	if (!alive) {
		glColor4f(1,0,0,.2f);
		bounds->draw();
		alive = true;
	}
	glDisable2D();
}

void Game::handleDownPress() {
	
	if (hero->on_ground) {
		const Rectangle h = hero->Bounds();
		Rectangle b = Rectangle(h.position_x, h.position_y + max_velocity, h.width, h.height);
		// teleporter?
		for (SolidThing *thing : *solid_things) {
			if (thing->Overlaps(b)) {
				int code = thing->getType();
				if (code == TYPE_GREENTELEPORTER) {
					printf("green teleporter activated.\n");
					teleport(reinterpret_cast<Teleporter *>(thing));
					break;
				} else if (code == TYPE_YELLOWTELEPORTER) {
					printf("yellow teleporter activated.\n");
					teleport(reinterpret_cast<Teleporter *>(thing));
					break;
				} else if (code == TYPE_PURPLETELEPORTER) {
					printf("purple teleporter activated.\n");
					teleport(reinterpret_cast<Teleporter *>(thing));
					break;
				}
			}
		}
	}
	for (StationaryThing *thing : *nonsolid_things) {
		if (thing->Overlaps(hero)) {
			// switch?
			int code = thing->getType();
			if (code == TYPE_REDSWITCH) {
				printf("red switch pressed.\n");
				switchSolids(code);
				break;
			} else if (code == TYPE_BLUESWITCH) {
				printf("blue switch pressed.\n");
				switchSolids(code);
				break;
			} else if (code == TYPE_GOLDSWITCH) {
				printf("gold switch pressed.\n");
				switchSolids(code);
				break;
			}
		}
	}
}

void Game::teleport(const Teleporter *src) {
	int ran_tele = m_rand() % solid_things->size();
	while (true){
		for (SolidThing *thing : *solid_things) {
			if (thing->getType() == src->getType() && thing != src) {
				if (ran_tele == 0){
					const Rectangle b = hero->Bounds();
					const Rectangle tb = thing->Bounds();
					hero->SetBounds(tb.position_x, tb.position_y - 0.1f*col_h, b.width, b.height);
					return;
				}
				ran_tele--;
			}
		}
	}
}

void Game::switchSolids(int code) {
	int codeh, codev;
	if (code == TYPE_REDSWITCH) {
		codeh = TYPE_HREDSWITCHSOLID;
		codev = TYPE_REDSWITCHSOLID;
	} else if (code == TYPE_BLUESWITCH) {
		codeh = TYPE_HBLUESWITCHSOLID;
		codev = TYPE_BLUESWITCHSOLID;
	} else if (code == TYPE_GOLDSWITCH) {
		codeh = TYPE_HGOLDSWITCHSOLID;
		codev = TYPE_GOLDSWITCHSOLID;
	}
	for (SolidThing *thing : *solid_things) {
		int type = thing->getType();
		if (type == codeh || type == codev) {
			reinterpret_cast<SwitchSolid *>(thing)->Switch();
		}
	}
}

int Game::handle(int event)
{
	if (Fl_Gl_Window::handle(event) != 0)
		return 1;
	int key = Fl::event_key();
	switch(event) {
		case FL_SHORTCUT:
		case FL_KEYBOARD:
			switch(key) {
				case FL_Left:
					hold_left = true;
					hold_right = false;
					break;
				case FL_Right:
					hold_right= true;
					hold_left = false;
					break;
				case FL_Up:
					hold_up = true;
					hold_down = false;
					break;
				case FL_Down:
					handleDownPress();
					hold_down = true;
					hold_up = false;
					break;
				case 'a':
					m_UI->startAnimating();
					break;
				case 's':
					m_UI->stopAnimating();
					break;
				case 'z':
					hold_jet_pack = true;
					break;
				case 'x':
					hold_phase = true;
					break;
				case ' ':
					hero->Jump(jump_restitution);
					break;
			}
			break;
		case FL_KEYUP:
			switch(key) {
				case FL_Left:
					hold_left = false;
					if (Fl::event_key(FL_Right))
						hold_right = true;
					break;
				case FL_Right:
					hold_right = false;
					if (Fl::event_key(FL_Left))
						hold_left = true;
					break;
				case FL_Up:
					hold_up = false;
					if (Fl::event_key(FL_Down))
						hold_down = true;
					break;
				case FL_Down:
					hold_down = false;
					if (Fl::event_key(FL_Up))
						hold_up = true;
					break;
				case 'z':
					hold_jet_pack = false;
					break;
				case 'x':
					hold_phase = false;
					break;
			}
			break;
		case FL_ENTER:
		case FL_MOVE:
		case FL_FOCUS:
		case FL_UNFOCUS:
			break;
		default:
			return 0;
			break;
		}
	return 1;
}