#include <stdlib.h>
#include <stdio.h>

int main(){
	int i[2];
	float a;
	a=0.9;
	i[0] = 0;
	i[1] = 1;	
	printf("100: %i\n",i[(int) a] );
	return 0;
}
