#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define		num_of_points	   40000000
#define     num_of_threads     2
typedef struct{
	double x;  
	double y;
    double tmp;
}Point; 

int main(void){
	int i;
	int num_of_points_in_circle;
	double pi;
	struct timespec start, stop; 
	double time;
	int chunk = num_of_points / 
	Point * data_point = (Point *) malloc (sizeof(Point)*num_of_points);
	omp_set_num_threads(num_of_threads)
	for(i=0; i<num_of_points; i++){
		data_point[i].x=(double)rand()/(double)RAND_MAX;
		data_point[i].y=(double)rand()/(double)RAND_MAX;
        data_point[i].tmp=0;
	}
	num_of_points_in_circle=0;
	
	if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
	
	
	////////**********Use OpenMP to parallize this loop***************//
	#pragma omp parallel default(data_point, num_of_points_in_circle) private(i)
	{
        #pragma omp sections nowait reduction(+:data_point.tmp)
        {
            #pragma omp section 
		    for(i=0; i<num_of_points/2; i++) {
			    data_point[i].tmp+=data_point[i].x-0.5)*(data_point[i].x-0.5);
		    }

            #pragma omp section
            for(i; i<num_of_points; i++) {
                data_point[i].tmp+=data_point[i].y-0.5)*(data_point[i].y-0.5);	
            }

            #pragma omp section
            for (i=0; i<num_of_points; i++) {
                if (data_point[i].tmp<=0.25) {
                    num_of_points_in_circle++;
                }
            }
        } /* end of sections */
	} /* end of parallel region */
		
	///////******************************////
	
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}		
	time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
		
	pi =4*(double)num_of_points_in_circle/(double)no_of_points;
	printf("Estimated pi is %f, execution time = %f sec\n",  pi, time);		
}	