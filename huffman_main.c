#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "huffman.h"

int main(int argc, char *argv[])
{
	int array[255] = {0};	
	
	Node *node;
	node = NULL;
	node = buildTree(argv[2]);
	if(strcmp(argv[1], "-c") == 0)
	{
		FILE *outptr;
		outptr = fopen(argv[3], "w");
		if(outptr == NULL)
		{
			fprintf(stderr, "Error: could not open %s", argv[3]);
			destroyNode(node);
			return EXIT_FAILURE;
		}
		if(writeHuffman(outptr, node, array, 0) == false)
		{
			fprintf(stderr, "Error: could not write huffman code book\n");
			fclose(outptr);
			destroyNode(node);
			return EXIT_FAILURE;
		}
		FILE *outptr1;
		outptr1 = fopen(argv[4], "w");
		if(outptr == NULL)
		{
			fprintf(stderr, "Error");
			fclose(outptr);
			destroyNode(node);
			return EXIT_FAILURE;
		}
		writeDecode(argv[2], node, outptr1);
		fclose(outptr);
		fclose(outptr1);
	}
	destroyNode(node);
	return EXIT_SUCCESS;
}
