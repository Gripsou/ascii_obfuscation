/**
  * @title functions.c
  * @brief function implementation for ascii_obfuscation
  * @note Created by vince on 08/02/2020.
  */

// ============================================================================
// ======================== INCLUDES ==========================================
// ============================================================================

#include "functions.h"
#include "main.h"

#include <stdlib.h>
#include <iso646.h>

// ============================================================================
// ======================== MACRO & CONSTANTS =================================
// ============================================================================

    // None at the moment

// ============================================================================
// ======================== PROTOTYPES ========================================
// ============================================================================

    // None at the moment

// ============================================================================
// ======================== FUNCTIONS =========================================
// ============================================================================

/*
 * Make 2 randomized letters out of 1 letter input
 * Parameters :
 *   - [in] input    Input character to be randomized
 *   - [out] output  Buffer in which we would write the resulting 2 characters
 *   - [out] offset  Offset of output characters in output buffer
 * Return : An int value :
 *           - RETURN_OK (0) if everything is OK
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
  * Translation loop function
  * Parameters :
  *   - [in] input             String that contains the original message
  *   - [in] input_length      Length of input string
  *   - [out] output           Buffer in which we would write the resulting string
  *   - [out] p_output_length  Pointer to length of output string
  * Return : An int value :
  *           - RETURN_OK (0) if everything is OK
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