#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#include "linked_list.h"
#include "serial.h"

#define MAX 65535

unsigned long test_serial_run(void){

    node *head = NULL;

    int m = 1000; //Number of operations
    float mmem = 0.99;
    float mins = 0.005;
    float mdel = 0.005;

    // Fractions of each operation
    int Mem = (int) (m * mmem);
    int Ins = (int)(m * mins);
    int Del= (int)( m * mdel);

    int insOps = 0;
    int memOps= 0;
    int delOps = 0;
    int totOps=0;

    int n = 100; //Number of elements in the list
    int count = 0;

    // Generate a linked list with n random numbers
    srand(time(0));
    while (count<n){
        Insert(rand()%MAX, &head);
        count++ ;
    }
    
    struct timeval stop;
    struct timeval start;
    gettimeofday(&start, NULL); 

    while (totOps< m){
        
        int rand_value = rand() % MAX;

        int op = rand() % 3;

        if (op==0 && insOps < Ins){
            short res = Insert(rand_value, &head);
            insOps++;
            totOps++;
            //printf("Operation %d , Insert %d %d\n", totOps, rand_value, res);
        }
        else if(op==1 && delOps < Del){
            short res = Delete(rand_value, &head);
            delOps++;
            totOps++;
            //printf("Operation %d , Delete %d %d\n", totOps, rand_value, res);
        }
        else if(op==2 && memOps < Mem){
            short res = Member(rand_value, head);
            memOps++;
            totOps++;
            //printf("Operation %d , Search %d %d\n", totOps, rand_value, res);
        }
    }

    gettimeofday(&stop, NULL);
    unsigned long time;
    time = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
    //printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 

    destructor(head);
    return time;
}