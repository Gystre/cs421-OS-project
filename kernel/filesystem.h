#ifndef FILESYSTEM_H
#define FILESYSTEM_H

char *get_cwd();
void init_file_system();
void list_files();
void change_directory(const char *file_name);

#endif