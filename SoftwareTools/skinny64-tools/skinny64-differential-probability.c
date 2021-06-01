// Written by Denise Verbakel

/*
 * Include the files needed in this program.
*/

#include "skinny64-common.h"
#include "../convolution.h"

int
main(void)
{
	/* 
	 * We initialize the table structure and after this the (big) integers.
	*/

	Table_fixed *number_of_differentials_superbox = table_fixed_create(UINT16_MAX+2);

	mpz_t val;
	mpz_init(val);
	mpz_set_ui(val, 1);

	/* 
	 * We get the (rounded) differential probability by taking the steps below. Some extra comments are added here for clarification.
	 * After having done this, we save the results to the file skinny64-differential-superbox.txt.
	*/

	unsigned int *table = (unsigned int *) malloc((UINT16_MAX+1)*sizeof(int));

	// For every a from 0 to 2^16.
	for (uint32_t a = 0; a <= UINT16_MAX; a++) {
		memset(table, 0, sizeof(int)*(UINT16_MAX+1));

		// For every x from 0 to 2^16.
		for (uint32_t x = 0; x <= UINT16_MAX; x++) {
			// difference a
			uint16_t left_one_round = sub_cells(x);			// S(x)
			uint16_t right_one_round = sub_cells(x^a);		// S(x+a)

			// difference b			
			uint16_t left_mixed = mix_columns(left_one_round);	// M(S(x))
			uint16_t right_mixed = mix_columns(right_one_round);	// M(S(x+a))

			//difference c
			uint16_t left_two_round = sub_cells(left_mixed);	// S(M(S(x)))
			uint16_t right_two_round = sub_cells(right_mixed);	// S(M(S(x+a)))

			//difference d
			table[left_two_round^right_two_round]++;		// S(M(S(x))) + S(M(S(x+a)))
		}

		// We iterate over a row of the table and increment relevant entries of the number_of_differentials_superbox table (rounded)
		for (int i = 0; i <= UINT16_MAX; i++) {
			if (table[i] == 0) continue;

			double differential_weight = (double) (1U << 16);
			differential_weight /= table[i];
			differential_weight = log2(differential_weight);
			differential_weight = round(differential_weight);
			table_fixed_insert_and_merge(number_of_differentials_superbox, (unsigned long) differential_weight, val, &mpz_add);
		}
	}	
	free(table);
	mpz_clear(val);

	// Data: (-log2(DP), not used, number of differentials)
	table_fixed_print("data/skinny64-differential-superbox.txt", number_of_differentials_superbox);

	/*
	 * Convolute the above results of the superboxes in order to compute the histogram of the full state(s). We initialize the table 
	 * structure and save the results to the files skinny64-differential-full.txt, skinny64-artificial-skinny256-differential-full.txt
	 * and skinny64-artificial-skinny384-differential-full.txt.
	*/

	Table_fixed *number_of_differentials_full = convolute_tables_fixed(number_of_differentials_superbox, NUMBER_OF_SUPERBOXES, 0, 0);
	Table_fixed *number_of_differentials_full_256 = convolute_tables_fixed(number_of_differentials_superbox, NUMBER_OF_SUPERBOXES*4, 0, 0);
	Table_fixed *number_of_differentials_full_384 = convolute_tables_fixed(number_of_differentials_superbox, NUMBER_OF_SUPERBOXES*6, 0, 0);

	// Data: (-log2(DP), not used, number of differentials)
	table_fixed_print("data/skinny64-differential-full.txt", number_of_differentials_full);
	table_fixed_print("data/skinny64-artificial-skinny256-differential-full.txt", number_of_differentials_full_256);
	table_fixed_print("data/skinny64-artificial-skinny384-differential-full.txt", number_of_differentials_full_384);

	/*
	 * Clean up the memory used by the tables.
	*/

	table_fixed_destroy(number_of_differentials_superbox);
	table_fixed_destroy(number_of_differentials_full);
	table_fixed_destroy(number_of_differentials_full_256);
	table_fixed_destroy(number_of_differentials_full_384);
}
