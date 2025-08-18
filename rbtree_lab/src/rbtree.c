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

node_t *rbtree_find(const rbtree *t,const key_t k){
  node_t *cur = t -> root;
  while(cur != t -> nil){
    if(k == cur -> key) return cur;
    else if(k > cur->key) cur = cur -> right;
    else if(k < cur->key) cur = cur -> left;
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  node_t *cur = t->root;
  if(cur == t->nil) return NULL;
  while(cur->left != t->nil){  
    cur = cur->left; 
  }
  return cur;
}

node_t *rbtree_max(const rbtree *t) {
  node_t *cur = t->root;
  if(cur == t->nil) return NULL;
  while(cur->right != t->nil){  
    cur = cur->right; 
  }
  return cur;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  size_t i = 0;
  inorder(t, t->root, arr, &i, n);
  return 0;
}

// size_t 변수를 쓰는 이유 - arr의 정보 저장 인덱싱을 위해
static void inorder(const rbtree *t, const node_t *node, key_t *arr, size_t *i, const size_t n) {
  if (node == t->nil || *i >= n) return;
  inorder(t, node->left, arr, i, n);
  if (*i < n) arr[(*i)++] = node->key;
  inorder(t, node->right, arr, i, n);
}


node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *z = malloc(sizeof(node_t)); // 새로운 key 노드
  z ->color = RBTREE_RED;
  z -> key = key;
  z -> left = z -> right = z -> parent = t -> nil;

  node_t *x = t->root; // Root부터 시작
  node_t *y = t->nil; // 부모 후보

  // BST 위치 찾기
  while (x != t->nil) {
      y = x;
      if(key < x) x = x->left;
      else if(key > x) x = x->right;

  }

  // 부모 자식 연결
  z -> parent = y;
  if (y == t->nil) t -> root = z;
  else if (key < y -> key) y -> left = z;
  else y -> right = z;

  insert_fixup(t,z);

  return z;

}

void insert_fixup(rbtree *t, node_t *z){

}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

