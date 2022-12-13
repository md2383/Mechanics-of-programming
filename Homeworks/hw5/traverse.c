//
// File:  traverse.c
//
// Description:  Traversal routine for the cave assignment.
//
// @author csci243@cs.rit.edu
// @author Miguel Dias Pinto md2383@rit.edu
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "cave.h"

//
// This message is printed when help is requested by the user
//
static const char *help_message =
    "\nDirectional commands:\n"
    "\tN or n - move to the North\n"
    "\tS or s - move to the South\n"
    "\tE or e - move to the East\n"
    "\tW or w - move to the West\n"
    "\nOther commands:\n"
    "\tH - print this message\n"
    "\tL - look around in the current cave cell\n"
    "\tT - take the key if it is in this cell\n"
    "\tQ - quit immediately\n"
    "\tX - exit from the cave using the Door in this cell\n";


///
/// traverse():  perform a traversal of the cave
///
bool traverse( cell_t *entry, FILE *in ) {

    // declare our input character variable so we can access it
    // if we fall out of the while loop
    int ch;

    // start at the entry point of the cave
    cell_t *curr = entry;

    // loop until the user either gives up or finds the key and
    // the door and leaves the cave
    while( 1 ) {
        if(!(curr == NULL)){            //Fix2
        // describe the current cell
        report( curr );

        // request an action
        fputs( "\nCommand? ", stdout );

        // loop until we get a non-whitespace character
        ch = ' ';
        while( isspace(ch) ) {
            ch = fgetc( in );
            // if we're out of characters, just leave
            if( ch == EOF ) {
                return( false );
            }
        }

        // got a character; convert it to uppercase,
        // but retain the original just in case we need it
        int upch = islower(ch) ? toupper(ch) : ch;

        int dir;
        char *stuff = curr->contents;   // for easier use

        switch( upch ) {

            // move
        case 'N': dir = NORTH; break;
        case 'S': dir = SOUTH; break;
        case 'E': dir = EAST;  break;
        case 'W': dir = WEST;  break;

            // print a list of commands 
        case 'H':
            puts( help_message );
            continue;

            // look around again
        case 'L':
            report( curr );
            continue;

            // take the key, if it's here
        case 'T':
            if( !stuff || !KEY_HERE(stuff) ) {
                puts( "Sorry, there is no key here." );
                continue;
            }
            if( has_key ) {
                puts( "Sorry, but you already have a key." );
            } else {
                // pick this one up
                has_key = true;
                // remember that it has been picked up
                curr->contents = NULL;
                puts( "You have picked up the key." );
            }
            continue;

            // quit (i.e., give up)
        case 'Q':
            return( false );

            // trying to leave through the door
        case 'X':
            if( !stuff || !DOOR_HERE(stuff) ) {
                puts( "Sorry, there is no door here." );
                continue;
            }
            // found the door; do we have the key?
            if( has_key ) {
                return( true );
            }
            // nope!
            puts( "You found the door, but you don't have they key." );
            continue;

            // unknown input character!
        default:
            printf( "Sorry, I don't know what '%c' means.", ch );
            continue;
        }

        // we don't get here unless the command from the user was
        // a direction to move
        if( curr->exits[dir] == NULL ) {
            puts( "Sorry, there is no tunnel in that direction." );
            continue;
        }
            curr = curr->exits[dir];
        }
    }

    // we should never fall out of the while loop; if we get to
    // this point, something very strange has happened, so we'll
    // report the character we read in most recently

    printf( "Uh-oh, shouldn't be here.  ch is 0x%02x.\n", (unsigned int) ch );

    return( false );

}
