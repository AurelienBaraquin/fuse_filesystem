#include "tree.h"

//* Global variables _________________________________________________________*/
node_t *root = NULL;
pthread_mutex_t tree_mutex = PTHREAD_MUTEX_INITIALIZER;




//* Thread safe functions _____________________________________________________*/
void lock_tree(void) {
    pthread_mutex_lock(&tree_mutex);
}

void unlock_tree(void) {
    pthread_mutex_unlock(&tree_mutex);
}

//* New node _________________________________________________________________*/
node_t *new_node(const char *name, node_t *parent) {
    node_t *node = malloc(sizeof(node_t));
    if (!node) {
        return NULL;
    }

    memset(node, 0, sizeof(node_t));
    
    node->name = strdup(strrchr(name, '/'));
    node->content = NULL;
    node->parent = parent;
    node->compressed_size = 0;
    
    return node;
}



//* Free tree ________________________________________________________________*/
void free_node(node_t *node) {
    free(node->name);
    free(node->content);
    free(node);
}

void free_tree(node_t *node) {
    if (!node) {
        return;
    }
    for (int i = 0; i < MAX_CHILD; i++) {
        free_tree(node->childs[i]);
    }
    free(node);
}



//* Utils for tree____________________________________________________________*/
int add_child_to_parent(node_t *parent, node_t *child) {
    child->parent = parent;
    for (int i = 0; i < MAX_CHILD; i++) {
        if (!parent->childs[i]) {
            parent->childs[i] = child;
            return 0;
        }
    }
    return -1;
}

int remove_child_from_parent(node_t *parent, node_t *child) {
    for (int i = 0; i < MAX_CHILD; i++) {
        if (parent->childs[i] == child) {
            free_tree(child);
            parent->childs[i] = NULL;
            return 0;
        }
    }
    return -1;
}

node_t *get_node(const char *path) {
    if (!root) {
        return NULL;
    }
    
    if (strcmp(path, "/") == 0) {
        return root;
    }

    char *path_copy = strdup(path);
    char *token = strtok(path_copy, "/");
    node_t *current = root;
    while (token) {
        int found = 0;
        for (int i = 0; i < MAX_CHILD; i++) {
            if (current->childs[i] && strcmp(&current->childs[i]->name[1], token) == 0) {
                current = current->childs[i];
                found = 1;
                break;
            }
        }
        if (!found) {
            free(path_copy);
            return NULL;
        }
        token = strtok(NULL, "/");
    }
    free(path_copy);
    return current;
}

node_t *get_parent(const char *path) {
    char *path_copy = strdup(path);
    char *last_slash = strrchr(path_copy, '/');
    if (!last_slash) {
        free(path_copy);
        return NULL;
    }

    *last_slash = '\0';
    node_t *parent = get_node(path_copy);
    free(path_copy);
    return parent;
}

void init_root(void) {
    root = malloc(sizeof(node_t));
    if (!root)
        return;

    memset(root, 0, sizeof(node_t));
    root->name = strdup("/");
    root->content = NULL;
    root->stat.st_mode = S_IFDIR | 0755;
    root->stat.st_nlink = 2;
    root->parent = NULL;
}



//* User side functions ______________________________________________________*/
void init_root(void);

node_t *sys_add_file(const char *path) {
    if (strlen(path) < 2) {
        goto error;
    }

    if (get_node(path)) {
        goto error;
    }

    node_t *parent = get_parent(path);
    if (!parent) {
        goto error;
    }
    
    node_t *file = new_node(path, parent);
    if (!file) {
        goto error;
    }

    if (add_child_to_parent(parent, file) == -1) {
        goto error;
    }

    return file;

error:
    return NULL;
}

int sys_remove_file(const char *path) {
    node_t *file = get_node(path);
    if (!file) {
        return -1;
    }
    
    return remove_child_from_parent(file->parent, file);
}

int sys_rename_file(const char *old_path, const char *new_path) {
    node_t *file = get_node(old_path);
    if (!file) {
        return -1;
    }

    node_t *new_parent = get_parent(new_path);
    if (!new_parent) {
        return -1;
    }

    if (get_node(new_path)) {
        return -1;
    }

    free(file->name);
    file->name = strdup(strrchr(new_path, '/'));
    return 0;
}

#include "compressor.h"

//* Getters user side_________________________________________________________*/
node_t *get_node(const char *);

node_t *sys_get_root(void) {
    return root;
}

node_t *get_file(const char *path) {
    node_t *file = get_node(path);
    if (!file)
        return NULL;

    return file;
}



#include <stdio.h>

//* Print tree ________________________________________________________________*/
void print_tree_helper(node_t *node, int depth) {
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("%s\n", node->name);
    for (int i = 0; i < MAX_CHILD; i++) {
        if (node->childs[i]) {
            print_tree_helper(node->childs[i], depth + 1);
        }
    }
}

void print_tree(void) {
    if (!root)
        printf("Empty tree\n");
    else
        print_tree_helper(root, 0);
}
