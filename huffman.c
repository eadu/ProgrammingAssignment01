#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "huffman.h"

Node *buildTree(char *filename)
{
	FILE *inptr;
	inptr = fopen(filename, "r");
	if(inptr == NULL)
	{
		fprintf(stderr,"Error: could not open %s",filename);
		return NULL;
	}
	Node *leaf;
	Qnode *leftLeaf;
	Qnode *rightLeaf;
	Node *tree;
	Qnode *Tree; 
	int c;
	Qnode *stack;
	stack = NULL;
	fseek(inptr, 3 * sizeof(long), SEEK_SET);
	while((c = fgetc(inptr)) != EOF)
	{
		if(c == '1')
		{
			c = fgetc(inptr);			//read the next byte
			leaf = createLeaf(c);			//Create a leaf node
			stack = stack_push(&stack, leaf);	//Push the new node unto the stack
		}
		else if(c == '0')
		{
		//if it is a 0, pop the previous items from stack then merge
		//first check to see if there are more than one element in the stack
			if (countStack(&stack) != 1)					//first check to see if there are more than one element in on the stack if there is then
			{
				rightLeaf =  stack_pop(&stack);				//pop the last item off, this will be the right leaf
				leftLeaf = stack_pop(&stack);				//pop the next item off, left leaf
				tree = mergeTree(leftLeaf->tree, rightLeaf->tree);	//merge the two leafs
				free(rightLeaf);
				free(leftLeaf);
				stack = stack_push(&stack, tree);			//Push new node back unto stack
				
			}
			else
			{
				Tree = stack_pop(&stack);
				tree = Tree -> tree;
				free(stack);
				free(Tree);
				break;
			}
		}
	}
	fclose(inptr);
	return tree;
}

Node *createLeaf(int data)
{
	Node *tree = (Node *)malloc(sizeof(Node));
	tree -> data = data;
	tree -> left = NULL;
	tree -> right = NULL;
	
	return tree;
}

Node *mergeTree(Node *leftLeaf, Node *rightLeaf)
{
	Node *non_leaf;
	non_leaf = (Node *)malloc(sizeof(Node));
	non_leaf -> data = 1000;
	non_leaf -> left = leftLeaf;
	non_leaf -> right = rightLeaf;
	
	return non_leaf;
}

Qnode *stack_push(Qnode **stack, const void *new_object)
{
	Qnode * newLink;
	newLink = (Qnode*)malloc(sizeof(Qnode));	//Allocates mememory for new link
	if(newLink == NULL)
	{
		fprintf(stderr, "Error: could not malloc newlink\n");
		return NULL;
	}
	newLink->tree = (void*)new_object;	//Stores data into ptr
	newLink->next = *stack;			//Stores the next link address
	*stack = newLink;			//Updates the stack
	return newLink;
}
                       
Qnode *stack_pop(Qnode **stack)
{
	if(*stack == NULL)
	{
		return NULL;
	}
	Qnode *head;
	Qnode *current;

	head = *stack;
	current = head;
	head = head -> next;
	
	*stack = head;
	current->next = NULL;

	return current;
}

void destroyNode(Node *root)
{
	if(root == NULL)
	{
		return;
	}
	destroyNode(root -> left);
	destroyNode(root -> right);
	free(root);
}

void print_tree(Node *tree, int i)
{
	if(tree == NULL)
	{
		return;
	}
	Node *leftChild;
	Node *rightChild;

	leftChild = tree -> left;
	rightChild = tree -> right;

	print_tree(leftChild,  + 1);
	print_tree(rightChild,  + 1);

	int j;
	for(j = 0; j < i; j++)
	{
		fprintf(stderr, " ");
	}
	
	fprintf(stderr, "data = %d ", tree -> data);
	if(tree -> data != 1000)
	{
		fprintf(stderr, "Character = %d or %c", tree -> data, tree ->data);
	}
	fprintf(stderr, "\n");
}

int countStack(Qnode **stack)
{
	int count;
	Qnode *current;
	
	count = 1;
	current = *stack;
	while (current -> next != NULL)
	{
		current = current -> next;
		count++;
	}
	return count;
}

bool writeHuffman(FILE *outptr, Node * node, int *array, int height)
{
	if(node == NULL)
	{
		return true;
	}
	if (node -> left != NULL)
	{	
		array[height] = 0;
		writeHuffman(outptr, node -> left, array, height + 1);
	}
	if (node -> right != NULL)
	{
		array[height] = 1;
		writeHuffman(outptr, node -> right, array, height + 1);
	}
	if(node -> data != 1000)
	{
		if(fprintf(outptr, "%c:", (char)node -> data) != 2)
		{
			fprintf(stderr, "Error: could not write leaf data to file\n");
			return false;
		}
		int i;
		for(i = 0; i < height; i++)
		{
			if(fprintf(outptr, "%d", array[i]) != 1)
			{
				fprintf(stderr, "Error: could not write path to file\n");
				return false;
			}
		}
		if(fprintf(outptr, "\n") != 1)
		{
			fprintf(stderr, "Error: could not write new line to file\n");
			return false;
		}
	}
	return true;
}

