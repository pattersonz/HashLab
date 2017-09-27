/***********************************************
 * This program takes in a text file as an 
 * argument assuming it is in the notation
 *
 * hash(8 char in hex) fileLocation
 *
 * on each line. Each hash is then compared with
 * each other and will output if a collision has
 * occured on those two lines. If there are no
 * collisions, the output will reflect that.
 * author: Zach Patterson
 * 9/15/2017
 ***********************************************/
#include <stdlib.h>
#include <stdio.h>

/*
 * This function takes in two strings representing
 * the hash values and checks if they are equal
 * if they are, returns true.
 * c1 - hash string primary
 * c2 - hash string secondary
 * return: (T/F) if the strings are the same
 */
int compareHash(char * c1, char * c2)
{
	for (int i = 0; i < 8; i++)
		if (c1[i] != c2[i])
			return 0;
	return 1;
}

//main
int main( int argc, char *argv[])
{
	FILE * input;
	input = fopen( argv[1], "r" );
	int numNL = 0;
	char c = 'a';
	//count number of new lines
	while ( (c = fgetc(input)) != EOF)
		if (c == '\n')
			numNL++;

	//create space
	char ** hashes;
	hashes = (char **)malloc(numNL * sizeof(char*));
	for (int i = 0; i < numNL; i++)
		hashes[i] = (char*)malloc(8 * sizeof(char));

	//reset file
	fclose(input);
	input = fopen( argv[1], "r" );

	//read in all chars
	for (int i = 0; i < numNL; i++)
	{
		for (int j = 0; j < 8; j++)
			hashes[i][j] = fgetc(input);
		while ( (c = fgetc(input)) != '\n' && c != EOF)
		{
			asm("nop");
		}

	}

	int flag = 0;
	//compare all hashes
	for (int i = 1; i < numNL; i++)
		for (int j = 0; j < i; j++)
			if (compareHash(hashes[i], hashes[j]))
			{
				printf("Collision at: Ln1:%d Ln2:%d\n", j, i);
				flag = 1;
			}
	if (!flag)
		printf("No Collisions\n");
	return 0;
}