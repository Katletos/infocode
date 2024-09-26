#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct NodeKey {
    unsigned long hash;
    unsigned int container_id;
    char *str;
};

struct Node {
    struct NodeKey *key;
    struct Node *left;
    struct Node *right;
    int height;
};

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

struct Node *createNode(struct NodeKey *key) {
    struct Node *node = (struct Node *) malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct Node *insert(struct Node *node, struct NodeKey *key) {
    if (NULL == node) {
        return createNode(key);
    }

    if (key->hash < node->key->hash) {
        node->left = insert(node->left, key);
    } else if (key->hash > node->key->hash) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int bf = getBalanceFactor(node);

    if (bf > 1 && key->hash < node->left->key->hash) {
        return rightRotate(node);
    }
    if (bf < -1 && key->hash > node->right->key->hash) {
        return leftRotate(node);
    }
    if (bf > 1 && key->hash > node->left->key->hash) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (bf < -1 && key->hash < node->right->key->hash) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

bool search(struct Node *node, unsigned long hash) {
    if (NULL == node) return false;

    if (node->key->hash == hash) {
        return true;
    } else if (node->key->hash < hash) {
        search(node->right, hash);
    } else if (node->key->hash > hash) {
        search(node->left, hash);
    } else {
        return false;
    }
}

void preOrder(struct Node *root) {
    if (root != NULL) {
        printf("%lu ", root->key->hash);
        printf("%s ", root->key->str);
        printf("%u \n", root->key->container_id);
        preOrder(root->left);
        preOrder(root->right);
    }
}


unsigned long hash_function(const char *str) {
    assert(NULL != str);

    unsigned long i = 0;
    for (int j = 0; str[j]; j++) {
        i += str[j];
    }

    return i;
}

#define NUMBER_OF_STRINGS 4
#define NUMBER_OD_CONTAINERS 3

int main(void) {
    char *strings[NUMBER_OF_STRINGS] = {"1", "mama", "31", "sdqweqwe"};
    struct NodeKey preparedStrings[NUMBER_OF_STRINGS] = {};
    struct Node *root = NULL;

    for (int i = 0; i < NUMBER_OF_STRINGS; ++i) {
        preparedStrings[i].hash = hash_function(strings[i]);
        preparedStrings[i].str = strings[i];
        preparedStrings[i].container_id = rand() % (NUMBER_OD_CONTAINERS - 0 + 1) + 0;

        root = insert(root, &preparedStrings[i]);
    }

    preOrder(root);

    char *sstr = "mama";
    printf("%b", search(root, hash_function(sstr)));


    return 0;
}
