#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "linked_list.h"

#define SERIAL_RUN
//#define CON_ONE_MUTEX
//#define CON_RD_WR_LOCK

void generate_report();

int main(){

    node *head = NULL;

    #ifdef SERIAL_RUN
        printf("Running in serial mode\n");
        int res;
    for (size_t i = 0; i < 10; i++){
        res = Insert((i+1)*2, &head);
        printf("result of insert %ld %d\n", i, res);
    }
    Print(head);

    for (size_t i = 1; i < 10; i++){
        res = Insert(i*2 - 1, &head);
        printf("result of insert %ld %d\n", i, res);
    }
    Print(head);

    for (size_t i = 0; i < 5; i++){
        res = Delete((i+1)*3, &head);
        printf("result of delete %ld %d\n", (i+1)*3, res);
    }
    Print(head);

    for (size_t i = 1; i <= 6; i++){
        res = Member(i*2, head);
        printf("result %ld %d\n", i*2, res);
    }
    
    #endif

    #ifdef CON_ONE_MUTEX
        printf("Running in concurrent mode with one mutex\n");
    #endif

    #ifdef CON_RD_WR_LOCK
        printf("Running in concurrent mode with read write locks\n");
    #endif

    destructor(head);
    return 0;
}