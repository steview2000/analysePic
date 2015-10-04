#include "stdio.h"
#include "stdlib.h"
#include "fftFunc.h"
#include "tiffFunc.h"


int main(int argc,char *argv[]){
	uint32 ImSize[2];
	int i,j,cor;
	printf("%s\n",argv[1]);
	CheckTiffSize(argv[1],ImSize); 

	uint8 image[ImSize[0] * ImSize[1]];
	uint8 imout[ImSize[0]*ImSize[1]];;
	double *fY;
	fY = (double *) malloc(sizeof(double)*ImSize[1]*ImSize[0]); 
	double temp[ImSize[0]*ImSize[1]];// = (double *) malloc(sizeof(double)*ImSize[1]*ImSize[0]);
	double maxin,maxout,minin,minout;
	maxin=0;
	maxout=0;
	minin=300;
	minout=100000;

//******* Reads TIFF ********
	ReadTiffgray8(argv[1],ImSize,image);

	for (i = 0;i<(ImSize[0]*ImSize[1]);i++){
		 temp[i] = (double) image[i];
		 maxin = (maxin>temp[i]) ? maxin : temp[i];
		 minin = (minin<temp[i]) ? minin : temp[i]; 
	}
   
	ffts2(temp,ImSize,fY);	

	for (i = 0;i<(ImSize[0]*ImSize[1]);i++){
		 maxout = (maxout>fY[i]) ? maxout : fY[i];
		 minout = (minout<fY[i]) ? minout : fY[i]; 
	}
	FILE *fp;
	double sum;
	sum=0;
	fp=fopen("matr.txt","w");
	for (i = 0;i<(ImSize[0]*ImSize[1]);i++){
		temp[i]=(fY[i]-minout)*100000/(maxout-minout) ;
		imout[i] = (uint8) ((temp[i]>255) ? 255 : temp[i]);
	}
	fclose(fp);
	printf("maxin: %f\n minin: %f\nmaxout: %f\n minout: %f\n",maxin,minin,maxout,minout);	
	printf("sum: %lf\n",sum);
	WriteTiffgray8("fftest.tif",ImSize,imout);
	return 0;	
}

