#ifndef CUS_LINKED_LIST_H
#define CUS_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct node {
  int data;
  struct node *next;
  pthread_mutex_t mutex;
}node;

int Member(int value, node* head_p);
int Insert(int value, node ** head_p);
int Delete(int value, node ** head_p);


#endif