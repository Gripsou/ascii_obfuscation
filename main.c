// =============================================================================
// ======================== INCLUDES ===========================================
// =============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// =============================================================================
// ======================== MACRO & CONSTANTS ==================================
// =============================================================================

// difference between uppercase and lower case letters
#define SHIFT_VAL   ('a'-'A')

// ---------------------------------------------------------------------------------------------------

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

// ---------------------------------------------------------------------------------------------------

// vowels and consonants tables
const char vowels[] = { 'a', 'e', 'i', 'o', 'u', 'y' };
const char consonants[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z' };
// test message string for character manipulation
const char mesage_str[] = "i think you know my point about inline if operations : it only obfuscates the code.";


// =============================================================================
// ======================== PROTOTYPES =========================================
// =============================================================================

bool is_a_vowel( char letter_to_analyse );
int calculate_vowel_translation( char vowel, unsigned char *p_out_buffer, int *p_offset );

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

// ---------------------------------------------------------------------------------------------------

/**
  * @brief Calculate the translation of a vowel into consonant
  * @param [in] vowel          Vowel character to translate into consonant character
  * @param [out] p_out_buffer  Pointer onto output buffer
  * @param [out] p_offset      Pointer onto offset value to set
  * @return An error value :<br>
  *         - 0 if OK <br>
  *         - (-1) if failure
  */
int calculate_vowel_translation( char vowel, unsigned char *p_out_buffer, int *p_offset )
{
    // declare and init variables
    unsigned char upper_half = '#';
    unsigned char lower_half = '#';

    // determine value of upper_half
    upper_half = ( vowel >> 4 ) & 0x0F;
    /*
     * Lower case letter values should be between 0x61 and 0x7A
     * => upper half byte can only be 0x6 or 0x7
     */
    if( ( upper_half & 0x06 ) || ( upper_half & 0x07 ) )
    {
        // success => nothing to do
    }
    else
    {
        // failure case... exit with error...
        return -1;
    }

    // determine value of lower_half
    lower_half = vowel & 0x0F;

    // set the values of translation into output buffer
    *p_out_buffer = 0x40 & upper_half;
    *(p_out_buffer + 1) = 0x40 & lower_half;
    *p_offset += 2; // update offset value

    return 0;
}

/**
  * @brief Tells if the character given in argument is a vowel or not
  * @param [in] letter_to_analyse  Character that we will tell if its a vowel or not
  * @return A boolean value :<br>
  *         - true  : letter_to_analyse is a vowel <br>
  *         - false : letter_to_analyse is a consonant
  */
bool is_a_vowel( char letter_to_analyse )
{
    int i = 0;
    // loop that parses the vowel table
    for( i = 0 ; i < sizeof(vowels) ; i++ )
    {
        // check that letter_to_analyse is value is the same as one in vowels[] table
        if( vowels[i] == letter_to_analyse )
        {
            // comparison success => vowel found => exit with true
            return true;
        }
    }

    // if we reach this point, then all comparisons failed and letter is not a vowel => exit with false
    return false;
}

/**
  * @brief Main program function
  */
int main( void )
{
    // local variable init
    int i = 0;
    int offset = 0;
    unsigned char output_buff[ 256 ];
    // buffer init
    memset( output_buff, 0x00, sizeof(output_buff) );

    // translation loop
    for( i = 0 ; i < sizeof(mesage_str) ; i++ )
    {
        if( is_a_vowel( mesage_str[ i ] ) ) // check if letter is a vowel
        {
            calculate_vowel_translation( mesage_str[ i ], &output_buff[ offset ], &offset );
        }
        else
        {
            //! @todo Work In Progress ...
        }
    }

    // print linebreak to have next shell command on a new line
    printf("\n");
    return 0;
}
