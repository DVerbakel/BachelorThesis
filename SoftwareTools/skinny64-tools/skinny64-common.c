// Written by Denise Verbakel

/*
 * Include the file needed in this program.
*/

#include "skinny64-common.h"

/*
 * S-box and inverse S-box of Skinny64 in hexadecimal notation.
*/

const uint8_t sbox[] = {0xc, 0x6, 0x9, 0x0, 0x1, 0xa, 0x2, 0xb, 0x3, 0x8, 0x5, 0xd, 0x4, 0xe, 0x7, 0xf};
const uint8_t inv_sbox[] = {0x3, 0x4, 0x6, 0x8, 0xc, 0xa, 0x1, 0xe, 0x9, 0x2, 0x5, 0x7, 0x0, 0xb, 0xd, 0xf};

/*
 * The MixColumns (MC) layer of Skinny64. 
 * All nibble columns of the ciphers internal state are multiplied by the following matrix:
 *	1  0  1  1
 *	1  0  0  0
 *	0  1  1  0
 *	1  0  1  0
*/

uint16_t 
mix_columns(uint16_t a)
{
	uint16_t first = (a >> 12) & 0xf;
	uint16_t second = (a >> 8) & 0xf;
	uint16_t third = (a >> 4) & 0xf;
	uint16_t fourth = a & 0xf;

	uint16_t new_second = first;
	uint16_t new_third = second ^ third;
	uint16_t new_fourth = first ^ third;
	uint16_t new_first = new_fourth ^ fourth;

	return (new_first << 12) | (new_second << 8) | (new_third << 4) | new_fourth;
}

/*
 * The transposed MixColumns (MC) layer of Skinny64. 
 * All nibble columns of the ciphers internal state are multiplied by the following matrix:
 *	1  1  0  1
 *	0  0  1  0
 *	1  0  1  1
 *	1  0  0  0
*/

uint16_t 
mix_columns_transpose(uint16_t a)
{
	uint16_t first = (a >> 12) & 0xf;
	uint16_t second = (a >> 8) & 0xf;
	uint16_t third = (a >> 4) & 0xf;
	uint16_t fourth = a & 0xf;

	uint16_t intermediate = first ^ fourth;

	uint16_t new_first = intermediate ^ second;
	uint16_t new_second = third;
	uint16_t new_third = intermediate ^ third;
	uint16_t new_fourth = first;

	return (new_first << 12) | (new_second << 8) | (new_third << 4) | new_fourth;
}

/*
 * The SubCells (SC) layer of Skinny64. 
 * The 4-bit S-box as defined above is applied to each cell of the ciphers internal state.
*/

uint16_t
sub_cells(uint16_t x)
{
   	uint16_t a = x & 0xf;
 	uint16_t b = (x >> 4) & 0xf;
 	uint16_t c = (x >> 8) & 0xf;
 	uint16_t d = (x >> 12) & 0xf;

	uint16_t s_a = sbox[a];		// S(a)
	uint16_t s_b = sbox[b];		// S(b)
	uint16_t s_c = sbox[c];		// S(c)
	uint16_t s_d = sbox[d];		// S(d)

	return (s_d << 12) | (s_c << 8) | (s_b << 4) | s_a;
}

