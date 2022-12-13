//// readcsv reads a csv file
//// written by: Miguel Dias Pinto
////             md2383@rit.edu
////
//// comment: Grader last time asked 'what happened?' bc code wasn't finished, 
////          if grader is the same, I  got caught up on work and didn't get to
////          finish so I decided to start working on it earlier :D. Have a good day!
////

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//main function runs the whole program
int main(){
    int numZipCodes = 0;            //the Total number of zipcodes parsed in
    int currentZip = 0;             //the ZipCode currently being looked at
    int totalPopulation = 0;        //the total population of ALL the zipcodes
    int fewestPeople = INT_MAX;     //smallest population size in a zipcode
    int fewestPeopleZip = 0;        //Zipcode with the smallest population size
    int mostPeople = 0;             //largest population size in a zipcode
    int mostPeopleZip = 0;          //Zipcode with the largest population size

    char tempString[256];           //Used to store input
    char *eptr;                     //Pointer for the input
    
    //Fgets takes input using stdin
    fgets( tempString, 256, stdin );
    while(fgets( tempString, 256, stdin )){
        numZipCodes++;
        int num;
        currentZip = 0;
        eptr = tempString;      //set pointer

        //For loop loops for each 'split' value in input
        for(int i = 0; i < 7; i++, eptr++){
            
            //Skip through anything that isn't ZipCode or Population
            if(i > 1){
                strtof(eptr, &eptr);
                continue;
            }
            
            num = (int) strtoll(eptr, &eptr,10);    //temporarily store the next set of data
            
            if( i == 0 && !(num == 0)) {            //at i=0, first value is a zipcode, so we sasve it into 'currentZip'
                currentZip = num;
                strtof(eptr, &eptr);
            }
            else if(i == 1 && num != currentZip){   //at i=1, value is population
                totalPopulation += num;
                if (num > mostPeople){              //compare current population with the most populated. If larger then replace both population number AND zipcode.
                    mostPeople = num;
                    mostPeopleZip = currentZip;
                }
                if(num < fewestPeople){             //compare current population with the least populated. If smaller, then replace both population number AND zipcode. 
                    fewestPeople = num;
                    fewestPeopleZip = currentZip;
                }
            }
        }
    }

    //print statements print out like in the sample output's
    printf("Total population across %d zipcodes is %d. \n", numZipCodes, totalPopulation);
    printf("The fewest people live in %d, population %d. \n", fewestPeopleZip, fewestPeople);
    printf("The most people live in %d, population %d. \n", mostPeopleZip, mostPeople);

}
