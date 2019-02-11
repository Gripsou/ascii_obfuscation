/**
  * @title ascii_obfuscation
  */

// ============================================================================
// ======================== INCLUDES ==========================================
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <iso646.h>  //!< allows to use `and`, `or`, `xor` keywords instead of `&&`, `||` symbols

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

int shift_letter( char character_to_shift, char *p_result_character );

// ============================================================================
// ======================== FUNCTIONS =========================================
// ============================================================================

/**
  * @brief Make 2 randomized letters out of 1 letter input
  * @param [in] input    Input character to be randomized
  * @param [out] output  Buffer in which we would write the resulting 2 characters
  * @param [out] offset  Offset of output characters in output buffer
  * @return An int value :<br>
  *           - RETURN_OK (0) if everything is OK <br>
  *           - GENERIC_ERROR (-1) if process ends in error
  */
int randomize_value( char input, char *output, unsigned int *offset )
{
    unsigned char upper_half   = 0xFF;
    unsigned char lower_half   = 0xFF;
    unsigned char working_half = 0x00;

    // Split input in two halves
    upper_half = (unsigned char)(input bitand 0xF0);
    lower_half = (unsigned char)(input bitand 0x0F);

    //! @todo We have to revise the following lines to ensure they do what they are supposed to
    // Create new character using upper_half

    // First : setup random value
    working_half = (unsigned char)(rand() % 0x7F);  // 0x7F is the usual limit of the standard ASCII table
    // Second : rearrange values to create first character
    working_half = (unsigned char)(working_half bitand 0x0F);
    output[ *offset ] = upper_half bitor working_half;
    (*offset)++; // increment offset

    // Create another new character using lower_half

    // First : regenerate random number
    working_half = (unsigned char)(rand() % 0x7F);
    // Second : arrange values to create second output character
    working_half = (unsigned char)(working_half bitand 0xF0);
    output[ *offset ] = lower_half bitor working_half;
    (*offset)++; // increment offset

    return RETURN_OK;
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
        retval = randomize_value( input[ idx ], (char *)( output + offset ), &offset );
        if( RETURN_OK != retval )
        {
            // abort loop, followed by update and exit
            break;
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

        // End of program
        return RETURN_OK;
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

    // End of program
    return RETURN_OK;
}
