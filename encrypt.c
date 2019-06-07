/*
*Problem Statement: Finish off where we left off in assignment 3 by completing encryption and decryption
*
*Author: Tim Wriglesworth
*Date: 04.04.17
*Comp 120. Capilano University
*Assignemnt 3

*/
/*specific outline
 * Comp120: Assignment 3 Started
 * Student write:  Encryption utiliy functions
 * Provided: Helper functions for doing array memory allocation
 *
 */
 /*
 *note with the posting of the assignemtn 2 solutions i have made a few corrections
 *to my functions. although i passed all tests i wanted to ensure there were
 ** no bugs, as i was having immense difficulty in debugging my encrypt/ decrypt
 *functions
 *
 */
 
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include <time.h>
#include "encrypt.h"




/******** HELPER FUNCTIONS ************************/
/******** Memory allocation and File open *********/

 /*
  * Allocate a dynamic array of chars 1 greater than length
  * Initialize to array to NULL
  */
char* str_create(int length) 
{
   char* str = malloc((length+1)*sizeof(char));
   
   int i;
   for (i=0; i<=length; i++) {
      str[i] = '\0';
   }
   return str;
}

/*
  * Allocate a dynamic array of integers of given length
  * Initialize to array to zeros
  */
int* int_array_create(int length) 
{
   int* array = malloc((length)*sizeof(int));
   
   int i;
   for (i=0; i<length; i++) {
      array[i] = 0;
   }
   return array;
}

/*
 * Open input file (read-only) and check that the file exists
 *  print an error message and exit(-1) if the file does not exist
 * Return open file handle otherwise.
 */
	FILE* open(char* filename)
	{
	   FILE* file = fopen(filename, "r");
	   if (file == NULL) {
		  printf("Error: file does not exist: %s \n", filename);
		  exit(-1);
	   }
	   return file;
	}

/*
 * Generate a random int within the given range.
 * @param min lower limit of range
 * @param max upper limit of range  min <= max
 * @return  r where min <= r <= max
 */
int randint(int min, int max)
{
   return rand()%(max-min+1) + min;
}
/*
 * Generate a random "encodable" char.
  * @return c where is_encodable(c)
 */
char randchar()
{
   return (char) randint((int)FIRST_ENCODABLE, (int)LAST_ENCODABLE);
}


/*
/*
 * Check if a character can be encoded - these are the printable characters.
 * @param c  the character to check
 * @return true iff FIRST_ENCODABLE <= c <= LAST_ENCODABLE
 */
bool is_encodable(char c)
{
	
return FIRST_ENCODABLE <= c && c <= LAST_ENCODABLE;
}

char zeroBase(char c)
{
   return c - FIRST_ENCODABLE;
}

/*
 * Shift a zeroBased encodable character back to normal ASCII position
 */
char asciiBase(char c)
{
   return c + FIRST_ENCODABLE;
}


/*
 * Encode a single cleartext character c using the given key character.
 * @param c  the cleartext character to be encoded
 * @param keychar  the key character to use to do encoding
 * @return c if ! is_encodable(c), otherwise 
 *         e where e is the Ceasar Cipher of (c, keychar) such that is_encodable(e) 
 */
char encode(char c, char keychar)      
{
   if (is_encodable(c)) {
      return asciiBase( (zeroBase(c) + zeroBase(keychar)) % NUM_ENCODABLE );
   }
   else {
      return c;
   }
}
/*
 * Decode a single ciphertext character c using the given key character.
 * @param c  the ciphertext character to be decoded
 * @param keychar  the key character to use to do orginal encoding
 * @return  d such that encode(d, keychar) == c 
 */
char decode(char c, char keychar) 
{
   if (is_encodable(c)) 
   {
      return asciiBase( (NUM_ENCODABLE + zeroBase(c) - zeroBase(keychar)) % NUM_ENCODABLE );
   }
   else {
      return c;
   }
}
/*
 * Genenerate a random cipherkey with the given length
 *   such that each character in the cipherkey is_encodable()
 * @param length  the length of the cipherkey to be generated 
 * @return a C-string, s, where strlen(s) == length and is_encodable(s[i]) for i in 0 .. length-1
 // Note: You must use str_create() utility to create the C-string returned by this function!
 */

 char* generate_key(int length)

{

  char* s = str_create(length);                          //intialze array filled with NULL character
  int i;

  srand(time(NULL));                          
  for ( i=0;  i<length; i++)                                          
 {
        s[i]=randchar();
  }
return s;


}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//notizen zum programmer. alle die Funktionen nach unten besteht nur von Aufgabe 3

