/***********************************************
 * This program takes in a text file as an 
 * argument and will then hash the text in that 
 * file down to a 32 bit output. The hash(in hex)
 * and the file used will then be output at the
 * end.
 * author: Zach Patterson
 * 9/14/2017
 ***********************************************/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//main
int main( int argc, char *argv[])
{
	FILE * input;

	char * c;
	unsigned long hash = 0;
	c = (char *)malloc(4 * sizeof(char));

	//read file
	input = fopen (argv[1], "r");

	int quitFlag = 1;
	//repeat loop until EOF
	while (quitFlag)
	{
		//get 4 characters, if EOF is read, replace remaining chars with 'X'
		//note this set up always pads
		for (int i = 0; i <  4; i++)
		{
			c[i] = fgetc(input);
			if (c[i] == EOF)
			{
				for (int j = i; j < 4; j++)
					c[j] = 'X';
				quitFlag = 0;
				break;
			}
		}

		unsigned char * u = (unsigned char *)malloc(4 * sizeof(unsigned char));
		for (int i = 0; i < 4; i++)
		{
			//convert to unsigned
			u[i] = c[i];
			//first bit is last bit
			u[i] ^= u[i] << 7;

		}

		//flip last 4 bits of every char
		for (int i = 0; i < 4; i++)
			u[i] = (~u[i] & 15) + (u[i] & 240);

		// //since there are so many 6 and 7s in the front 4 bits
		// //XOR back half with front half of each char.
		for (int i = 0; i < 4; i++)
			u[i] ^= (u[i] << 4);

		//convert 4 chars to long
		unsigned long this32 = 0;
		for (int i = 0; i < 4; i++)
			this32 += u[3 - i] << (8 * i);

		//move start and wrap
		this32 = (this32 << 15) | (this32 >> 17);

		//XOR with current hash
		hash = hash ^ this32;
		
		//force avalanching
		hash ^= hash << 1;
		hash += hash >> 3;
		hash ^= hash << 7;
		hash += hash >> 11;
		hash ^= hash << 16;
		hash += hash >> 22;


	}
	//print hash
	printf ("%08x %s\n", hash, argv[1]);

	return 0;
}