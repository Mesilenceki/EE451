/***** Using mutex and condition variable to 
 * implementation synchronization instead of 
 * iteratively join and create. *****/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

#define p 10
#define h 800
#define w 800
#define cluster_num 4
#define input_file "input.raw"
#define output_file "output.raw"

struct data_partition{
    int thread_id;
    int N;
    int num_clusters;
    unsigned char *data;
    unsigned int *cluster_dict;
    float *clusters;
    float *sums;
    float *counts;
    int num_threads;
};

pthread_mutex_t mu;

int main(int argc, char **argv) {
    int i;
    FILE *fp;
    struct timespec start, stop;
    double time;

    unsigned char *a = (unsigned char*) malloc(sizeof(unsigned char)*h*w);
    unsigned int *b = (unsigned int*) malloc (sizeof(unsigned int)*h*w);
    unsigned int n = h*w;
    int rc;
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
    int num_threads = p;
    int num_iterations = 50;
    int num_clusters = cluster_num;
    float centroids[] = {0, 65, 100, 125};
    float sums[] = {0, 0, 0, 0};
    float counts[] = {0, 0, 0, 0};

    pthread_t threads[num_threads];
    pthread_mutex_init(&mu, NULL);
    for (unsigned int iter=0; iter<num_iterations; iter++) {
        for (unsigned int i=0; i<num_threads; i++) {

        }
    }

}   