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

#include <stdio.h>
#include <string.h>

#include "dir.h"
#include "prog.h"
#include "exclude.h"

#define PROG_VERSION "1.0"
#define PROG_AUTHOR "L. Calza"

/*
 * missing: -f
 * ideas: -e (exclude)
 */

char *prog;

void print_help() {
    printf("%s: view directory tree structure\nUsage:\n\t%s [OPTIONS ...] [PATHS ...]\nOptions:\n\tSome options require an argument."
           "\n\t-n, --max-depth <arg>\tSpecify max recursion depth"
           "\n\t\t\t\t(arg must be a positive integer)"
           "\n\t-e, --exclude <arg>\tSpecify a substring of the path as a"
           "\n\t\t\t\tcase-sensitive exclusion pattern"
           "\n"
           "\n\t-p, --no-parent\t\tHide parent prefix"
           "\n\t-f, --files\t\tHide empty directories"
           "\n\t-d, --dirs\t\tShow only directories, hide files"
           "\n\t-h, --show-hidden\tShow hidden files and directories\n\t\t\t\t(name starts with .)"
           "\n"
           "\n\t-c, --color\t\tColor devices (everything except directories)"
           "\n\t-i, --no-indent\t\tOmit indentation of tree structure"
           "\n"
           "\n\t    --help\t\tShow current view"
           "\n\t    --version\t\tShow program version"
           "\nNotes:"
           "\n\t- The path(s) need(s) to be provided after the options,\n\t  otherwise the options will not apply."
           "\n\t- The options '-f' and '-d' do not apply to the 'root' devices\n\t  and directories passed to the program."
           "\n\t- If the path points to a deeper tree structure, the use of\n\t  the option '-f' may cause a significant additional overhead."
           "\n\n",
           prog, prog);
}

void print_version() {
    printf("%s: v" PROG_VERSION " (" PROG_AUTHOR ")\n", prog);
}

void print_no_path() {
    printf("%s: no path provided\n", prog);
}

int main(int argc, char *argv[]) {
    prog = argv[0];

    if (argc == 1) {
        print_no_path();
        return 0;
    }

    int shown_something = 0,
        param_is_max = 0,
        param_is_exclude = 0;
    int n;

    for (int i = 1; i < argc; ++i) {
        if (*argv[i] == '-') {
            if (!strcmp(argv[i], "--help")) {
                print_help();
                shown_something = 1;
                continue;
            }
            else if (!strcmp(argv[i], "--version")) {
                print_version();
                shown_something = 1;
                continue;
            }
            else if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--dirs")) {
                set_show_files(0);
                shown_something = 0;
                continue;
            }
            else if (!strcmp(argv[i], "-p") || !strcmp(argv[i], "--no-parent")) {
                set_prefix_parent(0);
                shown_something = 0;
                continue;
            }
            else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--show-hidden")) {
                set_show_hidden(1);
                shown_something = 0;
                continue;
            }
            else if (!strcmp(argv[i], "-c") || !strcmp(argv[i], "--color")) {
                set_color_files(1);
                shown_something = 0;
                continue;
            }
            else if (!strcmp(argv[i], "-i") || !strcmp(argv[i], "--no-indent")) {
                set_indent(0);
                shown_something = 0;
                continue;
            }
            else if (!strcmp(argv[i], "-f") || !strcmp(argv[i], "--files")) {
                set_show_empty_dir(0);
                shown_something = 0;
                continue;
            }
            else if (!strcmp(argv[i], "-n") || !strcmp(argv[i], "--max-depth")) {
                param_is_max = 1;
                shown_something = 0;
                continue;
            }
            else if (!strcmp(argv[i], "-e") || !strcmp(argv[i], "--exclude")) {
                param_is_exclude = 1;
                shown_something = 0;
                continue;
            }

            fprintf(stderr,"error: invalid option '%s'. Try `%s --help`\n", argv[i], argv[0]);
            wipe_patterns();
            return 1;
        }

        if (param_is_max) {
            param_is_max = 0;
            shown_something = 0;
            n = str_to_int_strict(argv[i]);

            if (n == INVALID_INT) {
                fprintf(stderr, "error: argument to '--max-depth' must be an integer\n");
                wipe_patterns();
                return 1;
            }

            set_max_depth(n);
            continue;
        }
        else if (param_is_exclude) {
            param_is_exclude = 0;
            add_pattern(argv[i]);
            shown_something = 0;
            continue;
        }

        shown_something = 1;
        process_dir(argv[i], get_max_depth());
        printf("\n");
    }

    if (!shown_something) {
        print_no_path();
    }

    wipe_patterns();
    return 0;
}
