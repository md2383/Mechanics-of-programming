// File:         tedtalk.h
// Description:  Interface for a module that represents a TEDtalk
// @author:      RIT CS Instructors
//

#ifndef TEDTALK_H
#define TEDTALK_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "EventTime.h"

/// The TEDtalk_t structure represents a TED talk that may be streamed.

typedef struct TEDtalk TEDtalk_t ;

/// Create a TEDtalk_t structure with the supplied arguments and
/// set the time last played to NULL.
/// @param title
/// @param creator

TEDtalk_t * newTEDtalk( char * title, char * creator);

/// delete the instance
/// @param item

void tedtalkDelete( TEDtalk_t * item);

/// @param item the talk
/// @param other the other talk to compare to item
/// @return non-zero(true) iff speaker and title are equivalent

bool tedtalkEquals( const TEDtalk_t * item, const TEDtalk_t * other );

/// @param item the talk
/// @return a copy of the talk

TEDtalk_t * tedtalkCopy( const TEDtalk_t * item);

/// @param item the talk
/// @return a c string pointer to the speaker/author of the talk

char * tedtalkGetSpeaker( const TEDtalk_t * item);

/// @param item the talk
/// @return title of the talk as a c string

char * tedtalkGetTitle( const TEDtalk_t * item);

/// record the last time tedtalk played (NULL if never)
/// @param item the talk
/// @param time of the streaming event

void tedtalkPlay( TEDtalk_t * item, EventTime_t * time);

/// @param item the talk
/// @return pointer to the streaming event time, if any; otherwise NULL.

EventTime_t * tedtalkGetLastPlayed( const TEDtalk_t * item);

/// @param item the talk
/// @return c string representation of the item

char * tedtalkToString( const TEDtalk_t * item);

#endif

