#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

double **naiveMethod(int n, double **A, double **B, double **C);
void **parallelMethod(void *threadarg);
void initMatrix(double **A, double **B, double **C);

typedef thread_data {
    int n;
    int bw;
    double **A;
    double **B;
    double **C;
};

int main(int argc, char *argv[]) {
    int n = 4096;
    int num_thread = atoi(&argv[1]);
    double time;
    struct timespec start, stop;

    double **A = (double**)malloc(sizeof(double*)*n);
    double **B = (double**)malloc(sizeof(double*)*n);
    double **C = (double**)malloc(sizeof(double*)*n);

    for (int i=0; i<n; i++) {
        A[i] = (double**)malloc(sizeof(double)*n);
        B[i] = (double**)malloc(sizeof(double)*n);
        C[i] = (double**)malloc(sizeof(double)*n);
    }
    //initialize the matrix
	initMatrix(n, A, B, C);

	if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
		
	// Your code goes here //
	// Matrix C = Matrix A * Matrix B //	
	//*******************************//
    C = naiveMethod(n, A, B, C);
	//*******************************//
		
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}		
	time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
		
	printf("Number of FLOPs = %u, Execution time = %f sec,\n%lf MFLOPs per sec\n", 2*n*n*n, time, 1/time/1e6*2*n*n*n);		
	printf("C[100][100]=%f\n", C[100][100]);
    
    //initialize the matrix
    initMatrix(n, A, B, C);

    if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
		
	// Your code goes here //
	// Matrix C = Matrix A * Matrix B //	
	//*******************************//

    //use the pthread to do matrix mulptication
    pthread_t threads[num_thread];
    int blockwidth = n/num_thread;
    //create thread
    for (int th=0; th<num_thread; th++) {
        int *p;
        pthread_create(&threads[th], NULL, parallelMethod, (void*)(p))
    }

    for (int th=0; th<num_thread; th++) {
        pthread_join(threads[th], NULL);
    }
	//*******************************//
		
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}		
	time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
		
	printf("Number of FLOPs = %u, Execution time = %f sec,\n%lf MFLOPs per sec\n", 2*n*n*n, time, 1/time/1e6*2*n*n*n);		
	printf("C[100][100]=%f\n", C[100][100]);

    // release momory to avoid overflow
    for (int i=0; i<n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
    return 0;
}

double **naiveMethod(int n, double** A, double **B, double **C) {
    for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                for (int k=0; k<n; k++) {
                    C[i][j] += A[i][k]*B[k][j];
                }
            }
        }
    return C;
}

void **parallelMethod(void *threadarg) {
    struct thread_data *p_data;
    p_data = (struct thread_data *) threadarg;
    int bw = p_data->bw;
    int n = p_data->n;

    for (int i=0; i<n; i+=) {
        for (int j=0; j<n; j+=bw) {
            for (int k=0;k<bw;k++) {
                (p_data->C)[i][j] += (p_data->A)[i][k]*(p_data->B)[k][j];
            }
        }
    }
}

void initMatrix(int n, double **A, double **B, double **C) {
    for (int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			A[i][j]=i;
			B[i][j]=i+j;
			C[i][j]=0;			
		}
	}
}