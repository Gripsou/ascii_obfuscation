// =============================================================================
// ======================== INCLUDES ===========================================
// =============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "deprecated_functions.h"

// =============================================================================
// ======================== MACRO & CONSTANTS ==================================
// =============================================================================

// String used for bit shifting character function
const char input_table[] = "I think you know my point about inline if operations : it only obfuscates the code.\n";
const char bit_shifted_char_table[] =
{
    0x92, 0x40, 0xe8, 0xd0, 0xd2, 0xdc, 0xd6, 0x40, 0xf2, 0xde, 0xea, 0x40, 0xd6, 0xdc, 0xde, 0xee, 0x40, 0xda, 0xf2,
    0x40, 0xe0, 0xde, 0xd2, 0xdc, 0xe8, 0x40, 0xc2, 0xc4, 0xde, 0xea, 0xe8, 0x40, 0xd2, 0xdc, 0xd8, 0xd2, 0xdc, 0xca,
    0x40, 0xd2, 0xcc, 0x40, 0xde, 0xe0, 0xca, 0xe4, 0xc2, 0xe8, 0xd2, 0xde, 0xdc, 0xe6, 0x40, 0x74, 0x40, 0xd2, 0xe8,
    0x40, 0xde, 0xdc, 0xd8, 0xf2, 0x40, 0xde, 0xc4, 0xcc, 0xea, 0xe6, 0xc6, 0xc2, 0xe8, 0xca, 0xe6, 0x40, 0xe8, 0xd0,
    0xca, 0x40, 0xc6, 0xde, 0xc8, 0xca, 0x5c
};

// =============================================================================
// ======================== FUNCTIONS ==========================================
// =============================================================================

/*
 * First example of string obfuscation : Shift letters from upper case to lower case
 * and the other way around.
 * Does not really obfuscate anything.
 */

/**
  * @brief Shift letters from upper case to lower case or from lower case to upper case
  */
void shift_letters( void )
{
    // declare variable
    int i = 0;
    char user_input[ 256 ];
    // initialize buffer
    memset( user_input, 0x00, sizeof(user_input) );
    // init is finished, say hello
    printf( "Hello world!\n" );
    // Ask user for a string
    printf( "Please enter a sentence :\n> " );
    scanf( "%s", user_input );
    // for loop to shift value of characters
    for( i = 0 ; ( i < sizeof(user_input) ) && ( user_input[i] != 0x00 ) ; i++ )
    {
        if( ( user_input[ i ] >= 'a' ) && ( user_input[ i ] <= 'z' ) )
        {
            user_input[ i ] = user_input[ i ] - SHIFT_VAL;
        }
        else if( ( user_input[ i ] >= 'A' ) && ( user_input[ i ] <= 'Z' ) )
        {
            user_input[ i ] = user_input[ i ] + SHIFT_VAL;
        }
        else
        {
            user_input[ i ] = '~';
        }
    }

    // if max size is not reached, then add '\n'
    if( i < sizeof(user_input) )
    {
        user_input[ i ] = '\n';
    }

    // print the result
    printf( user_input );
}

// ---------------------------------------------------------------------------------------------------

/*
 * Second example of string obfuscation : bit shift character in the ASCII table
 * Makes it completely unreadable but, can be a problem when trying to decode it because of the format.
 */

/**
  * @brief Bit shifts a string of character to make it unreadable
  */
void character_bit_shifting( void )
{
    // variable init
    int i = 0;
    unsigned char output_table[ sizeof(input_table) ];
    // init buffer
    memset( output_table, 0x00, sizeof(output_table) );
    // print input table
    printf( input_table );
    // shift all bytes of the string by one bit
    for( i = 0 ; i < sizeof(output_table) ; i++ )
    {
        output_table[ i ] = (unsigned char)input_table[ i ] << 1;
    }

    // print input table after bit-shifting
    printf( (char *)output_table );
    printf( "\n" );
    for( i = 0 ; i < sizeof(output_table) ; i++ )
    {
        printf( "0x%02x ", (unsigned char)output_table[ i ] );
    }

    printf("\n");
}
