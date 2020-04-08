
#include<stdio.h> // standard Input and Output console library
#include<stdlib.h> // Random Function's Library
#include<unistd.h> // Sleep Function's Library
#include<pthread.h> // thread Manipulations
#include<semaphore.h> // Synchronization tool

pthread_mutex_t x,wsem; // Read and Write Semaphores


int readcount; // Counter Variable for Counting the operation and Synchronize with other operations

void * reader (void * param);
void * writer (void * param);

int main()
{
    int n1,n2,i;
    pthread_t tid[n1+n2];

    printf("\n Enter the number of Readers: ");
    scanf("%d",&n1);

    printf("\nEnter the number of Writers: ");
    scanf("%d",&n2);

    for(i=0;i<n1;i++)
        pthread_create(&tid[i],NULL,reader,NULL);

    for(i=0;i<n2;i++)
        pthread_create(&tid[i],NULL,writer,NULL);

    for(i = 0; i < (n1 + n2); i++)
    {
    pthread_join(tid[i], NULL);
    }
    sleep(30);
    exit(0);
}


void * reader (void * param)
{
    int waittime;
    waittime = rand() % 5;
    printf("\nReader is trying to enter");
    pthread_mutex_lock(&x);
    readcount++;
    if(readcount==1)
        pthread_mutex_lock(&wsem);
    printf("\n%d Reader is inside ",readcount);
    pthread_mutex_unlock(&x);
    sleep(waittime);
    pthread_mutex_lock(&x);
    readcount--;
    if(readcount==0)
        pthread_mutex_unlock(&wsem);
    pthread_mutex_unlock(&x);
    printf("\nReader is Leaving");
    sleep(30);
    exit(0);
}

void * writer (void * param)
{
    int waittime;
    waittime=rand() % 3;
    printf("\nWriter is trying to enter");
    pthread_mutex_lock(&wsem);
    printf("\n\nWrite has entered");
    sleep(waittime);
    pthread_mutex_unlock(&wsem);
    printf("\nWriter is leaving\n");
    sleep(30);
    exit(0);
}
