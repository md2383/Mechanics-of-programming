// File: EventTime.c 
// 
// Description: Representation of the time an event happened
// @author      RIT CS Instructors
// 
// // // // // // // // // // // // // // // // // // // // // // // // 

#ifndef EVENTTIME_H
#define EVENTTIME_H

#include <string.h>

typedef struct EventTime { ///< structure for the time of an event
    int hour;              ///< start hour
    int min;               ///< start minute
    char * timeofday;      ///< start text of the time of day
} EventTime_t ;

/// construct and initialize a time structure
/// @param hour an event's hour of delivery/presentation
/// @param min an event's hour of delivery/presentation
/// @param tod text for the time of day
/// @return pointer to a new event time instance

EventTime_t * newEventTime( int hour, int min, char * tod ) ;

/// delete the event time structure
/// @param t an event time instance pointer

void timeDelete( EventTime_t * t ) ;

/// copy a time creating space if needed.
/// @param src an event time instance pointer
/// @return pointer the copy to a new event time instance

EventTime_t * timeCopy( const EventTime_t * src );

/// @param t an event time instance pointer
/// @return this time's hour

int timeGetHour( const EventTime_t * t );

/// @param t an event time instance pointer
/// @return this time's minutes

int timeGetMinute( const EventTime_t * t );

/// @param t an event time instance pointer
/// @return this time's am/pm status

char * timeGetTOD( const EventTime_t * t );

/// @param t an event time instance pointer
/// @return a string representation of the time

char * timeToString( const EventTime_t * t ) ;

#endif

