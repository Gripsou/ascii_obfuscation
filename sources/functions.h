/**
  * @title functions.h
  * @brief function definition for `ascii_obfuscation`
  * @note Created by vince on 08/02/2020.
  */

#ifndef ASCII_OBFUSCATION_FUNCTIONS_H
#define ASCII_OBFUSCATION_FUNCTIONS_H

// ============================================================================
// ======================== INCLUDES ==========================================
// ============================================================================

    // None at the moment

// ============================================================================
// ======================== PROTOTYPES ========================================
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
int randomize_value( char input, char *output, unsigned int *offset );

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
int translate_into_obscure( char *input,
                            unsigned int input_length,
                            unsigned char *output,
                            unsigned int *p_output_length );


#endif //ASCII_OBFUSCATION_FUNCTIONS_H
