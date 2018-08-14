#include <stdio.h>

int main(void)
{
    char out_char = 0;
    unsigned char upper_half = 0;
    unsigned char lower_half = 0;
    for( int idx = 33 /*33 = 0x21 = !*/ ; idx < 127 /*127 = 0x7F = DEL*/ ; idx++ )
    {
        // get upper half  and lower half of resulting character
        upper_half = (unsigned char)idx & 0xF0 ;
        lower_half = (unsigned char)idx & 0x0F ;
		printf( "---------------------\n"
				"upper_half --> 0x%02x\n"
				"lower_half --> 0x%02x\n",
				upper_half, lower_half );

        // recreate a new character by inverting upper half and lower half
        upper_half = upper_half >> 4;
        lower_half = lower_half << 4;
        out_char = (char)( ( upper_half | lower_half ) & 0x000000FFUL ) ;
        printf( "- - - - - - - - - - -\n"
				"upper_half --> 0x%02x\n"
				"lower_half --> 0x%02x\n"
				"out_char   --> 0x%02x\n"
				"idx 0x%02x --> %c\n"
				"---------------------\n",
				upper_half, lower_half, (unsigned char)out_char, idx, out_char);
    }

    return 0;
}
