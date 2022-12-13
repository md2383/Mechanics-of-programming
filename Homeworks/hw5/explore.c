//
// File:  explore.c
//
// Description:  Main routine for the cave exploration program
//
// Usage:  ./explore cave_file
//  where cave_file contains a cave description
//
// @author  csci243@cs.rit.edu
// @author  Miguel Dias Pinto md2383@rit.edu
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cave.h"
#include "traverse.h"

///
/// main function
///
/// @param argc - number of things on the command line
/// @param argv - vector of command-line arguments
///
/// @return 0 on success, 1 if an error occurs
///
int main( int argc, char *argv[] ) {

    // process the cave file and build the graph
    if(!(argc > 1)) {			//Fix1
	printf("usage: ./explore cave_file\n");
	exit( 1 );
    }

    cell_t *start = build_cave( argv[1] );
    if( start == NULL ) {
        // something went wrong!
	fputs( "Build failed!\n", stderr );
        exit( 1 );
    }

    // perform the traversal
    if( traverse( start, stdin ) ) {
        puts( "Congratulations!  You have found your way out!" );
    } else {
        puts( "Gave up, eh?  Well, maybe next time...." );
    }

    // all done, so free the cave
    free_cave();

    // indicate successful termination
    return( 0 );
}
