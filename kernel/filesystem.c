#include "filesystem.h"
#include "../libc/string.h"

#define NULL 0

struct FileNode
{
	char name[256];

	// linked lists
	struct FileNode *children;
	struct FileNode *sibling;
};

// the current folder, calling create_file will make the file to the siblings of this folder
struct FileNode *root = NULL;
char cwd[] = "/";

// create a new node
struct FileNode *create_file_node(const char *name)
{
	struct FileNode *node = (struct FileNode *)kmalloc(sizeof(struct FileNode));
	if (node)
	{
		strcpy(node->name, name);
		node->children = NULL;
		node->sibling = NULL;
	}
	return node;
}

void list_files()
{
	struct FileNode *current = root;

	if (!current || !current->sibling)
	{
		kprintf("No files found\n");
		return;
	}

	current = current->sibling;

	while (current)
	{
		kprintf("%s  ", current->name);
		current = current->sibling;
	}
	kprintf("\n");
}

void create_file(const char *name)
{
	struct FileNode *newDir = create_file_node(name);
	if (!root)
	{
		root = newDir;
	}
	else
	{
		struct FileNode *current = root;
		while (current->sibling)
		{
			current = current->sibling;
		}
		current->sibling = newDir;
	}
}

void get_cwd(char *return_value)
{
	strcpy(return_value, cwd);
}

void init_file_system()
{
	// create the root folder
	root = create_file_node("/");

	// create some sibling files
	create_file("file1");
	create_file("file2");
}