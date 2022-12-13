///Miguel Dias Pinto md2383
///CS243 - hw7

#include <stdio.h>    // size_t type
#include <string.h>   // C strings
#include <stdint.h>   // uint64_t type
#include <stdlib.h>   // for calloc

const size_t SETSIZE = sizeof( uint64_t ) << 3 ;
const size_t BUFSIZE = 256;

//function shift getting the number to shift by character
//@param c
//@return number to shift by
int shift(char c){
    if(c == '0'){
        return 63;
    }
    if(c == '1'){
        return 62;
    }
    if(c == '2'){
        return 61;
    }
    if(c == '3'){
        return 60;
    }
    if(c == '4'){
        return 59;
    }
    if(c == '5'){
        return 58;
    }
    if(c == '6'){
        return 57;
    }
    if(c == '7'){
        return 56;
    }
    if(c == '8'){
        return 55;
    }
    if(c == '9'){
        return 54;
    }
    if(c == '.'){
        return 53;
    }
    if(c == 'a'){
        return 52;
    }
    if(c == 'b'){
        return 51;
    }
    if(c == 'c'){
        return 50;
    }
    if(c == 'd'){
        return 49;
    }
    if(c == 'e'){
        return 48;
    }
    if(c == 'f'){
        return 47;
    }
    if(c == 'g'){
        return 46;
    }
    if(c == 'h'){
        return 45;
    }
    if(c == 'i'){
        return 44;
    }
    if(c == 'j'){
        return 43;
    }
    if(c == 'k'){
        return 42;
    }
    if(c == 'l'){
        return 41;
    }
    if(c == 'm'){
        return 40;
    }
    if(c == 'n'){
        return 39;
    }
    if(c == 'o'){
        return 38;
    }
    if(c == 'p'){
        return 37;
    }
    if(c == 'q'){
        return 36;
    }
    if(c == 'r'){
        return 35;
    }
    if(c == 's'){
        return 34;
    }
    if(c == 't'){
        return 33;
    }
    if(c == 'u'){
        return 32;
    }
    if(c == 'v'){
        return 31;
    }
    if(c == 'w'){
        return 30;
    }
    if(c == 'x'){
        return 29;
    }
    if(c == 'y'){
        return 28;
    }
    if(c == 'z'){
        return 27;
    }
    if(c == ','){
        return 26;
    }
    if(c == 'A'){
        return 25;
    }
    if(c == 'B'){
        return 24;
    }
    if(c == 'C'){
        return 23;
    }
    if(c == 'D'){
        return 22;
    }
    if(c == 'E'){
        return 21;
    }
    if(c == 'F'){
        return 20;
    }
    if(c == 'G'){
        return 19;
    }
    if(c == 'H'){
        return 18;
    }
    if(c == 'I'){
        return 17;
    }
    if(c == 'J'){
        return 16;
    }
    if(c == 'K'){
        return 15;
    }
    if(c == 'L'){
        return 14;
    }
    if(c == 'M'){
        return 13;
    }
    if(c == 'N'){
        return 12;
    }
    if(c == 'O'){
        return 11;
    }
    if(c == 'P'){
        return 10;
    }
    if(c == 'Q'){
        return 9;
    }
    if(c == 'R'){
        return 8;
    }
    if(c == 'S'){
        return 7;
    }
    if(c == 'T'){
        return 6;
    }
    if(c == 'U'){
        return 5;
    }
    if(c == 'V'){
        return 4;
    }
    if(c == 'W'){
        return 3;
    }
    if(c == 'X'){
        return 2;
    }
    if(c == 'Y'){
        return 1;
    }
    if(c == 'Z'){
        return 0;
    }
    return -1;
}

