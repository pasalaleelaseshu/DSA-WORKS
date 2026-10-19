/*
Problem:
A system stores unique integer identification numbers using a Binary Search
Tree. Insert n values, display inorder, preorder and postorder traversals,
search for a specified value, and report whether it exists. Explain why
inorder traversal produces sorted values.
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

// Insert a unique value into the BST
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

// Inorder traversal: Left, Root, Right
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder traversal: Root, Left, Right
void preorder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder traversal: Left, Right, Root
void postorder(struct Node *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Search for an identification number
struct Node* search(struct Node *root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);

    return search(root->right, key);
}

// Release all dynamically allocated nodes
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

    printf("Enter number of identification numbers: ");
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

    printf("\nInorder traversal: ");
    inorder(root);

    printf("\nPreorder traversal: ");
    preorder(root);

    printf("\nPostorder traversal: ");
    postorder(root);

    printf("\n\nEnter identification number to search: ");
    if (scanf("%d", &key) != 1) {
        printf("Invalid search value.\n");
        freeTree(root);
        return EXIT_FAILURE;
    }

    if (search(root, key) != NULL)
        printf("%d exists in the BST.\n", key);
    else
        printf("%d does not exist in the BST.\n", key);

    freeTree(root);
    return 0;
}
