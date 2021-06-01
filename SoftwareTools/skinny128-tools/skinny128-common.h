// Written by Denise Verbakel

#ifndef __SKINNY_COMMON_H__
#define __SKINNY_COMMON_H__

/*
 * Include the file needed in this program.
*/

#include "../global-common.h"

/* 
 * Define important parameters specific to Skinny128.
*/

#define NUMBER_OF_SUPERBOXES 4
#define NUMBER_OF_BOXES_IN_SUPERBOX 4
#define MAX_BOX_WEIGHT (2*NUMBER_OF_BOXES_IN_SUPERBOX)
#define BOX_WIDTH 8

/*
 * Define the S-box of Skinny128 and its inverse.
*/

extern const uint8_t sbox[];
extern const uint8_t inv_sbox[];

/*
 * Define three operations of Skinny128.
*/

uint32_t mix_columns(uint32_t);
uint32_t mix_columns_transpose(uint32_t);
uint32_t sub_cells(uint32_t);

#endif
