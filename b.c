
#include<stdio.h> // Standard input and output
#include<pthread.h> // Thread Manipulations

#define MAX  5 // Limits the Computation Time

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int sharedVariable = 2;  // Shared Resource between threads

void * counting_thread(void * arg);

int main(void)
{
	// Thread Spawning
	pthread_t thread1;
	int offset1 = 1;


		pthread_create(&thread1, NULL, counting_thread, &offset1);

	pthread_t thread2;
    int offset2 = -1;

		pthread_create(&thread2, NULL, counting_thread, &offset2);

	// Main Function shouldn't exit before these threads, So, join as a wait system call in thread library
		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);

	printf("Final Value of Shared Variable: %d\n", sharedVariable );

	return 0;
}


void * counting_thread(void * arg)
{
    for(int i = 0; i < MAX; i++)
    {
	int offset = * (int *) arg;

	pthread_mutex_lock(&mutex);

// Critical Section Starts

	sharedVariable += offset;
	printf("%d\n", sharedVariable);
// Critical Section ends
	pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL); // thread returns NULL Value, more like return or exit in main()
}
