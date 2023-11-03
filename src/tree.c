#include "tree.h"

node_t *root = NULL;

node_t *new_node(const char *name, node_t *parent) {
    node_t *node = malloc(sizeof(node_t));
    if (!node) {
        return NULL;
    }

    memset(node, 0, sizeof(node_t));
    
    node->name = strdup(name);
    node->content = NULL;
    node->parent = parent;
    
    return node;
}

void free_node(node_t *node) {
    free(node->name);
    free(node->content);
    free(node);
}

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
            free_node(child);
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
            if (current->childs[i] && strcmp(current->childs[i]->name, token) == 0) {
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

int add_file(const char *path) {
    if (!root) {
        root = new_node("/", NULL);
        if (!root) {
            return -1;
        }
    }

    node_t *parent = get_parent(path);
    if (!parent) {
        return -1;
    }
    
    node_t *file = new_node(path, parent);
    if (!file) {
        return -1;
    }
    
    return add_child_to_parent(parent, file);
}

int remove_file(const char *path) {
    node_t *file = get_node(path);
    if (!file) {
        return -1;
    }
    
    return remove_child_from_parent(file->parent, file);
}

node_t *get_file(const char *path) {
    return get_node(path);
}





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
    if (!root) {
        printf("Empty tree\n");
        return;
    }
    print_tree_helper(root, 0);
}
