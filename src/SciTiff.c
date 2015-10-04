#include "stdio.h"
#include "tiffFunc.h"



// Reads TIFF images and gives them back as matrix

void ReadTiffgray8(char *arg, uint8 (*image)[ImWidth]){
	int i,j;
	TIFF* tif;
	tif=TIFFOpen(arg,"r");
	if (tif) {
		uint32 w, h;
		size_t npixels;
		uint32 *raster;

		TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
		TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
		if((h!=ImHeight)||(w!=ImWidth)){
			printf("Wrong ImageSize. Change tiffFunc.h !\n");
			printf("h: %i\n w: %i\n",h,w);
			exit(-1);
		}
	npixels = w*h;
	raster = (uint32 *) _TIFFmalloc(npixels * sizeof (uint32));
	if (raster != NULL){
	  if (TIFFReadRGBAImage(tif, w, h, raster, 0)){
		for(i=0;i<h;i++){
		 for(j=0;j<w;j++){
		    image[i][j] = (uint8)raster[i*w+j];
		 }

		}
	  }
	  _TIFFfree(raster);
		}

			
	}
	else {
	  printf("File %s not available !\n",arg);
	  exit(-1);
	}	
	TIFFClose(tif);	

}

void WriteTiffgray8(char *arg, uint8 (*image)[ImWidth]){
	int i,j;
	unsigned long		stripBytes;
	unsigned long		numStrips;
	unsigned short		bitsPerSample;
	unsigned short		samplesPerPixel;
	unsigned short		photometric;
	numStrips = ImHeight;
	stripBytes=ImHeight*ImWidth;
	TIFF* tiffout;
	//write lines to out.tif
	tiffout=TIFFOpen(arg,"w");
	
	TIFFSetField( tiffout, TIFFTAG_ROWSPERSTRIP,  (unsigned short)1 );
	TIFFSetField( tiffout, TIFFTAG_BITSPERSAMPLE,  (unsigned short)8 );
	TIFFSetField( tiffout, TIFFTAG_SAMPLESPERPIXEL,  (unsigned short)1);

	TIFFSetField(tiffout, TIFFTAG_IMAGEWIDTH,ImWidth);
	TIFFSetField(tiffout, TIFFTAG_IMAGELENGTH,ImHeight);
	TIFFSetField(tiffout, TIFFTAG_PHOTOMETRIC, (unsigned short) 1 );
	TIFFSetField(tiffout, TIFFTAG_PLANARCONFIG, (unsigned short) 1);
	TIFFSetField( tiffout, TIFFTAG_COMPRESSION, ( unsigned short ) 1 );	// None
	unsigned char ima[ImHeight*ImWidth];
	for (i=0;i<ImHeight;i++){
		for(j=0;j<ImWidth;j++){
			 ima[i*ImWidth+j]=(unsigned char)image[i][j];
			// printf("%i ",ima[i*ImWidth+j]);
		}
	};
	char * pointim;
	unsigned char* srcPtr = ( unsigned char* )( ima );
	unsigned long strip;
	for ( strip = 0; strip < numStrips; strip++ )
	{
		TIFFWriteEncodedStrip( tiffout, strip, srcPtr, stripBytes );
		srcPtr += ImWidth;
	}
	TIFFClose(tiffout);

}
