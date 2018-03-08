/*
 * Filename: testrevTimeCompare.c
 * Author: Shengkai He
 * Userid: cs30xcy
 * Description: TODO
 * Date: Mar 07 2017
 * Sources of Help: NONE
 */


#include <stdlib.h>
#include <stdio.h>
#include "pa4.h"
#include "test.h"

/*
 * Unit test for revTimeCompare.s
 *
 * int revTimeCompare( const void * p1, const void * p2);
 *
 * sort the files based on the time created
 */

void testrevTimeCompare() {
  printf( "Testing revTimeCompare()\n");
  struct fileInfo f1;
  struct fileInfo f2;

  f1.filename = "file1";
  f2.filename = "file2";
  TEST( revTimeCompare(&f1, &f2) == 1);

  TEST( revTimeCompare(&f2, &f1) == -1);

  int t = f1.statInformation.st_mtime;
  f2.statInformation.st_mtime = t;
  TEST( revTimeCompare(&f1, &f2) == 0);

  printf( "Finished running tests on revTimeCompare()\n");
}

int main() {
  testrevTimeCompare();

  return 0;
}
