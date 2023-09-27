// File: $Id: ahnentafel.c
//
// Project 1: Ahnentafel Relation Tree
// Author: rwd, sps

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ahnentafel.h"

/**
 * Convert a decimal number to binary string
 *
 * @param decimal The decimal number to convert
 * @param binary  The output buffer to store binary as a string
 */
void decimalToBinary(int decimal, char* binary) {
    int index = 0;
    while (decimal > 0) {
        binary[index++] = (decimal % 2) + '0';
        decimal /= 2;
    }
    binary[index] = '\0';

    // Reverse the binary string
    int length = index;
    for (int i = 0; i < length / 2; i++) {
        char temp = binary[i];
        binary[i] = binary[length - i - 1];
        binary[length - i - 1] = temp;
    }
}

/**
 * Convert a binary string to a decimal number
 *
 * @param binary The binary string to convert
 * @return The decimal number
 */
int binaryToDecimal(const char* binary) {
    int decimal = 0;
    for (int i = 0; binary[i] != '\0'; i++) {
        decimal = decimal * 2 + (binary[i] - '0');
    }
    return decimal;
}

/**
 * Calculate the number of generations back based on the given ahnentafel number
 *
 * @param ahnentafel The ahnentafel number
 * @return The number of generations back
 */
int calculateGenerations(int ahnentafel) {
    int generations = 0;
    while (ahnentafel > 1) {
        if (ahnentafel % 2 == 0) {
            ahnentafel /= 2;
        } else {
            ahnentafel = (ahnentafel - 1) / 2;
        }
        generations++;
    }
    return generations;
}


void displayDescription() {
    printf("The Ahnentafel number is used to determine the relation\n");
    printf("between an individual and each of his/her direct ancestors.\n");
}

void convertBase10ToBase2(int decimal) {

    int originalDecimal = decimal;

    char binary[MAX_INPUT_LENGTH];
    decimalToBinary(decimal, binary);

    printf("ahnentafel number in binary: %s\n", binary);

    printf("family relation: ");
    if (decimal == 1) {
        printf("self");
    } else {
        int generations = calculateGenerations(originalDecimal); 
        for (int i = 0; i < generations - 1; i++) {
            if (decimal % 2 == 0) {
                printf("father's ");
                decimal /= 2;
            } else {
                printf("mother's ");
                decimal = (decimal - 1) / 2;
            }
        }
        if (generations > 0) {
            if (decimal % 2 == 0) {
                printf("father");
            } else {
                printf("mother");
            }
        }
    }

    printf("\ngenerations back: %d\n", calculateGenerations(originalDecimal)); 
}


void convertBase2ToBase10(char binary[MAX_INPUT_LENGTH]) {

    int decimal = binaryToDecimal(binary);
    int originalDecimal = decimal;

    printf("base-10 value: %d\n", decimal);

    printf("family relation: ");
    if (decimal == 1) {
        printf("self");
    } else {
        int generations = calculateGenerations(originalDecimal); 
        for (int i = 0; i < generations - 1; i++) {
            if (decimal % 2 == 0) {
                printf("father's ");
                decimal /= 2;
            } else {
                printf("mother's ");
                decimal = (decimal - 1) / 2;
            }
        }
        if (generations > 0) {
            if (decimal % 2 == 0) {
                printf("father");
            } else {
                printf("mother");
            }
        }
    }

    printf("\ngenerations back: %d\n", calculateGenerations(originalDecimal)); // Use the original decimal value
}

void displayRelation(char relation[MAX_INPUT_LENGTH]) {
    // Convert the relation to lowercase for easier comparison
    for (int i = 0; relation[i] != '\0'; i++) {
        relation[i] = tolower(relation[i]);
    }

    int decimal = 1; // Start with the base individual

    for (int i = 0; relation[i] != '\0'; i++) {
        if (relation[i] == 'f') {
            decimal = (decimal << 1); // Double the decimal value for each 'f'
        } else if (relation[i] == 'm') {
            decimal = (decimal << 1) + 1; // Double the decimal value and add 1 for 'm'
        }
    }
    
    decimal = decimal - 1;

    char binary[MAX_INPUT_LENGTH];
    decimalToBinary(decimal, binary);

    printf("ahnentafel number in binary: %s\n", binary);
    printf("ahnentafel number in base-10: %d\n", decimal);
    printf("generations back: %d\n", calculateGenerations(decimal));
}



int main(int argc, char* argv[]) {
    if (argc < 2) {
        // No command line arguments provided, display the menu and prompt for user input
        int choice;

        while (choice != 5) {
            printf("1) description\n");
            printf("2) ahnentafel number (base 10)\n");
            printf("3) ahnentafel number (base 2)\n");
            printf("4) relation (e.g., mother's mother's father)\n");
            printf("5) exit\n");
            printf("> ");
            scanf("%d", &choice);
            printf("\n");
            switch (choice) {
                case 1:
                    displayDescription();
                    break;
                case 2: {
                    int decimal;
                    printf("Enter the ahnentafel number in base-10: ");
                    scanf("%d", &decimal);
                    convertBase10ToBase2(decimal);
                    break;
                }
                case 3: {
                    char binary[MAX_INPUT_LENGTH];
                    printf("Enter the ahnentafel number in binary: ");
                    scanf("%s", binary);
                    convertBase2ToBase10(binary);
                    break;
                }
                case 4: {
                    char relation[MAX_INPUT_LENGTH];
                    printf("Enter family relation (e.g., \"father's mother\"): ");
                    scanf(" %[^\n]", relation);
                    displayRelation(relation);
                    break;
                }
                case 5:
                    printf("Exiting the program.\n");
                    break;
                default:
                    printf("Unknown operation!\n");
                    break;
            }
            printf("\n");
        }
    } else {
        // Command line arguments given
        if (argc == 2) {
            // Check if argument is binary
            char* binary = argv[1];
            if (strlen(binary) > 1 && binary[strlen(binary) - 1] == 'b') {
                binary[strlen(binary) - 1] = '\0';
                convertBase2ToBase10(binary);
            } else {
                // Treat argument as decimal
                int decimal = atoi(argv[1]);
                convertBase10ToBase2(decimal);
            }
        } else if (argc > 2) {
            // Combine multiple arguments into one string
            char relation[MAX_INPUT_LENGTH];
            strcpy(relation, argv[1]);
            for (int i = 2; i < argc; i++) {
                strcat(relation, " ");
                strcat(relation, argv[i]);
            }
            displayRelation(relation);
        } else {
            printf("Unknown operation!\n");
        }
    }

    return EXIT_SUCCESS;
}
