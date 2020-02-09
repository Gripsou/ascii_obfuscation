/**
  * @title unit_tests.c
  * @brief Unit test implementation for `ascii_obfuscation`
  * @note Created by vince on 08/02/2020.
  */

// ============================================================================
// ======================== INCLUDES ==========================================
// ============================================================================

#include "unity.h"  // This include contains all the macro and definition of the **Unity** test framework
#include "functions.h"

#include <string.h>
#include <iso646.h>

// ============================================================================
// ======================== SET UP & TEAR DOWN ================================
// ============================================================================

void setUp( void )
{
    // nothing here for now
}

void tearDown( void )
{
    // nothing here for now
}

// ============================================================================
// ======================== TESTS IMPLEMENTATIONS =============================
// ============================================================================

void TEST_randomize_value(void)
{
    // prepare the elements needed to test the function
    unsigned char output_buffer[ 5 ];
    unsigned int offset = 2;
    memset( output_buffer, 0x00, sizeof( output_buffer ) );
    // call the function
    randomize_value( 'a', (char *)output_buffer, &offset );
    // verify the results
    // test upper_half
    TEST_ASSERT_EQUAL_HEX8( ( 'a' bitand 0xF0 ), ( output_buffer[2] bitand 0xF0 ) );
    // test lower_half
    TEST_ASSERT_EQUAL_HEX8( ( 'a' bitand 0x0F ), ( output_buffer[3] bitand 0x0F ) );
    // test offset
    TEST_ASSERT_EQUAL( 4, offset );
}

#ifdef __WIP__
void TEST_translate_into_obscure(void)
{
    TEST_ASSERT_EQUAL_HEX8(80, translate_into_obscure() );
}
#endif // __WIP__

// ============================================================================
// ======================== TEST RUNNER (MAIN) ================================
// ============================================================================

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(TEST_randomize_value);
#ifdef __WIP__
    RUN_TEST(TEST_translate_into_obscure);
#endif // __WIP__
    return UNITY_END();
}

