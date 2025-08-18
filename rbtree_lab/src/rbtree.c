#include "rbtree.h"
#include <stdlib.h>

static void postorder_free(rbtree *t, node_t *x);
static void inorder(const rbtree *t, const node_t *node, key_t *arr, size_t *i, const size_t n);
static void r_rotate(rbtree *t, node_t *x);
static void l_rotate(rbtree *t, node_t *x);
static void insert_fixup(rbtree *t, node_t *z);

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  if (p == NULL) return NULL;

  p->nil = (node_t *)calloc(1, sizeof(node_t));
  if (p->nil == NULL) {
    free(p);
    return NULL;
  }

  p->nil->color = RBTREE_BLACK;
  p->nil->left = p->nil->right = p->nil->parent = p->nil;
  p->root = p->nil;
  return p;
}


void delete_rbtree(rbtree *t) {
  postorder_free(t,t->root);
  free(t->nil);
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

static void l_rotate(rbtree *t, node_t *x) {
  node_t *y = x->right;
  x->right = y->left;
  if (y->left != t->nil) y->left->parent = x;
  y->parent = x->parent;
  if (x->parent == t->nil)
    t->root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}

static void r_rotate(rbtree *t, node_t *x) {
  node_t *y = x->left;
  x->left = y->right;
  if (y->right != t->nil)
    y->right->parent = x;

  y->parent = x->parent;
  if (x->parent == t->nil)
    t->root = y;
  else if (x == x->parent->right)
    x->parent->right = y;
  else
    x->parent->left = y;

  y->right = x;
  x->parent = y;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *z = malloc(sizeof(node_t));
  z ->color = RBTREE_RED;
  z -> key = key;
  z -> left = z -> right = z -> parent = t -> nil;

  node_t *x = t->root; // Root부터 시작
  node_t *y = t->nil; // 부모 후보

  while(x != t->nil) {
      y = x;
      if (key < x->key)
        x = x->left;
      else
        x = x->right;
  }

  z->parent = y;
  if(y == t->nil) {
    t->root = z;
  }else if (key < y->key) {
    y->left = z;
  }else {
    y->right = z;
  }

  insert_fixup(t,z);

  return z;

}

static void insert_fixup(rbtree *t, node_t *z){
  
  while (z->parent != t->nil && z->parent->color == RBTREE_RED){
    node_t *gp = z->parent ->parent;
    if(z->parent == gp -> left){
      node_t *u = gp->right;
      if(u->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        u->color = RBTREE_BLACK;
        gp-> color = RBTREE_RED;
        z = z->parent->parent;

      }else if(u->color == RBTREE_BLACK){
        if (z == z->parent->right) {
          z = z->parent;
          l_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        gp-> color = RBTREE_RED;
        r_rotate(t, z->parent->parent);
      }
    }
    else if(z->parent == gp-> right){
      node_t *u = gp ->left;
      if(u->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        u->color = RBTREE_BLACK;
        gp->color = RBTREE_RED;
        z = z->parent->parent;
      }else if(u->color == RBTREE_BLACK){
        if(z == z->parent->left){
        z = z->parent;
        r_rotate(t, z);
        }
      z->parent->color = RBTREE_BLACK;
      gp ->color = RBTREE_RED;
      l_rotate(t, z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *p) {
  
  return 0;
}

