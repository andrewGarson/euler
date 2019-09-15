#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "debug.h"

// private 

ListNode *list_create_node(void *value){
  ListNode *new_node = calloc(1, sizeof(ListNode));
  if(!new_node) { return 0; }

  new_node->value = value;
  new_node->next = NULL;
  new_node->prev = NULL;

  return new_node;
}

int list_get_node_at(List *list, int index, ListNode **out) {
  if(index < 0 || index >= list->length) { return 0; }
  if(index <= (list->length - 1)/2){
    *out = list->head;
    for(int i = 0; i < index; i++){
      *out = (*out)->next;
    }
    return 1;
  } else {
    *out = list->tail;
    for(int i = list->length -1; i > index; i--){
      *out = (*out)->prev;
    }
    return 1;
  }
}

// public 

List *list_create() {
  List *list = calloc(1, sizeof(List));

  list->head = NULL;
  list->tail = NULL;
  list->length = 0;

  return list;
}

void list_destroy(List **list) {
  if(!list) { return; }

  ListNode *next = (*list)->head;
  ListNode *release_me;
  while(next){
    release_me = next;
    next = next->next;

    free(release_me->value);
    release_me->value = NULL;
    release_me->next = NULL;
    release_me->prev = NULL;

    free(release_me);
  }

  free(*list);
  *list = NULL;
}

void list_iterate(List *list, t_list_iterate_callback *callback){
  ListNode *current = list->head;
  while(NULL != current){
    (*callback)(current->value);
    current = current->next;
  }
}

void list_print_reverse(List *list, t_list_iterate_callback *callback){
  ListNode *current = list->tail;

  while(NULL != current){
    (*callback)(current->value);
    current = current->prev;
  }
}

int list_insert_front(List *list, void *value){
  ListNode *new_node = list_create_node(value);
  if(!new_node) { return 0; }

  new_node->next = list->head;
  new_node->prev = NULL;

  if(list->head){
    list->head->prev = new_node;
  }
  list->head = new_node;

  if(NULL == list->tail){
    list->tail = new_node;
  }
  list->length++;

  return 1;
}

int list_insert_back(List *list, void *value){
  ListNode *new_node = list_create_node(value);
  if(!new_node) { return 0; }

  new_node->prev = list->tail;
  new_node->next = NULL;

  if(list->tail) {
    list->tail->next = new_node;
  }
  list->tail = new_node;
  if(NULL == list->head){
    list->head = new_node;
  }   
  list->length++;

  return 1;
}

int list_insert_at(List *list, void *value, int index){
  if(index <= 0) {
    return list_insert_front(list, value);
  }

  if(index >= list->length){
    return list_insert_back(list, value);
  }

  ListNode *new_node = list_create_node(value);
  if(!new_node) { return 0; }

  ListNode *insert_before;
  if(list_get_node_at(list, index, &insert_before)){
    ListNode *insert_after = insert_before->prev; 
    insert_after->next = new_node;
    new_node->next = insert_before;

    new_node->prev = insert_after;
    insert_before->prev = new_node;

    list->length++;
  } else {
    return 0;
  }

  return 1;
}

int list_get_front(List *list, void **out){
  if(!list->head) { return 0; }

  *out = list->head->value;

  return 1;
}

int list_get_back(List *list, void **out){
  if(!out) { return 0; }
  if(!list->tail) { return 0; }

  *out = list->tail->value;

  return 1;
}

int list_get_at(List *list, int index, void **out){
  ListNode *node;
  if(list_get_node_at(list, index, &node)){
    *out = node->value;
    return 1;
  }
  return 0;
}

int list_remove_front(List *list){
  if(!list->head) { return 0; }

  ListNode *old_head = list->head;
  if(old_head->next){
    list->head = old_head->next;
    list->head->prev = NULL;
  } else {
    list->head = NULL;
    list->tail = NULL;
  }

  list->length--;

  free(old_head);
  old_head = NULL;

  return 1;
}

int list_remove_back(List *list){
  if(!list->tail) { return 0; }

  ListNode *old_tail = list->tail;
  if(old_tail->prev) {
    list->tail = old_tail->prev;
    list->tail->next = NULL;
  } else {
    list->head = NULL;
    list->tail = NULL;
  }

  list->length--;
  free(old_tail);
  old_tail = NULL;

  return 1;
}

int list_index_of(List *list, void *search, t_list_item_equality *equals) {
  ListNode *current = list->head;
  int i = 0;
  while(current) {
    if((*equals)(current->value, search) == 0){
      return i;
    }
    i++;
    current = current->next;
  }
  return -1;
}



// int list helpers

int int_list_equality(void *lhs, void *rhs) {
  return *((int *)lhs) - *((int *)rhs);
}

void int_list_print_callback(void *value){
  printf("%d -> ", *((int *)value));
}

void int_list_insert_back(List *list, int new_value) {
  int *copy = calloc(1, sizeof(int));
  *copy = new_value;
  list_insert_back(list, copy);
}

void print_integer_list(List *list){
  list_iterate(list, &int_list_print_callback);
  printf("\u2205\n");
}

