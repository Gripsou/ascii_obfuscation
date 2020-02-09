/**
  * @title ascii_obfuscation
  */

// ============================================================================
// ======================== INCLUDES ==========================================
// ============================================================================

#include <stdio.h>
#include <string.h>

#include "functions.h"
#include "main.h"

// ============================================================================
// ======================== MACRO & CONSTANTS =================================
// ============================================================================

//! Title string to ebe displayed in console
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

    // None at the moment

// ============================================================================
// ======================== FUNCTIONS =========================================
// ============================================================================

    // None at the moment

// ============================================================================
// ======================== PROGRAM ENTRY POINT (MAIN) ========================
// ============================================================================

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
