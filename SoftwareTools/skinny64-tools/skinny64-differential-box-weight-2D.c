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

	Table *box_weights_superbox = table_create();
	
	mpz_t row, col, val;
	mpz_inits(row, col, val, NULL);
	mpz_set_ui(col,0);
	mpz_set_ui(val,1);

	/*
	 * We get the box weight using the function box_weight32 defined in global-common.c. We compute the box weight of the input a and set it to 
	 * the row. Similarly, we compute the box weight of the output MixColumns(a) and set it to the column. We merge the entries with the same
	 * combinations for the pair (input,output) in a table. Lastly, we save the results to the file skinny64-differential-box-superbox-2D.txt.
	*/

	for (uint32_t a = 0; a <= UINT16_MAX; a++) {
		mpz_set_ui(row, box_weight32(a, NUMBER_OF_BOXES_IN_SUPERBOX, BOX_WIDTH));
		mpz_set_ui(col, box_weight32(mix_columns(a), NUMBER_OF_BOXES_IN_SUPERBOX, BOX_WIDTH));
		table_insert_and_merge(box_weights_superbox, row, col, val, &mpz_add);
	}
	
	mpz_clears(row, col, val, NULL);
	
	// Data: (box weight input, box weight output, number of differences) 
	table_print("data/skinny64-differential-box-superbox-2D.txt", box_weights_superbox);
	
	/*
	 * Clean up the memory used by the table.
	*/

	table_destroy(box_weights_superbox);
	
	return 0;
}
