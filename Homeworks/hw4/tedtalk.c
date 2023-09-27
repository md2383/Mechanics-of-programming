// File: tedtalk.c 
// 
// Description: Representation of a TEDtalk
// @author      RIT CS Instructors
// 
// // // // // // // // // // // // // // // // // // // // // // // // 

//
// Content supplied to the student.
//

#include <stdio.h>
#include <string.h>

#include "EventTime.h"

/// TEDtalk structure is private to the .c file.

struct TEDtalk {
     char  * speaker;
     char  * title;
     EventTime_t * lastPlayed;
};

/// Note: The TEDtalk_t typedef is defined in the .h file

#include "tedtalk.h"

/// Initialize a TEDtalk_t structure with the given values.

TEDtalk_t * newTEDtalk(char * t, char * a) {

    TEDtalk_t * m = NULL;
 
    m = malloc(sizeof(TEDtalk_t));

    m->speaker = malloc(sizeof(a) + 1);
    strcpy(m->speaker, a);

    m->title = malloc(sizeof(t) + 1);
    strcpy(m->title, t);

    m->lastPlayed = NULL;

    return m;
}

/// delete the talk

void tedtalkDelete(TEDtalk_t * m) {

    //speaker
    free(m->speaker);
    //title
    free(m->title);
    //time
    if (NULL != m->lastPlayed) {
        timeDelete(m->lastPlayed);
    }
}

/// get the talk's speaker

char * tedtalkGetSpeaker( const TEDtalk_t * m) {
    char * tmp = NULL;
    tmp = malloc(strlen(m->speaker)+1);
    strcpy(tmp, m->speaker);
    return tmp;
}

/// get the talk's title

char * tedtalkGetTitle( const TEDtalk_t * m) {
    char * tmp = NULL;
    tmp = malloc(strlen(m->title)+1);
    strcpy(tmp, m->title);
    return tmp;
}

/// get the talk's last play time

EventTime_t * tedtalkGetLastPlayed( const TEDtalk_t * m) {
    EventTime_t * tmp = NULL;
    tmp = timeCopy(m->lastPlayed);
    return tmp;
}

/// play or show the talk

void tedtalkPlay(TEDtalk_t * m, EventTime_t * t) {
    if (NULL != m->lastPlayed) {
        free(m->lastPlayed);
    }
    m->lastPlayed = t;
}

/// compare 2 instances for equivalence (equivalent field values)

bool tedtalkEquals( const TEDtalk_t * m, const TEDtalk_t * o) {
    // Two tedtalks are equal if their titles and speakers are equal
    if ((NULL != m) && (NULL != o)) {
        if ((0 == strcmp(m->speaker, o->speaker)) &&
            (0 == strcmp(m->title, o->title))) {
            return true;
        }
    }
    return false;
}

/// make a complete copy of the talk

TEDtalk_t * tedtalkCopy( const TEDtalk_t * m) {
    TEDtalk_t * d = NULL;
    EventTime_t * tmp = NULL;

    d = malloc(sizeof(TEDtalk_t));

    d->speaker = malloc(sizeof(m->speaker) + 1);
    strcpy(d->speaker, m->speaker);

    d->title = malloc(sizeof(m->title) + 1);
    strcpy(d->title, m->title);

    if (NULL != m->lastPlayed) {
        // copy the last played
        tmp = timeCopy(m->lastPlayed);
        d->lastPlayed = tmp;
    } else {
        // set lastPlayed to NULL
        d->lastPlayed = NULL;
    }

    return d;
}

/// create a string representation

char * tedtalkToString( const TEDtalk_t * m) {
    char * sstr = NULL;
    char * st = NULL;
    char * sd = NULL;
    char * tt = NULL;
    int len = 0;

    st = tedtalkGetTitle(m);
    sd = tedtalkGetSpeaker(m);

    // calculate the total string length needed.
    len = strlen("Title: ") + strlen(st) +
                  strlen("  Speaker: ") + strlen(sd) + 1;

    if (NULL != m->lastPlayed) {
        tt = timeToString(m->lastPlayed);
        len += strlen(" at ") + strlen(tt);
    }

    // allocate enough space for the tedtalk
    sstr = malloc( len );

    sprintf(sstr, "Title: %s  Speaker: %s", st, sd);

    if (NULL != m->lastPlayed) {
        sstr = strcat(sstr, " at ");
        sstr = strcat(sstr, tt);
    }

    free(sd);
    free(st);
    free(tt);
    return sstr;
}

