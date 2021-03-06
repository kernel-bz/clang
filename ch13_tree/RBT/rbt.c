//
//  Source: rbt.c written by Jung,JaeJoon at the www.kernel.bz
//  Compiler: Standard C
//  Copyright(c): 2010, Jung,JaeJoon(rgbi3307@nate.com)
//
//  rsum:
//		2010-11-24 Red-Black Tree를 코딩하다.
//		yyyy-mm-dd ...
//

#include <stdio.h>
#include <stdlib.h>
#include "rbt.h"

//RBT 생성(구조체 메모리 할당)
TREE_RBT* create (int (*compare) (void* argu1, void* argu2))
{
	TREE_RBT* tree;

	tree = (TREE_RBT*) malloc (sizeof(TREE_RBT));
	if (tree) {
		tree->root = NULL;
		tree->count = 0;
		tree->compare = compare;
	}
	return tree;
}

//RBT 메모리 할당 해제
TREE_RBT* destroy (TREE_RBT* tree)
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

//트리 출력
void traverse (TREE_RBT* tree, void (*process) (void* data))
{
	_traverse (tree->root, process);
}

//INORDER-TREE-WALK
void _traverse (NODE3* node, void (*process) (void* data))
{
	if (node) {
		_traverse (node->left, process);
		process (node->data);
		_traverse (node->right, process);
	}
}

//삽입(노드 메모리 할당)
bool insert (TREE_RBT* tree, void* data_in)
{
	NODE3* node_new;

	node_new = (NODE3*)malloc(sizeof(NODE3));
	if (!node_new) return false;

	node_new->left = NULL;
	node_new->right = NULL;	
	node_new->data = data_in;
	node_new->parent = NULL;
	
	node_new->color = BLACK;  //root
	if (tree->count == 0) tree->root = node_new;
	else rbt_insert (tree, node_new);

	(tree->count)++;
	return true;
}

//주어진 노드로부터 가장 최소의 노드
NODE3* rbt_minimum (NODE3* node)
{
	while (node->left)
		node = node->left;
	return node;
}

//주어진 노드로부터 가장 최대의 노드
NODE3* rbt_maximum (NODE3* node)
{
	while (node->right)
		node = node->right;
	return node;
}

//주어진 노드보다 큰 노드중에서 최소 노드
NODE3* rbt_successor (NODE3* node)
{
	NODE3* node_parent;  //y, 상위노드

	if (node->right) return rbt_minimum (node->right);

	node_parent = node->parent;
	while (node_parent && node == node_parent->right) {
		node = node_parent;
		node_parent = node_parent->parent;
	}
	return node_parent;
}

/*
RB-INSERT(T, z) 
 1  y ← nil[T] 
 2  x ← root[T] 
 3  while x ≠ nil[T] 
 4      do y ← x 
 5         if key[z] < key[x] 
 6            then x ← left[x] 
 7            else x ← right[x] 
 8  p[z] ← y 
 9  if y = nil[T] 
10     then root[T] ← z 
11     else if key[z] < key[y] 
12             then left[y] ← z 
13             else right[y] ← z 
14  left[z] ← nil[T] 
15  right[z] ← nil[T] 
16  color[z] ← RED 
17  RB-INSERT-FIXUP(T, z) 
*/
//tree에 z 노드를 삽입한다.
void rbt_insert (TREE_RBT* tree, NODE3* z)
{
	NODE3* x;
	NODE3* y;

	y = NULL;
	x = tree->root;
	while (x) {
		y = x;
		if (tree->compare (z->data, x->data) < 0) 
			x = x->left;
		else x = x->right;
	}
	z->parent = y;
	if (!y) tree->root = z;
	else {
		if (tree->compare (z->data, y->data) < 0) 
			y->left = z;
		else y->right = z;
	}
	z->left = NULL;
	z->right = NULL;
	z->color = RED;
	rbt_insert_fixup (tree, z);
}

