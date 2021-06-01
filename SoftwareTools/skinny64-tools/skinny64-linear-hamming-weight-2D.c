// Written by Denise Verbakel

/*
 * Include the files needed in this program.
*/

#include "skinny64-lookup-table.c"
#include "skinny64-common.h"
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
	 * We get the hamming weight from the table defined in skinny64-lookup-table.c. We compute the hamming weight of the input found in the
	 * lookup table and set it to the row. Similarly, we compute the hamming weight of the output found in the lookup table and set it to the
	 * column. We merge the entries with the same combinations for the pair (input,output) in a table. Lastly, we save the results to the 
         * file skinny64-linear-hamming-weight-2D.txt.
	*/	

	for (int i = 0; i < 16; i++) {
		mpz_set_ui(row, lookup_table_linear_hamming_weight[i][0]);
		mpz_set_ui(col, lookup_table_linear_hamming_weight[i][1]);
		table_insert_and_merge(hamming_weights, row, col, val, &mpz_add);
	}

	mpz_clears(row, col, val, NULL);
	
	// Data: (hamming weight input, hamming weight output, number of masks)
	table_print("data/skinny64-linear-hamming-weight-2D.txt", hamming_weights);
	
	/*
	 * Clean up the memory used by the table.
	*/
	
	table_destroy(hamming_weights);
	
	return 0;
}
