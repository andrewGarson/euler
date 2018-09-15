#ifndef _HASHSET_H_
#define _HASHSET_H_

#include "list.h"

typedef struct _HashSet {
  int buckets_size;
  List **buckets;
} HashSet;

HashSet *hashset_create(int buckets_size);
void hashset_destroy(HashSet **hashset);

void hashset_print(HashSet *hashset);

void hashset_insert(HashSet *set, int n);
int hashset_includes(HashSet *set, int n);

#endif
