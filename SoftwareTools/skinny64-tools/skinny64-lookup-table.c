// Written by Denise Verbakel

/*
 * Note that we use a lookup table in order to make clear how the hamming weight is computed.
 * Another reason is that this is perfectly fine doable by hand in comparison to the box weight.
*/

/*
 * Differential hamming weight lookup table:
 *
 *	0000 -> 0000		0x0 -> 0x0		0 + 0 = 0
 *	0001 -> 1000		0x1 -> 0x8		1 + 1 = 2
 *	0010 -> 1011		0x2 -> 0xb		1 + 3 = 4
 *	0011 -> 0011		0x3 -> 0x3		2 + 2 = 4
 *	0100 -> 0010		0x4 -> 0x2		1 + 1 = 2
 *	0101 -> 1010		0x5 -> 0xa		2 + 2 = 4
 *	0110 -> 1001		0x6 -> 0x9		2 + 2 = 4
 *	0111 -> 0001		0x7 -> 0x1		3 + 1 = 4
 *	1000 -> 1101		0x8 -> 0xd		1 + 3 = 4
 *	1001 -> 0101		0x9 -> 0x5		2 + 2 = 4
 *	1010 -> 0110		0xa -> 0x6		2 + 2 = 4
 *	1011 -> 1110		0xb -> 0xe		3 + 3 = 6
 *	1100 -> 1111		0xc -> 0xf		2 + 4 = 6
 *	1101 -> 0111		0xd -> 0x7		3 + 3 = 6
 *	1110 -> 0100		0xe -> 0x4		3 + 1 = 4
 *	1111 -> 1100		0xf -> 0xc		4 + 2 = 6
 *
 * The lookup table for the differential hamming weight is obtained by multiplying all possible 4 bit vectors 
 * as a (4x1)-matrix by the following (4x4)-matrix:
 *	1  0  1  1
 *	1  0  0  0
 *	0  1  1  0
 *	1  0  1  0
 * We then count the bits set to 1 in the 4 bit input vector and the bits set to 1 in the 4 bit output vector.
*/

const int lookup_table_differential_hamming_weight[16][2] = {
	{0, 0},
	{1, 1},
	{1, 3},
	{2, 2},
	{1, 1},
	{2, 2},
	{2, 2},
	{3, 1},
	{1, 3},
	{2, 2},
	{2, 2},
	{3, 3},
	{2, 4},
	{3, 3},
	{3, 1},
	{4, 2},
};

/*
 * Linear hamming weight lookup table:
 *
 *	0000 -> 0000		0x0 -> 0x0		0 + 0 = 0
 *	0001 -> 1010		0x1 -> 0xa		1 + 2 = 3
 *	0010 -> 0110		0x2 -> 0x6		1 + 2 = 3
 *	0011 -> 1100		0x3 -> 0xc		2 + 2 = 4
 *	0100 -> 1000		0x4 -> 0x8		1 + 1 = 2
 *	0101 -> 0010		0x5 -> 0x2		2 + 1 = 3
 *	0110 -> 1110		0x6 -> 0xe		2 + 3 = 5
 *	0111 -> 0100		0x7 -> 0x4 		3 + 1 = 4
 *	1000 -> 1011		0x8 -> 0xb		1 + 3 = 4
 *	1001 -> 0001		0x9 -> 0x1		2 + 1 = 3
 *	1010 -> 1101		0xa -> 0xd		2 + 3 = 5
 *	1011 -> 0111		0xb -> 0x7		3 + 3 = 6
 *	1100 -> 0011		0xc -> 0x3		2 + 2 = 4
 *	1101 -> 1001		0xd -> 0x9		3 + 2 = 5
 *	1110 -> 0101		0xe -> 0x5		3 + 2 = 5
 *	1111 -> 1111		0xf -> 0xf		4 + 4 = 8
 *
 * The lookup table for the linear hamming weight is obtained by multiplying all possible 4 bit vectors 
 * as a (4x1)-matrix by the following (4x4)-matrix:
 *	1  1  0  1
 *	0  0  1  0
 *	1  0  1  1
 *	1  0  0  0
 * Note: this is the transpose of the matrix above.
 * We then count the bits set to 1 in the 4 bit input vector and the bits set to 1 in the 4 bit output vector.
*/

const int lookup_table_linear_hamming_weight[16][2] = {
	{0, 0},
	{1, 2},
	{1, 2},
	{2, 2},
	{1, 1},
	{2, 1},
	{2, 3},
	{3, 1},
	{1, 3},
	{2, 1},
	{2, 3},
	{3, 3},
	{2, 2},
	{3, 2},
	{3, 2},
	{4, 4},
};