///function unshift takes in shifts and returns the character
///@param c
///@return character
char unshift(int c){
    if(c == 63){
        return '0';
    }
    if(c == 62){
        return '1';
    }
    if(c == 61){
        return '2';
    }
    if(c == 60){
        return '3';
    }
    if(c == 59){
        return '4';
    }
    if(c == 58){
        return '5';
    }
    if(c == 57){
        return '6';
    }
    if(c == 56){
        return '7';
    }
    if(c == 55){
        return '8';
    }
    if(c == 54){
        return '9';
    }
    if(c == 53){
        return '.';
    }
    if(c == 52){
        return 'a';
    }
    if(c == 51){
        return 'b';
    }
    if(c == 50){
        return 'c';
    }
    if(c == 49){
        return 'd';
    }
    if(c == 48){
        return 'e';
    }
    if(c == 47){
        return 'f';
    }
    if(c == 46){
        return 'g';
    }
    if(c == 45){
        return 'h';
    }
    if(c == 44){
        return 'i';
    }
    if(c == 43){
        return 'j';
    }
    if(c == 42){
        return 'k';
    }
    if(c == 41){
        return 'l';
    }
    if(c == 40){
        return 'm';
    }
    if(c == 39){
        return 'n';
    }
    if(c == 38){
        return 'o';
    }
    if(c == 37){
        return 'p';
    }
    if(c == 36){
        return 'q';
    }
    if(c == 35){
        return 'r';
    }
    if(c == 34){
        return 's';
    }
    if(c == 33){
        return 't';
    }
    if(c == 32){
        return 'u';
    }
    if(c == 31){
        return 'v';
    }
    if(c == 30){
        return 'w';
    }
    if(c == 29){
        return 'x';
    }
    if(c == 28){
        return 'y';
    }
    if(c == 27){
        return 'z';
    }
    if(c == 26){
        return ',';
    }
    if(c == 25){
        return 'A';
    }
    if(c == 24){
        return 'B';
    }
    if(c == 23){
        return 'C';
    }
    if(c == 22){
        return 'D';
    }
    if(c == 21){
        return 'E';
    }
    if(c == 20){
        return 'F';
    }
    if(c == 19){
        return 'G';
    }
    if(c == 18){
        return 'H';
    }
    if(c == 17){
        return 'I';
    }
    if(c == 16){
        return 'J';
    }
    if(c == 15){
        return 'K';
    }
    if(c == 14){
        return 'L';
    }
    if(c == 13){
        return 'M';
    }
    if(c == 12){
        return 'N';
    }
    if(c == 11){
        return 'O';
    }
    if(c == 10){
        return 'P';
    }
    if(c == 9){
        return 'Q';
    }
    if(c == 8){
        return 'R';
    }
    if(c == 7){
        return 'S';
    }
    if(c == 6){
        return 'T';
    }
    if(c == 5){
        return 'U';
    }
    if(c == 4){
        return 'V';
    }
    if(c == 3){
        return 'W';
    }
    if(c == 2){
        return 'X';
    }
    if(c == 1){
        return 'Y';
    }
    if(c == 0){
        return 'Z';
    }
    return -1;
}

///function file_set_encode encodes from file
///@param fp
///@return returns an encoded unsigned long int
uint64_t file_set_encode( FILE * fp ){
    uint64_t result = 0x0;
    if(!feof(fp)){
        char st;
        while(!feof(fp)){
            st = getc(fp);
            int shifted = shift(st);
            if(shifted != -1){
                result = result | ((uint64_t) 1 << shifted);
            }
        }
        return result;
    }
    return 0x0;
}

///function set_encode encodes from a char *
///@param st
///@return returns an encoded unsigned long int
uint64_t set_encode( char * st ){
    uint64_t result = 0x0;
    if(st != NULL){
        for(int i = 0; i < (int) strlen(st); i++){
            int shifted = shift(st[i]);
            if(shifted != -1){
                result = result | ((uint64_t) 1 << shifted);
            }
        }
        return result;
    }
    return 0x0;
}

///function set_intersect intersects two different sets
///@param set1 set2
///@return intersect of set1 and set2
uint64_t set_intersect( uint64_t set1, uint64_t set2 ){
    return set1 & set2;
}

///function set_union creates a union from two different sets
///@param set1 set2
///@return union of set1 and set2
uint64_t set_union( uint64_t set1, uint64_t set2 ){
    return set1 | set2;
}

