#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include "avl_tree.h"

struct NodeData {
    unsigned int container_id;
    char *str;
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

void printInfo(struct NodeData *data) {
    printf("%s ", data->str);
    printf("%u \n", data->container_id);
}

void printTreeInfo(struct Node *root) {
    if (root != NULL) {
        printf("%lu ", root->hash);
        printInfo(root->data);
        printTreeInfo(root->left);
        printTreeInfo(root->right);
    }
}

#define NUMBER_OF_STRINGS 4
#define NUMBER_OD_CONTAINERS 3
#define MAX_STRING_LENGTH 25

int main(void) {
    srand(time(0));
    char *strings[NUMBER_OF_STRINGS] = {"1", "mama", "31", "sdqweqwe"};
    struct NodeData preparedStrings[NUMBER_OF_STRINGS] = {};
    struct Node *root = NULL;

    for (int i = 0; i < NUMBER_OF_STRINGS; ++i) {
        preparedStrings[i].str = strings[i];
        preparedStrings[i].container_id = rand() % NUMBER_OD_CONTAINERS;

        root = insert(root, &preparedStrings[i], hash_function(strings[i]));
    }

    for (int container_number = 0; container_number < NUMBER_OD_CONTAINERS; ++container_number) {
        printf("Container № %d  - [ ", container_number);
        for (int j = 0; j < NUMBER_OF_STRINGS; ++j) {
            unsigned int id = preparedStrings[j].container_id;
            if (id == container_number) {
                printf("%s, ", preparedStrings[j].str);
            }
        }
        puts(" ]");
    }

//    printTreeInfo(root);

    while (true) {
        printf("Enter string [0, %d]: ", MAX_STRING_LENGTH);
        char buf[MAX_STRING_LENGTH];


        char *status = fgets(buf, MAX_STRING_LENGTH, stdin);
        printf("%b\n", search(root, hash_function(buf)));
        puts("\n");
    }
}
