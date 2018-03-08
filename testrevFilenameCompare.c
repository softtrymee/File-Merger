/*
 * Filename: testrevFilenameCompare.c
 * Author: Shengkai He
 * Userid: cs30xcy
 * Description: Unit test program to test the assembly function revFilenameCompare.
 * Date: Feb 7 2017
 * Sources of Help: none
 */ 

#include <string.h>

#include "test.h"
#include "pa4.h"


/*
 * Unit Test for revFilenameCompare.s
 *
 * 
 * int revFilenameCompare( const void * p1, const void * p2 )
 * 
 * Compares two file names passed in for sorting purposes. 
 * Returns 0 if the file names are the same, +1 if the first name
 * is smaller, or -1 if the first name is larger.
 */

void testrevFilenameCompare() {
  printf( "Testing filenameCompare()\n" );

  struct fileInfo f1; 
  struct fileInfo f2; 
  
  f1.filename = "helloWorld";
  f2.filename = "jelloWorld";
  TEST( revFilenameCompare( &f1, &f2 ) == 1 );
  
  
  f1.filename = "zebra";
  f2.filename = "abstract";
  TEST( revFilenameCompare( &f1, &f2 ) == -1);

  f1.filename = "equal";
  f2.filename = "equal";
  TEST( revFilenameCompare( &f1, &f2) == 0);


  printf( "Finished running tests on revFilenameCompare()\n" );
}


int main() {
  testrevFilenameCompare();

  return 0;
}
