// File: $Id: ahnentafel.h
//
// Project 1: Ahnentafel Relation Tree
// Author: rwd, sps


#ifndef AHNENTAFEL_H
#define AHNENTAFEL_H

#define MAX_INPUT_LENGTH 50
#define MAX_GENERATIONS 10


/**
 * Convert a decimal number to binary representation.
 *
 * @param decimal The decimal number to convert.
 * @param binary  The output buffer to store the binary representation.
 */
void decimalToBinary(int decimal, char* binary);

/**
 * Convert a binary string to a decimal number.
 *
 * @param binary The binary string to convert.
 * @return The decimal value.
 */
int binaryToDecimal(const char* binary);

/**
 * Calculate the number of generations back based on the given ahnentafel number.
 *
 * @param ahnentafel The ahnentafel number.
 * @return The number of generations back.
 */
int calculateGenerations(int ahnentafel);

#endif /* AHNENTAFEL_H */
