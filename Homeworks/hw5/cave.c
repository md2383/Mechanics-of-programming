//
// File:  cave.c
//
// Description:  cave-related support routines
//
// @author csci243@cs.rit.edu
// @author Miguel Dias Pinto md2383@rit.edu
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <ctype.h>

#include "cave.h"

// delimeter characters for parsing the cave description lines
#define WHITESPACE  " \t\r\n"
#define NEWLINE     "\n"

//
// Private variables holding the cave
//
static cell_t **cave;   // dynamic array of cave cells
static int ncells;      // number of cells in the cave
static int entry;       // entry point to the cave system

//
// Keep track of whether or not the explorer has picked up the
// key that will allow them to leave via the exit door.
//
bool has_key = false;

///
/// get the next line of data from the input,
/// skipping blank/empty lines and comment lines
///
/// @param buf - input buffer for the line
/// @param len - size of the buffer
/// @param in  - input stream to read
///
/// @return input line length, or -1 on EOF or error
///
static int readline( char *buf, size_t len, FILE *in ) {
    int n;

    do {

        // try to read the line
        if( fgets(buf,len,in) == NULL ){
            // no data, so we're done
            return( -1 );
        }

        // OK, we read a line.  See if it contains any
        // non-whitespace characters.
        n = strlen(buf);
        int prefix = strspn( buf, WHITESPACE );

        // it's a blank line if the line contains only one
        // character (the newline), or if the prefix containing
        // whitespace characters is the entire line
        if( n < 2 || prefix == n ) {
            // blank line
            continue;
        }
        
        // must be at least one non-whitespace character; if
        // the first one is '#', this is a comment line
        if( buf[prefix] == '#' ) {
            continue;
        }

        // not a blank line, and not a comment, so we're all set
        break;
        
    } while( 1 );

    return( strlen(buf) );
}

///
/// process a cell connectivity line
///
/// @param buf - buffer containing the cell description
///
/// @return true on success, else false
///
static bool process( char *buf ) {

    // sanity checking!  if we get a bad parameter, blow up
    assert( buf != NULL );

    // format of cell lines:
    //
    //     cell#  linkN  linkS  linkE  linkW  contents
    //
    // valid cell# is 0 through ncells-1
    // each link is -1 if not present, else a valid cell#
    // contents is a string (first non-WS to end of line) or empty

    // convert the cell number
    char *tok = strtok( buf, WHITESPACE );
    errno = 0;
    long num = strtol( tok, NULL, 10 );
    if( errno != 0 || num < 0 || num >= ncells ) {
        fprintf( stderr, "error - invalid cell number '%ld'\n", num );
        return( false );
    }

    cell_t *cell = cave[num];
    assert( cell != NULL );     // another sanity check

    // links will be in order: N S E W
    int ix = NORTH;
    tok = strtok( NULL, WHITESPACE );
    while( tok != NULL ) {

        // convert this link
        errno = 0;
        long dir = strtol( tok, NULL, 10 );

        // validate it
        if( errno != 0 || dir < -1 || dir >= ncells ) {

            // bad value
            fprintf( stderr, "error - invalid link '%ld'\n", dir );
            // this will get us out of the loop
            tok = NULL;
            ix = -1;
            return( false );

        }

        // if this was an actual link, record it in the
        // current direction
        if( dir != -1 ) {
            cell->exits[ix] = cave[dir];
            cell->links += 1;
        }

        // move to the next direction
        ++ix;

        // have we processed them all?
        if( ix == NDIRS ) {
            break;
        }

        // find the next link
        tok = strtok( NULL, WHITESPACE );

    }

    // verify that we had exactly four link values
    if( ix != NDIRS ) {
        fprintf( stderr, "error - cell %ld has %d (%s) tunnel numbers\n",
                 num, ix, ix < 4 ? "too few" : "too many" );
        return( false );
    }

    // the rest of the line describes the contents of this
    // cave cell, so we'll use strtok() to just find the
    // end of the line
    tok = strtok( NULL, NEWLINE );

    // at this point, if tok is NULL, we know that there were
    // no "contents" characters on the line; otherwise, tok
    // is pointing to the first character after the last
    // tunnel link number, and the newline at the end of the
    // input line is now a NUL character (or there was no 
    // newline on the line)

    char *debris = NULL;
    if( tok != NULL ) {

        // find the first non-whitespace character
        int length = strlen( tok );
        int firstix = strspn( tok, WHITESPACE );

        // was there one?
        if( firstix < length ) {

            // yes; trim any trailing whitespace

            // find the last character in the string
            int endix = strlen(tok) - 1;

            // back up until we find a non-whitespace character;
            // make sure we don't back up past the first
            // non-whitespace character we found earlier!
            while( endix >= firstix && isspace(tok[endix]) ) {
                --endix;
            }

            // if endix >= firstix, there's at least one
            // non-whitespace character
            if( endix >= firstix ) {
                // follow i with a NUL byte
                tok[endix+1] = '\0';
                // remember where the first non-WS character was
                debris = tok + firstix;
            }

        }

    }

    // set the "contents" value
    if( debris != NULL ) {

        cell->contents = (char *) malloc( sizeof(debris) + 10 ); //Fix2
        if( cell->contents == NULL ) {
            fputs( "error - can't allocate cell contents space\n", stderr );
            return( false );
        }
        strcpy( cell->contents, debris );

    } else {

        // nothing here!
        cell->contents = NULL;

    }

    // whew!  all set!
    return( true );

}

