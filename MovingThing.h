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
	virtual void move(float x, float y) { 
		bounds->position_x += x;  
		bounds->position_y += y;
		draw_bounds->position_x += x;  
		draw_bounds->position_y += y;
	}

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
		draw_bounds->draw();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	/* Sets the bounds for this thing.  Adjusts for size. Use SetActualBounds in order to dodge this adjustment */
	virtual void SetBounds(float x, float y, float width, float height) {
		if (bounds) 
			delete bounds; 
		if (draw_bounds)
			delete draw_bounds;

		adjustToBounds(x, y, width, height);
	}

protected:

	/* adjusts the bounds to match ratios and center thing */
	virtual void adjustToBounds(float x, float y, float width, float height) {
		float margin_l = (width - (width_ratio * width)) / 2.f;
		float margin_t = (height - (height_ratio * height)) / 2.f;
		bounds = new Rectangle(margin_l + x, y - margin_t, width_ratio * width, height_ratio * height);
		
		margin_l = (width - (d_width_ratio * width)) / 2.f;
		margin_t = (height - (d_height_ratio * height)) / 2.f;
		draw_bounds = new Rectangle(margin_l + x, y - margin_t, d_width_ratio * width, d_height_ratio * height);
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
	float width_ratio, height_ratio;	// ratios of bounds to world squares
	float d_width_ratio, d_height_ratio;// ratios of drawing bounds to world squares
	Rectangle *draw_bounds;				// bounds to use for drawing sprite
	bool on_ground,						// Baddies must know a little about their state to hunt the hero
		 on_ladder;
};


#endif // MOVING_THING_H_