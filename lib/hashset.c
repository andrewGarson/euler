#include <stdlib.h>
#include <stdio.h>

#include "hashset.h"
#include "list.h"

HashSet *hashset_create(int buckets_size){
  HashSet *hashset = calloc(1, sizeof(HashSet));

  hashset->buckets_size = buckets_size;
  hashset->buckets = calloc(buckets_size, sizeof(List *));
  for(int i = 0; i < buckets_size; i++){
    hashset->buckets[i] = list_create();
  }

  return hashset;
}

void hashset_destroy(HashSet **hashset){
  if(!hashset) { return; }

  for(int i=0; i < (*hashset)->buckets_size; i++){
    list_destroy(&((*hashset)->buckets[i]));
  }

  free((*hashset)->buckets);
  free(*hashset);
  *hashset = NULL;
}

void hashset_print(HashSet *hashset) {
  printf("{\n");
  for(int i = 0; i < hashset->buckets_size; i++){
    printf("\t[%d] -> ", i);
    list_print(hashset->buckets[i]);
  }
  printf("}\n");
}

List *bucket_for(HashSet *hashset, int n){
  return hashset->buckets[n % hashset->buckets_size];
}

void hashset_insert(HashSet *hashset, int n){
  List *bucket = bucket_for(hashset, n);
  list_insert_front(bucket, n);
}

int hashset_includes(HashSet *hashset, int n){
  List *bucket = bucket_for(hashset, n);
  return list_index_of(bucket, n) != -1;
}


