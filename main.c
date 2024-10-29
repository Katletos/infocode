#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include "avl_tree.h"
#include "limits.h"

#define MAX_STRING_CHARS_COUNT 5
#define BUF_LENGTH 256
//#define DEBUG

struct NodeData {
    unsigned long container_id;
    char *string;
};
typedef struct NodeData NodeData;

#ifdef DEBUG

void print_info(struct NodeData *data) {
    printf("string: %s; ", data->string);
    printf("container:%lu \n", data->container_id);
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

unsigned long hash_function(const char *str) {
    assert(NULL != str);

    unsigned long i = 0;
    for (unsigned long j = 0; str[j]; j++) {
        i += str[j] * (j + 1);
    }

    return i;
}

unsigned long get_number(char *str) {
    char buf[18];
    char *endPtr;

    printf("Enter number %s (max 18 chars): ", str);
    while (true) {
        char *input = fgets(buf, sizeof(buf), stdin);
        assert(NULL != input);

        unsigned long result = strtoul(buf, &endPtr, 10);

        int read_all = buf + strlen(buf) - 1 == endPtr;
        if (!read_all || result == ULONG_MAX && errno == ERANGE) {
            perror("Invalid number, try again");
        } else if (result == 0) {
            perror("Number can't be zero");
        } else {
            return result;
        }
    }
}

void generate_random_string(char *dest, unsigned long length) {
    char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (length-- > 0) {
        *dest++ = charset[rand() % sizeof(charset)];
    }
    *dest = '\0';
}

void allocate_random_strings(char **pArr, unsigned long number_of_strings) {
    assert(NULL != pArr);

    for (int i = 0; i < number_of_strings; ++i) {
        pArr[i] = malloc(MAX_STRING_CHARS_COUNT * sizeof(char));
        generate_random_string(pArr[i], MAX_STRING_CHARS_COUNT);
    }
}

int main(void) {
    srand(time(0));

    unsigned long number_of_strings = get_number("of strings N");
    unsigned long number_of_containers = get_number("of containers M");

    char *strings[number_of_strings];
    struct NodeData preparedStrings[number_of_strings];
    struct Node *root = NULL;

    allocate_random_strings(strings, number_of_strings);

    for (unsigned long i = 0; i < number_of_strings; ++i) {
        preparedStrings[i].string = strings[i];
        preparedStrings[i].container_id = rand() % number_of_containers;

        root = insert(root, &preparedStrings[i], hash_function(strings[i]));
    }

    for (unsigned long container_number = 0; container_number < number_of_containers; ++container_number) {
        printf("Container № %zu  - [ ", container_number);
        for (int j = 0; j < number_of_strings; ++j) {
            unsigned long id = preparedStrings[j].container_id;
            if (id == container_number) {
                printf("'%s', ", preparedStrings[j].string);
            }
        }
        puts(" ]");
    }

#ifdef DEBUG
    print_tree_info(root);
#endif

    char buf[BUF_LENGTH];
    while (true) {
        memset(buf, 0, BUF_LENGTH);
        printf("Enter string (max %d chars): ", MAX_STRING_CHARS_COUNT);

        char *status = fgets(buf, sizeof(buf), stdin);
        assert(status != NULL);


        buf[strcspn(buf, "\n")] = 0;

#ifdef DEBUG
        printf("Hash for input: %lu\n", hash_function(buf));
#endif

        Node *pNode = search(root, hash_function(buf));
        if (NULL == pNode) {
            puts("There is no such line\n");
            continue;
        }

        NodeData *pData = pNode->pData;
        if (NULL == pData) {
            puts("There is no data =(");
            continue;
        }

        printf("The entered string is in container №: %zu\n", pData->container_id);
    }
}
