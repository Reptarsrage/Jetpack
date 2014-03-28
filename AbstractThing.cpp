#include "AbstractThing.h"

const Rectangle AbstractThing::Bounds() const{
	return *bounds;
}

bool AbstractThing::Overlaps(const AbstractThing *other) const{
	return bounds->Overlaps(other->Bounds());
}

void AbstractThing::Show() const {
	visable = true;
}

void AbstractThing::Hide() const {
	visable = false;
}