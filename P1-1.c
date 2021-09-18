//=================================================================
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

/*    
Please fill in the following
 Student Name: Rahul Mone 
 Date: 2/21/21

ECE 2035 Project 1-1

This is the only file that should be modified for the C implementation
of Project 1.

Do not include any additional libraries.
------------------------------------------

Match Puzzle

This program finds the reference pattern in the candidates which might be
rotated or flipped.

*/

#include <stdio.h>
#include <stdlib.h>
#define DEBUG 0 // RESET THIS TO 0 BEFORE SUBMITTING YOUR CODE

int main(int argc, char *argv[]) {
  int  Reference;
  int  Candidates[8];
  int  NumCandidates;
  int  Position = -9; //temporary initial value (you can change it)
  int  Load_Reference(char *);
  int  Load_Mem(char *, int *);
  int  RefArray[2][8];
  int  adder = 3;
  int  CandArray[8][8];
  int  solution = 0;
  int  solArray[8];

  if (argc != 2) {
    printf("usage: ./P1-1 testfile\n");
    exit(1);
  }
  Reference = Load_Reference(argv[1]);
  if (Reference == 0) {
    printf("Invalid Reference pattern.\n");
    exit(1);
   }
  NumCandidates = Load_Mem(argv[1], Candidates);
   if (NumCandidates != 8) {
      printf("testfiles must contain 8 candidates\n");
      exit(1);
   }


   for (int i = 0; i < 8; i++) { // extract refence data into an array of all colors in that block.
	   RefArray[0][i] = Reference & adder;
	   Reference = Reference >> 2;
   }

   for (int i = 2; i >= 0; i--) { // flipped reference for first 3 positions 0-2
	   RefArray[1][i] = RefArray[0][2-i];
   }

   for (int i = 0; i < 5; i++) { // flipped reference for the rest of the square positions 3-7
	   RefArray[1][i+3] = RefArray[0][7-i];
   }

   

   for (int i = 0; i < 8; i++) {
	   for (int a = 0; a < 8; a++) { // extract refence data into an array of all colors in that block.
		   CandArray[i][a] = Candidates[i] & adder;
		   Candidates[i] = Candidates[i] >> 2;
	   }
   }
 
   


   for (int i = 0; i < 2; i++) { // iterate through the forwards and backwards array of the reference (forwards: i = 0, backwards/flipped i = 1)
	   for (int c = 0; c < 4; c++) { // rotate the refference array by 90 degrees 4 times for each the forward and flipped array
		   for (int a = 0; a < 8; a++) { // iterate through the 8 surrounding larger group boxes (0-7)


			   for (int b = 0; b < 8; b++) { // iterate through each color in the respective b spot in the box positions 0 - 7 in each box
				   if (RefArray[i][b] == CandArray[a][b]) { // compare the color in the current position in the reference array to the color in the current position to the resptive candidate(a).

					   //solArray[b] = CandArray[a][b];

					   if ((b == 7) && RefArray[i][b] == CandArray[a][b]) { // if you are on the last color, and it matches, you have a perfect match, set answer to candidate array (a)
						   Position = a;
						   solution = 1;
						   break;
					   }
					   else {
						   continue;
					   }
				   }

				   else {
					   break; // if the color does not match, break out of the for loop and move onto the next candidate
				   }


			   }

			   if (solution == 1) { // if a match is found, break
				   break;
			   }
		   }

		   if (solution == 1) {// if a match is found, break
			   break;
		   }

		   int sub1 = RefArray[i][0]; // temp value for first value in ref array
		   int sub2 = RefArray[i][1]; // temp value for the second value in ref array
		   
		   for (int z = 2; z < 8; z++) { // shift the reference array by 2
			   RefArray[i][z-2] = RefArray[i][z];
		   }
		   RefArray[i][6] = sub1; // add the temp values to the end of the new rotated ref array
		   RefArray[i][7] = sub2;
		   

	   }

	   if (solution == 1) {// if a match is found, break
		   break;
	   }
   }

   



   /* Use a statement like this to print information helpful to
      debugging (e.g., the current value of some variable).
      Set DEBUG to 1 using the #define above when debugging, but
      reset it back to 0 before submitting your code so that your
      program doesn't confuse the autograder with superfluous prints. */
   if (DEBUG){
     printf("Reference: %d == 0x%08x\n", Reference, Reference);
   }

   // your program should use this print statement to report the answer
   printf("The matching pattern is at position [0-7]: %d\n", Position);
   exit(0);
}






/* This routine reads in one integer value from the first line of a named file in the local directory (each line of the file is in the form Addr: integer). The integer is returned. */

int Load_Reference(char *InputFileName) {
  int	Reference, NumVals, Addr, Value;
  FILE	*FP;

  FP = fopen(InputFileName, "r");
  if (FP == NULL) {
    printf("%s could not be opened; check the filename\n", InputFileName);
    return 0;
  } else {
    NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
    if (NumVals == 2)
      Reference = Value;
    else {
      printf("test file must contain Addr: Value pairs on each line.\n");
      Reference = 0;
    }
    fclose(FP);
    return Reference;
   }
}

/* This routine loads in up to 8 newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray[]) {
   int	N, Addr, Value, NumVals;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
     printf("%s could not be opened; check the filename\n", InputFileName);
     return 0;
   } else {
     fscanf(FP, "%d: %d", &Addr, &Value); // ignore first line
     for (N=0; N < 8; N++) {
       NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
       if (NumVals == 2)
	 IntArray[N] = Value;
       else
	 break;
     }
     fclose(FP);
     return N;
   }
}
