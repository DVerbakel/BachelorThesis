// Written by Denise Verbakel

/*
 * Include the files needed in this program.
*/

#include "skinny128-lookup-table.c"
#include "skinny128-common.h"
#include "../convolution.h"

int
main(void)
{
	/* 
	 * We initialize the table structure and after this the (big) integers.
	*/

	Table *hamming_weights = table_create();
	
	mpz_t row, col, val;
	mpz_inits(row, col, val, NULL);
	mpz_set_ui(col,0);
	mpz_set_ui(val,1);
	
	/*
	 * We get the hamming weight from the table defined in skinny128-lookup-table.c. We compute for difference a: 
         * w := hw(a) + hw(MixColumnsTranspose(a)). Then we increment the entry indexed by w in the histogram by 1. Lastly, 
	 * we save the results to the file skinny128-linear-hamming-weight.txt.
	*/
	
	for (int i = 0; i < 256; i++) {
		mpz_set_ui(row, lookup_table_linear_hamming_weight[i][0] + lookup_table_linear_hamming_weight[i][1]);
		table_insert_and_merge(hamming_weights, row, col, val, &mpz_add);
	}
	
	mpz_clears(row, col, val, NULL);
	
	// Data: (hamming weight, not used, number of masks)
	table_print("data/skinny128-linear-hamming-weight.txt", hamming_weights);
	
	/*
	 * Convolute the above results of one column in order to compute the histogram of the full state(s). We initialize the
	 * table structure and save the results to the files skinny128-linear-hamming-weight-full.txt,
	 * skinny128-artificial-skinny256-linear-hamming-weight-full.txt and
	 * skinny128-artificial-skinny384-linear-hamming-weight-full.txt.
	*/
	
	Table *hamming_weights_full = convolute_tables(hamming_weights, NUMBER_OF_SUPERBOXES, 0, 0, differential_combiners);
	Table *hamming_weights_full_256 = convolute_tables(hamming_weights, NUMBER_OF_SUPERBOXES*2, 0, 0, differential_combiners);
	Table *hamming_weights_full_384 = convolute_tables(hamming_weights, NUMBER_OF_SUPERBOXES*3, 0, 0, differential_combiners);
	
	// Data: (hamming weight, not used, number of masks)
	table_print("data/skinny128-linear-hamming-weight-full.txt", hamming_weights_full);
	table_print("data/skinny128-artificial-skinny256-linear-hamming-weight-full.txt", hamming_weights_full_256);
	table_print("data/skinny128-artificial-skinny384-linear-hamming-weight-full.txt", hamming_weights_full_384);
	
	/*
	 * Clean up the memory used by the tables.
	*/
	
	table_destroy(hamming_weights);
	table_destroy(hamming_weights_full);
	table_destroy(hamming_weights_full_256);	
	table_destroy(hamming_weights_full_384);
	
	return 0;
}
