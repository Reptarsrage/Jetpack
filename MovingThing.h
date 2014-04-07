/* Justin Robb
 * 3-27-14
 * JetPack
 * A moving thing
*/

#ifndef MOVING_THING_H_
#define MOVING_THING_H_

#include "AbstractThing.h"

/*
 * Base (abstract) class for all things moving in the game, i.e. baddies.
 */
class MovingThing : public AbstractThing{

// Functions
public:
	
	/* Moves this thing by x and y */
	virtual void move(float x, float y) { bounds->position_x += x;  bounds->position_y += y;}

	/* Gets the intended y-dir change */
	/* Expects updateHeroLocation to be called beforehand */
	virtual float getIntendedY() = 0;

	/* Gets the intended x-dir change */
	/* Expects updateHeroLocation to be called beforehand */
	virtual float getIntendedX() = 0;

	/* Attempts to apply gravity to the object, returns the value dropped due to gravity */
	virtual float applyGravity(float force_gravity, float max_velocity_grav) = 0;

	/* Updates the location of the hero on the map, used for hunting purposes */
	virtual void updateHeroLoc(float x, float y) { hero_x = x; hero_y = y; }

	/*  Sets whether this moving thing is on a solid surface */
	virtual void Grounded(bool b) { on_ground = b; }

	/*  Sets whether this moving thing can climb a ladder */
	virtual void OnLadder(bool b, float ladder_x, float ladder_y) { on_ladder = b; }

	/* draws this thing */
	virtual void draw() {
		glBindTexture(GL_TEXTURE_2D, sprites->getSprite(def_sprite));
		bounds->draw();
		glBindTexture(GL_TEXTURE_2D, 0);
	}

// Attributes
public:
	bool hit_wall_top,		// Baddies must know a little about their environment to hunt the hero
		  hit_wall_bottom,
		  hit_wall_left,
		  hit_wall_right;
	
	float hero_x,			// hero's position in the game (not relative to this)
		  hero_y;

protected:
	bool on_ground,	// Baddies must know a little about their state to hunt the hero
		 on_ladder;
};


#endif // MOVING_THING_H_