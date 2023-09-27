// EventTime.c
//
// Implementation of the EventTime  functions.
//
// @author CS instructors

#include <stdlib.h>
#include <stdio.h>

#include "EventTime.h"

/// allocates space for a new  event time structure, copies
/// the tod string passed in

EventTime_t * newEventTime( int hour, int min, char *tod ) {
    char *mtod ;
    mtod = malloc(3 * sizeof(char)) ;   // tod is always two characters
    EventTime_t *t = malloc(sizeof(EventTime_t)) ;

    // verify hour, minute and tod values
    hour = hour % 12 ;
    if (0 == hour)
    {
        hour = 12 ;
    }
    min = min % 60 ;

    // verify that the tod is "am" or "pm"
    if ((0 != strcmp(tod, "am")) && (0 != strcmp(tod, "pm")))
    {
        strcpy(mtod, "xm") ;
    }
    else
    {
        strcpy(mtod, tod) ;
    }

    // initialize structure
    t->hour = hour ;
    t->min = min ;
    t->timeofday = malloc((strlen(mtod) + 1) * sizeof(char)) ;
    strcpy(t->timeofday, mtod) ;

    // clean up before leaving
    free(mtod) ;

    return t ;
}

/// time destructor

void timeDelete(EventTime_t *t) {
    free(t->timeofday) ;   // has to be done explicitly
    free(t) ;
}

/// copy a time structure

EventTime_t * timeCopy(const EventTime_t *src) {
    EventTime_t *dest = NULL ;

    dest = malloc(sizeof(EventTime_t )) ;

    dest->hour = src->hour ;
    dest->min = src->min ;
    dest->timeofday = malloc((strlen(src->timeofday) + 1) * sizeof(char)) ;
    strcpy(dest->timeofday, src->timeofday) ;

    return dest ;
}

/// getHour

int timeGetHour(const EventTime_t *t) {
    return t->hour;
}

/// getMinute

int timeGetMinute(const EventTime_t *t) {
  return t->min;
}

/// getTOD

char * timeGetTOD(const EventTime_t *t) {
    return t->timeofday ;
}

///  timeToString - convert the contents of an EventTime_t structure
///                 to a string representation
/// allocates space for the string

char *timeToString(const EventTime_t *t) {

    char *tstr = NULL ;

    // allocate enough space for the time as a string
    tstr = malloc((2 + 1 + 2 + 2 + 1) * sizeof(char)) ;

    // put the string together
    sprintf(tstr, "%2d:%02d%s", timeGetHour(t), timeGetMinute(t),
            t->timeofday) ;

    return tstr ;
}

