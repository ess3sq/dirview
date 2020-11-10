#include <string.h>
#include <ctype.h>

#include "prog.h"
#include "dir.h"

static struct {
    int prefix_dir_symbol;
    int prefix_parent;
    int show_files;
    int color_files;
    int max_depth;
    int show_hidden;
    int indent;
    int show_empty_dir;
} options = {0,1,1, 0, MAX_DEPTH, 0, 1, 1};

void set_prefix_dir_symbol(int o) {
    options.prefix_dir_symbol = o;
}

void set_prefix_parent(int o) {
    options.prefix_parent = o;
}

void set_show_files(int o) {
    options.show_files = o;
}

void set_color_files(int o) {
    options.color_files = o;
}

void set_max_depth(int o) {
    options.max_depth = o;
}

void set_show_hidden(int o) {
    options.show_hidden = o;
}

void set_indent(int o) {
    options.indent = o;
}

void set_show_empty_dir(int o) {
    options.show_empty_dir = o;
}


int get_prefix_dir_symbol() {
    return options.prefix_dir_symbol;
}

int get_prefix_parent() {
    return options.prefix_parent;
}

int get_show_files() {
    return options.show_files;
}

int get_color_files() {
    return options.color_files;
}

int get_max_depth() {
    return options.max_depth;
}

int get_show_hidden() {
    return options.show_hidden;
}

int get_indent() {
    return options.indent;
}

int get_show_empty_dir() {
    return options.show_empty_dir;
}

int str_to_int_strict(char *s) {
    int n = 0;

    for (int i = 0; i < strlen(s); ++i) {
        if (!isdigit(s[i])) {
            return INVALID_INT;
        }
        n = n * 10 + (s[i] - '0');
    }

    return n;
}