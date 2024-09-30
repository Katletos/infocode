#ifndef INFOCOD_AVL_TREE_H
#define INFOCOD_AVL_TREE_H

#include <stddef.h>
#include <malloc.h>
#include <stdbool.h>

struct Node {
    void *data;
    unsigned long hash;
    struct Node *left;
    struct Node *right;
    int height;
};
typedef struct Node Node;

int getHeight(struct Node *n) {
    return NULL == n ? 0 : n->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getBalanceFactor(struct Node *n) {
    if (n == NULL) {
        return 0;
    }
    return getHeight(n->left) - getHeight(n->right);
}

struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;

    return x;
}

struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;

    return y;
}

struct Node *createNode(struct NodeData *data, unsigned long hash) {
    struct Node *node = (struct Node *) malloc(sizeof(struct Node));
    node->data = data;
    node->hash = hash;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct Node *insert(struct Node *node, void *data, unsigned long hash) {
    if (NULL == node) {
        return createNode(data, hash);
    }

    if (hash < node->hash) {
        node->left = insert(node->left, data, hash);
    } else if (hash > node->hash) {
        node->right = insert(node->right, data, hash);
    } else {
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int bf = getBalanceFactor(node);

    if (bf > 1 && hash < node->left->hash) {
        return rightRotate(node);
    }
    if (bf < -1 && hash > node->right->hash) {
        return leftRotate(node);
    }
    if (bf > 1 && hash > node->left->hash) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (bf < -1 && hash < node->right->hash) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

bool search(struct Node *node, unsigned long hash) {
    if (NULL == node) return false;

    if (node->hash == hash) {
        return true;
    } else if (node->hash < hash) {
        search(node->right, hash);
    } else if (node->hash > hash) {
        search(node->left, hash);
    }

    return false;
}

#endif //INFOCOD_AVL_TREE_H
