//
// Created by vince on 09/02/2020.
//

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
    GENERIC_ERROR   = -1,
    RETURN_OK       = 0,
};

typedef struct __message
{
    const char *string;
#ifdef __DEBUG__
    void (*init)( const char* init_string );
#endif // __DEBUG__
    const char* (*get)( struct __message this );
} message_t;

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
#ifdef __DEBUG__
extern message_t message;
#endif // __DEBUG__
extern const char message_str[ 0xFF ];

#endif //ASCII_OBFUSCATION_MAIN_H
