#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "avl_tree.h"

#define NUMBER_OF_STRINGS 6
#define NUMBER_OD_CONTAINERS 3
#define MAX_STRING_LENGTH 25
//#define DEBUG

struct NodeData {
    unsigned int container_id;
    char *string;
};
typedef struct NodeData NodeData;

unsigned long hash_function(const char *str) {
    assert(NULL != str);

    unsigned long i = 0;
    for (int j = 0; str[j]; j++) {
        i += str[j];
    }

    return i;
}

#ifdef DEBUG

void print_info(struct NodeData *data) {
    printf("string: %s; ", data->string);
    printf("container:%u \n", data->container_id);
}

void print_tree_info(struct Node *root) {
    if (root != NULL) {
        printf("hash: %lu; ", root->hash);
        print_info(root->pData);
        print_tree_info(root->pLeft);
        print_tree_info(root->pRight);
    }
}

#endif

int main(void) {
    srand(time(0));
    char *strings[NUMBER_OF_STRINGS] = {"new world", "hello", "meow", "git", "infocode", "linus torvalds"};
    struct NodeData preparedStrings[NUMBER_OF_STRINGS] = {};
    struct Node *root = NULL;

    for (int i = 0; i < NUMBER_OF_STRINGS; ++i) {
        preparedStrings[i].string = strings[i];
        preparedStrings[i].container_id = rand() % NUMBER_OD_CONTAINERS;

        root = insert(root, &preparedStrings[i], hash_function(strings[i]));
    }

    for (int container_number = 0; container_number < NUMBER_OD_CONTAINERS; ++container_number) {
        printf("Container № %d  - [ ", container_number);
        for (int j = 0; j < NUMBER_OF_STRINGS; ++j) {
            unsigned int id = preparedStrings[j].container_id;
            if (id == container_number) {
                printf("%s, ", preparedStrings[j].string);
            }
        }
        puts(" ]");
    }

#ifdef DEBUG
    print_tree_info(root);
#endif

    while (true) {
        printf("Enter string [0, %d]: ", MAX_STRING_LENGTH);
        char buf[MAX_STRING_LENGTH];

        char *status = fgets(buf, sizeof(buf), stdin);
        assert(status != NULL);

        size_t len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') {
            buf[len - 1] = 0;
        }

#ifdef DEBUG
        printf("Hash for input: %lu \n", hash_function(buf));
#endif

        Node *pNode = search(root, hash_function(buf));
        if (NULL == pNode) {
            puts("There is no such line");
            continue;
        }

        NodeData *pData = pNode->pData;
        if (NULL == pData) {
            puts("There is no data =(");
            continue;
        }

        printf("The entered string is in container №: %u\n", pData->container_id);
    }
}