/*
RB-INSERT-FIXUP(T, z) 
 1 while color[p[z]] = RED 
 2     do if p[z] = left[p[p[z]]] 
 3           then y ← right[p[p[z]]] 
 4                if color[y] = RED 
 5                   then color[p[z]] ← BLACK                    ▹ Case 1 
 6                        color[y] ← BLACK                       ▹ Case 1 
 7                        color[p[p[z]]] ← RED                   ▹ Case 1 
 8                        z ← p[p[z]]                            ▹ Case 1 
 9                   else if z = right[p[z]] 
10                           then z ← p[z]                       ▹ Case 2 
11                                LEFT-ROTATE(T, z)               ▹ Case 2 
12                           color[p[z]] ← BLACK                 ▹ Case 3 
13                           color[p[p[z]]] ← RED                ▹ Case 3 
14                           RIGHT-ROTATE(T, p[p[z]])             ▹ Case 3 
15           else (same as then clause 
                         with "right" and "left" exchanged) 
16 color[root[T]] ← BLACK 
*/
void rbt_insert_fixup (TREE_RBT* tree, NODE3* z)
{
	NODE3* y;

	while (z->parent && z->parent->color == RED) {
		if (z->parent == z->parent->parent->left) {
			y = z->parent->parent->right;
			if (y && y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} else {
				if (z == z->parent->right) {
					z = z->parent;
					rbt_left_rotate (tree, z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				rbt_right_rotate (tree, z->parent->parent);
			}
		} else {
			y = z->parent->parent->left;
			if (y && y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} else {
				if (z == z->parent->left) {
					z = z->parent;
					rbt_right_rotate (tree, z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				rbt_left_rotate (tree, z->parent->parent);
			}			
		}
	} //while

	tree->root->color = BLACK;
}

/*
LEFT-ROTATE(T, x) 
 1  y ← right[x]            ▹ Set y. 
 2  right[x] ← left[y]      ▹ Turn y's left subtree into x's right subtree. 
 3  p[left[y]] ← x 
 4  p[y] ← p[x]             ▹ Link x's parent to y. 
 5  if p[x] = nil[T] 
 6     then root[T] ← y 
 7     else if x = left[p[x]] 
 8             then left[p[x]] ← y 
 9             else right[p[x]] ← y 
10  left[y] ← x             ▹ Put x on y's left. 
11  p[x] ← y 
*/
void rbt_left_rotate (TREE_RBT* tree, NODE3* x)
{
	NODE3* y;

	y = x->right;
	x->right = y->left;
	if (y->left) y->left->parent = x;
	y->parent = x->parent;
	if (x->parent) {
		if (x == x->parent->left) x->parent->left = y;
		else x->parent->right = y;		
	} else tree->root = y;
	y->left = x;
	x->parent = y;
}

void rbt_right_rotate (TREE_RBT* tree, NODE3* x)
{
	NODE3* y;

	y = x->left;
	x->left = y->right;
	if (y->right) y->right->parent = x;
	y->parent = x->parent;
	if (x->parent) {
		if (x == x->parent->right) x->parent->right = y;
		else x->parent->left = y;		
	} else tree->root = y;
	y->right = x;
	x->parent = y;
}

/*
RB-DELETE(T, z) 
 1 if left[z] = nil[T] or right[z] = nil[T] 
 2    then y ← z 
 3    else y ← TREE-SUCCESSOR(z) 
 4 if left[y] ≠ nil[T] 
 5    then x ← left[y] 
 6    else x ← right[y] 
 7 p[x] ← p[y] 
 8 if p[y] = nil[T] 
 9    then root[T] ← x 
10    else if y = left[p[y]] 
11            then left[p[y]] ← x 
12            else right[p[y]] ← x 
13 if y 3≠ z 
14    then key[z] ← key[y] 
15         copy y's satellite data into z 
16 if color[y] = BLACK 
17    then RB-DELETE-FIXUP(T, x) 
18 return y 
*/

NODE3* rbt_delete (TREE_RBT* tree, NODE3* z)
{
	NODE3* x;
	NODE3* y;

	if (z->left == NULL || z->right == NULL) y = z;
	else y = rbt_successor (z);

	if (y->left) x = y->left;
	else x = y->right;

	x->parent = y->parent;
	if (!y->parent) tree->root = x;
	else {
		if (y == y->parent->left) y->parent->left = x;
		else y->parent->right = x;
	}

	if (y != z) z->data = y->data;

	if (y->color == BLACK) rbt_delete_fixup (tree, x);

	return y;
}

/*
RB-DELETE-FIXUP(T, x) 
 1 while x ≠ root[T] and color[x] = BLACK 
 2     do if x = left[p[x]] 
 3           then w ← right[p[x]] 
 4                if color[w] = RED 
 5                   then color[w] ← BLACK                        ▹  Case 1 
 6                        color[p[x]] ← RED                       ▹  Case 1 
 7                        LEFT-ROTATE(T, p[x])                    ▹  Case 1 
 8                        w ← right[p[x]]                         ▹  Case 1 
 9                if color[left[w]] = BLACK and color[right[w]] = BLACK 
10                   then color[w] ← RED                          ▹  Case 2 
11                        x p[x]                                  ▹  Case 2 
12                   else if color[right[w]] = BLACK 
13                           then color[left[w]] ← BLACK          ▹  Case 3 
14                                color[w] ← RED                  ▹  Case 3 
15                                RIGHT-ROTATE(T, w)              ▹  Case 3 
16                                w ← right[p[x]]                 ▹  Case 3 
17                         color[w] ← color[p[x]]                 ▹  Case 4 
18                         color[p[x]] ← BLACK                    ▹  Case 4 
19                         color[right[w]] ← BLACK                ▹  Case 4 
20                         LEFT-ROTATE(T, p[x])                   ▹  Case 4 
21                         x ← root[T]                            ▹  Case 4 
22        else (same as then clause with "right" and "left" exchanged) 
23 color[x] ← BLACK 
*/

void rbt_delete_fixup (TREE_RBT* tree, NODE3* x)
{
	NODE3* w;

	while (x && x->color == BLACK) {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rbt_left_rotate (tree, x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				x = x->parent;
			} else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					rbt_right_rotate (tree, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				rbt_left_rotate (tree, x->parent);
				x = tree->root;
			}
		} else {
			w = x->parent->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rbt_right_rotate (tree, x->parent);
				w = x->parent->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				x = x->parent;
			} else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					rbt_left_rotate (tree, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				rbt_right_rotate (tree, x->parent);
				x = tree->root;
			}
		}
	} //while
	x->color = BLACK;
}
