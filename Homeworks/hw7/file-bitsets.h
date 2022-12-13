
#ifndef _FILE-BITSETS_H_
#define _FILE-BITSETS_H_

#include <stdio.h>    // size_t type
#include <string.h>   // C strings
#include <stdint.h>   // uint64_t type

const size_t SETSIZE = sizeof( uint64_t ) << 3 ;
const size_t BUFSIZE = 256;

//
uint64_t file_set_encode( FILE * fp ) ;


uint64_t set_encode( char * st ) ;

//returns the intersect between two sets: set1 and set2
uint64_t set_intersect( uint64_t set1, uint64_t set2 ) ;

//returns the union between two sets: set1 and set2
uint64_t set_union( uint64_t set1, uint64_t set2 ) ;

//returns the complement of set 1
uint64_t set_complement( uint64_t set1 ) ;

//returns the difference between two sets: set1 and set2
uint64_t set_difference( uint64_t set1, uint64_t set2 ) ;

//return the 
uint64_t set_symdifference( uint64_t set1, uint64_t set2 ) ;

//returns the cardinality of the set given
size_t set_cardinality( uint64_t set ) ;


char * set_decode( uint64_t set ) ;

#endif
