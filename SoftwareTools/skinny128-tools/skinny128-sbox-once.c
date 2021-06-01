// Written by Denise Verbakel

/*
 * Include the files needed in this program.
*/

#include "skinny128-common.h"
#include "../convolution.h"
#include "../walsh-transform.h"

/*
 * Define SIZE to be the size of all different possible inputs for an S-box: 2^8 = 256
*/

#define SIZE 256

int
main(void)
{	
	/* 
	 * We initialize the (big) integers and after this the table structures.
	*/

	mpz_t val, correlation_table_entry_non_negative;
	mpz_inits(val, correlation_table_entry_non_negative, NULL);

	Table_fixed *superbox_counts = table_fixed_create(SIZE+1);
	Table_fixed *correlation_table_superbox;

	/*
	 * We get the correlation of one S-box by taking the steps below. Some extra comments are added here for clarification.
	 * After having done this, we save the results to the file skinny128-sbox-once.txt
	*/

	// We fix an output mask v.
	for (uint64_t v = 0; v < SIZE; v++) {
		correlation_table_superbox = table_fixed_create(SIZE);

		// We compute a histogram that holds the pairs of the form (x, (-1)^(S(x) dot v))
		for (uint64_t x = 0; x < SIZE; x++) {
			uint32_t y_one_round = sub_cells(x);						// S(x)
			mpz_set_si(val, dot_prod(y_one_round, v) ? -1 : 1);				// 1 or -1
			table_fixed_insert_and_merge(correlation_table_superbox, x, val, &mpz_add);
		}

		// We compute the linear characteristics of S(x) dot v using the Walsh tranform on the correlation_table_superbox
		// table structure.
		walsh_transform(correlation_table_superbox->head, correlation_table_superbox->size);

		// We extract the counts given the linear characteristics column, take the absolute value to handle negative values
		// and save them in the table structure superbox_counts.
		mpz_set_ui(val, 1);
		
		for (int i = 0; i < SIZE; i++) {
			mpz_abs(correlation_table_entry_non_negative, correlation_table_superbox->head[i]);
			table_fixed_insert_and_merge(superbox_counts, mpz_get_ui(correlation_table_entry_non_negative), val, &mpz_add);
		}

		table_fixed_destroy(correlation_table_superbox);
	}
	mpz_clear(val);
	
	// Data: (numerator of correlation, number of correlations)
	table_fixed_print("data/skinny128-sbox-once.txt", superbox_counts);

	/*
	 * Clean up the memory used by the table.
	*/

	table_fixed_destroy(superbox_counts);

}
