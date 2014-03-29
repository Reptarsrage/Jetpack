/* Justin Robb
 * 3-27-14
 * JetPack
 * A Recatngle
*/

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <assert.h>     /* assert */

/*
 * Used to represent bounds of things, as well as bounds of the window.
 * Positions are based off of Top-right hand coords, growing right and up.
 */
class Rectangle {
// Functions
public:
	Rectangle();
	Rectangle(float x, float y, float w, float h);
	
	/* Returns true if this rectangle overlaps the other.
	 * If two rectangles just touch, they do not overlap.
	 */
	bool Overlaps(const Rectangle other) const;
	
	/* Returns true if the specified point lies exculsively within this rectangle. */
	bool ContainsPoint(float x, float y) const;
	
	/* Returns the y-coord of the top of this rectangle */
	float top() const;
	
	/* Returns the y-coord of the bottom of this rectangle */
	float bottom() const;
	
	/* Returns the x-coord of the left-edge of this rectangle */
	float left() const;
	
	/* Returns the x-coord of the right-edge of this rectangle */
	float right() const;

// Attributes
public:
	float position_x,	// Rectangle's top position
		  position_y,	// Rectangle's left-edge position
		  width,		// width of rect
		  height;		// height of rect
};

#endif // RECTANGLE_H_