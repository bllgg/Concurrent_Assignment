#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int content;
  struct node *next;
}node; 

node *constructor() {
  node *head = NULL;

  head = (node *)malloc(sizeof(node)); //because we allocate memory in heap we need to deallocate after using it
  head->content = NULL;
  head->next = NULL;

  return head;
}

void destructor(node *head) {
  node *del_node = head;
  node *next_node = NULL;

  while (NULL != del_node)
  {
    next_node = del_node ->next;
    printf("destructed node %d\n",del_node->content);
    free(del_node);
    del_node = next_node;
  }
}


void insert(node *head, int content){
  node *curr = head;
  node *new_node = NULL;

  while (NULL != curr->next) //Go to the tail of the list
  {
    curr = curr->next;
  }
  if (NULL != head->content)
  {
    new_node = (node *) malloc(sizeof(node));
    new_node->content = content;
    new_node->next = NULL;
    curr->next = new_node; //linking to the last node.
    printf("New node %d has been inserted\n", new_node->content);
  }
  else
  {
    head->content = content;
  }
}



int compare(int content_1, int content_2) {
  if (content_1 == content_2)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

node* delete(node *head, int content) { // deletion will remove the first node with the matching content.
  node *curr = head;
  node *prev = NULL;
  node *next = NULL;
  int x = 0;

  while(NULL != curr->next) { // search the linked list
    x = compare(curr->content,content);
    if(x == 1)
      break;
    else
      prev = curr;
      curr = curr->next;
  }

  if(curr != NULL) {
    if(NULL == prev) {
      head = curr->next;
      printf("Successfully deleted head %d\n",curr->content);
      free(curr);
    }
    else {
      next = curr->next; // get next node
      if(prev != NULL) prev->next = next;
      printf("Successfully deleted %d\n",curr->content);
      free(curr);

    }
    printf("content of %d\n",head ->content);
  }
  return head;
  
}

void print_linked_list(node *head) {
  node *curr = head;

  while(curr != NULL) {
    printf("%d",curr->content);
    curr = curr->next;
  }
  printf("\n");
}

void main(void) {
  node *head_node = constructor();

  insert(head_node,1);
  insert(head_node,2);
  insert(head_node,3);
  insert(head_node,4);
  print_linked_list(head_node);

  head_node = delete(head_node,1);
  printf("content of head %d\n",head_node ->content);
  print_linked_list(head_node);

  destructor(head_node);
}
