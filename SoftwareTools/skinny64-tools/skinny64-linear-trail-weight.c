// Written by Denise Verbakel

/*
 * Include the files needed in this program.
*/

#include "skinny64-common.h"
#include "../global-common.h"
#include "../convolution.h"

/*
 * Define useful parameters and a table of integers that holds all possible differences
*/

#define NUMBER_OF_ELEMENTS (1 << BOX_WIDTH)
#define DT_SIZE (NUMBER_OF_ELEMENTS*NUMBER_OF_ELEMENTS)

int correlation_table[DT_SIZE];

/*
 * Count number of input correlations equal to v in column corresponding to output correlation b
*/
void
count_input(mpz_t c, uint16_t b, int v)
{
	mpz_set_ui(c, 0);
	for (int i = 0; i < NUMBER_OF_ELEMENTS; i++) {
		if (abs(correlation_table[NUMBER_OF_ELEMENTS*i+b]) == v) {
			mpz_add_ui(c, c, 1);
		}
	}
}

/*
 * Count number of output differences equal to v in row corresponding to input difference a
*/
void
count_output(mpz_t c, uint16_t a, int v)
{
	mpz_set_ui(c, 0);
	for (int i = 0; i < NUMBER_OF_ELEMENTS; i++) {
		if (abs(correlation_table[NUMBER_OF_ELEMENTS*a+i]) == v) {
			mpz_add_ui(c, c, 1);
		}
	}
}

int
main(void)
{
	/* 
	 * We initialize the table structures, the correlation table and the (big) integers.
	*/

	Table *weights_superbox = table_create();
	Table *bases[MAX_BOX_WEIGHT];	

	fill_correlation_table(correlation_table, sbox, BOX_WIDTH);

	mpz_t row, col, val;
	mpz_inits(row, col, val, NULL);
	mpz_set_ui(col,0);
	mpz_set_ui(row,0);

	/*
	 * We get the linear trail weight by taking the steps below. Some extra comments are added here for clarification.
	 * After having done this, we save the results to the file skinny64-linear-trail-superbox.txt.
	*/

	// The input difference to mix_columns is fixed.
	for (uint32_t b = 0; b <= UINT16_MAX; b++) {
		// The output difference to mix_columns_transpose is computed.
		uint16_t a = mix_columns_transpose(b);	

		// A trail weight histogram for the sboxes before mix_columns_transpose and after mix_columns_transpose is created.
		for (int i = 0; i < MAX_BOX_WEIGHT; i++) {
			bases[i] = table_create();
		}

		/* Because we have the values of 16, (-)4 and (-)8 in the correlation table, we have the following correlation weights:
		 * weight_c = 2 * (4 - log2(16))
		 * weight_c = 2 * (4 - log2(4))
		 * weight_c = 2 * (4 - log2(8))
		 * Now, for fixed b and c, we count the number of input differences having the weight 0, 4 or 2. 
		*/
		for (int i = 0; i < 4; i++) {
			mpz_set_ui(row, 0);
			count_output(val, (b >> 4*i) & 0xf, 16);
			table_insert_and_merge(bases[4+i], row, col, val, &mpz_add);
			count_input(val, (a >> 4*i) & 0xf, 16);
			table_insert_and_merge(bases[i], row, col, val, &mpz_add);

			mpz_set_ui(row, 4);
			count_output(val, (b >> 4*i) & 0xf, 4);
			table_insert_and_merge(bases[4+i], row, col, val, &mpz_add);
			count_input(val, (a >> 4*i) & 0xf, 4);
			table_insert_and_merge(bases[i], row, col, val, &mpz_add);

			mpz_set_ui(row, 2);
			count_output(val, (b >> 4*i) & 0xf, 8);
			table_insert_and_merge(bases[4+i], row, col, val, &mpz_add);
			count_input(val, (a >> 4*i) & 0xf, 8);
			table_insert_and_merge(bases[i], row, col, val, &mpz_add);
		}

		// We convolute the histograms of the sboxes.
		Table *r = table_copy(bases[0]);
		for (int i = 1; i < MAX_BOX_WEIGHT; i++) {
			Table *tmp = convolute(r, bases[i], 0, 0, differential_combiners);	
			table_destroy(r);
			r = tmp;
		}	

		// Step over all of the weights and increment the relevant entries in the histogram of the superbox.
		for (HeadNode *node = r->head; node != NULL; node = node->next_row) {
			table_insert_and_merge(weights_superbox, node->node.row, node->node.col, node->node.val, &mpz_add);
		}

		// Remove all tables used.
		for (int i = 0; i < MAX_BOX_WEIGHT; i++) {
			table_destroy(bases[i]);
		}

		table_destroy(r);
	}
	mpz_clears(row, col, val, NULL);

	// Data: (abs value of correlation numerator, not used, number of masks)
	table_print("data/skinny64-linear-trail-superbox.txt", weights_superbox);

	/*
	 * Convolute the above results of the superboxes in order to compute the histogram of the full state(s). We initialize the 
	 * table structure and save the results to the files skinny64-differential-trail-full.txt,
	 * skinny64-artificial-skinny256-linear-trail-full.txt and skinny64-artificial-skinny384-linear-trail-full.txt.
	*/

	Table *weights_full = convolute_tables(weights_superbox, NUMBER_OF_SUPERBOXES, 0, 0, differential_combiners);
	Table *weights_full_256 = convolute_tables(weights_superbox, NUMBER_OF_SUPERBOXES*4, 0, 0, differential_combiners);
	Table *weights_full_384 = convolute_tables(weights_superbox, NUMBER_OF_SUPERBOXES*6, 0, 0, differential_combiners);

	// Data: (abs value of correlation numerator, not used, number of masks)
	table_print("data/skinny64-linear-trail-full.txt", weights_full);
	table_print("data/skinny64-artificial-skinny256-linear-trail-full.txt", weights_full_256);
	table_print("data/skinny64-artificial-skinny384-linear-trail-full.txt", weights_full_384);

	/*
	 * Clean up the memory used by the tables.
	*/

	table_destroy(weights_superbox);
	table_destroy(weights_full);
	table_destroy(weights_full_256);
	table_destroy(weights_full_384);

	return 0;
}
