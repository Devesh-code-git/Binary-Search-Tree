#include <stdio.h>
#include <stdlib.h>
#include "BinarySearchTree.h"

int main() {
	// Create root
    Tree* root = create(50);

    // Insert values
    int values[] = {30, 70, 20, 40, 60, 80, 70, 30, 30};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++) {
        add(values[i], root);
    }
	
    // Traversals
    printf("Inorder: ");
    inorder_traversal(root);
    printf("\n");

    printf("Preorder: ");
    preorder_traversal(root);
    printf("\n");

    printf("Postorder: ");
    postorder_traversal(root);
    printf("\n\n");

    // Search test
    int target = 30;
    Tree* found = search(target, root);
    if (found) {
        printf("Found %d with count = %d\n\n", target, found->count);
    } else {
        printf("%d not found\n\n", target);
    }

    // Delete tests
    printf("=== Deleting 30 (node removal) ===\n");
    root = delete(30, root);
	root = delete(30, root);
	root = delete(30, root);
    inorder_traversal(root);
    printf("\n\n");

    printf("=== Deleting 50 (root with two children) ===\n");
    root = delete(50, root);
    inorder_traversal(root);
    printf("\n\n");

    printf("=== Deleting 20 (leaf node) ===\n");
    root = delete(20, root);
    inorder_traversal(root);
    printf("\n\n");

    printf("=== Final Tree (Inorder) ===\n");
    inorder_traversal(root);
    printf("\n");

    // Cleanup
    delete_tree(root);
    root = NULL;

    printf("\nTree memory freed.\n");

    return 0;
}