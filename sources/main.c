/**
  * @title ascii_obfuscation
  * @verbatim
                                                       __          ___                                   __                            
                             __   __                  /\ \       / ___\                                 /\ \__  __                     
      __       ____    ___  /\_\ /\_\             ___ \ \ \____ /\ \__/  __  __    ____    ___      __  \ \ ,_\/\_\     ___     ___    
    / __`\    / ,__\  / ___\\/\ \\/\ \           / __`\\ \  __`\\ \  __\/\ \/\ \  / ,__\  / ___\  / __`\ \ \ \/\/\ \   / __`\ /  _ `\  
   /\ \_\.\_ /\__, `\/\ \__/ \ \ \\ \ \         /\ \_\ \\ \ \_\ \\ \ \_/\ \ \_\ \/\__, `\/\ \__/ /\ \_\.\_\ \ \_\ \ \ /\ \_\ \/\ \/\ \ 
   \ \__/.\_\\/\____/\ \____\ \ \_\\ \_\        \ \____/ \ \____/ \ \_\  \ \____/\/\____/\ \____\\ \__/.\_\\ \__\\ \_\\ \____/\ \_\ \_\
    \/__/\/_/ \/___/  \/____/  \/_/ \/_/  _______\/___/   \/___/   \/_/   \/___/  \/___/  \/____/ \/__/\/_/ \/__/ \/_/ \/___/  \/_/\/_/
                                         /\______\                                                                                     
                                         \/______/                                                                                     
  * @endverbatim
  */

// ============================================================================
// ======================== INCLUDES ==========================================
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iso646.h>  // allows to use 'and', 'or', 'xor' keywords instead of '&&', '||' symbols
#ifdef __unix__
    #include <unistd.h>
#else
    #include <windows.h>
#endif // __unix__

// ============================================================================
// ======================== MACRO & CONSTANTS =================================
// ============================================================================

// difference between uppercase and lower case letters
#define UPPERCASE_LOWERCASE_SHIFT   ('a'-'A')

// Stupid macro definition
#define ever        (;;)
#define forever     for ever    //! equivalent to for(;;)... I thought it would be fun, but it's still very stupid

// Define error codes to avoid using magic numbers
enum error_codes
{
    GENERIC_ERROR   = -1,
    RETURN_OK       = 0,
};

