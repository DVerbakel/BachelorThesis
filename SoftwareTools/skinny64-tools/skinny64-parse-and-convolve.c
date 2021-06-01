// Written by Denise Verbakel

/*
 * Include the files needed in this program.
*/

#include "skinny64-common.h"
#include "../convolution.h"
#include "../csvparser.h"

int 
main(void) 
{
	/* 
	 * We initialize the table structure and after this the (big) integers.
	*/

	Table *superbox = table_create();

	mpz_t row, col, val;
	mpz_inits(row, col, val, NULL);
	mpz_set_ui(col, 0);

	/*
	 * We read in the file called skinny64-linear-weight-superbox.txt and save this file inside the table
	 * structure called superbox. The arguments of CsvParser_new represent respectively the file, the
	 * delimiter and 0 states that the first line is the header line.
	*/

	CsvParser *csvparser = CsvParser_new("data/skinny64-linear-weight-superbox.txt", ",", 0);
	CsvRow *line;

	while ((line = CsvParser_getRow(csvparser)) ) {
       		const char **lineFields = CsvParser_getFields(line);
		mpz_set_str(row, lineFields[0], 10);
		mpz_set_str(val, lineFields[1], 10);
		table_insert_and_merge(superbox, row, col, val, &mpz_add);
        	CsvParser_destroy_row(line);
	}	
	CsvParser_destroy(csvparser);

	mpz_clears(row, col, val, NULL);

	/*
	 * Convolute the above results of the superboxes in order to compute the histogram of the full state(s). 
	 * We initialize the table structure and save the results to the files skinny64-linear-weight-full.txt,
	 * skinny64-artificial-skinny256-linear-weight-full.txt and 
	 * skinny64-artificial-skinny384-linear-weight-full.txt.
	*/

	Table *full_state = convolute_tables(superbox, NUMBER_OF_SUPERBOXES, 0, 0, differential_combiners);
	Table *full_state_256 = convolute_tables(superbox, NUMBER_OF_SUPERBOXES*4, 0, 0, differential_combiners);
	Table *full_state_384 = convolute_tables(superbox, NUMBER_OF_SUPERBOXES*6, 0, 0, differential_combiners);

	// Data: (linear approximation weight, not used, number of linear approximations)
	table_print("data/skinny64-linear-weight-full.txt", full_state);
	table_print("data/skinny64-artificial-skinny256-linear-weight-full.txt", full_state_256);
	table_print("data/skinny64-artificial-skinny384-linear-weight-full.txt", full_state_384);

	/*
	 * Clean up the memory used by the tables.
	*/

	table_destroy(superbox);
	table_destroy(full_state);
	table_destroy(full_state_256);
	table_destroy(full_state_384);
	
	return 0;
}
