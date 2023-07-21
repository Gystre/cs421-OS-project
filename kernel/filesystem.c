#include "filesystem.h"
#include "../libc/string.h"

#define NULL 0

struct FileNode
{
	char name[256];

	struct FileNode *children;
	struct FileNode *sibling;
};

struct FileNode *root = NULL;
char cwd[] = "/";

void list_files()
{
	struct FileNode *current = root;
	while (current)
	{
		// printf("%s\n", current->name);
		current = current->sibling;
	}
}

void get_cwd(char *return_value)
{
	strcpy(return_value, cwd);
}