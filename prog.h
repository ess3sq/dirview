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
