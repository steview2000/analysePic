/* tiffTest.c
 * this is for testing the TIFF - functions, writen in tiffFunc.h 
 */

#include "tiffio.h"
#include "stdio.h"
#include "../include/tiffFunc.h"


int main(){
	int i,j;
	uint32 ImSize[2];
	CheckTiffSize("in.tif",ImSize);
	uint8 image[ImSize[0] *ImSize[1] ];
	ReadTiffgray8("in.tif",ImSize,image);
	
	printf("Oben: %i\n Unten: %i",image[10],image[30000]);
	
	WriteTiffgray8("out.tif",ImSize, image);
	printf("\n keineFehler\n");
	return 0;
}


