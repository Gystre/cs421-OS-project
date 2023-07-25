#include "filesystem.h"

#include "../libc/string.h"

#define NULL 0

struct FileNode
{
	char name[256];

	// linked lists, we got the whole family tree here!
	struct FileNode *parent;
	struct FileNode *children;
	struct FileNode *sibling;
};

// the current folder, calling create_file will add the created file to the
// siblings of this folder
struct FileNode *root = NULL;

// create a new node
struct FileNode *create_file_node(const char *name)
{
	struct FileNode *node = (struct FileNode *)kmalloc(sizeof(struct FileNode));
	if (node)
	{
		strcpy(node->name, name);
		node->parent = NULL;
		node->children = NULL;
		node->sibling = NULL;
	}
	return node;
}

void list_files()
{
	// iterate through the root's children and print their names
	struct FileNode *current = root->children;
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
		return;
	}

	// set the file's parent to the root
	newDir->parent = root;

	// if the root has no children, set the root's children to the new file
	if (!root->children)
	{
		root->children = newDir;
		return;
	}

	// otherwise, find the last child and add the new file to the end
	struct FileNode *current = root->children;
	while (current->sibling)
	{
		current = current->sibling;
	}
	current->sibling = newDir;
}

void change_directory(const char *file_name)
{
	// move up one directory
	if (strcmp(file_name, "..") == 0)
	{
		if (root->parent)
		{

			root = root->parent;
			kprintf("%s\n", get_cwd());
			return;
		}
		else
		{
			kprintf("You are in the root directory.\n");
			return;
		}
	}

	// find the file in the root's children
	struct FileNode *current = root->children;
	while (current)
	{
		if (strcmp(current->name, file_name) == 0)
		{
			root = current;
			break;
		}
		current = current->sibling;
	}

	if (!current)
	{
		kprintf("Directory not found\n");
		return;
	}

	root = current;

	kprintf("%s\n", get_cwd());
}

char *get_cwd()
{
	char *cwd = (char *)kmalloc(512 * sizeof(char));

	cwd[0] = '\0'; // Null-terminate the string to start

	struct FileNode *node = root;
	if (node == NULL)
	{
		strcpy(cwd, "/");
		return cwd;
	}

	// Temporarily hold path components
	char **path = (char **)kmalloc(256 * sizeof(char *));
	int depth = 0;

	// Walk up the tree, storing each node
	while (node)
	{
		path[depth] = node->name;
		node = node->parent;
		depth++;
	}

	// Construct the path from root to the current directory
	int i;
	for (i = depth - 1; i >= 0; i--)
	{
		strcat(cwd, "/");
		strcat(cwd, path[i]);
	}

	return cwd;
}

void init_file_system()
{
	// create the root folder
	root = create_file_node("ROOT");

	// create some sibling files
	create_file("FILE1");
	create_file("FILE2");
}