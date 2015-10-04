// this program converts an 8bit bniary file to a tiff file


#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "dirent.h"
#include "sys/types.h"
#include "../include/tiffFunc.h"
//#include "sys/dir.h"

int main(int argc, char* argv[]){
	int length,w,i,j;
	double dw,pixeld;
	uint16 pixel,pmax;
	uint32 ImSize;
	uint32 SizeArray[2];
	int32 image[1000*1000];
	char inname[100];
	char outname[]=".tiff";
	FILE *fbnr;
	
	length=0;
	printf("%s\n",argv[1]);
	fbnr=fopen(argv[1],"rb");
	if(!fbnr){
		printf("Unable to open: %s\n",argv[1]);
		return 1;
	}
	while(fread(&pixel,1,1,fbnr)){
	//	printf("%i\n",length++);
		length++;	
	}
	printf("%i\n",length);

	fclose(fbnr);
	fbnr=fopen(argv[1],"rb");
	pmax=0;
	dw=sqrt(length);
	if((dw-(int)dw)==0){
		ImSize = sqrt(length);		
		printf("This is an 8bit image!!\n");
		for(i=0;i<ImSize;i++){
			for(j=0;j<ImSize;j++){
				fread(&image[i*ImSize+j],1,1,fbnr);
			}		
		}
		printf("size: %lf\n",dw);
	}else if((sqrt(length/2)-(int)sqrt(length/2))==0){
		printf("This might be a 12bit image!!\n");
		ImSize = sqrt(length/2);		
		for(i=0;i<length/2;i++){
			fread(&pixel,1,1,fbnr);
			pixeld = (float)pixel;
			fread(&pixel,1,1,fbnr);
			pixeld = 255*pixeld+(float)pixel;
			pixeld = 255*((pixeld))/(4095.0);
//			if(pixeld<0) printf("pixeld: %lf\t image: %i\t",pixeld,image[i*ImSize+j]);	
			image[i]=(unsigned int) pixeld;
			
		};
	}else{
		printf("This is not a square image!\n\n");
		printf("size: %lf\n",dw);
		exit(1);
	}

	uint8 imageTiff[ImSize*ImSize];//malloc(ImSize*ImSize*sizeof(uint8));   
	for(i=0;i<ImSize;i++){
		for(j=0;j<ImSize;j++){
			imageTiff[i*ImSize+j] = (uint8)image[i*ImSize+j];
//			printf("%d\t",image)
		}		
	};
	fclose(fbnr);
	strcpy(inname,argv[1]);
	strcat(inname,outname); 
	printf("Size: %i\toutname: %s\n",ImSize,inname);
	printf("max Int: %i\n",pmax);
	SizeArray[0]=ImSize;
	SizeArray[1]=ImSize;
	WriteTiffgray8(inname,SizeArray,imageTiff);
	// open binary file
	return 0;
}
