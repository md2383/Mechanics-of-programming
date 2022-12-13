//
// File:  traverse.h
//
// Description:  prototypes for the traversal module
//
// @author csci243@cs.rit.edu
// @author  ADD_FULL_NAME_AND_LOGIN_HERE
//

#ifndef TRAVERSE_H_
#define TRAVERSE_H_

#include <stdio.h>

#include "cave.h"

///
/// perform a traversal of the cave
///
/// @param entry - pointer to the entry point of the cave
/// @param in    - input stream from which commands are to be read
///
/// @returns true if the explorer left via the exit door, else false
///
bool traverse( cell_t *entry, FILE *in );

#endif
