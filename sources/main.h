/**
  * @title main.h
  * @brief `ascii_obfuscation` program header file for specific definition share
  * @note Created by vince on 09/02/2020.
  */

#ifndef ASCII_OBFUSCATION_MAIN_H
#define ASCII_OBFUSCATION_MAIN_H

// ============================================================================
// ======================== INCLUDES ==========================================
// ============================================================================

    // None at the moment

// ============================================================================
// ======================== MACRO =============================================
// ============================================================================

//! difference between uppercase and lower case letters
#define UPPERCASE_LOWERCASE_SHIFT   ('a'-'A')

// Stupid macro definition
#define ever        (;;)
#define forever     for ever    //! equivalent to for(;;)... I thought it would be fun, but it's still very stupid

// ============================================================================
// ======================== ENUM & STRUCTURES =================================
// ============================================================================

//! Define custom/personal error codes to avoid using magic numbers
enum error_codes
{
    GENERIC_ERROR   = -1,   //!< General purpose error ; no particular details to share
    RETURN_OK       = 0,    //!< All good !
};

// ============================================================================
// ======================== PROTOTYPES ========================================
// ============================================================================

    // None at the moment

// ============================================================================
// ======================== EXTERN VARIABLES & CONSTANTS ======================
// ============================================================================

// vowels and consonants tables
extern const char vowels[ 6 ];
extern const char consonants[ 20 ];
// test message string for character manipulation
extern const char message_str[ 0xFF ];

#endif //ASCII_OBFUSCATION_MAIN_H
