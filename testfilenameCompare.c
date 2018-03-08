/*
 * Filename: testfilenameCompare.c
 * Author: Shengkai He
 * Userid: cs30xcy
 * Description: Unit test program to test the assembly function filenameCompare.
 * Date: Feb 7 2017
 * Sources of Help: none
 */ 

#include <string.h>

#include "test.h"
#include "pa4.h"


/*
 * Unit Test for filenameCompare.s
 *
 * 
 * int filenameCompare( const void * p1, const void * p2 )
 * 
 * Compares two file names passed in for sorting purposes. 
 * Returns 0 if the file names are the same, -1 if the first name
 * is smaller, or +1 if the first name is larger.
 */

void testfilenameCompare() {
  printf( "Testing filenameCompare()\n" );

  struct fileInfo f1; 
  struct fileInfo f2; 
  
  f1.filename = "helloWorld";
  f2.filename = "jelloWorld";
  TEST( filenameCompare( &f1, &f2 ) == -1 );
  
  
  f1.filename = "zebra";
  f2.filename = "abstract";
  TEST( filenameCompare( &f1, &f2 ) == 1);

  f1.filename = "equal";
  f2.filename = "equal";
  TEST( filenameCompare( &f1, &f2) == 0);


  printf( "Finished running tests on filenameCompare()\n" );
}


int main() {
  testfilenameCompare();

  return 0;
}
