/* Justin Robb
 * 3-27-14
 * JetPack
*/

#include "Enums.h"
#include <time.h> // for seeding rand()
#include <stdlib.h>
#include "SolidThing.h"
#include "NonSolidThing.h"
#include "Gem.h"
#include "Ladder.h"
#include "Pinwheel.h"
#include "Bat.h"
#include "Predator.h"
#include "Spring.h"
#include "Egg.h"
#include "Robot.h"
#include "Door.h"
#include "Hero.h"
#include "Gold.h"
#include "Item.h"
#include "Box.h"
#include "WoodSolid.h"
#include "BrickSolid.h"
#include "FastSolid.h"
#include "SwitchSolid.h"
#include "Deathsicle.h"
#include "Mine.h"
#include "Missile.h"
#include "Teleporter.h"
#include "Switch.h"
#include "StoneSolid.h"


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
		case TYPE_STONESOLID_CONVEYOR_R:
			result = new StoneSolid(x,y,width, height, sprites);
			static_cast<StoneSolid *>(result)->setAttribute(CONVEYOR_RIGHT);
			break;
		case TYPE_STONESOLID_CONVEYOR_L:
			result = new StoneSolid(x,y,width, height, sprites);
			static_cast<StoneSolid *>(result)->setAttribute(CONVEYOR_LEFT);
			break;
		case TYPE_BRICKSOLID_CONVEYOR_R:
			result = new BrickSolid(x,y,width, height, sprites);
			static_cast<BrickSolid *>(result)->setAttribute(CONVEYOR_RIGHT);
			break;
		case TYPE_BRICKSOLID_CONVEYOR_L:
			result = new BrickSolid(x,y,width, height, sprites);
			static_cast<BrickSolid *>(result)->setAttribute(CONVEYOR_LEFT);
			break;
		case TYPE_WOODSOLID_CONVEYOR_R:
			result = new WoodSolid(x,y,width, height, sprites);
			static_cast<WoodSolid *>(result)->setAttribute(CONVEYOR_RIGHT);
			break;
		case TYPE_WOODSOLID_CONVEYOR_L:
			result = new WoodSolid(x,y,width, height, sprites);
			static_cast<WoodSolid *>(result)->setAttribute(CONVEYOR_LEFT);
			break;
		case TYPE_BRICKSOLID:
			result = new BrickSolid(x,y,width, height, sprites);
			break;
		case TYPE_BRICKSOLID_ICY:
			result = new BrickSolid(x,y,width, height, sprites);
			static_cast<BrickSolid *>(result)->setAttribute(ICY);
			break;
		case TYPE_BRICKSOLID_MOSSY:
			result = new BrickSolid(x,y,width, height, sprites);
			static_cast<BrickSolid *>(result)->setAttribute(MOSSY);
			break;
		case TYPE_SHIELDED_BRICK_D:
			result = new BrickSolid(x,y,width, height, sprites);
			static_cast<BrickSolid *>(result)->setAttribute(SHIELDED_DOWN);
			break;
		case TYPE_SHIELDED_BRICK_U:
			result = new BrickSolid(x,y,width, height, sprites);
			static_cast<BrickSolid *>(result)->setAttribute(SHIELDED_UP);
			break;
		case TYPE_SHIELDED_BRICK_L:
			result = new BrickSolid(x,y,width, height, sprites);
			static_cast<BrickSolid *>(result)->setAttribute(SHIELDED_LEFT);
			break;
		case TYPE_SHIELDED_BRICK_R:
			result = new BrickSolid(x,y,width, height, sprites);
			static_cast<BrickSolid *>(result)->setAttribute(SHIELDED_RIGHT);
			break;
		case TYPE_WOODSOLID:
			result = new WoodSolid(x,y,width, height, sprites);
			break;
		case TYPE_WOODSOLID_ICY:
			result = new WoodSolid(x,y,width, height, sprites);
			static_cast<WoodSolid *>(result)->setAttribute(ICY);
			break;
		case TYPE_WOODSOLID_MOSSY:
			result = new WoodSolid(x,y,width, height, sprites);
			static_cast<WoodSolid *>(result)->setAttribute(MOSSY);
			break;
		case TYPE_SHIELDED_WOOD_D:
			result = new WoodSolid(x,y,width, height, sprites);
			static_cast<WoodSolid *>(result)->setAttribute(SHIELDED_DOWN);
			break;
		case TYPE_SHIELDED_WOOD_U:
			result = new WoodSolid(x,y,width, height, sprites);
			static_cast<WoodSolid *>(result)->setAttribute(SHIELDED_UP);
			break;
		case TYPE_SHIELDED_WOOD_L:
			result = new WoodSolid(x,y,width, height, sprites);
			static_cast<WoodSolid *>(result)->setAttribute(SHIELDED_LEFT);
			break;
		case TYPE_SHIELDED_WOOD_R:
			result = new WoodSolid(x,y,width, height, sprites);
			static_cast<WoodSolid *>(result)->setAttribute(SHIELDED_RIGHT);
			break;
		case TYPE_STONESOLID:
			result = new StoneSolid(x,y,width, height, sprites);
			break;
		case TYPE_STONESOLID_ICY:
			result = new StoneSolid(x,y,width, height, sprites);
			static_cast<StoneSolid *>(result)->setAttribute(ICY);
			break;
		case TYPE_STONESOLID_MOSSY:
			result = new StoneSolid(x,y,width, height, sprites);
			static_cast<StoneSolid *>(result)->setAttribute(MOSSY);
			break;
		case TYPE_IVY:
			result = new NonSolidThing(x,y,width, height, sprites);
			static_cast<NonSolidThing *>(result)->setInfo(TYPE_IVY, SPRITE_IVY, "Ivy");
			break;
		case TYPE_PILLAR:
			result = new NonSolidThing(x,y,width, height, sprites);
			static_cast<NonSolidThing *>(result)->setInfo(TYPE_PILLAR, SPRITE_PILLAR, "Pillar");
			break;
		case TYPE_REDSWITCH:
			result = new Switch(x,y,width, height, sprites);
			static_cast<Switch *>(result)->bindSwitch(SWITCH_RED_H);
			break;
		case TYPE_BAT:
			result = new Bat(x,y,width, height, sprites);
			break;
		case TYPE_BLUESWITCH:
			result = new Switch(x,y,width, height, sprites);
			static_cast<Switch *>(result)->bindSwitch(SWITCH_BLUE_H);
			break;
		case TYPE_BLUESWITCHSOLID:
			result = new SwitchSolid(x,y,width, height, sprites);
			static_cast<SwitchSolid *>(result)->bindSwitch(SWITCH_BLUE_V);
			break;
		case TYPE_BOX:
			result = new Box(x,y,width, height, sprites);
			break;
		case TYPE_DEATHDOWN:
			result = new Deathsicle(x,y,width, height, sprites);
			static_cast<Deathsicle *>(result)->setDir(DOWN);
			break;
		case TYPE_DEATHLEFT:
			result = new Deathsicle(x,y,width, height, sprites);
			static_cast<Deathsicle *>(result)->setDir(LEFT);
			break;
		case TYPE_DEATHRIGHT:
			result = new Deathsicle(x,y,width, height, sprites);
			static_cast<Deathsicle *>(result)->setDir(RIGHT);
			break;
		case TYPE_DEATHUP:
			result = new Deathsicle(x,y,width, height, sprites);
			static_cast<Deathsicle *>(result)->setDir(UP);
			break;
		case TYPE_EGG:
			result = new Egg(x,y,width, height, sprites);
			break;
		case TYPE_FASTSOLID:
			result = new FastSolid(x,y,width, height, sprites);
			break;
		case TYPE_FULLFUEL:
			result = new Item(x,y,width, height, sprites);
			static_cast<Item *>(result)->setType(TYPE_FULLFUEL);
			break;
		case TYPE_GEM:
			result = new Gem(x,y,width, height, sprites);
			break;
		case TYPE_GOLD1:
			result = new Gold(x,y,width, height, sprites);
			static_cast<Gold *>(result)->setValue(100);
			break;
		case TYPE_GOLD2:
			result = new Gold(x,y,width, height, sprites);
			static_cast<Gold *>(result)->setValue(250);
			break;
		case TYPE_GOLD3:
			result = new Gold(x,y,width, height, sprites);
			static_cast<Gold *>(result)->setValue(500);
			break;
		case TYPE_GOLD4:
			result = new Gold(x,y,width, height, sprites);
			static_cast<Gold *>(result)->setValue(1000);
			break;
		case TYPE_GOLDSWITCH:
			result = new Switch(x,y,width, height, sprites);
			static_cast<Switch *>(result)->bindSwitch(SWITCH_GOLD_H);
			break;
		case TYPE_GOLDSWITCHSOLID:
			result = new SwitchSolid(x,y,width, height, sprites);
			static_cast<SwitchSolid *>(result)->bindSwitch(SWITCH_GOLD_V);
			break;
		case TYPE_GREENTELEPORTER:
			result = new Teleporter(x,y,width, height, sprites);
			static_cast<Teleporter *>(result)->bindTeleporter(TELE_GREEN);
			break;
		case TYPE_HALFFUEL:
			result = new Item(x,y,width, height, sprites);
			static_cast<Item *>(result)->setType(TYPE_HALFFUEL);
			break;
		case TYPE_HBLUESWITCHSOLID:
			result = new SwitchSolid(x,y,width, height, sprites);
			static_cast<SwitchSolid *>(result)->bindSwitch(SWITCH_BLUE_H);
			break;
		case TYPE_HGOLDSWITCHSOLID:
			result = new SwitchSolid(x,y,width, height, sprites);
			static_cast<SwitchSolid *>(result)->bindSwitch(SWITCH_GOLD_H);
			break;
		case TYPE_HREDSWITCHSOLID:
			result = new SwitchSolid(x,y,width, height, sprites);
			static_cast<SwitchSolid *>(result)->bindSwitch(SWITCH_RED_H);
			break;
		case TYPE_HUNTER:
			result = new Predator(x,y,width, height, sprites);
			break;
		case TYPE_INVINCIBILITY:
			result = new Item(x,y,width, height, sprites);
			static_cast<Item *>(result)->setType(TYPE_INVINCIBILITY);
			break;
		case TYPE_LADDER:
			result = new Ladder(x,y,width, height, sprites);
			break;
		case TYPE_LADDERUP:
			result = new Ladder(x,y,width, height, sprites);
			static_cast<Ladder *>(result)->setDirection(UP);
			break;
		case TYPE_LADDERDOWN:
			result = new Ladder(x,y,width, height, sprites);
			static_cast<Ladder *>(result)->setDirection(DOWN);
			break;
		case TYPE_MINE:
			result = new Mine(x,y,width, height, sprites);
			break;
		case TYPE_MISSILE:
			result = new Missile(x,y,width, height, sprites);
			break;
		case TYPE_PINWHEEL:
			result = new Pinwheel(x,y,width, height, sprites);
			break;
		case TYPE_PURPLETELEPORTER:
			result = new Teleporter(x,y,width, height, sprites);
			static_cast<Teleporter *>(result)->bindTeleporter(TELE_PURPLE);
			break;
		case TYPE_REDSWITCHSOLID:
			result = new SwitchSolid(x,y,width, height, sprites);
			static_cast<SwitchSolid *>(result)->bindSwitch(SWITCH_RED_V);
			break;
		case TYPE_ROBOT:
			result = new Robot(x,y,width, height, sprites);
			break;
		case TYPE_SPRING:
			result = new Spring(x,y,width, height, sprites);
			break;
		case TYPE_TIMER:
			result = new Item(x,y,width, height, sprites);
			static_cast<Item *>(result)->setType(TYPE_TIMER);
			break;
		case TYPE_YELLOWTELEPORTER:
			result = new Teleporter(x,y,width, height, sprites);
			static_cast<Teleporter *>(result)->bindTeleporter(TELE_YELLOW);
			break;
		case TYPE_DOOR:
			result = new Door(x,y,width, height, sprites);
			break;
		case TYPE_HERO:
			result = new Hero(x,y,width, height, sprites);
			break;
		default:
			printf("UNIDENTIFIED THING! CODE:%d\n", code);
			break;
	}
	result->SetActualBounds(x,y, width, height);
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