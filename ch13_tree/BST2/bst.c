//
//  Source: bst.c written by Jung,JaeJoon at the www.kernel.bz
//  Path: /a030502/
//  Compiler: Standard C
//  Copyright(C): 2010, Jung,JaeJoon(rgbi3307@nate.com)
//
//  rsum:
//		2010-03-28 Binary Search Tree 자료구조를 코딩하다.
//		2010-11-24 Introduction to Algorithms 책의 
//					Chapter 12: Binary Search Trees 를 참조하여 BST를 재코딩하다.
//		yyyy-mm-dd ...
//

#include <stdlib.h>
//#include <malloc.h>
#include "bst.h"


//BST 생성(구조체 메모리 할당)
TREE_BST* bst_create (int (*compare) (void* argu1, void* argu2))
{
	TREE_BST* tree;

	tree = (TREE_BST*) malloc (sizeof(TREE_BST));
	if (tree) {
		tree->root = NULL;
		tree->count = 0;
		tree->compare = compare;
	}
	return tree;
}

//BST 삽입(노드 메모리 할당)
bool bst_insert (TREE_BST* tree, void* data_in)
{
	NODE3* node_new;

	node_new = (NODE3*)malloc(sizeof(NODE3));
	if (!node_new) return false;

	node_new->left = NULL;
	node_new->right = NULL;	
	node_new->data = data_in;
	node_new->parent = NULL;

	if (tree->count == 0)
		tree->root = node_new;
	else 
		_insert (tree, tree->root, node_new);

	(tree->count)++;
	return true;
}

/*
TREE-INSERT(T, z) 
 1  y ← NIL 
 2  x ← root[T] 
 3  while x ≠ NIL 
 4      do y ←  x 
 5         if key[z] < key[x] 
 6            then x ← left[x] 
 7            else x ← right[x] 
 8  p[z] ← y 
 9  if y = NIL 
10     then root[T] ← z              ⊹ Tree T was empty 
11     else if key[z] < key[y] 
12             then left[y] ← z 
13             else right[y] ← z 
*/
void _insert (TREE_BST* tree, NODE3* node, NODE3* node_new)
{
	NODE3* node_parent;  //y, 상위노드
	int iflag = 0;;

	while (node) {
		node_parent = node;
		if (tree->compare (node_new->data, node->data) < 0) {
			node = node->left;
			iflag = 0;
		} else {
			node = node->right;
			iflag = 1;
		}
	}
	node_new->parent = node_parent;
	if (iflag) node_parent->right = node_new;
	else node_parent->left = node_new;
}

//BST 출력
void bst_traverse (TREE_BST* tree, void (*process) (void* data))
{
	_traverse (tree->root, process);
	//printf ("BST data size: %d\n", usize);
}

/*
INORDER-TREE-WALK (root[T]).  
INORDER-TREE-WALK(x) 
1  if x ≠ NIL 
2     then INORDER-TREE-WALK(left[x]) 
3          print key[x] 
4          INORDER-TREE-WALK(right[x]) 
*/
void _traverse (NODE3* node, void (*process) (void* data))
{
	if (node) {
		_traverse (node->left, process);
		process (node->data);
		_traverse (node->right, process);
	}
}

/*
TREE-MINIMUM (x) 
1  while left[x] ≠ NIL 
2      do x ← left[x] 
3  return x 
*/
//주어진 노드로부터 가장 최소의 노드
NODE3* bst_minimum (NODE3* node)
{
	while (node->left)
		node = node->left;
	return node;
}

/*
TREE-MAXIMUM(x) 
1  while right[x] ≠ NIL 
2      do x ← right[x] 
3  return x 
*/
//주어진 노드로부터 가장 최대의 노드
NODE3* bst_maximum (NODE3* node)
{
	while (node->right)
		node = node->right;
	return node;
}

/*
TREE-SUCCESSOR(x) 
1  if right[x] ≠ NIL 
2      then return TREE-MINIMUM (right[x]) 
3  y ← p[x] 
4  while y ≠ NIL and x = right[y] 
5      do x ← y 
6         y ← p[y] 
7  return y 
*/
//주어진 노드보다 큰 노드중에서 최소 노드
NODE3* bst_successor (NODE3* node)
{
	NODE3* node_parent;  //y, 상위노드

	if (node->right) return bst_minimum (node->right);

	node_parent = node->parent;
	while (node_parent && node == node_parent->right) {
		node = node_parent;
		node_parent = node_parent->parent;
	}
	return node_parent;
}