///function set_complement creates a complement of the set given
///@param set1
///@return complement of set1
uint64_t set_complement( uint64_t set1 ){
    return ~set1;
}

///function set_difference is the difference between set1 and set2
///@param set1 set2
///@return difference of set1 and set2
uint64_t set_difference( uint64_t set1, uint64_t set2 ){
    return set1 & ~set2;
}

///function set_symdifference is the symdifference between set1 and set2
///@param set1 set2
///@return symdifference of set1 and set2
uint64_t set_symdifference( uint64_t set1, uint64_t set2 ){
    return set1 ^ set2;
}

///function set_cardinality gets the cardinality using the given set
///@param set
///@return cardinality of set
size_t set_cardinality( uint64_t set ){
    size_t result = 0;
    for(int i = 0; i < 64; i++){
        uint64_t temp = 0x0;
        temp = temp | ((uint64_t) 1 << i);
        if(temp == set_intersect(set, temp)){
            result += 1;
        }
    }
    return result;
}

///function set_decode decodes the given unsigned long int and returns the characters represented
///@param set
///@return members of the set
char * set_decode( uint64_t set ){
    char * ptr;
    ptr = (char*)malloc(sizeof(char) * (int)set_cardinality(set));
    int j = 0;
    for(int i = 63; i >= 0; i--){
        uint64_t temp = 0x0;
        temp = temp | ((uint64_t) 1 << i);
        if(temp == set_intersect(set, temp)){
            ptr[j] += unshift(i);
            j++;
        }
    }
    return ptr;
}

///function prints given the usigned long ints
///@param i1 i2
///@return nothing
void printer(uint64_t i1, uint64_t i2){

    printf("set1:\t0x%016lx\n", i1);
    printf("set2:\t0x%016lx\n", i2);
    printf("\n");

    printf("set_intersect:  \t0x%016lx\n", set_intersect(i1, i2));
    printf("set_union:      \t0x%016lx\n", set_union(i1, i2));
    printf("\n");

    printf("set1 set_complement:\t0x%016lx\n", set_complement( i1 ));
    printf("set2 set_complement:\t0x%016lx\n", set_complement( i2 ));
    printf("\n");

    printf("set_difference:     \t0x%016lx\n", set_difference( i1, i2 ));
    printf("set_symdifference:  \t0x%016lx\n", set_symdifference( i1, i2 ));
    printf("\n");

    printf("set1 set_cardinality:   %d\n", (int) set_cardinality( i1 ));
    printf("set2 set_cardinality:   %d\n", (int) set_cardinality( i2 ));
    printf("\n");

    printf("members of set1:    '%s'\n", set_decode( i1 ));
    printf("members of set2:    '%s'\n", set_decode( i2 ));
}

///function main runs the program
///@param argc argv[]
///return 0
int main( int argc, char * argv[]){
    
    if(argc < 2) {
        fprintf( stderr, "Usage: file-bitsets string1 string2\n");
        return EXIT_FAILURE;
    }
        
    FILE *f1 = fopen(argv[1], "r");
    FILE *f2 = fopen(argv[2], "r");

    if(f1 == NULL && f2 == NULL){
        
        printf("string1:    %s\tEncoding the string:    %s\n", argv[1], argv[1]);
        printf("string2:    %s\tEncoding the string:    %s\n", argv[2], argv[2]);
        printf("\n");
        
        uint64_t i1 = set_encode(  argv[1] );
        uint64_t i2 = set_encode(  argv[2] );

        printer( i1 , i2);
    }
    else{
        
        printf("string1:    %s\tEncoding the file:    %s\n", argv[1], argv[1]);
        printf("string2:    %s\tEncoding the file:    %s\n", argv[2], argv[2]);
        printf("\n");
        
        uint64_t i1 = file_set_encode( f1 );
        uint64_t i2 = file_set_encode( f2 );

        printer( i1 , i2);
    }

    free(f1);
    free(f2);

    return 0;
}