///
/// free_cave(): free the cave structure
///
void free_cave( void ) {

    // make sure we have a cave to free!
    if( cave == NULL ) {
        return;
    }
    for(int i = 0; i < ncells; i++){    //Fix5
        free(cave[i]->contents);
        free(cave[i]);
    }
    free( cave );
}

///
/// report(): describe the contents of a cave cell
///
/// @param cell - the cell to be described
///
void report( cell_t *cell ) {
    
    if(!(cell == NULL)){            //Fix2
    // collect some information from the fields, just to
    // avoid repeatedly dereferencing the cell pointer
    int num = cell->number;
    char *contents = cell->contents;
    int links = cell->links;

    // basic information about the cell
    printf( "\nYou are in cell #%d.\n", num );

    if( contents != NULL) {
        if( KEY_HERE(contents) ) {
            puts( "There is a key here." );
        } else if( DOOR_HERE(contents) ) {
            puts( "There is a locked exit door here." );
        } else {
            printf( "You see %s here.\n", contents );
        }
    }

    // if they have the key in had, remind them
    if( has_key ) {
        puts( "You are carrying a key." );
    }

    // if there are no tunnels to other cells, we're done
    if( links < 1 ) {
        puts( "There are no tunnels here to other cells." );
        return;
    }

    // OK, we have tunnels to report
    if( links == 1 ) {
        fputs( "There is one tunnel here, leading", stdout );
    } else {
        printf( "There are %d tunnels here, leading", links );
    }

    // iterate through the directions, reporting which ones
    // are non-NULL

    int count = 0;  // tracks the number of tunnels we have seen

    for( int i = NORTH; i <= WEST; ++i ) {

        // does this cell have an exit in this direction?
        if( cell->exits[i] != NULL ) {

            // yes; if this is not the first one we've seen,
            // print a ',' to neaten-up the output
            if( count > 0 ) {
                putchar( ',' );
            }

            switch( i ) {
            case NORTH:  fputs( " North", stdout );  break;
            case SOUTH:  fputs( " South", stdout );  break;
            case EAST:   fputs( " East", stdout );  break;
            case WEST:   fputs( " West", stdout );  break;
            default:     fputs( " Somewhere", stdout );  break;
            }

            // indicate we've seen another tunnel
            ++count;
        }
    }

    // wrap up the last line
    putchar( '\n' );
    }
    else{

    }
}

///
/// build_cave(): create a cave from the specified description file
///
/// See the README file for a description of the format of a
/// cave description file.
///
/// @param name - name of the file to be processed
///
/// @return a pointer to the entrance cell, or NULL if the cave
/// couldn't be built
///
cell_t *build_cave( const char *name ) {
    char buf[MAXLINE];

    printf( "Processing cave file '%s'\n", name );

    // open the description file
    FILE *in = fopen( name, "r" );
    if( in == NULL ) {			//Fix1
        // something went wrong!
        perror( name );
        return( NULL );
    }

    // first input line is number of cells
    int len = readline( buf, MAXLINE, in );
    if( len < 1 ) {
        fputs( "error - cannot read cell count\n", stderr );
        fclose( in );
        return( NULL );
    }

    // convert the cell count
    int n = sscanf( buf, "cells %d", &ncells );
    if( n != 1 ) {
        fprintf( stderr, "error - bad cell line '%s'", buf );
        return( NULL );
    }

    // next input line is the entry point to the cave system
    len = readline( buf, MAXLINE, in );
    if( len < 1 ) {
        fputs( "error - cannot read entry point\n", stderr );
        fclose( in );
        return( NULL );
    }

    // convert the entry cell number
    n = sscanf( buf, "entry %d", &entry );
    if( n != 1 ) {
        fprintf( stderr, "error - bad entry line '%s'", buf );
        return( NULL );
    }

    // allocate space for the cave array
    cave = (cell_t **) malloc( ncells * sizeof(cell_t *) );
    if( cave == NULL ) {
        fputs( "error - cannot allocate space for cave", stderr );
        return( NULL );
    }

    // allocate the individual cells
    for( int i = 0; i < ncells; ++i ) {
        cave[i] = (cell_t *) malloc( sizeof(cell_t) );
        if( cave[i] == NULL ) {
            fprintf( stderr, "error - cannot allocate cave cell #%d\n", i );
            return( NULL );
        }
        cave[i]->number = i;
        cave[i]->links = 0;     //fix4
        cave[i]->exits[0] = NULL;  //fix4
        cave[i]->exits[1] = NULL;
        cave[i]->exits[2] = NULL;
        cave[i]->exits[3] = NULL; //Set all 4 sides to NULL because there are 4 sides to each cell.
    }

    // read the connectivity information and connect the cells
    //
    // there may be fewer than 'ncells' connectivity lines, but should
    // never be more of them

    n = 0;
    while( 1 ) {

        len = readline( buf, MAXLINE, in );
        if( len < 1 ) {
            break;
        }

        if( n >= ncells ) {
            // too many cell lines!
            fprintf( stderr, "error - more than %d cell lines!\n", n );
            return( NULL );
        }

        if( !process(buf) ) {
            return( NULL );
        }

        ++n;
    }
    fclose(in);     //fix4
    // return the pointer to the cave entrance
    return( cave[entry] );
}
