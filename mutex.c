#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "linked_list.h"

#include <sys/time.h>

#define MAX 65535

void *threadFunc(void* rank);

pthread_mutex_t mutex;
node *head = NULL;

int thread_count = 5; // Number of threads 
int m = 1000; //Number of operations
float mmem = 0.99;
float mins = 0.005;
float mdel = 0.005;

// Fractions of each operation
int Mem,Ins,Del;

int insOps = 0;
int memOps= 0;
int delOps = 0;
int totOps=0;

int main(){

    int n = 100; //Number of elements in the list
    int count = 0;
    

    // Generate a linked list with n random numbers
    srand(time(0));
    while (count<n){
        Insert(rand()%MAX, &head);
        count++ ;
    }

    Mem = (int) (m * mmem);
    Ins = (int)(m * mins);
    Del= (int)( m * mdel);
    
    // Initializing the mutex
    pthread_mutex_init(&mutex, NULL);

    // Generate Threads
    
    pthread_t *thread_handles = malloc(thread_count * sizeof(pthread_t));
    struct timeval stop;
    struct timeval start;
    gettimeofday(&start, NULL); 
    //Assign work to threads
    for (int thread=0; thread<thread_count ; thread++){
        pthread_create(&thread_handles[thread],NULL,threadFunc,(void*) thread);
    }

    printf("Hello from main thread\n");

    for (int thread=0; thread<thread_count ; thread++){
        pthread_join(thread_handles[thread],NULL);
    }

    free(thread_handles);
    
    //Function call
    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 

    destructor(head);
    return 0;
}

void *threadFunc(void * rank){
    long my_rank = (long) rank;
    while (totOps< m){
        
        int rand_value = rand() % MAX;

        int op = rand() % 3;

        if (op==0 && insOps < Ins){
            pthread_mutex_lock(&mutex);
            if (totOps<m){
                short res = Insert(rand_value, &head);
                insOps++;
                totOps++;
                printf("Thread %ld Operation %d , Insert %d %d\n", rank, totOps, rand_value, res);
            }
            pthread_mutex_unlock(&mutex);
        }
        else if(op==1 && delOps < Del){
            pthread_mutex_lock(&mutex);
            if (totOps<m){
                short res = Delete(rand_value, &head);
                delOps++;
                totOps++;
                printf("Thread %ld Operation %d , Delete %d %d\n", rank, totOps, rand_value, res);
            }
            pthread_mutex_unlock(&mutex);
            
        }
        else if(op==2 && memOps < Mem){
            pthread_mutex_lock(&mutex);
            if (totOps<m){
                short res = Member(rand_value, head);
                memOps++;
                totOps++;
                printf("Thread %ld Operation %d , Search %d %d\n", rank, totOps, rand_value, res); 
            }
            pthread_mutex_unlock(&mutex);
        }
    }

    
}