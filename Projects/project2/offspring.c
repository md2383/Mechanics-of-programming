// File: $Id: offspring.c
//
// Project 2: Offspring Family Tree
// Author: Miguel Dias Pinto (md2383)
//
// Comments:
//     - Function Comments predefined in offspring.h
//     - Whenever the program takes input, it might not work if you make a 
//       mistake and use backspace. It takes in the backspace as a part of 
//       the command and it'll either give you a command error or not find 
//       the person you actually wanted. Please just retype the command and
//       it should work completely fine.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "offspring.h"

/**
 * Queue Struct for BFS traversal
 */
typedef struct QueueNode {
    TreeNode *node;
    struct QueueNode *next;
} QueueNode;

TreeNode *createNode(const char *name) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node) {
        node->name = strdup(name);
        node->child_count = 0;
        node->children = NULL;
    }
    return node;
}

void destroyTree(TreeNode *tree) {
    if (tree == NULL){
        return;
    }
    if (tree) {
        for (size_t i = 0; i < tree->child_count; ++i) {
            destroyTree(tree->children[i]);
        }
        if(tree->children){
            free(tree->children);
        }
        free(tree->name);
        free(tree);
    }
}


void initializeTree(TreeNode **root) {
    destroyTree(*root);
    *root = NULL;
}

void handleAddCommand(TreeNode **root, const char *parentName, const char *childName) {
    if (!parentName || !childName || !strlen(parentName) || !strlen(childName)) {
        printf("Usage: 'add parent name , child name'\n");
        return;
    }

    TreeNode *parent = findNode(*root, parentName);
    if (!parent) {
        printf("error: '%s' not in the tree and '%s' is not the root.\n", parentName, childName);
        return;
    }

    TreeNode *child = createNode(childName);
    if (child) {
        parent->children = (TreeNode **)realloc(parent->children, (parent->child_count + 1) * sizeof(TreeNode *));
        if (parent->children) {
            parent->children[parent->child_count] = child;
            parent->child_count++;
        } else {
            printf("error: Memory allocation failed while adding child '%s' to '%s'.\n", childName, parentName);
            free(child->name);
            free(child);
        }
    } else {
        printf("error: Memory allocation failed while creating child '%s'.\n", childName);
    }
}

TreeNode *findNode(TreeNode *tree, const char *name) {
    if (!tree || !name || !strlen(name)) {
        return NULL;
    }

    if (strcmp(tree->name, name) == 0) {
        return tree;
    }

    for (size_t i = 0; i < tree->child_count; ++i) {
        TreeNode *foundNode = findNode(tree->children[i], name);
        if (foundNode) {
            return foundNode;
        }
    }

    return NULL;
}

void printNode(TreeNode *node) {
    printf("%s", node->name);

    if (node->child_count > 0) {
        printf(" had ");
        for (int i = 0; i < node->child_count; i++) {
            printf("%s", node->children[i]->name);
            if (i < node->child_count - 1) {
                printf(", ");
            }
        }
        printf(".");
    } else {
        printf(" had no offspring.");
    }

    printf("\n");

    for (int i = 0; i < node->child_count; i++) {
        printNode(node->children[i]);
    }
}

size_t getTreeSize(TreeNode *root, const char *name) {
    TreeNode *startNode = root;

    if (name && strlen(name)) {
        startNode = findNode(root, name);
        if (!startNode) {
            return 0;
        }
    }

    if (!startNode) {
        return 0;
    }

    size_t size = 1;
    for (size_t i = 0; i < startNode->child_count; ++i) {
        size += getTreeSize(startNode->children[i], NULL);
    }
    return size;
}

int getTreeHeight(TreeNode *root, const char *name) {
    TreeNode *startNode = root;

    if (name && strlen(name)) {
        startNode = findNode(root, name);
        if (!startNode) {
            return -1;
        }
    }

    if (!startNode) {
        return -1;
    }

    if (startNode->child_count == 0) {
        return 0;
    }

    int maxHeight = -1;
    for (size_t i = 0; i < startNode->child_count; ++i) {
        int childHeight = getTreeHeight(startNode->children[i], NULL);
        if (childHeight > maxHeight) {
            maxHeight = childHeight;
        }
    }
    return maxHeight + 1;
}

void handleFindCommand(TreeNode *root, const char *name) {
    TreeNode *node = findNode(root, name);
    if (node) {
        printf("%s had ", node->name);
        if (node->child_count > 0) {
            printf("%s", node->children[0]->name);
            for (size_t i = 1; i < node->child_count; ++i) {
                printf(" and %s", node->children[i]->name);
            }
            printf(".\n");
        } else {
            printf("no offspring.\n");
        }
    } else {
        printf("error: '%s' not found.\n", name);
    }
}


