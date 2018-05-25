// ============================================================================
// ======================== INCLUDES ==========================================
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ============================================================================
// ======================== MACRO & CONSTANTS =================================
// ============================================================================

// difference between uppercase and lower case letters
#define SHIFT_VAL   ('a'-'A')

// Stupid macro definition
#define ever        (;;)
#define forever     for ever

// vowels and consonants tables
const char vowels[] = { 'a', 'e', 'i', 'o', 'u', 'y' };
const char consonants[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z' };
// test message string for character manipulation
const char mesage_str[] = "i think you know my point about inline if operations : it only obfuscates the code.";

// ============================================================================
// ======================== PROTOTYPES ========================================
// ============================================================================

bool is_a_vowel( char letter_to_analyse );
int calculate_vowel_translation( char vowel, unsigned char *p_out_buffer, int *p_offset );

// ============================================================================
// ======================== FUNCTIONS =========================================
// ============================================================================

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
  * @brief Translation loop function
  * @param [in] input    String that contains the original message
  * @param [out] output  Buffer in which we would write the resulting string
  * @return An int value :<br>
  *           - 0 if everything is OK <br>
  *           - (-1) if process ends in error
  */
int translate_into_obscure( char *input, unsigned char *output )
{
    // local variable init
    int i = 0;
    int offset = 0;

    // translation loop
    for( i = 0 ; i < sizeof(mesage_str) ; i++ )
    {
        if( is_a_vowel( mesage_str[ i ] ) ) // check if letter is a vowel
        {
            calculate_vowel_translation( mesage_str[ i ], &output[ offset ], &offset );
        }
        else
        {
            //! @todo Work In Progress : calculate consonant translation
        }
    }

    return 0;
}

/**
  * @brief Main program function
  */
int main( int argC, char **argV )
{
    unsigned char output_buff[ 256 ];
    // buffer init
    memset( output_buff, 0x00, sizeof(output_buff) );

    /**
      * @todo Work in Progress : Add conditionnal fork:
      *         - if there are arguments in the program call, just translates
      *           the input string and exit (or print error message)
      *         - if there is no argument, go to the infinite loop to use the
      *           program until asked to quit
      */
    if( argC > 0 )
    {
        // translate input string
        printf( "%s\n", argV[ 0 ] );  //! @remark print which option has been chosen (encode or decode) (this line is only here for debug)
        printf( "%s\n", argV[ 1 ] );  //! @remark just print the input string for now (translation part of the program is not finished)

        // jump to end of programm
        goto exit_program;
    }


    // forever loop
    forever
    {
        printf( "Exit [yes/no] ? " );
        memset( output_buff, 0x00, sizeof(output_buff) );
        scanf( "%s", (char *)output_buff );
        if( strncmp( (const char *)output_buff, "yes", strlen("yes") ) == 0 )
        {
            break;
        }
    }

exit_program:
    // print linebreak to have next shell command on a new line
    printf("\n");
    return 0;
}
