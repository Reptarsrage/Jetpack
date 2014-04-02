/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "Enums.h"
#include <time.h> // for seeding rand()
#include <stdlib.h>
#include "SolidThing.h"
#include "NonSolidThing.h"
#include "Collectable.h"
#include "Ladder.h"
#include "Pinwheel.h"
#include "Bat.h"
#include "Predator.h"
#include "Spring.h"
#include "Egg.h"
#include "Robot.h"


int m_rand() {
	rand();
	return rand();
}

void init_rand() {
	srand(time(NULL));
}

float m_randf() {
	rand();
	return (float)rand() / RAND_MAX;
}

AbstractThing* getThingFromCode(int code, float x, float y, float width, float height, Sprites *sprites){
	AbstractThing *result = NULL;
	switch (code) {
		case MENU_IVY:
			result = new NonSolidThing(x,y,width, height, sprites);
			break;
		case MENU_PILLAR:
			result = new NonSolidThing(x,y,width, height, sprites);
			break;
		case MENU_REDSWITCH:
			result = new NonSolidThing(x,y,width, height, sprites);
			break;
		case MENU_BAT:
			result = new Bat(x,y,width, height, sprites);
			break;
		case MENU_BLUESWITCH:
			result = new NonSolidThing(x,y,width, height, sprites);
			break;
		case MENU_BLUESWITCHSOLID:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_BOX:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_CONVEYORSOLIDLEFT:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_CONVEYORSOLIDRIGHT:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_D:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_DEATHDOWN:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_DEATHLEFT:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_DEATHRIGHT:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_DEATHUP:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_EGG:
			result = new Egg(x,y,width, height, sprites);
			break;
		case MENU_FASTSOLID:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_FULLFUEL:
			result = new Collectable(x,y,width, height, sprites);
			break;
		case MENU_GEM:
			result = new Collectable(x,y,width, height, sprites);
			break;
		case MENU_GOLD1:
			result = new Collectable(x,y,width, height, sprites);
			break;
		case MENU_GOLD2:
			result = new Collectable(x,y,width, height, sprites);
			break;
		case MENU_GOLD3:
			result = new Collectable(x,y,width, height, sprites);
			break;
		case MENU_GOLD4:
			result = new Collectable(x,y,width, height, sprites);
			break;
		case MENU_GOLDSWITCH:
			result = new NonSolidThing(x,y,width, height, sprites);
			break;
		case MENU_GOLDSWITCHSOLID:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_GREENTELEPORTER:
			result = new NonSolidThing(x,y,width, height, sprites);
			break;
		case MENU_HALFFUEL:
			result = new Collectable(x,y,width, height, sprites);
			break;
		case MENU_HARDERSOLID:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_HBLUESWITCHSOLID:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_HGOLDSWITCHSOLID:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_HREDSWITCHSOLID:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_HUNTER:
			result = new Predator(x,y,width, height, sprites);
			break;
		case MENU_ICESOLID:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_INVINCIBILITY:
			result = new Collectable(x,y,width, height, sprites);
			break;
		case MENU_L:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_LADDER:
			result = new Ladder(x,y,width, height, sprites);
			break;
		case MENU_LADDERUP:
			result = new Ladder(x,y,width, height, sprites);
			break;
		case MENU_LADDERDOWN:
			result = new Ladder(x,y,width, height, sprites);
			break;
		case MENU_MINE:
			result = new NonSolidThing(x,y,width, height, sprites);
			break;
		case MENU_MISSILE:
			result = new Spring(x,y,width, height, sprites);
			break;
		case MENU_MOSSSOLID:
			break;
		case MENU_NONPSOLID:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_PINWHEEL:
			result = new Pinwheel(x,y,width, height, sprites);
			break;
		case MENU_PURPLETELEPORTER:
			result = new NonSolidThing(x,y,width, height, sprites);
			break;
		case MENU_R:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_REDSWITCHSOLID:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_ROBOT:
			result = new Robot(x,y,width, height, sprites);
			break;
		case MENU_SOLID:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_SPRING:
			result = new Spring(x,y,width, height, sprites);
			break;
		case MENU_TIMER:
			result = new Collectable(x,y,width, height, sprites);
			break;
		case MENU_U:
			result = new SolidThing(x,y,width, height, sprites);
			break;
		case MENU_YELLOWTELEPORTER:
			result = new NonSolidThing(x,y,width, height, sprites);
			break;
		default:
			printf("UNIDENTIFIED THING!");
			break;
	}
	return result;
}

