// Written by Denise Verbakel

/*
 * Include the files needed in this program.
*/

#include <stdio.h>
#include <inttypes.h>

/*
 * Specify the S-box of Skinny64.
*/

const uint8_t sbox[] = {0xc, 0x6, 0x9, 0x0, 0x1, 0xa, 0x2, 0xb, 0x3, 0x8, 0x5, 0xd, 0x4, 0xe, 0x7, 0xf};

/*
 * This function is used to convert decimal numbers to binary numbers.
*/

void bin(uint8_t n, FILE *fp)
{
    uint8_t i;
    for (i = 1 << 3; i > 0; i = i / 2)
        (n & i) ? fprintf(fp, "1") : fprintf(fp, "0");
}
 

int main()
{
    /*
     * We create a file called skinny64.in, write the input for the Espresso algorithm to this file and 
     * then close this file again.
    */

    FILE *fp;
    fp = fopen("skinny64.in", "w+");

    fprintf(fp, ".i 4               	# .i specifies the number of inputs\n");
    fprintf(fp, ".o 4               	# .o specifies the number of outputs\n");
    fprintf(fp, ".ilb X0 X1 X2 X3      	# .ilb specifies the names of the inputs in order\n");
    fprintf(fp, ".ob Y0 Y1 Y2 Y3      	# .ob specifies the names of the outputs in order\n");

    for (int i = 0; i < 16; i++) {
	bin(i, fp);
	fprintf(fp, " ");
    	bin(sbox[i], fp);
	fprintf(fp, "\n");
    }

    fprintf(fp, ".e       		# Signifies the end of the file");

    fclose(fp);
}
