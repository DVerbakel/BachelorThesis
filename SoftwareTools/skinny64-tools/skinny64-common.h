// Written by Denise Verbakel

#ifndef __SKINNY_COMMON_H__
#define __SKINNY_COMMON_H__

/*
 * Include the file needed in this program.
*/

#include "../global-common.h"

/* 
 * Define important parameters specific to Skinny64.
*/

#define NUMBER_OF_SUPERBOXES 4
#define NUMBER_OF_BOXES_IN_SUPERBOX 4
#define MAX_BOX_WEIGHT (2*NUMBER_OF_BOXES_IN_SUPERBOX)
#define BOX_WIDTH 4

/*
 * Define the S-box of Skinny64 and its inverse.
*/

extern const uint8_t sbox[];
extern const uint8_t inv_sbox[];

/*
 * Define three operations of Skinny64.
*/

uint16_t mix_columns(uint16_t);
uint16_t mix_columns_transpose(uint16_t);
uint16_t sub_cells(uint16_t);

#endif
