#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
//#include <omp.h>

#define h  800 
#define w  800
#define cluster_num 4
#define input_file  "input.raw"
#define output_file "output.raw"

int main(int argc, char** argv){
    int i;
    FILE *fp;
	struct timespec start, stop; 
	double time;

  	unsigned char *a = (unsigned char*) malloc (sizeof(unsigned char)*h*w);
    unsigned int *b = (unsigned int*) malloc (sizeof(unsigned int)*h*w);
	// the matrix is stored in a linear array in row major fashion
	if (!(fp=fopen(input_file, "rb"))) {
		printf("can not opern file\n");
		return 1;
	}
	fread(a, sizeof(unsigned char), w*h, fp);
	fclose(fp);
    
	// measure the start time here
	if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) { perror( "clock gettime" );}
	//  Your code goes here
	float centroid[cluster_num] = {0, 85, 170, 255};
	float sum[cluster_num] = {0, 0, 0, 0};
	int count[cluster_num] = {0, 0, 0, 0};
	int belonging_temp = -1;
	float dist_temp;
	float dist_min;
	//if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
	//compute the distance from each point to the centroids
	for (int epoch=0; epoch<30; epoch++) {
		for (int i=0; i<h*w; i++) {
			dist_temp = 0;
			dist_min = __DBL_MAX__; 
			
			for (int j=0; j<cluster_num; j++) {
				dist_temp = (a[i]>centroid[j]) ? a[i]-centroid[j]:centroid[j]-a[i];
				if (dist_temp<dist_min) {
					dist_min = dist_temp;
					belonging_temp = j;
				}
			}
			b[i] = belonging_temp;
			count[belonging_temp]+=1;
			sum[belonging_temp]+=a[i];
			
		}

		//recompute each centroids

		for (int j=0; j<cluster_num; j++) {
			centroid[j] = sum[j] / count[j];
			count[j] = 0;
			sum[j] = 0;
		}
	}
	
	//output the final points
	for (int i=0; i<h*w; i++) {
		a[i] =(unsigned char) centroid[b[i]];
	}
	
	// measure the end time here
	if (clock_gettime(CLOCK_REALTIME, &stop) == -1) { perror("clock gettime"); }
	time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	// print out the execution time here
	printf("Execution time = %f sec", time);
	
	if (!(fp=fopen(output_file,"wb"))) {
		printf("can not opern file\n");
		return 1;
	}	
	fwrite(a, sizeof(unsigned char),w*h, fp);
    fclose(fp);
    free(a);
	free(b);
    return 0;
}