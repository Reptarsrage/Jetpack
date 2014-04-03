/* Justin Robb
 * 4-3-14
 * JetPack
 * File I/O
*/

#ifndef FILE_IO_H_
#define FILE_IO_H_

#include "AbstractThing.h"
#include "Sprites.h"
#include <queue>
#include <list>
#include <cstdint>
#include <iostream>
#include <fstream>
using namespace std;

/*File specifications:
 * 32 bit magic word
 * 16 bit length of title
 * title
 * 16 bit length of description
 * description
 * 16 bit length of passcode
 * passcode
 * 16 bit number of columns
 * 16 bit number of rows
 * col-wise level map, with token 255(max) seperating 1 byte words.
 */

//loads the level from the given filename.
//Returns the level info via the following parameters:
//	num_rows = number of rows on the level
//	num_cols = number of collumns on the level
//	title = title of the level
//	description = description of level
//	passcode = jump to this level passcodee (used by dev levels only)
//	level = all the things on the level with their correct (relative) positions
//			set to their column number and row number.

extern void load(string& filename,  
							 float row_w, 
							 float col_h, 
							 int *num_rows, 
							 int *num_cols,
							 string **title,
							 string **description,
							 string **passcode,
							 list<AbstractThing *> *level,
							 Sprites *sprites);

// Saves the level to the given filename
// expects the queue to be in col-wise order,
// with null values in place of empty tiles.
extern void save(string& filename, 
		  string& title, 
		  string& description, 
		  string& passcode, 
		  queue<AbstractThing *> level,
		  int num_rows, 
		  int num_cols);

#endif // FILE_IO_H_