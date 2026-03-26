#ifndef BinarySearchTree_H
#define BinarySearchTree_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
    int value;
	int count; // For repeated values
    struct Tree* left;
    struct Tree* right;
} Tree;

Tree* create(int v);

void add(int v, Tree* t);
Tree* delete(int v, Tree* t);
Tree* search(int v, Tree* t);

void delete_tree(Tree* t);

void inorder_traversal(Tree* t);
void preorder_traversal(Tree* t);
void postorder_traversal(Tree* t);

#endif