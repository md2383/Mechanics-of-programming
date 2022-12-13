///@author: Miguel Dias Pinto md2383


#include <stdio.h>
#include <stdlib.h>

#include "trie.c"
#include "trie.h"

///Converts Numbers into IPV4 addresses.
///@param ip
///@return xxx.xxx.xxx.xxx
char * InttoIPV4(u_int64_t ip){
    u_int64_t bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;
    char *c = (char *)malloc(sizeof(bytes) + sizeof(char)*3);
    sprintf(c, "%ld.%ld.%ld.%ld", bytes[0], bytes[1], bytes[2], bytes[3]);
    return c;
}

///Converts IPV4 to long
///@param c
///@return Long number to compare with keys
u_int64_t IPV4toInt(char * c){
    
    u_int64_t oct1, oct2, oct3, oct4 = 0;
    int curr = 1;
    int temp = 0;
    for(int i = 0; i < (int) strlen(c); i++){
        if(c[i] == '.'){
            if(curr == 1){
                oct1 = (u_int64_t) temp;
            }
            else if(curr == 2){
                oct2 = (u_int64_t) temp;
            }
            else if(curr == 3){
                oct3 = (u_int64_t) temp;
            }
            else if(curr == 4){
                oct4 = (u_int64_t) temp;
            }
            curr++;
        }
        else{
            temp *= 10;
            char * ptr = &c[i];
            temp += atoi(ptr);
        }
    } 
    oct1 *= (256 * 256 * 256);
    oct2 *= (256 * 256);
    oct3 *= (256);
    return (u_int64_t) oct1 + oct2 + oct3 + oct4;
}

///Builds an entry with paramaters
///@param ip, code, country, province, city
///@return entry
Entry *buildentry(int ip, char * code, char * country, char * province, char *city){
    Entry *e = (Entry *)malloc(sizeof(Entry));
    e->key = (ikey_t) ip;
    e->givenIP = InttoIPV4(ip);
    e->country_code = code;
    e->country_name = country;
    e->province = province;
    e->city = city;
    return e;
}

///Runs the main function
///@param argc, argv[]
///returns 0
int main( int argc, char * argv[]){

    if( argc < 1 ){
        fprintf( stderr, "Usage: place_ip filename\n");
        return EXIT_FAILURE;
    }

    FILE *f = fopen(argv[1], "r");

    if(f == NULL){
        fprintf(stderr, "ERROR: File not found\n");
        return EXIT_FAILURE;
    }

    Trie t = ibt_create();
    char line[256];
    while(fgets(line, 256, f)){
        char * c = strtok(line, "\",\"");
        int ip1 = atoi(&c[0]);
        int ip2 =atoi(&c[1]);
        char *code = &c[2];
        char *country = &c[3];
        char *province = &c[4];
        char *city = &c[5];
        
        printf("ip1: %d, %s, %s, %s, %s", ip1, code, country, province, city);

        Entry *e1 = buildentry(ip1, code, country, province, city);
        Entry *e2 = buildentry(ip2, code, country, province, city);

        ibt_insert(t, *e1);
        ibt_insert(t, *e2);
    }
    ibt_show(t, stderr);

    fclose(f);

    printf("height: %d\n", (int) ibt_height(t));
    printf("size: %d\n", (int) ibt_size(t));
    printf("node_count: %d\n", (int) ibt_node_count(t));
    printf("\n");
    printf("Enter an IPV4 string or number or blank line to quit\n");
        
    char * input = (char *)malloc(256);
    int num = 0;;
    if((scanf("%s", input) && strcmp(input,"") != 0)){
        if(input[0] == '.' || input[1] == '.' || input[2] == '.' || input[3] == '.'){
            num = (int) IPV4toInt(input);
        }    
        else{
            num = atoi(input);
        }
        Entry e = ibt_search(t, (ikey_t) num);
        ikey_t key = e.key;
        char * givenIP = e.givenIP;
        char * code = e.country_code;
        char * name = e.country_name;
        char * province = e.province;
        char * city = e.city;
        printf("%d: (%s, %s: %s, %s, %s)\n", key, givenIP, code, name, province, city);
    }
    
    ibt_destroy(t);
    free(input);

    return 0;
}
