#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Structure definition for the node
typedef struct Node
{
	int data;
	struct Node *left;
	struct Node *right;
}Node;
//Structure definition for the stack
typedef struct Qnode
{
	Node *tree;
	struct Qnode *next;
}Qnode;


//Functions List
Node *createLeaf(int);
Node *buildTree(char *);
int countStack(Qnode **);
Node *mergeTree(Node *leftLeaf, Node *rightLeaf);
Qnode *stack_push(Qnode **stack, const void *new_object);
Qnode *stack_pop(Qnode **stack);
void destroyNode(Node *);
void print_tree(Node *tree, int i);
bool writeHuffman(FILE *outptr, Node * node, int *array, int height);
void printArray(int *array, int height);
void writeDecode(char *filename, Node *node, FILE *);