// vowels and consonants tables
const char vowels[] = { 'a', 'e', 'i', 'o', 'u', 'y' };
const char consonants[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z' };
// test message string for character manipulation
const char message_str[] = "i think you know my point about inline if operations : it only obfuscates the code.";
const char title_str[] = \
    "                                 _/  _/                _/            _/_/                                            _/      _/                  \n"
    "    _/_/_/    _/_/_/    _/_/_/                _/_/    _/_/_/      _/      _/    _/    _/_/_/    _/_/_/    _/_/_/  _/_/_/_/        _/_/    _/_/_/ \n"
    " _/    _/  _/_/      _/        _/  _/      _/    _/  _/    _/  _/_/_/_/  _/    _/  _/_/      _/        _/    _/    _/      _/  _/    _/  _/    _/\n"
    "_/    _/      _/_/  _/        _/  _/      _/    _/  _/    _/    _/      _/    _/      _/_/  _/        _/    _/    _/      _/  _/    _/  _/    _/ \n"
    " _/_/_/  _/_/_/      _/_/_/  _/  _/        _/_/    _/_/_/      _/        _/_/_/  _/_/_/      _/_/_/    _/_/_/      _/_/  _/    _/_/    _/    _/  \n"
    "                                  _/_/_/_/                                                                                                       \n";

// ============================================================================
// ======================== PROTOTYPES ========================================
// ============================================================================

bool is_a_vowel( char letter_to_analyse );
int shift_letter( char character_to_shift, char *p_result_character );
int calculate_vowel_translation( char vowel, unsigned char *p_out_buffer, unsigned int *p_offset );
int calculate_consonant_translation( char consonant, unsigned char *p_out_buffer, unsigned int *p_offset );

// ============================================================================
// ======================== FUNCTIONS =========================================
// ============================================================================

/**
  * @brief Shift letters from upper case to lower case or from lower case to upper case
  * @param [in] character_to_shift   Character to shift
  * @param [out] p_result_character  Pointer onto resulting character
  * @return An int error code value :<br>
  *         - RETURN_OK (0) if OK <br>
  *         - GENERIC_ERROR (-1) if failure
  */
int shift_letter( char character_to_shift, char *p_result_character )
{
    // check that there is a value to set
    if( NULL == p_result_character )
    {
        return GENERIC_ERROR;
    }

    // shift process depending on if the input character is uppercase or lowercase
    if( ( character_to_shift >= 'a' ) and ( character_to_shift <= 'z' ) )
    {
        *p_result_character = (char)(character_to_shift - UPPERCASE_LOWERCASE_SHIFT);
    }
    else if( ( character_to_shift >= 'A' ) and ( character_to_shift <= 'Z' ) )
    {
        *p_result_character = (char)(character_to_shift + UPPERCASE_LOWERCASE_SHIFT);
    }
    else
    {
        *p_result_character = '~';
        return GENERIC_ERROR;
    }

    return RETURN_OK;
}

/**
  * @brief Calculate the translation of a vowel into consonant
  * @param [in] vowel          Vowel character to translate into consonant character
  * @param [out] p_out_buffer  Pointer onto output buffer
  * @param [out] p_offset      Pointer onto offset value to set
  * @return An error value :<br>
  *         - RETURN_OK (0) if OK <br>
  *         - GENERIC_ERROR (-1) if failure
  *
  * @note The translation of a vowel will not always give 2 consonants but is likely to output one consonant and
  *       one vowel from time to time.
  *       It has been observed that the translation from 'i' is 'FI' i.e. second character is a vowel.
  *       It might be of interest to translate vowels only into consonants i.e. 'i' giving 'FJ' for example
  *       (and maybe have consonants only give consonants)
  */
int calculate_vowel_translation( char vowel, unsigned char *p_out_buffer, unsigned int *p_offset )
{
    // declare and init variables
    //! @remark Clang-Tidy complains about '#' init value being not used
    //! @todo look for a workaround for this case
    unsigned char upper_half = '#';
    unsigned char lower_half = '#';
    /**
      * @note ```unsigned_vowel``` is used instead of ```vowel``` to avoid Clang-Tidy warnings
      * about wrong implicit casts or value size, during value manipulation and bitwise operations
      */
    unsigned char unsigned_vowel = (unsigned char)vowel;

    /**
      * Determine value of upper_half
      * @note operation could be written as follow
      * ```c
      *   upper_half = (unsigned char)( ( vowel >> 4U ) & 0x0FU );
      * ```
      * but it triggers a Clang-Tidy warning, which we want to avoid at the moment
      */
    upper_half =  unsigned_vowel >> 4U;
    upper_half &=  0x0FU;
    /*
     * Lower case letter values should be between 0x61 and 0x7A
     * => upper half byte can only be 0x6 or 0x7
     */
    if( ( ( upper_half bitand 0x06U ) != 0 ) or
        ( ( upper_half bitand 0x07U ) != 0 )  )
    {
        // success => nothing to do
    }
    else
    {
        // failure case... exit with error...
        return GENERIC_ERROR;
    }

    // determine value of lower_half
    lower_half = (unsigned char)( unsigned_vowel bitand 0x0FU );

    // set the values of translation into output buffer
    *p_out_buffer = (unsigned char)( 0x40U bitor upper_half );
    *(p_out_buffer + 1) = (unsigned char)( 0x40U bitor lower_half );
    *p_offset += 2; // update offset value

    return RETURN_OK;
}

/**
  * @brief Calculate the translation of a consonant into another one
  * @param [in] consonant      Vowel consonant character to translate
  * @param [out] p_out_buffer  Pointer onto output buffer
  * @param [out] p_offset      Pointer onto offset value to set
  * @return An error value :<br>
  *         - RETURN_OK (0) if OK <br>
  *         - GENERIC_ERROR (-1) if failure
  */
int calculate_consonant_translation( char consonant, unsigned char *p_out_buffer, unsigned int *p_offset )
{
    // declare and init variables
    //! @remark Clang-Tidy complains about '#' init value being not used
    //! @todo look for a workaround for this case
    unsigned char upper_half = '#';
    unsigned char lower_half = '#';
    /**
      * @note ```unsigned_consonant``` is used instead of ```consonant``` to avoid Clang-Tidy warnings
      * about wrong implicit casts or value size, during value manipulation and bitwise operations
      */
    unsigned char unsigned_consonant = (unsigned char)consonant;

    /**
      * Determine value of upper_half
      * @note operation could be written as follow
      * ```c
      *   upper_half = (unsigned char)( ( consonant >> 4U ) & 0x0FU );
      * ```
      * but it triggers a Clang-Tidy warning, which we want to avoid at the moment
      */
    upper_half =  unsigned_consonant >> 4U;
    upper_half &=  0x0FU;
    /*
     * Lower case letter values should be between 0x61 and 0x7A
     * => upper half byte can only be 0x6 or 0x7
     */
    if( ( ( upper_half bitand 0x06U ) != 0 ) or
        ( ( upper_half bitand 0x07U ) != 0 )  )
    {
        // success => nothing to do
    }
    else
    {
        // failure case... exit with error...
        return GENERIC_ERROR;
    }

    // determine value of lower_half
    lower_half = (unsigned char)( unsigned_consonant bitand 0x0FU );

    // set the values of translation into output buffer
    //! @note an idea that came while writting the code : if resulting char is a vowel, why not shifting it in addition ?
    *p_out_buffer = (unsigned char)( 0x60U bitor upper_half );
    *(p_out_buffer + 1) = (unsigned char)( 0x60U bitor lower_half );
    *p_offset += 2; // update offset value

    return RETURN_OK;

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
    unsigned int idx = 0;
    char shifted_letter_to_analyse = 0;

    /**
      * Since 'vowels' table only contains lowercase letters, and we need to handle uppercase
      * we will shift the 'letter_to_analyse' value and use it in the analyse itself afterward
      */
    if( RETURN_OK != shift_letter( letter_to_analyse, &shifted_letter_to_analyse) )
    {
        /**
          * Error case handling :<br>
          * 'shift_letter' fail means that 'letter_to_analyse' is not within the alphabet
          * (see 'shift_letter' return codes)
          */
        return false;
    }

    //! Parse the vowel table within a loop
    for( idx = 0 ; idx < sizeof(vowels) ; idx++ )
    {
        //! Check that letter_to_analyse is value is the same as one in 'vowels[]' table
        if( ( vowels[ idx ] == letter_to_analyse )         or
            ( vowels[ idx ] == shifted_letter_to_analyse )  )   // uppercase letter handling
        {
            //! Comparison success => vowel found => exit with true
            return true;
        }
    }

    /*
     * if we reach this point, then all comparisons failed and letter is not a vowel
     * => exit with false
     */
    return false;
}

/**
  * @brief Translation loop function
  * @param [in] input             String that contains the original message
  * @param [in] input_length      Length of input string
  * @param [out] output           Buffer in which we would write the resulting string
  * @param [out] p_output_length  Pointer to length of output string
  * @return An int value :<br>
  *           - RETURN_OK (0) if everything is OK <br>
  *           - GENERIC_ERROR (-1) if process ends in error
  */
int translate_into_obscure( char *input, unsigned int input_length, unsigned char *output, unsigned int *p_output_length )
{
    // local variable init
    int          retval = 0;
    unsigned int idx    = 0;
    unsigned int offset = 0;

    // check output
    if( NULL == output )
    {
        /**
          * If 'output' buffer is 'NULL' we might get in trouble trying to set values to a random memory location <br>
          *   => We would better exit the function as soon as  possible with an error code to inform the caller
          */
        return GENERIC_ERROR;
    }

    // check input
    if( NULL == input )
    {
        //! If there is no input buffer passed in argument, use default string 'message_str'
        input = (char *)message_str;
        input_length = sizeof(message_str);
    }

    // translation loop
    for( idx = 0 ; ( idx < input_length ) and ( input[ idx ] != '\0' ) ; idx++ )
    {
        if( true == is_a_vowel( input[ idx ] ) ) // check if letter is a vowel
        {
            retval = calculate_vowel_translation( input[ idx ], &output[ offset ], &offset );
        }
        else
        {
            retval = calculate_consonant_translation( input[ idx ], &output[ offset ], &offset );
        }
    }

    *p_output_length = offset;

    return retval;
}

/**
  * @brief Main program function
  * @param [in] argC  Argument number
  * @param [in] argV  Pointer onto input argument strings
  * @return RETURN_OK (0) in case of successful execution
  */
int main( int argC, char **argV )
{
    int          res                  = 0;
    unsigned int idx                  = 0;
    unsigned int output_useful_length = 0;

    char input_buff[ 256 ];    // used to store user input when no argument are passed to program
    char output_buff[ 256 ];

    // buffer init
    memset( input_buff, 0x00, sizeof(input_buff) );
    memset( output_buff, 0x00, sizeof(output_buff) );

    /**
      * Conditional behavior of program:
      *   - if there are arguments in the program call, just translates
      *     the input string and exit (or print error message)
      *   - if there is no argument, go to the infinite loop to use the
      *     program until asked to quit
      */
    if( argC > 1 )
    {
        //! @remark show how many arguments are passed to the program (following line is only here for debug)
        printf( "argC --> %d\n", argC );
        // translate input string
        /**
          * @remarks - Just print the input string for now (translation part of the program is not finished yet)<br>
          *          - Perhaps keep a print of which option has been chosen in the end ('encode' or 'decode' for example)
          */
        for( idx = 0 ; idx < argC ; idx++ )
        {
            printf( "argV[ %d ] --> %s\n", idx, argV[ idx ] );
        }

        // Call to string obfuscation function
        //! @todo Add a check on return code for 'translate_into_obscure' function (and take action depending on it) 
        res = translate_into_obscure( argV[ 1 ], strlen(argV[ 1 ]), (unsigned char *)output_buff, &output_useful_length );

        if( RETURN_OK == res )
        {
            printf( "%s\n", output_buff );
        }

        //! @todo Remove following lines after debug
        //! @remark Lines are left as commented code to allow multiple use cases, depending on IDE used for development
//#ifdef __unix__
//        pause();
//#else
//        system("PAUSE");
//#endif

        // Jump to end of program
        goto exit_program;  //! @todo remove 'goto' ASAP => goes against coding style
    }

	// Print program title
	printf( title_str );
    // forever loop
    forever
    {
        // Prompt user for input string
        printf( ":> " );
        scanf( "%s", input_buff );
        // Translate input
        res = translate_into_obscure( input_buff, strlen(input_buff), (unsigned char *)output_buff, &output_useful_length );
        // Print output if no error in the obfuscation process
        if( RETURN_OK == res )
        {
            printf( "%s\n", output_buff );
        }

        // Prompt user for continuation or exit
        printf( "Exit [yes/no] ? " );
        memset( output_buff, 0x00, sizeof(output_buff) );   // reset output buffer used for user input
        scanf( "%s", (char *)output_buff );
        if( strncmp( (const char *)output_buff, "yes", strlen("yes") ) == 0 )
        {
            break;
        }
    }

    //! @todo rework following lines : coding style chosen is not to have 1 exit point per function & forbids 'goto' usage
exit_program:
    // print linebreak to have next shell command on a new line
    printf("\n");
    return RETURN_OK;
}