void printTree(TreeNode *root) {
    if (!root) {
        return;
    }

    QueueNode *front = (QueueNode *)malloc(sizeof(QueueNode));
    front->node = root;
    front->next = NULL;
    QueueNode *rear = front;

    while (front != NULL) {
        TreeNode *node = front->node;

        if (node->child_count > 0) {
            printf("%s had ", node->name);
            for (size_t i = 0; i < node->child_count; ++i) {
                printf("%s", node->children[i]->name);
                if (i < node->child_count - 1) {
                    printf(" and ");
                }

                QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
                newNode->node = node->children[i];
                newNode->next = NULL;
                rear->next = newNode;
                rear = newNode;
            }
            printf(".\n");
        } else {
            printf("%s had no offspring.\n", node->name);
        }

        QueueNode *temp = front;
        front = front->next;
        free(temp);
    }
    
    while (front != NULL) {
        QueueNode *temp = front;
        front = front->next;
        free(temp);
    }
    
}   

void handlePrintCommand(TreeNode *root, const char *nodeName) {
    if (!nodeName || strlen(nodeName) == 0) {
        printTree(root);
    } else {
        TreeNode *node = findNode(root, nodeName);
        if (node) {
            printTree(node);
        } else {
            printf("error: '%s' not found.\n", nodeName);
        }
    }
}

void handleSizeCommand(TreeNode *root, const char *name) {
    size_t size = getTreeSize(root, name);
    printf("size: %zu\n", size);
}

void handleHeightCommand(TreeNode *root, const char *name) {
    int height = getTreeHeight(root, name);
    if (height >= 0) {
        printf("height: %d\n", height);
    } else {
        printf("height: -1\n");
    }
}

void handleHelpCommand() {
    printf("User Commands for offspring:\n");
    printf("add parent-name, child-name # find parent and add child.\n");
    printf("find name     # search and print name and children if name is found.\n");
    printf("print [name]  # breadth first traversal of offspring from name.\n");
    printf("size [name]   # count members in the [sub]tree.\n");
    printf("height [name] # return the height of [sub]tree.\n");
    printf("init          # delete current tree and restart with an empty tree.\n");
    printf("help          # print this information.\n");
    printf("quit          # delete current tree and end program.\n");
}

void fileToTree(TreeNode **root, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("error: could not open file '%s'\n", filename);
        return;
    }

    char line[1024];
    TreeNode *currentParent = NULL;

    while (fgets(line, sizeof(line), file)) {
        line[strlen(line) - 1] = '\0';

        char *parentName = strtok(line, ",");
        if (parentName) {
            while (parentName[0] == ' ') {
                parentName++;
            }

            char *childName = strtok(NULL, ",");
            if (*root == NULL) {
                *root = createNode(parentName); 
                currentParent = *root;
            } else {
                currentParent = findNode(*root, parentName); 
                if (!currentParent) {
                    printf("error: '%s' not in the tree and '%s' is not the root.\n", parentName, childName);
                    continue; 
                }
            }

            while (childName) {
                while (childName[0] == ' ') {
                    childName++;
                }
                handleAddCommand(root, currentParent->name, childName); 
                childName = strtok(NULL, ",");
            }
        }
    }

    fclose(file);
}


int main(int argc, char *argv[]) {
    TreeNode *root = NULL;

    if (argc > 1) {
        fileToTree(&root, argv[1]);
    }

    char command[1024];
    while (1) {
        printf("offspring> ");
        fgets(command, sizeof(command), stdin);
        command[strlen(command) - 1] = '\0'; 

        char *commandName = strtok(command, " ,");
        char *arg1 = strtok(NULL, ",");
        char *arg2 = strtok(NULL, ",");

        if (commandName) {
            if (strcmp(commandName, "add") == 0) {
                handleAddCommand(&root, arg1, arg2);
            } else if (strcmp(commandName, "find") == 0) {
                handleFindCommand(root, arg1);
            } else if (strcmp(commandName, "print") == 0) {
                handlePrintCommand(root, arg1);
            } else if (strcmp(commandName, "size") == 0) {
                handleSizeCommand(root, arg1);
            } else if (strcmp(commandName, "height") == 0) {
                handleHeightCommand(root, arg1);
            } else if (strcmp(commandName, "init") == 0) {
                initializeTree(&root);
            } else if (strcmp(commandName, "help") == 0) {
                handleHelpCommand();
            } else if (strcmp(commandName, "quit") == 0) {
                destroyTree(root);
                printf("Exiting...\n");
                return 0;
            } else {
                printf("Unknown command. Type 'help' for available commands.\n");
            }
        }
    }
    
    
    if(root){
        destroyTree(root);
    }
    
    return 0;
}
