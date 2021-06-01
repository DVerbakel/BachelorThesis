// Written by Denise Verbakel

/*
 * Include the files needed in this program.
*/

#include "skinny128-common.h"
#include "../convolution.h"

/*
 * Define a uint8_t to hold the box pattern and an array to hold the box pattern cardinalities.
*/

uint8_t box_pattern(uint32_t);

uint64_t box_pattern_cardinalities[65536];

/*
 * This function is used to calculate the box pattern.
*/

uint8_t
box_pattern(uint32_t a)
{
	uint16_t pattern = 0;
	uint32_t b = mix_columns(a);

	for (int i = 0; i < 4; i++) {
		if ((a & 0xff) != 0) {
			pattern |= 1 << i;
		}
		if ((b & 0xff) != 0) {
			pattern |= 1 << (4 + i);
		}
		a >>= 8;
		b >>= 8;
	}

	return pattern;
}


int
main(void)
{
	/* 
	 * We initialize the table structure and after this the (big) integers.
	*/

	Table *box_partition_superbox = table_create();
	
	mpz_t row, col, val;
	mpz_inits(row, col, val, NULL);
	mpz_set_ui(col,0);
	mpz_set_ui(val,1);

	/*
	 * We get the differential cluster histogram of the superbox by first filling the array box_pattern_cardinalities with all the
	 * box patters for every a. Then we go through the array and save the activity pattern accordingly in the table structure
	 * box_partition_superbox. Lastly, we save the results to the file skinny128-differential-clustering-superbox.txt.
	*/

	for (uint64_t a = 0; a <= UINT32_MAX; a++) {
		box_pattern_cardinalities[box_pattern(a)]++;
	}	

	mpz_set_ui(val, 1);
	for (int i = 0; i < 65536; i++) {
		uint64_t b = box_pattern_cardinalities[i];
		if (b != 0) {
			mpz_set_ui(col, b);
			mpz_set_ui(row, hamming_weight8(i));
			table_insert_and_merge(box_partition_superbox, row, col, val, &mpz_add);
		}
	}
	mpz_clears(row, col, val, NULL);

	// Data: (weight, cardinality of cluster class, number of cluster classes)
	table_print("data/skinny128-differential-clustering-superbox.txt", box_partition_superbox);

	/*
	 * Convolute the above results of the super boxes in order to compute the histogram of the full state. We initialize the table 
	 * structure and save the results to the file skinny128-differential-clustering-full.txt.
	*/

	Table *box_partition_full = convolute_tables(box_partition_superbox, NUMBER_OF_BOXES_IN_SUPERBOX, 0, 0, differential_combiners);
	
	// Data: (weight, cardinality of cluster class, number of cluster classes)
	table_print("data/skinny128-differential-clustering-full.txt", box_partition_full);	

	/*
	 * Clean up the memory used by the tables.
	*/

	table_destroy(box_partition_superbox);
	table_destroy(box_partition_full);

	return 0;
}
