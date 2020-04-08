#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

#define MAX  5 // Limits the Computation Time

sem_t mutex1,mutex2, mutex3;

int sharedVariable = 2;

void* thread1(void* arg);
void* thread2(void* arg);
void* thread3(void* arg);

int main()
{
	sem_init(&mutex1, 0, 1);
	sem_init(&mutex2, 0, 1);
	sem_init(&mutex3, 0, 1);


	pthread_t t1,t2, t3;

	int offset1 = -1;
	int offset2 = 0;
	int offset3 = 1;

// Spawn Threads

	pthread_create(&t1,NULL,thread1,&offset1);
	pthread_create(&t2,NULL,thread2,&offset1);
	pthread_create(&t3,NULL,thread3,&offset1);

// Wait for threads to complete

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t2,NULL);

	printf("\nFinal Value of Shared Variable: %d", sharedVariable);

// Free Mutex Locks

	sem_destroy(&mutex1);
	sem_destroy(&mutex2);
	sem_destroy(&mutex3);
	return 0;
}




void* thread1(void* arg)
{
	for(int i = 0; i < MAX; i++)
    {

	int offset = * (int *) arg;

	sem_wait(&mutex1);
	sem_wait(&mutex2);
	sleep(2);
	sem_wait(&mutex3);

// Critical Section Starts

	sharedVariable += offset;
	printf("%d\n", sharedVariable);

// Critical Section ends
	sem_post(&mutex1);
	sem_post(&mutex2);
	sem_post(&mutex3);
    }

	return 0;

}

void* thread2(void* arg)
{
	for(int i = 0; i < MAX; i++)
    {

	int offset = * (int *) arg;

	sem_wait(&mutex3);
	sem_wait(&mutex1);
	sleep(2);
	sem_wait(&mutex2);

// Critical Section Starts

	sharedVariable += offset;
	printf("%d\n", sharedVariable);

// Critical Section ends
	sem_post(&mutex3);
	sem_post(&mutex1);
	sem_post(&mutex2);
    }

	return 0;

}


void* thread3(void* arg)
{
	for(int i = 0; i < MAX; i++)
    {

	int offset = * (int *) arg;

	sem_wait(&mutex2);
	sem_wait(&mutex3);
	sleep(2);
	sem_wait(&mutex1);

// Critical Section Starts

	sharedVariable += offset;
	printf("%d\n", sharedVariable);

// Critical Section ends
	sem_post(&mutex2);
	sem_post(&mutex3);
	sem_post(&mutex1);
    }

	return 0;
}

