	/*
 *  Comp120 - Lab 7:  Starter project -- Complete this code
 *    Charcter Frequency analysis -- read a text file and display frequency analysis
 *     for all printable characters.
 *
 *  Author: J. Fall
 *  Date: Feb. 2017
 */
 
#include <stdlib.h>
#include <stdio.h> 
#include <stdbool.h>

// Function prototypes:
void init_array(int array[], int length);
int sum_array(const int array[], int length);
bool isPrintable(char c);
void compute_frequency(char* filename, int histogram[], int length);
void write_histogram(char* filename, int histogram[], int length);
FILE* openFileRead(char* filename);
FILE* openFileWrite(char* filename);

// Definition of printable character set 
#define FIRST_PRINTABLE ' '  // Space character code 32, see Etter 2016 text, pp. 418-420
#define LAST_PRINTABLE  '~'  // Tilde character code 126
#define NUM_PRINTABLE  (int) (LAST_PRINTABLE - FIRST_PRINTABLE + 1)

int main( int argc, char* argv[] )
{
   if (argc < 3) 
   {
      printf("Usage: freq inputFile outputFile \n");
      exit(-1);
   }

   int histogram[NUM_PRINTABLE];  // Array of counters -- one for each printible character
   
   compute_frequency(argv[1], histogram, NUM_PRINTABLE);
   
   write_histogram(argv[2], histogram, NUM_PRINTABLE);
   
   printf( "Program complete. Frequency histogram written to file %s \n", argv[2] );

   return 0;
}

/*
 * Initialize the array of integers of given length to all zeros
 */
void init_array(int array[], int length) 
{
    // TODO: write function to assign 0 too every array element.
   int i;
   for(i=0; i<length;i++)
   {   
    array[i]=0;
   }
}


/*
 * Return the sum of all items in the given array
 */
int sum_array(const int array[], int length)
{
	int i;
	int sum=0;
  for(i=0; i<length; i++)
  {
   sum= sum + array[i];

  }	  

return sum;
  //return -1; // TODO: write function to add up every element in the given array.
}

/*
 * Return true iff the character is PRINTABLE
 */
bool isPrintable(char c)
{
	
	
	return (FIRST_PRINTABLE<=c && c>=LAST_PRINTABLE);
   //return false;  // TODO:  write function to return true iff c is a printable character
}
 
/*
 * Compute the frequency histogram for all PRINTABLE characters in the given file
 */
void compute_frequency(char* filename, int histogram[], int length)
{
   FILE* inputFile = openFileRead(filename);
   
   init_array(histogram, length);
   char c = getc(inputFile);
   while (c != EOF) 
   {
	   int i = c-FIRST_PRINTABLE;
	   length=NUM_PRINTABLE;
       
	  histogram[i]++;
	  c = getc(inputFile);
	 // TODO: write algorithm to count the number of times character c occurs.
      // HINT: since array indexes start at zero, map the ASCII code for each
      //       printable charcter onto an index by subtracting FIRST_PRINTABLE

}
}
/*
 * Write the frequency histogram out to the given file
 */
void write_histogram(char* filename, int histogram[], int length)
{
   FILE* outputFile = openFileWrite(filename);
   
   int total_count = sum_array(histogram, length);
   fprintf(outputFile, "Frequency Analysis Results.  Input contained %d printable characters. \n", total_count);
   fprintf(outputFile, "Char | Frequency \n");
   fprintf(outputFile, "____ | _________ \n");
   int i;
   for (i=0; i<length; i++) {
      char ch = (char) (i + FIRST_PRINTABLE);
      double freq;
      if (histogram[i] > 0) {
         double freq = histogram[i]/(double)total_count * 100;
         fprintf(outputFile, "%3c  | %9.3f%% \n", ch, freq);
      }
      else
         fprintf(outputFile, "%3c  | %9d%% \n", ch, 0);
   }
}

/*
 * Attempt to open the file for read access.
 * Peforms error check and exits if file is not accessible
 */
FILE* openFileRead(char* filename)
{
   FILE* inFile = fopen(filename, "r" );
   if( inFile == NULL) {
      printf( "Error opening input file %s, program terminating!\n", filename);
      exit(-1);
   }
   return inFile;
}

/*
 * Attempt to open the file for write access.
 * Peforms error check and exits if file is not accessible
 */
FILE* openFileWrite(char* filename)
{
   FILE* outFile = fopen(filename, "w" );
   if( outFile == NULL) {
      printf( "Error opening output file %s, program terminating!\n", filename);
      exit(-1);
   }
   return outFile;
}
