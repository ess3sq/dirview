/*
 * MIT License
 *
 * Copyright (c) 2020 Lorenzo Calza
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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