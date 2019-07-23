/*
*Problem Statement: 
*this will create a command dispatcher for assignment 2
*
*Author: Tim Wriglesworth
*Date: 17.02.17
*Comp 120. Capilano University
Assignment 3

*/


#include <stdlib.h>
#include <stdio.h>
#include "encrypt.h"


void help();                  //protype functions
void check();
void encrypt(char*, char*);
void decipher(char* , char* );

int main (int argc, char* argv[])  //this works..but could lead to SEG fault on another maschine... FIX this TW
{
 
 if (argc < 2 || argc >4 )    //check arguement count
	   {
         check();		
		 help('h');   
         exit(-1);
        }
	
char* input = argv[1];       //get user input.
 char i =input[1];           //get 2nd place in array

int length = 0;
if (argc > 2) {
	length = atoi(argv[2]);   //gather  user input of length
}

char* filenames1 = argv[2];	
char* filenames2 = argv[3]; 
printf("%s\n", argv[3]);
char displayOption;             //intialize variables ie switch parameter
 
 
 if (i=='h')         //logic of program dispatcher.
                    //checks each parameter and triggers corresponding switch
  {
	help();
  }	
	else if (i =='k')
	{
		 displayOption = 'A';
	}
	  else if (i=='f')
	  {
		 displayOption= 'B';
	  }
	   else if (i=='e')
	   {
		   displayOption='C';
	   }
	   else if(i=='d')
	   {
		   displayOption='D';
	   }
	   else
	   {
      check();		   
	  help();
	   }	
	
	switch(displayOption)  	         //used to print messages
	{
	
	 case 'A':                       //-k
	 if(length <= 0)              //need to check input follows parameter rules
	 {
      check();
	  help();                     //call function if false is returned from if statement. ie error handling
	 }
	 else
	 { 
	 print_key(length);
	 }
	 break;
	
	
	case 'B':                                   //-f     
	
	 frequency_histogram(filenames1);             //call to functions that appropiate the utilization of histogram
	break;
	
	case 'C':                                    //-e
	//printf("Encrypting the cleartxt file: %s with given keyfile: %s....\n ",filenames1,filenames2);
	encrypt(filenames1,filenames2);
	

	break;
	
	
	case 'D':                                                // -d
	//printf("Decipher ciphertext: %s filename with given keyfile: %s.",filenames1,filenames2);
	decipher(filenames1,filenames2);
	break;
	 }	

return 0;
}
	   
	void help()                //prints the help menu 	
{  
	
	{	

       printf("Options:\n");
                printf("-h                      Print this help manual.\n");
                printf("-k <length>             Generate encryption key of given length (length > 0).\n");
                printf("-f <filename>           Generate frequency histogram for filename.\n");
                printf("-e <filename> <keyfile> Encrypt cleartxt in filename with given keyfile.\n");
                printf("-d <filename> <keyfile> Decipher ciphertext filename with given keyfile.\n");
	}
	
}

void check()              //prints usage settings 
{

	     printf("Usage:   encrypt -k 123\n");
         printf("or:   encrypt -f textfile.txt\n");
         printf("or:   encrypt -e/d textfile.txt keyfile.txt\n\n");
}