//BST 검색
void* bst_retrieve (TREE_BST* tree, void* data)
{
	NODE3* node;
	node = bst_search (tree, data, tree->root);
	if (node) return node->data;
	return NULL;
}

/*
TREE-SEARCH (x, k) 
1  if x= NIL or k = key[x] 
2     then return x 
3  if k < key[x] 
4     then return TREE-SEARCH(left[x], k) 
5     else return TREE-SEARCH(right[x], k) 
*/
//재귀를 루프로 수정한 bst_select 함수로 대체
void* _retrieve (TREE_BST* tree, void* data, NODE3* node)
{
	if (node) {
		if (tree->compare (data, node->data) < 0)
			return _retrieve (tree, data, node->left);
		else if (tree->compare (data, node->data) > 0)
			return _retrieve (tree, data, node->right);
		else
			return node->data;
	} else
		return NULL;
}

/*
ITERATIVE-TREE-SEARCH(x, k) 
1  while x ≠ NIL and k ≠ key[x] 
2      do if k < key[x] 
3            then x ← left[x] 
4            else x ← right[x] 
5  return x 
*/
//data가 검색된 노드를 반환(검색)
NODE3* bst_search (TREE_BST* tree, void* data, NODE3* node)
{
	while (node) {
		if (tree->compare (data, node->data) < 0)
			node = node->left;
		else if (tree->compare (data, node->data) > 0)
			node = node->right;
		else
			return node;
	}
	return NULL;
}

//데이터가 검색된 노드 삭제
bool bst_delete (TREE_BST* tree, void* data_key)
{
	NODE3* node;

	//삭제 대상노드 찾음
	node = bst_search (tree, data_key, tree->root);
	if (node) node = _delete (tree, node);
	if (node) {
		free(node->data);
		free(node);
		(tree->count)--;
		//if (tree->count == 0) tree->root = NULL;
		return true;
	}
	return false;
}

/*
TREE-DELETE(T, z) 
 1  if left[z] = NIL or right[z] = NIL 
 2      then y ← z 
 3      else y ← TREE-SUCCESSOR(z) 
 4  if left[y] ≠ NIL 
 5      then x ← left[y] 
 6      else x ← right[y] 
 7  if x ≠ NIL 
 8      then p[x] ← p[y] 
 9  if p[y] = NIL 
10      then root[T] ← x 
11      else if y = left[p[y]] 
12              then left[p[y]] ← x 
13              else right[p[y]] ← x 
14  if y ≠ z 
15      then key[z] ← key[y] 
16           copy y's satellite data into z 
17  return y 
*/
NODE3* _delete (TREE_BST* tree, NODE3* z)
{
	NODE3* x;
	NODE3* y;

	//if (!z->left || !z->right) y = z;
	//else y = bst_successor (z);  //z 보다 큰 노드중에서 최소 노드
	if (z->left && z->right) y = bst_successor (z);
	else y = z;

	if (y->left) x = y->left;
	else x = y->right;

	if (x) x->parent = y->parent;

	if (!y->parent) tree->root = x;
	else {
		if (y == y->parent->left) y->parent->left = x;
		else y->parent->right = x;
	}

	if (y != z) {
		z->data = y->data;
	}
	return y;  //삭제할 노드
}

bool bst_empty (TREE_BST* tree)
{
	return (tree->count == 0);
}

bool bst_full (TREE_BST* tree)
{
	NODE3* node_new;

	node_new = (NODE3*)malloc(sizeof(*(tree->root)));
	if (node_new) {
		free (node_new);
		return false;
	} else
		return true;
}

int bst_count (TREE_BST* tree)
{
	return (tree->count);
}

TREE_BST* bst_destroy (TREE_BST* tree)
{
	if (tree) _destroy (tree->root);

	free (tree);
	return NULL;
}

void _destroy (NODE3* node)
{
	if (node) {
		_destroy (node->left);
		free (node->data);
		_destroy (node->right);
		free (node);
	}
}
