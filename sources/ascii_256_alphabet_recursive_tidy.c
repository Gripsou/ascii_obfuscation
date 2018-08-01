/**
  * @brief ```ascii_256_alphabet_recursive.c``` tidied up version
  * @remark This looks much nicer than the K&R style isn't it
  * @details Some terminals are printing out character foor values that are greater than ```0x7F```
  *          we would like to see which
  */

#include <stdio.h>

void alphabet_printer( int i )
{
    if( i < 256 )
    {
        printf("idx : %d --> %c\n", i, i);
        i++;
        alphabet_printer( i );
    }
}

int main( void )
{
    int i = 0;
    alphabet_printer( i );
    return 0;
}
