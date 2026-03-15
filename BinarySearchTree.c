#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
    int value;
	int count; // For repeated values
    struct Tree* left;
    struct Tree* right;
} Tree;

Tree* create(int v) {
    Tree *t = malloc(sizeof(Tree));
    if (!t) {
        return NULL;
    }
	
	t->value = v;
	t->count = 1;
	t->left = NULL;
	t->right = NULL;
	
    return t;
}

void add(int v, Tree* t) {
	if (t == NULL || !t) { // If tree dosent exist, i.e there is no root
		return;
	}
	
	Tree* current = t;
	
	while(1) {
		if (v < current->value) {
			if (current->left == NULL) {
				current->left = create(v);
				break;
			} else {
				current = current->left;
			}
		} else if (v > current->value) {
			if (current->right == NULL) {
				current->right = create(v);
				break;
			} else {
				current = current->right;
			}
		} else { // If v is equal to value
			current->count++;
			break;
		}
	}
}

Tree* delete(int v, Tree* t) {
	if (t == NULL) { // Base case if value is not found
		return NULL;
	}
	
	if (v == t->value) {
		if (t->count > 1) { // For repeated values, decrements count
			t->count--;
			return t;
		} else if (t->left == NULL && t->right == NULL) { // No children
			free(t);
			t = NULL;
			return t;
		} else if (t->left != NULL && t->right == NULL) { // Only left child
			Tree* current = t;
			t = t->left;
			free(current);
			return t;
		} else if (t->left == NULL && t->right != NULL) { // Only right child
			Tree* current = t;
			t = t->right;
			free(current);
			return t;
		} else { // If there are two child nodes
			Tree* current = t->right;
			Tree* prev = t;
			
			if (current->left == NULL) { // If the right-subtree is the successor
				t->value = current->value;
				t->count = current->count;
				
				if (current->right != NULL) { // If the right-subtree has a right child
					t->right = current->right;
				} else {
					t->right = NULL;
				}
				
				free(current);
				return t;
			}
			
			while(1) {
				if (current->left == NULL) {
					break;
				}
				
				prev = current;
				current = current->left;
			}
			
			t->value = current->value;
			t->count = current->count;
			
			if (current->right != NULL) { // If the leftmost node of the right-subtree has a right child
				prev->left = current->right;
			} else {
				prev->left = NULL;
			}
			
			free(current);
			return t;	
		}
	} else {
		if (v < t->value) {
			t->left = delete(v, t->left);
		} else {
			t->right = delete(v, t->right);
		}
	}
	
	return t; // default return just in case
}

Tree* search(int v, Tree* t) {
	Tree* current = t;
	
	while(current != NULL) {
		if (v == current->value) {
			return current;
		} else if (v < current->value) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	
	return NULL;
}

void delete_tree(Tree* t) {
	if (t == NULL) {
		return;
	}
	
	delete_tree(t->left);
	delete_tree(t->right);
	
	free(t);
}

void inorder_traversal(Tree* t) {
	if (t == NULL) {
		return;
	}
	
	inorder_traversal(t->left);
	
	printf("%d ", t->value);
	
	inorder_traversal(t->right);
}

void preorder_traversal(Tree* t) {
	if (t == NULL) {
		return;
	}
	
	printf("%d ", t->value);
	
	preorder_traversal(t->left);
	
	preorder_traversal(t->right);
}

void postorder_traversal(Tree* t) {
	if (t == NULL) {
		return;
	}
	
	postorder_traversal(t->left);
	
	postorder_traversal(t->right);
	
	printf("%d ", t->value);
}
