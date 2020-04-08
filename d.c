#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include<pthread.h>
#include<semaphore.h>

sem_t s1,s2,s3;

int shared=10;

void *fun1(){
    int x;
    sem_wait(&s1);
    sleep(2);
    sem_wait(&s2);
    sem_wait(&s3);
    x=shared;
    x++;

    shared = x;
    sem_post(&s1);
    sem_post(&s2);
    sem_post(&s3);
}
void *fun3(){
    int x ;
    sem_wait(&s3);
    sem_wait(&s1);
    sleep(2);
    sem_wait(&s2);
    x=shared;
    x--;

    shared=x;
    sem_post(&s3);
    sem_post(&s1);
    sem_post(&s2);
}
void *fun2(){
    int x ;
    sem_wait(&s2);
    sem_wait(&s3);
    sleep(2);
    sem_wait(&s1);
    x=shared;
    x--;
    shared=x;
    sem_post(&s2);
    sem_post(&s3);
    sem_post(&s1);

}

int main(){

   sem_init(&s1,0,1);
   sem_init(&s2,0,1);
   sem_init(&s3,0,1);

   pthread_t t1,t2,t3;


    pthread_create(&t1,NULL,fun1,NULL);
    pthread_create(&t2,NULL,fun2,NULL);
    pthread_create(&t3,NULL,fun3,NULL);
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    
    printf("Shared variable is : %d",shared);
}