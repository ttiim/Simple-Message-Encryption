#include <stdbool.h>
/*
 * Definitions of character set encoded by the Encryption Utilities
 */
#define FIRST_ENCODABLE ' '  // Space character code 32, see Etter 2016 text, pp. 418-420
#define LAST_ENCODABLE  '~'  // Tilde character code 126
#define NUM_ENCODABLE  (LAST_ENCODABLE - FIRST_ENCODABLE + 1)
#define ASCII_CODES 128

/**
 * Generate a random int within the given range.
 * @param min lower limit of range
 * @param max upper limit of range  min <= max
 * @return  r where min <= r <= max
 */
int randint(int min, int max);

/**
 * Generate a random "encodable" char.
  * @return c where is_encodable(c)
 */
char randchar();

/**
 * Check if a character can be encoded - these are the printable characters.
 * @param c  the character to check
 * @return true iff FIRST_ENCODABLE <= c <= LAST_ENCODABLE
 */
bool is_encodable(char c);

/**
 * Encode a single cleartext character c using the given key character.
 * @param c  the cleartext character to be encoded
 * @param keychar  the key character to use to do encoding
 * @return c if ! is_encodable(c), otherwise 
 *         e where e is the Ceasar Cipher of (c, keychar) such that is_encodable(e) 
 */
char encode(char c, char keychar);

/**
 * Decode a single ciphertext character c using the given key character.
 * @param c  the ciphertext character to be decoded
 * @param keychar  the key character to use to do orginal encoding
 * @return  d such that encode(d, keychar) == c 
 */
char decode(char c, char keychar);

/**
 * Genenerate a random cipherkey with the given length
 *   such that each character in the cipherkey is_encodable()
 * @param length  the length of the cipherkey to be generated 
 * @return a C-string, s, where strlen(s) == length and is_encodable(s[i]) for i in 0 .. length-1
 */
char* generate_key(int length);
// Note: You must use str_create() utility to create the C-string returned by this function!



// ********* Utility functions **************
// **** The functions are provided to students to perform memory allocation for dynamic arrays

/**
 * Dynamically allocate a C-string (char array)
 * @param length - the size of the C-string to create
 * @return  array of length+1 chars, all initialized to NULL
 */
char* str_create(int length);

/**
 * Dynamically allocate an int array
 * @param length - the size of the int array to create
 * @return  array of length ints, all initialized to 0
 */
int* int_array_create(int length);

/**
 * Open the given file for read access
 * @param filename - the name of the file to open
 * @return  open file handle, ready for reading
 * @exit(-1) if the file does not exist
 */
 FILE* open(char* filename);
 
 ////////////////////////////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 /**
* Print a cipherkey to stdout (terminal window)
*   the first line should contain the cipher length
* @param length  the length of the cipherkey to be 
printed
*/
void print_key(int length);




/**
* Reada cipherkey from the given file, produced by print_key
* @param keyfilethe name of the file containing the cipher key
*/
char* read_keyfile(char* keyfile );
// Note: You must use str_create()utility to create the C-string returned by this function!




/**
* 
Encrypt the cleartext fileusing a Vigenère Cipher with the given key
* @param filename the name of the file to be encrypted
* @param keyfilethe name of a file containing the encryption key
*/
//void encrypt(char* filename, char* keyfile);
/**
* 
Decipher theciphertext fileusing the givenkey.
* @param filename the name of the file to be decrypted
* @param keyfilethe name of a file containing the decryption key
*/
//void decipher(char* filename, char* keyfile);
/**
* Genenerate a frequency histogram for 
printable characters in a file
* frequency historgram table is printed to stdout (terminal window)
* @param filename the name of the file to be analyzed
*/
void frequency_histogram(char* filename);


void print_histogram(char* filename, int histogram[], int length);

int sum_array(const int array[], int length);

void init_array(int array[], int length);

void compute_frequency(char* filename, int histogram[], int length);

char zeroBase(char c);

char asciiBase(char c);