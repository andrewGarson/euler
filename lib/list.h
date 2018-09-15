#ifndef _COLLECTIONS_H_
#define _COLLECTIONS_H_

// Linked List

typedef struct _ListNode {
  int value;
  struct _ListNode *next;
  struct _ListNode *prev;
} ListNode;

typedef struct {
  ListNode *head;
  ListNode *tail;
  int length;
} List;

List *list_create();
void list_destroy(List **list);

void list_print(List *list);
void list_print_reverse(List *list);

int list_insert_front(List *list, int value);
int list_insert_back(List *list, int value);
int list_insert_at(List *list, int value, int index);

int list_get_front(List *list, int *out);
int list_get_back(List *list, int *out);
int list_get_at(List *list, int index, int *out);

int list_remove_front(List *list);
int list_remove_back(List *list);
int list_remove_at(List*list, int index);

int list_index_of(List *list, int n);

#endif
