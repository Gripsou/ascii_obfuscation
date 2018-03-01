#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHIFT_VAL   ('a'-'A')

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

const char input_table[] = "I think you know my point about inline if operations : it only obfuscates the code.\n";
const char bit_shifted_char_table[] =
{
    0x92, 0x40, 0xe8, 0xd0, 0xd2, 0xdc, 0xd6, 0x40, 0xf2, 0xde, 0xea, 0x40, 0xd6, 0xdc, 0xde, 0xee, 0x40, 0xda, 0xf2,
    0x40, 0xe0, 0xde, 0xd2, 0xdc, 0xe8, 0x40, 0xc2, 0xc4, 0xde, 0xea, 0xe8, 0x40, 0xd2, 0xdc, 0xd8, 0xd2, 0xdc, 0xca,
    0x40, 0xd2, 0xcc, 0x40, 0xde, 0xe0, 0xca, 0xe4, 0xc2, 0xe8, 0xd2, 0xde, 0xdc, 0xe6, 0x40, 0x74, 0x40, 0xd2, 0xe8,
    0x40, 0xde, 0xdc, 0xd8, 0xf2, 0x40, 0xde, 0xc4, 0xcc, 0xea, 0xe6, 0xc6, 0xc2, 0xe8, 0xca, 0xe6, 0x40, 0xe8, 0xd0,
    0xca, 0x40, 0xc6, 0xde, 0xc8, 0xca, 0x5c
};

int character_bit_shifting( )
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

    return 0;
}

const char vowels[] = { 'a', 'e', 'i', 'o', 'u', 'y' };
const char consonants[] = { 'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z' };

const char mesage_str[] = "i think you know my point about inline if operations : it only obfuscates the code.";

char calculate_vowel_translation( char vowel )
{
    // declare and init variables
    unsigned char upper_half = '#';
    unsigned char lower_half = '#';

    // determine value of upper_half
    upper_half = ( vowel >> 4 ) & 0x0F;
    if( upper_half & 0x06 )
    {
        upper_half = 0x06
    }
    else if( upper_half & 0x07 )
    {
        upper_half = 0x07
    }
    else
    {
        // failure case...
        //! @todo need to specify what to do in this case
    }

    //! @

    return result;
}

int main( )
{
    // local variable init
    int i = 0;
    unsigned char output_buff[ 256 ];
    // buffer init
    memset( output_buff, 0x00, sizeof(output_buff) );

    // translation
    for( i = 0 ; i < sizeof(mesage_str) ; i++ )
    {
        if( is_a_vowel( mesage_str[ i ] ) )
        {
            output_buff[ i ] =
        }
    }

    printf("\n");
    return 0;
}
