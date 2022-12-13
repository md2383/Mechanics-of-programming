//
// File:  cave.h
//
// Description:  cave description and prototypes
//
// @author csci243@cs.rit.edu
// @author  ADD_FULL_NAME_AND_LOGIN_HERE
//

#ifndef CAVE_H_
#define CAVE_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// input buffer size
#define MAXLINE    64

// directions
#define NORTH   0
#define SOUTH   1
#define EAST    2
#define WEST    3

// number of directions
#define NDIRS   4

//
// Structure of a cell in the cave.
//
// Each cell has an ID, can have up to four exits,
// and may contain some type of artifact.
//
typedef
    struct cell_s {
        char *contents;                 // what's here?
        struct cell_s *exits[NDIRS];    // how to get out
        uint16_t number;                // cell ID number
        uint8_t links;                  // number of exit tunnels
    }
        cell_t;

// "shorthand" names for the different exits
#define North   exits[NORTH]
#define South   exits[SOUTH]
#define East    exits[EAST]
#define West    exits[WEST]

// shorthand test for presence of a key
#define KEY_HERE(x)  (strcmp((x),"KEY") == 0)

// shorthand test for presence of a door
#define DOOR_HERE(x) (strcmp((x),"DOOR") == 0)

//
// Keep track of whether or not the explorer has picked up the
// key that will allow them to leave via the exit door.
//
extern bool has_key;

///
/// build_cave(): create a cave from the specified description file
///
/// @param name - name of the file to be processed
///
/// @return a pointer to the entrance cell, or NULL if the cave
/// couldn't be built
///
cell_t *build_cave( const char *name );

///
/// report(): describe the contents of a cave cell
///
/// @param cell - the cell to be described
///
void report( cell_t *cell );

///
/// free_cave(): free the cave structure
///
void free_cave( void );

#endif
