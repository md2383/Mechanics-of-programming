// File: tedtalktest.c 
// 
// Description: test the tedtalk.c module
// @author      RIT CS Instructors
// 
// // // // // // // // // // // // // // // // // // // // // // // // 

//
// Content supplied to the student.
//

#include <stdio.h>
#include <stdlib.h>

#include "tedtalk.h"
#include "EventTime.h"

/// main function tests the tedtalk module.
/// @returns errorCode  error Code; EXIT_SUCCESS if no error

int main( void ) {

    EventTime_t * atime = NULL ;
    TEDtalk_t * talk1 = NULL ;
    TEDtalk_t * talk2 = NULL ;
    TEDtalk_t * talk3 = NULL ;

    printf( "Creating a time...\n" ) ;
    atime = newEventTime( 6, 30, "pm" ) ;

    printf( "Starting tedtalk tests...\n" ) ;

    talk1 = newTEDtalk( "Do schools kill creativity?", "Ken Robinson" ) ;
    printf( "First tedtalk initialized...\n" ) ;

    char * speaker = tedtalkGetSpeaker( talk1 ) ;
    char * title = tedtalkGetTitle( talk1 ) ;
    printf( "The current tedtalk is: \n\t%s by %s.\n", title, speaker) ;
    free( speaker ) ;
    free( title ) ;

    char * mstr = tedtalkToString( talk1 ) ;
    printf( "Otherwise... %s\n", mstr ) ;

    tedtalkPlay( talk1, atime ) ;
    mstr = tedtalkToString( talk1 ) ;
    printf( "After playing the tedtalk... \n\t%s\n", mstr ) ;

    EventTime_t * glp = tedtalkGetLastPlayed( talk1 ) ;
    char * sglp = timeToString(glp) ;
    speaker = tedtalkGetSpeaker( talk1 ) ;
    title = tedtalkGetTitle( talk1 ) ;
    printf( "The same tedtalk referencing members is: \n\t%s by %s. Last played at: %s\n", 
             title, speaker, sglp ) ;
    free( speaker ) ;
    free( title ) ;
    timeDelete( glp ) ;
    free( sglp ) ;

    tedtalkDelete( talk1 ) ;

    speaker = malloc( sizeof( "Amy Cuddy" ) + 1 ) ;
    title = malloc( sizeof( "Your body shapes who you are" ) + 1 ) ;
    strcpy( speaker, "Amy Cuddy" ) ;
    strcpy( title, "Your body shapes who you are" ) ;
    talk2 = newTEDtalk( title, speaker ) ;
    free( speaker ) ;
    free( title ) ;
    mstr = tedtalkToString( talk2 ) ;
    printf( "The talk2 is: \n\t%s\n", mstr ) ;
    
    talk1 = tedtalkCopy( talk2 ) ;
    mstr = tedtalkToString( talk1 ) ;
    printf( "The copy of talk2 tedtalk is: \n\t%s \n", mstr ) ;
    tedtalkDelete( talk2 ) ;
    mstr = tedtalkToString( talk1 ) ;
    printf( "After deleting the original talk2, the copy of talk2 "
            "tedtalk is ... \n\t%s\n", mstr ) ;

    char * pstr ;
    talk3 = tedtalkCopy( talk1 ) ;
    if ( tedtalkEquals( talk1, talk3 ) ) {
        mstr = tedtalkToString( talk1 ) ;
        pstr = tedtalkToString( talk3 ) ;
        printf( "The talk3 tedtalk \n\t%s\n"
                "    is the same as this tedtalk \n\t%s\n", pstr, mstr ) ;
        free( pstr ) ;
    } else {
        printf( "ERROR: tedtalkCopy() failure!\n" ) ;
    }

    tedtalkDelete( talk3 ) ;
    tedtalkDelete( talk1 ) ;

    talk3 = newTEDtalk( "How great leaders inspire action", "Simon Sinek" ) ;
    mstr = tedtalkToString( talk3 ) ;
    printf( "The current talk3 tedtalk is: \n\t%s\n", mstr ) ;

    tedtalkPlay( talk3, newEventTime(4, 42, "am") ) ;

    mstr = tedtalkToString( talk3 ) ;
    printf( "The current talk3 tedtalk is: \n\t%s\n", mstr ) ;
    free( mstr ) ;

    tedtalkDelete( talk1 ) ;
    tedtalkDelete( talk3 ) ;

    return EXIT_SUCCESS ;
}
