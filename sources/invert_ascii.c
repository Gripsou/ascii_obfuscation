#include <stdio.h>

int main(void)
{
    char out_char = 0;
    unsigned char upper_half = 0;
    unsigned char lower_half = 0;
    for( int idx = 33 /*33 = 0x21 = !*/ ; idx < 127 /*127 = 0x7F = DEL*/ ; idx++ )
    {
        // get upper half  and lower half of resulting character
        upper_half = ( (unsigned char)idx << 4 ) & 0xF0 ;
        lower_half = (unsigned char)idx & 0x0F ;
        
        // recreate a new character by inverting upper half and lower half
        upper_half = upper_half >> 4;
        lower_half = lower_half << 4;
        out_char = (char)(upper_half & lower_half);
        printf( "idx %d --> %c\n", idx, out_char );
    }
    
    return 0;
}
