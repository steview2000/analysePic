#include <stdio.h>

int main(){
	FILE *fp;
	int i;
	unsigned int a[1000];
//	char a[10000];	
	i=1;
	fp=fopen("test.tif","r");
	while(i<100){
		fscanf(fp,"%ui",a[i]);
		printf("\n %i\t%c",i,a[i]);
		i++;
	} 	
	printf("i: %i",i);	
	fclose(fp);
	return 0;
}
