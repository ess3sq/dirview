#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "exclude.h"

static int num = 0;
static list_node base = {NULL, NULL};

void add_pattern(char * pattern) {
    list_node *node = &base;
    while (node->pattern) {
        node = node->next;
    }

    node->pattern = strdup(pattern);
    node->next = malloc(sizeof(list_node));

    ++num;
}

char *get_pattern(int i) {
    if (i >= num) return NULL;

    list_node *node = &base;
    while (i--) {
        node = node->next;
    }
    return node->pattern;
}

void wipe_patterns() {
    list_node *node = &base;
    list_node *cpy = node;
    if (node->pattern) free(node->pattern);
    node = node->next;

    while (node && node->pattern) {
        free(node->pattern);
        cpy = node->next;
        free(node);
        node = cpy;
    }

}

int match_pattern(char *s) {
    for (int i = 0; i < num; ++i) {
        if (strstr(s, get_pattern(i))) {
            return PATTERN_MATCH;
        }
    }

    return PATTERN_NOT_MATCH;
}

int get_pattern_list_size() {
    return num;
}