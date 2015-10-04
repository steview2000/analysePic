#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "fftFunc.h"

void ffts1(double *y, double sr, double *fx, double *fyn);


/********* 2dim FFT   **********
*			       *
*			       *
*  y  ... values to transform  *
*  fY ... Fourier-Trafor of y  *
*  fX ... Scale for x	       *
*  sr ... scales pixel/mm      *
********************************/


void ffts2(double *y, unsigned int *ImSize, double *fY ){	
	int i,j;
	int32 h,w;
	h = ImSize[0];
	w = ImSize[1];
	double *tempFY = (double *) malloc(h * w * sizeof(double));
	fftw_complex *in, *out;
	fftw_plan p;
	
	in = (fftw_complex* ) fftw_malloc(sizeof(fftw_complex) * h * w);
	out = (fftw_complex* ) fftw_malloc(sizeof(fftw_complex) * h * w);

	for(i=0;i<(w * h);i++){
		in[i][0] = y[i];
		in[i][1] = 0;
	} 

	p =fftw_plan_dft_2d(h, w, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	fftw_destroy_plan(p);
	FILE *fp;
	fp=fopen("mat.txt","w");
	for(i=0;i<h;i++){
	   for(j=0;j<w;j++){
		fprintf(fp,"%lf ",hypot(out[i*w+j][0],out[i*w+j][1]));
	   }
	   fprintf(fp,"\n");
	}
	fclose(fp);

       	for(i = (h/2+1);i<h;i++){
		for(j = (w/2+1); j<w; j++){
			fY[ (i-(h/2+1))*w + j-(w/2+1)] = hypot(out[(i*w + j)][0],out[ (i*w + j )][1]);
		}
		for(j=0;j<(w/2+1); j++){	
			fY[((i-(h/2+1))*w+j+w/2-1)] = hypot(out[i*w + j][0],out[i*w + j][1]);
		}	
			
	}
       	for(i=0;i<(h/2+1);i++){
		for(j = (w/2+1);j<w;j++){
			fY[  (i+h/2-1)*w + j-(w/2+1)] = hypot(out[i*w + j][0],out[i*w + j][1]);
		}
		for(j=0;j<(w/2+1);j++){	
			fY[(i+h/2-1)*w+j+w/2-1] = hypot(out[i*w + j][0],out[i*w + j][1]);
		}	
			
	}
 
//	for(i=0;i<(h*w);i++){
//		fY[i] = hypot(out[i][0],out[i][1]);
//	}
      fftw_free(in);
      fftw_free(out);

	// Transform the matrix

			
}


/*
int main(){
	float y[1000];
	float fy[1000];
	double x;
	int i;
	FILE *fin,*fout;
		

	fftw_complex *in, *out;
	fftw_plan p;
		
	in = (fftw_complex* ) fftw_malloc(sizeof(fftw_complex) * 1000);
	out = (fftw_complex* ) fftw_malloc(sizeof(fftw_complex) * 1000);
	p =fftw_plan_dft_1d(1000, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	
	//iin =y;
	 
	for(i=0;i<1000;i++){
		x=(double)i/50;
		in[i][0]=sin(2*x);//+cos(10*x);
		printf("sin(%lf) = %lf\n",x,sin(2*x));
	} 
	//iin = y;
	
	fftw_execute(p);
	//fy=&out;
	fin=fopen("fin.txt","w");
	fout=fopen("fout.txt","w");
	for(i=0;i<1000;i++){
		fprintf(fin,"%f\n",in[i][0]);
		fprintf(fout,"%lf\n",out[i][0]*out[i][0]+out[i][1]*out[i][1]);
	};

	fclose(fin);
	fclose(fout);
	fftw_destroy_plan(p);
	fftw_free(in); fftw_free(out);
	
	
	//creating a nice sinus wave
	return 0;
}*/
