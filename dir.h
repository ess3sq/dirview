#ifndef DIRVIEW_DIR_H
#define DIRVIEW_DIR_H

#define MAX_DEPTH -1

void process_dir(char *dirname, int max_dep);
void set_pre_char_len(int len);
int path_is_dir(char *path);

#endif