const char *SpriteNames[] = { "Gameover-web-final.jpg",
							"Ivy.png",
							"Pillar.png",
							"RedSwitch.png",
							"background.bmp",
							"bat1.png",
							"bat2.png",
							"bat3.png",
							"bat4.png",
							"blowingup.png",
							"blowingup2.png",
							"blowingup3.png",
							"blowingup4.png",
							"blowingup5.png",
							"blowingup6.png",
							"blueSwitch.png",
							"blueSwitchSolid.png",
							"box.png",
							"conveyorsolid1.png",
							"conveyorsolid2.png",
							"conveyorsolid3.png",
							"conveyorsolid4.png",
							"conveyorsolid5.png",
							"credits.png",
							"d.png",
							"dead.png",
							"deathdown.png",
							"deathleft.png",
							"deathright.png",
							"deathup.png",
							"doorclosed.png",
							"doorclosing2.png",
							"dooropen.png",
							"dooropening1.png",
							"dying1.png",
							"dying2.png",
							"dying3.png",
							"dying4.png",
							"dying5.png",
							"egg.png",
							"fastsolid.png",
							"front.png",
							"fuel.png",
							"fuelback.png",
							"fuelred.png",
							"fuelyellow.png",
							"fullfuel.png",
							"gem.png",
							"gemcollected.png",
							"gold1.png",
							"gold2.png",
							"gold3.png",
							"gold4.png",
							"goldSwitch.png",
							"goldSwitchSolid.png",
							"greenteleporter.png",
							"halffuel.png",
							"hardersolid.png",
							"hblueSwitchSolid.png",
							"heroteleportinggreen1.png",
							"heroteleportinggreen2.png",
							"heroteleportingpurple1.png",
							"heroteleportingpurple2.png",
							"heroteleportingyellow1.png",
							"heroteleportingyellow2.png",
							"hgoldSwitchSolid.png",
							"hredSwitchSolid.png",
							"hunterh1.png",
							"hunterh2.png",
							"hunterv1.png",
							"hunterv2.png",
							"icesolid.png",
							"invincibility.png",
							"invincibility1.png",
							"jetpack_0.png",
							"jumping.png",
							"l.png",
							"ladder.png",
							"ladder2.png",
							"ladder3.png",
							"ladder4.png",
							"left1.png",
							"left2.png",
							"leftjet.png",
							"loadsave.png",
							"lowerbackground.png",
							"mine.png",
							"missiledown1.png",
							"missiledown2.png",
							"missileleft1.png",
							"missileleft2.png",
							"missileright1.png",
							"missileright2.png",
							"missileup1.png",
							"missileup2.png",
							"mosssolid.png",
							"nonpsolid.png",
							"phasedown1.png",
							"phasedown2.png",
							"phasingleft1.png",
							"phasingleft2.png",
							"phasingright1.png",
							"phasingright2.png",
							"phasingup1.png",
							"phasingup2.png",
							"pinwheel1.png",
							"pinwheel2.png",
							"pinwheel3.png",
							"pinwheel4.png",
							"purpleteleporter.png",
							"r.png",
							"redSwitchSolid.png",
							"right1.png",
							"right2.png",
							"rightjet.png",
							"roboleft1.png",
							"roboleft2.png",
							"roboright1.png",
							"roboright2.png",
							"solid.png",
							"solidphased.png",
							"solidphasing1.png",
							"solidphasing2.png",
							"spring1.png",
							"spring2.png",
							"springsmall.png",
							"timer.png",
							"timer2.png",
							"u.png",
							"win.png",
							"win1.png",
							"win2.png",
							"win3.png",
							"yellowteleporter.png" };