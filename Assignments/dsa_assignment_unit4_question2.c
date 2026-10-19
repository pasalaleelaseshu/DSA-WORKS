/*
Problem:
Extend a Binary Search Tree (BST) program to support deletion. Create a BST,
delete a user-specified node, correctly handle nodes with zero, one and two
children, and display inorder traversal before and after deletion.
Test separately for all three deletion cases.
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Create a new node
struct Node* createNode(int value) {
    struct Node *newNode = malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Insert a value into the BST; duplicate values are ignored
struct Node* insert(struct Node *root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    else
        printf("Duplicate value %d ignored.\n", value);

    return root;
}

// Display values in ascending order
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Find the smallest node in a subtree
struct Node* findMin(struct Node *root) {
    while (root != NULL && root->left != NULL)
        root = root->left;

    return root;
}

// Delete a node while preserving BST properties
struct Node* deleteNode(struct Node *root, int key) {
    if (root == NULL)
        return NULL;

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        // Case 1: Node has no children (leaf)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // Case 2a: Node has only a right child
        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }

        // Case 2b: Node has only a left child
        if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Node has two children.
        // Replace its value with its inorder successor.
        struct Node *successor = findMin(root->right);
        root->data = successor->data;
        root->right = deleteNode(root->right, successor->data);
    }

    return root;
}

// Free all nodes before the program exits
void freeTree(struct Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main(void) {
    struct Node *root = NULL;
    int n, value, key, i;

    printf("Enter number of values: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of values.\n");
        return EXIT_FAILURE;
    }

    printf("Enter %d unique integers:\n", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &value) != 1) {
            printf("Invalid input.\n");
            freeTree(root);
            return EXIT_FAILURE;
        }
        root = insert(root, value);
    }

    printf("\nInorder traversal before deletion: ");
    inorder(root);

    printf("\nEnter value to delete: ");
    if (scanf("%d", &key) != 1) {
        printf("Invalid value.\n");
        freeTree(root);
        return EXIT_FAILURE;
    }

    // Check whether the value exists before attempting deletion
    {
        struct Node *current = root;
        while (current != NULL && current->data != key) {
            if (key < current->data)
                current = current->left;
            else
                current = current->right;
        }

        if (current == NULL)
            printf("%d was not found in the BST.\n", key);
        else {
            root = deleteNode(root, key);
            printf("%d deleted successfully.\n", key);
        }
    }

    printf("Inorder traversal after deletion: ");
    inorder(root);
    printf("\n");

    freeTree(root);
    return 0;
}
