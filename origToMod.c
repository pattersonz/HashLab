/***********************************************
 * This program takes in a text file as an 
 * argument assuming it is in the notation
 *
 * hash(8 char in hex) fileLocation
 * modedHash(8 char in hex) fileLcation
 *
 * on every other line. Each hash is then compared
 * with it's modified hash value. The average 
 * change in bits from the original to the modded
 * hashes are compared and then totaled up and
 * averaged across all pairs.
 * author: Zach Patterson
 * 9/18/2017
 ***********************************************/
#include <stdlib.h>
#include <stdio.h>


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
	unsigned long *hashes;
	hashes = (unsigned long *)malloc(numNL * sizeof(unsigned long));

	//reset file
	fclose(input);
	input = fopen( argv[1], "r" );

	//read in all chars
	for (int i = 0; i < numNL; i++)
	{
		fscanf( input, "%08x", &hashes[i]);
		while ( (c = fgetc(input)) != '\n' && c != EOF)
		{
			asm("nop");
		}

	}

	unsigned long num1s = 0;

	// each pair is XORd against eachother providing so
	// each bit that is changed will be a 1. Then the 
	// XOR val is shifted to count the number of 1s.
	for (int i = 0; i < numNL; i += 2)
	{
		int temp = 0;
		unsigned long xor = hashes[i] ^ hashes[i + 1];
		for (int j = 0; j < 32; j++)
		{
			if (xor % 2 == 1)
				temp++;
			xor = xor >> 1;
		}
		num1s += temp;
	}


	//output
	printf("Average bit change from orig to mod: %.3lf or %.3lf%%\n", 
		(double)num1s / ((double)numNL / 2.0),
		 100.0 * (double)num1s / ((double)numNL / 2.0 )/ 32.0);
	

	return 0;
}