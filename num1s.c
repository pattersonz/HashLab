/***********************************************
 * This program takes in a text file as an 
 * argument and will then count the number of
 * 1s in each column, and the total average
 * overall(average per line). The statistics
 * are then output
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

	//vars for number of 1s
	unsigned long num1s = 0;
	int * cols;
	cols = (int*)malloc(32 * sizeof(int));
	for (int i = 0; i < 32; i++)
		cols[i] = 0;

	//bit shift each long to count totals
	for (int i = 0; i < numNL; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			//mod 2 for if last bit is a 1
			if (hashes[i] % 2 == 1)
			{
				num1s++;
				cols[31 - j]++;
			}
			hashes[i] = hashes[i] >> 1;
		}
	}

	//output statistics
	printf("Average 1s per line: %.3lf or %.3lf%%\n", 
		(double)num1s / (double)numNL,
		 100.0 * (double)num1s / (double)numNL / 32.0);
	
	for (int i = 0; i < 32; i++)
		printf("%% in col%d: %.3lf%%\n", i, 100.0 *(double)cols[i] / (double)numNL);


	return 0;
}