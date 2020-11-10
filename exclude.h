#ifndef DIRVIEW_EXCLUDE_H
#define DIRVIEW_EXCLUDE_H

#define PATTERN_MATCH 1
#define PATTERN_NOT_MATCH 0

typedef struct _list_node {
    char *pattern;
    struct _list_node *next;
} list_node;

void add_pattern(char *s);
char *get_pattern(int i);
void wipe_patterns();
int match_pattern(char *s);
int get_pattern_list_size();

#endif
