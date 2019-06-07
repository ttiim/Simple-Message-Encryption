/*
 * Comp120: Assignment 2 Part A  
 * Unit Tests that encode and decode perform opposite roles for every encodable
 * Build instructions:  > gcc test-encode-decode.c encrypt.c -o test-encode-decode
 *
 * Author: J. Fall
 * Date: Mar, 2017
 */

#include <stdio.h> 
#include <stdlib.h>
#include "encrypt.h"


/*
* Run a single test case
* Report on failed test
* Return 0 if test successful, 1 otherwise
*/

int run_test(char c, char key) 
{
   char e = encode(c, key);
   char d = decode(e, key);
   
   if (d != c)
   {
      printf("Test failed: encode(%c, %c) --> \"%c\", but decode(%c, %c) --> \"%c\" expected \"%c\"\n", c, key, e, e, key, d, c);
      return(1);
   }
   return(0);
}

/*
 * Run a series of test cases.
 * Report on failed tests.
 * Return the number of failed tests.
 */
int main()
{
   int failed_test_counter = 0;
   char c, k;
   printf("Testing encode-decode for every key / character combination\n");
   
   for (k=FIRST_ENCODABLE; k<=LAST_ENCODABLE; k++) {
      for (c=FIRST_ENCODABLE; c<=LAST_ENCODABLE; c++) {
         failed_test_counter+=run_test(c, k);
      }
   }

   if (failed_test_counter == 0) {
      printf("----- ALL TESTS PASSED -----\n");
   }
   return(failed_test_counter);
     
}
 