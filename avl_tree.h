#ifndef INFOCOD_AVL_TREE_H
#define INFOCOD_AVL_TREE_H

#include <malloc.h>

struct Node {
    void *pData;
    unsigned long hash;
    struct Node *pLeft;
    struct Node *pRight;
    int height;
};
typedef struct Node Node;

int get_height(struct Node *n) {
    return NULL == n ? 0 : n->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int get_balance_factor(struct Node *n) {
    if (n == NULL) {
        return 0;
    }
    return get_height(n->pLeft) - get_height(n->pRight);
}

struct Node *right_rotate(struct Node *y) {
    struct Node *x = y->pLeft;
    struct Node *T2 = x->pRight;

    x->pRight = y;
    y->pLeft = T2;

    x->height = max(get_height(x->pRight), get_height(x->pLeft)) + 1;
    y->height = max(get_height(y->pRight), get_height(y->pLeft)) + 1;

    return x;
}

struct Node *left_rotate(struct Node *x) {
    struct Node *y = x->pRight;
    struct Node *T2 = y->pLeft;

    y->pLeft = x;
    x->pRight = T2;

    x->height = max(get_height(x->pRight), get_height(x->pLeft)) + 1;
    y->height = max(get_height(y->pRight), get_height(y->pLeft)) + 1;

    return y;
}

struct Node *create_node(void *data, unsigned long hash) {
    struct Node *node = (struct Node *) malloc(sizeof(struct Node));
    node->pData = data;
    node->hash = hash;
    node->pLeft = NULL;
    node->pRight = NULL;
    node->height = 1;
    return node;
}

struct Node *insert(struct Node *node, void *data, unsigned long hash) {
    if (NULL == node) {
        return create_node(data, hash);
    }

    if (hash < node->hash) {
        node->pLeft = insert(node->pLeft, data, hash);
    } else if (hash > node->hash) {
        node->pRight = insert(node->pRight, data, hash);
    } else {
        return node;
    }

    node->height = 1 + max(get_height(node->pLeft), get_height(node->pRight));
    int bf = get_balance_factor(node);

    if (bf > 1 && hash < node->pLeft->hash) {
        return right_rotate(node);
    }
    if (bf < -1 && hash > node->pRight->hash) {
        return left_rotate(node);
    }
    if (bf > 1 && hash > node->pLeft->hash) {
        node->pLeft = left_rotate(node->pLeft);
        return right_rotate(node);
    }
    if (bf < -1 && hash < node->pRight->hash) {
        node->pRight = right_rotate(node->pRight);
        return left_rotate(node);
    }
    return node;
}

Node *search(struct Node *node, unsigned long hash) {
    if (NULL == node) return NULL;

    if (node->hash == hash) {
        return node;
    } else if (node->hash < hash) {
        search(node->pRight, hash);
    } else if (node->hash > hash) {
        search(node->pLeft, hash);
    } else {
        return NULL;
    }
}

#endif //INFOCOD_AVL_TREE_H
