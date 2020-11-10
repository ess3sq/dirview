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

#ifndef DIRVIEW_PROG_H
#define DIRVIEW_PROG_H

#define INVALID_INT -1

void set_prefix_dir_symbol(int o);
void set_prefix_parent(int o);
void set_show_files(int o);
void set_color_files(int o);
void set_max_depth(int o);
void set_show_hidden(int o);
void set_indent(int o);
void set_show_empty_dir(int o);

int get_prefix_dir_symbol();
int get_prefix_parent();
int get_show_files();
int get_color_files();
int get_max_depth();
int get_show_hidden();
int get_indent();
int get_show_empty_dir();

int str_to_int_strict(char *s);

#endif
