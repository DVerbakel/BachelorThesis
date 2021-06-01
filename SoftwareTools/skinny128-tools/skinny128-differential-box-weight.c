// Written by Denise Verbakel

/*
 * Include the files needed in this program.
*/

#include "skinny128-common.h"
#include "../convolution.h"

int
main(void)
{
	/* 
	 * We initialize the table structure and after this the (big) integers.
	*/

	Table *box_weights_superbox = table_create();
	
	mpz_t row, col, val;
	mpz_inits(row, col, val, NULL);
	mpz_set_ui(col,0);
	mpz_set_ui(val,1);

	/*
	 * We get the box weight using the function box_weight64 defined in global-common.c. We compute for difference a: 
	 * w := bw(a) + bw(MixColumns(a)). Then we increment the entry indexed by w in the histogram by 1. Lastly, we save the results to the 
	 * file skinny128-differential-box-superbox.txt.
	*/

	for (uint64_t a = 0; a <= UINT32_MAX; a++) {
		mpz_set_ui(row, box_weight64(a, NUMBER_OF_BOXES_IN_SUPERBOX, BOX_WIDTH) + box_weight64(mix_columns(a), NUMBER_OF_BOXES_IN_SUPERBOX, BOX_WIDTH));
		table_insert_and_merge(box_weights_superbox, row, col, val, &mpz_add);
	}	

	mpz_clears(row, col, val, NULL);

	// Data: (box weight, not used, number of differences) 
	table_print("data/skinny128-differential-box-superbox.txt", box_weights_superbox);

	/*
	 * Convolute the above results of the super boxes in order to compute the histogram of the full state(s). We initialize the table 
	 * structure and save the results to the files skinny128-differential-box-full.txt, skinny128-artificial-skinny256-differential-box-full.txt
	 * and skinny128-artificial-skinny384-differential-box-full.txt.
	*/

	Table *box_weights_full = convolute_tables(box_weights_superbox, NUMBER_OF_BOXES_IN_SUPERBOX, 0, 0, differential_combiners);
	Table *box_weights_full_256 = convolute_tables(box_weights_superbox, NUMBER_OF_BOXES_IN_SUPERBOX*2, 0, 0, differential_combiners);
	Table *box_weights_full_384 = convolute_tables(box_weights_superbox, NUMBER_OF_BOXES_IN_SUPERBOX*3, 0, 0, differential_combiners);
	
	// Data: (box weight, not used, number of differences) 
	table_print("data/skinny128-differential-box-full.txt", box_weights_full);
	table_print("data/skinny128-artificial-skinny256-differential-box-full.txt", box_weights_full_256);
	table_print("data/skinny128-artificial-skinny384-differential-box-full.txt", box_weights_full_384);

	/*
	 * Clean up the memory used by the tables.
	*/

	table_destroy(box_weights_superbox);
	table_destroy(box_weights_full);
	table_destroy(box_weights_full_256);
	table_destroy(box_weights_full_384);

	return 0;
}
