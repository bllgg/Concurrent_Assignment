#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "linked_list.h"

int main(){
    node *head = NULL;
    //head = constructor();
    int res;
    for (size_t i = 0; i < 10; i++)
    {
        res = Insert((i+1)*2, &head);
        printf("result of insert %ld %d\n", i, res);
    }
    Print(head);

    for (size_t i = 1; i < 10; i++)
    {
        res = Insert(i*2 - 1, &head);
        printf("result of insert %ld %d\n", i, res);
    }
    Print(head);

    for (size_t i = 0; i < 5; i++)
    {
        res = Delete((i+1)*3, &head);
        printf("result of delete %ld %d\n", (i+1)*3, res);
    }
    Print(head);

    for (size_t i = 1; i <= 6; i++)
    {
        res = Member(i*2, head);
        printf("result %ld %d\n", i*2, res);
    }
    
    destructor(head);
    return 0;
}