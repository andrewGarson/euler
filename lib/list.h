#ifndef _COLLECTIONS_H_
#define _COLLECTIONS_H_

// Linked List

typedef struct _ListNode {
  void *value;
  struct _ListNode *next;
  struct _ListNode *prev;
} ListNode;

typedef struct {
  ListNode *head;
  ListNode *tail;
  int length;
} List;

typedef int (t_list_item_equality)(void *,void *);
typedef void (t_list_iterate_callback)(void *);

List *list_create();
void list_destroy(List **list);

void list_iterate(List *list, t_list_iterate_callback *callback);
void list_iterate_reverse(List *list, t_list_iterate_callback *callback);

int list_insert_front(List *list, void *value);
int list_insert_back(List *list, void *value);
int list_insert_at(List *list, void *value, int index);

int list_get_front(List *list, void **out);
int list_get_back(List *list, void **out);
int list_get_at(List *list, int index, void **out);

int list_remove_front(List *list);
int list_remove_back(List *list);
int list_remove_at(List*list, int index);

int list_index_of(List *list, void *search, t_list_item_equality *equals);

int int_list_equality(void *lhs, void *rhs);
void int_list_print_callback(void *value);
void int_list_insert_back(List *list, int new_value);

void print_integer_list(List *list);

#endif
