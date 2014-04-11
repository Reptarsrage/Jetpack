/* Justin Robb
 * 3-27-14
 * JetPack
 * Player controlled hero
*/

#ifndef HERO_H_
#define HERO_H_

#include "AbstractThing.h"

/*
 * Position and properties of the player controlled charcter.
 */
class Hero : public AbstractThing {

// Functions
public:

	~Hero();
	Hero(float x, float y, float w, float h, const Sprites *s);
	Hero(const Rectangle r, const Sprites *s);
	
	/* Constrols whether or not the hero is using his phaser */
	/* Assumes not phasing if given a negative dir */
	void Hero::phase(int dir);

	/* Draws this thing */
	virtual void draw();
	
	/* Moves this thing by one step*/
	virtual void move(float x, float y);

	/* Makes this hero jump */
	virtual void Jump(float restitution);

	/* Attempts to apply gravity to the object, returns the value dropped due to gravity */
	virtual float applyGravity(float delta_y);

	/* Sets the bounds for this thing. */
	virtual void SetBounds(float x, float y, float width, float height);
	
private:
	/* initializes this hero */
	void Init(const Rectangle r, const Sprites *s);

// Attributes
public:
	float velocity_x,		// veloxity in x-dir
		  velocity_y,		// veloxity in y-dir
		  force_x,			// force in x-dir
		  force_y,			// force in y-dir
		  mass,				// Mass of hero
		  velocity_jump,	// veloxity of jump
		  on_ground,		// hero currently touching the ground?
		  on_ladder;		// hero currently climbing?
	int ladder_dir;
	int ground_type;
};


#endif // HERO_H_