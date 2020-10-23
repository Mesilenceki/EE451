#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

char *messages[NUM_THREADS];

struct  thread_data{
   int	thread_id;
   char  *message;
};

struct  thread_data  thread_data_array[NUM_THREADS];

void *PrintHello(void *threadarg){
	struct  thread_data * my_data;
	my_data = (struct thread_data *) threadarg;

	int  thread_id = my_data->thread_id; 
	char *hello_msg = my_data->message;

  printf("Thread %d says %s  \n", thread_id , hello_msg);
	pthread_exit(NULL);
}

int  main(int argc, char *argv[]) {
			pthread_t  threads[NUM_THREADS];
			int *thread_ids[NUM_THREADS];
			int rc, i;
			char * message[NUM_THREADS];
			messages[0] = "Hello!";
			messages[1] = "How are you!";
			messages[2] = "I am good";
			messages[3] = "Thank you";
			for(i=0; i<NUM_THREADS; i++) {	  
				thread_data_array[i].thread_id = i;
				thread_data_array[i].message = messages[i];
				rc = pthread_create(&threads[i], NULL, PrintHello, (void *) &thread_data_array[i] );
				if (rc) { printf("ERROR; return code from pthread_create() is %d\n", rc); exit(-1);}
			}
			pthread_exit(NULL);
}



