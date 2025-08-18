#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  p->nil = calloc(1,sizeof(node_t));
  p ->nil ->color = RBTREE_BLACK;
  p ->nil ->left = p -> nil -> right = p-> nil ->parent = p ->nil;
  p ->root = p -> nil;
  return p;
}

void delete_rbtree(rbtree *t) {
  postorder_free(t,t->root);
  free(t);
}

static void postorder_free(rbtree *t,node_t *x){
  if(x==t->nil) return;
  postorder_free(t,x->left);
  postorder_free(t,x->right);
  free(x);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  return t->root;
}

node_t *rbtree_find(const rbtree *t,const key_t k){
  node_t *cur = t -> root;
  while(cur != t -> nil){
    if(k == cur -> key) return cur;
    cur = (k < cur -> key) ? cur -> left : cur -> right;
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