/**
* Print a cipherkey to stdout (terminal window)
*   the first line should contain the cipher length
* @param length  the length of the cipherkey to be 
printed
*/
void print_key (int length)
{
	printf("%s\n",generate_key(length));
	
}



/**
* Read a ci	pherkey from the given file, produced by print_key
* @param keyfile the name of the file containing the cipher key
// Note: You must use str_create()utility to create the C-string returned by this function!
*/
char* read_keyfile(char* keyfile)          //NOTE Professor Jo Wang talked me through this idea and we developed this algorithm

{

	char *s;  
	FILE* inkey= open(keyfile);	
	int i = 0;
	
	char c = fgetc(inkey);  	//prime the while loop
	
	 while(c !=EOF)
	 {
		
	   i++;             //need to find length of the file
	   c = fgetc(inkey);  
	     
	 }
	 
	 s =str_create(i);
	 
	 i =0;
	 rewind(inkey);         //move file pointer to the beginning of file
	 c = fgetc(inkey);     //prime the while loop
	 
	 while(c!= EOF)
	 {
		s[i] = c;
		             //need get characters into dynamic memory of string
		i++;
		c=fgetc(inkey);
	 }
	 
     fclose (inkey);
return s;
		
}



/**
* 
Encrypt the cleartext fileusing a Vigenère Cipher with the given key
* @param filename the name of the file to be encrypted
* @param keyfilethe name of a file containing the encryption key
*/
void encrypt(char* filename, char* keyfile)

{
	
	FILE* encryptTxt= open(filename);   //open of file to be encrypted
	char* key= read_keyfile(keyfile);  
    int i;
	
	char c = getc(encryptTxt);   //prime while loop     
	while(c != EOF)
	{
		if (i==strlen(key))      //this is essentially a modulus operator but this made sense to me to write out in more then one step
		{
			i=0;
		}
		printf( "%c", encode(c, key[i]));
		c = getc(encryptTxt);
		i++;
	}
	
}
	
		
/**
* 
Decipher theciphertext fileusing the givenkey.
* @param filename the name of the file to be decrypted
* @param keyfilethe name of a file containing the decryption key
*/
void decipher(char* filename, char* keyfile)
{
	char* key= read_keyfile(keyfile);
    FILE* decryptTxt= open(filename);
	int i;
	char c = getc(decryptTxt);        
	while(c != EOF)
	{
		if (i==strlen(key))    
		{
			i=0;
		}
		printf( "%c", decode(c, key[i]));
		c = getc(decryptTxt);
		i++;
	}
	
	
}

/**
* Genenerate a frequency histogram for 
printable characters in a file
* frequency historgram table is printed to stdout (terminal window)
* @param filename the name of the file to be analyzed
*/
void frequency_histogram(char* filename)
{

 int histogram[NUM_ENCODABLE];  // Array of counters -- one for each printible character
   
   compute_frequency(filename, histogram, NUM_ENCODABLE);
   
   print_histogram(filename, histogram, NUM_ENCODABLE);
   
    printf( "Program complete. Frequency histogram of file %s \n", filename );


}


void compute_frequency(char* filename, int histogram[], int length)
{
   FILE* inputFile = open(filename);
   
   init_array(histogram, length);
   char c = getc(inputFile);
   while (c != EOF) 
   {
	   int i = c-FIRST_ENCODABLE;
	   length= NUM_ENCODABLE;
       
	  histogram[i]++;
	  c = getc(inputFile);
	
}
}
/*
 * Write the frequency histogram out to the given file
 */
void print_histogram(char* filename, int histogram[], int length)
{
   
   
   int total_count = sum_array(histogram, length);
   printf( "Frequency Analysis Results.  Input contained %d printable characters. \n", total_count);
   printf( "Char | Frequency \n");
   printf( "____ | _________ \n");
   int i;
   for (i=0; i<length; i++) {
      char ch = (char) (i +FIRST_ENCODABLE);
      double freq;
      if (histogram[i] > 0) {
         double freq = histogram[i]/(double)total_count * 100;
         printf( "%3c  | %9.3f%% \n", ch, freq);
      }
      else
         printf( "%3c  | %9d%% \n", ch, 0);
   }
}
void init_array(int array[], int length) 
{
   int i;
   for(i=0; i<length;i++)
   {   
    array[i]=0;
   }
}


/*
 * Return the sum of all items in the given array                   
 
 //this was not included in program specs but i really liked the idea of including this. 
 it helped with debugging and is handy.
 
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
  
}
