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
#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include <errno.h>

#include <sys/stat.h>
#include <unistd.h>

#define _COLOR_IMPL
#include <clz/color.h>

#include "dir.h"
#include "prog.h"
#include "exclude.h"

#define CHECK_PATTERN(path) (get_pattern_list_size() == 0 || match_pattern(path) == PATTERN_NOT_MATCH )
#define CHECK_DIR_EMPTY(path) (!get_show_empty_dir() && is_empty_dir(path))

static int max_depth;
static char pre_char = ' ';
static int pre_char_len = 4;
static int color_next = 0;

static char *trim_trailing_char(char *s, char c);
static int str_last(char *s, char c);
static int do_color(char *path);
static int is_empty_dir(char *dirname);

void process_dir_rec(char *dirname, int depth) {
    if (!path_is_dir(dirname) && !get_show_files()) return;
    else if (!CHECK_PATTERN(dirname)) return;
    else if (CHECK_DIR_EMPTY(dirname)) return;

    trim_trailing_char(dirname, '/');
    char *prefix = NULL;

    if (get_indent()) {
        prefix = malloc(sizeof(char) * (depth * pre_char_len + 1));
        for (int i = 0; i < depth * pre_char_len; ++i) {
            prefix[i] = pre_char;
        }
        prefix[depth * pre_char_len] = '\0';
    }

    if (get_prefix_parent()) {
        printf("%s%s%s%s\n", prefix ? prefix : "", color_next ? COL_RED : "",
               dirname, color_next ? COL_RESET : "");
    }
    else {
        printf("%s%s%s%s\n", prefix ? prefix : "", color_next ? COL_RED : "",
               dirname + str_last(dirname, '/'), color_next ? COL_RESET : "");
    }
    color_next = 0;

    if (depth == max_depth) {
        printf("%s\t...\n", prefix ? prefix : "");
        if (prefix) free(prefix);
        return;
    }

    if (prefix) free(prefix);

    if (!path_is_dir(dirname)) return;

    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        printf("error: cannot access path %s (%s)\n", dirname, strerror(errno));
        exit(errno);
    }

    struct dirent *nextdir;
    char *buffer;

    while ((nextdir = readdir(dir)) != NULL) {
        if (!strcmp(nextdir->d_name, "..")) continue; // is ../ superdir pointer
        else if (!strcmp(nextdir->d_name, ".")) continue; // is ./ current dir pointer
        else if (*nextdir->d_name == '.' && !get_show_hidden()) continue; // is ./ current dir pointer

        buffer = malloc(sizeof(char) * (strlen(nextdir->d_name) + strlen(dirname) + 2)); // +2: one char fot '/' and one for '\0'
        strcpy(buffer, dirname);
        strcat(buffer, "/");
        strcat(buffer, nextdir->d_name);

        color_next = do_color(buffer);
        process_dir_rec(buffer, depth + 1);
        free(buffer);
    }

    if (errno != 0) {
        fprintf(stderr,"error: cannot access path %s (%s)\n", dirname, strerror(errno));
        exit(errno);
    }

    closedir(dir);
}

void process_dir(char *dirname, int max_dep) {
    DIR *d = opendir(dirname);

    if (access(dirname, F_OK) && !d) { // test file existence with F_OK or directory existence with d != NULL (-> no read permissions required if it is a file)
        fprintf(stderr,"error: cannot access path %s (%s)\n", dirname, strerror(errno));
        exit(errno);
    }

    if (d) closedir(d);

    max_depth = max_dep;
    color_next = do_color(dirname);
    process_dir_rec(dirname, 0);

    return;
}

void set_pre_char_len(int len) {
    pre_char_len = len;
}

int path_is_dir(char *path) {
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

static char *trim_trailing_char(char *s, char c) {
    while (s[strlen(s) - 1] == c) s[strlen(s) - 1] = '\0';
    return s;
}

static int str_last(char *s, char c) {
    int index = 0;
    int pos = -1;

    while (s[index]) {
        if (s[index] == c) {
            pos = index;
        }
        ++index;
    }

    return ++pos;
}

static int do_color(char *path) {
    struct stat stat_info;
    stat(path, &stat_info);
    return !(stat_info.st_mode & S_IFDIR) && get_color_files();
}

int is_empty_dir(char *dirname) {
    DIR *dir = opendir(dirname);
    if (!dir) {
        errno = 0;
        return 0;
    }

    struct dirent *e;
    struct stat stat_info;

    while((e = readdir(dir)) != NULL) {
        if (strcmp(e->d_name, ".") && strcmp(e->d_name, "..")) {
            char *s = malloc(sizeof(char) * (strlen(dirname) + strlen(e->d_name) + 2));
            sprintf(s, "%s/%s", dirname, e->d_name);

            stat(s, &stat_info);
            if (!(S_IFDIR & stat_info.st_mode)) {
                closedir(dir);
                free(s);
                return 0;
            }

            if (!is_empty_dir(s)) {
                closedir(dir);
                free(s);
                return 0;
            }

            free(s);
        }
    }

    closedir(dir);
    return 1;
}
