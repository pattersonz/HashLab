--------------------------------
---------------INTRO------------
--------------------------------
The following text is instructions for compilation and execution of the 4 programs. 
All programs have documentation at the top and are commented throughout the code with
the algorithms and methods used. This README information assumes the user is running
all code through a linux based terminal at the location of this README file. Also keep 
in mind that these programs are not robust, make sure that input and text in files are 
in the proper format to avoid crashing.

NOTE: This is not proven to be a cryptographically secure hash. This is for educational purposes and use only. 


--------------------------------
-------RUNNING PROGRAMS---------
--------------------------------

1.) Hashing function - hashbrowns.c
	
	To compile hashbrowns.c:

		gcc hashbrowns.c -o hashbrowns

		Note: compilation will throw a warning, it can be ignored.
	
	To run hashbrowns:
		
		./hashbrowns *file name here*

		example: ./hashbrowns hashme/orig/1


	To run all original texts: (this will read in all 1000 original files and places the output text in the file hashes.orig)

		rm hashes.orig; for I in $(seq 1 1000); do ./hashbrowns hashme/orig/$I >> hashes.orig; done

		Note: you may get a warning if the file does not already exist, but it will still work.


	To run ALL texts: (this will read in all 1000 original & modded files and places the output text in the file hashes.all)

		rm hashes.all; for I in $(seq 1 1000); do ./hashbrowns hashme/orig/$I >> hashes.all; ./hashbrowns hashme/mod/$I >> hashes.all; done

		Note: you may get a warning if the file does not already exist, but it will still work.



2.) Checking for collisions - areThereCol.c

	To compile areThereCol.c:

		gcc areThereCol.c -o areThereCol

	To run areThereCol.c:

		./areThereCol *file name here*

		example: ./areThereCol hashes.orig
			Note: file withCollisions has collisions, for testing.


3.) Checking number of 1s in hash - num1s.c

	To compile num1s.c:

		gcc num1s.c -o num1s

		Note: compilation will throw a warning, it can be ignored.

	To run num1s:

		./num1s *file name here*
		
		example: ./num1s hashes.orig

		NOTE: columns are listed as the bit# with 31 being the least
			significant, and 0 being the most significant bit. This can
			be viewed easily by running the file "withCollisions". 


4.) Comparing Original text to Moddified text - origToMod.c

	To compile origToMod.c:

		gcc origToMod.c -o origToMod

		Note: compilation will throw a warning, it can be ignored.

	To run origToMod:

		./origToMod *file name here*
		example: ./origToMod hashes.all

		Note: This input assumes that the input contains hashes for an original
			text with the next line being a hash from a character changed
			version of the text. This file can be created by using the
			"to run ALL texts" in hashbrowns provided above.


--------------------------------
----------FINAL NOTES-----------
--------------------------------

This provides 2000 different texts which should be able to hash into 2000 different outputs.
However, the 32bit output is not particularly secure, so even a perfect 32 bit hash function
isn't ideal for strong cryptographic use. On top of that, this information only runs through 
2000 of a possible 2^32(4294967296) outputs, which is roughly 0.0000465%. Needless to say a
function passing with no collisions is not a good indicator of strength.

