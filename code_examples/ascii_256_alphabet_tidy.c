/**
  * @brief ```ascii_256_alphabet.c``` tidied up version
  * @remark This looks much nicer than the K&R style isn't it
  * @details Some terminals are printing out character foor values that are greater than ```0x7F```
  *          we would like to see which
  */

#include <stdio.h>

int main( void )
{
    int i = 0;
    for( i = 0 ; i < 256 ; i++ )
    {
        printf("idx : %d --> %c\n", i, i);
    }
    
    return 0;
}
