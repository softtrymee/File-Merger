/*
 * Filename: testsortFiles.c
 * Author: Shengkai He
 * Userid: cs30xcy
 * Description: Unit test program to test the function sortFiles().
 * Date: Mar 8 2017
 * Sources of Help: none
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#include "pa4.h"       /* For sortFiles() function prototype */
#include "test.h"      /* For TEST() macro and stdio.h */

#define SYSRUN(CMD) (system(CMD))

static void runTest( int numFiles, char * filenames[], unsigned int flags, 
                     char * expectedOrder[],
                     int expectedNull, char * expectedErr, char * testDesc );

static char * testFileName = ".test_sortFiles_student_file";
static FILE * testFilePtr;


/*
 * Unit Test for sortFiles.c
 * 
 * FILE ** sortFiles( int numFIles, char * filenames[], unsigned int flags );
 *
 * Sorts the files specified by the filenames based on the sort comparison
 * specified by the flags. Then opens the files for reading and returns their
 * file pointers.
 */
static void testsortFiles() {
  int numFiles;
  int expectedNull;
  unsigned int flags;


  /* Test 1 */
  (void) fprintf( stderr, "\nRUNNING TEST 1!\n" );
  numFiles = 1;
  char * filenames1[] = { "badfile" };
  flags = 0;
  char * expectedOrder1[] = { "badfile" };
  expectedNull = 1;
  char * expectedErr1 = "badfile: No such file or directory\n";

  runTest( numFiles, filenames1, flags, expectedOrder1, expectedNull, 
           expectedErr1, "Test 1, file does not exist" );

  
  /* Test 2 */
  /* TODO create the file needed for this test */
  (void) fprintf( stderr, "\nRUNNING TEST 2!\n" );
  numFiles = 1;
  char * filenames2[] = { "restrictedFile" };
  flags = 0;
  char * expectedOrder2[] = { "restrictedFile" };
  expectedNull = 1;
  char * expectedErr2 = "restrictedFile: Permission denied\n";

  runTest( numFiles, filenames2, flags, expectedOrder2, expectedNull, 
           expectedErr2, "Test 2, do not have permission to open file" );
  
  
  /* TODO: YOU MUST WRITE MORE TEST CASES FOR FULL POINTS! */
  /* Test 3 */
  (void) fprintf(stderr, "\nRUNNING TEST 3!\n");
  numFiles = 3;
  char * filenames3[] = {"orange", "apple", "banana" };
  flags = 0;
  char * expectedOrder3[] = {"apple", "banana", "orange"};
  expectedNull = 0;
  char expectedErr3[BUFSIZ] = {0};
  
  runTest(numFiles, filenames3, flags, expectedOrder3, expectedNull,
          expectedErr3, "Test 3, should be ok");

  
  /* Test 4 */
  (void) fprintf(stderr, "\nRUNNING TEST 4!\n");
  numFiles = 3;
  char * filenames4[] = {"orange", "banana", "apple"};
  flags = 0x40;
  char * expectedOrder4[] = {"apple", "banana", "orange"};
  expectedNull = 0;
  char expectedErr4[BUFSIZ] = {0};

  runTest(numFiles, filenames4, flags, expectedOrder4, expectedNull,
          expectedErr4, "Test 4, sort from old to new");

  
  /* Test 5 */
  (void) fprintf(stderr, "\nRUNNING TEST 5!\n");
  numFiles = 3;
  char * filenames5[] = {"apple", "banana", "orange"};
  flags = 0x50;
  char * expectedOrder5[] = {"orange", "banana", "apple"};
  expectedNull = 0;
  char expectedErr5[BUFSIZ] = {0};
           
  runTest(numFiles, filenames5, flags, expectedOrder5, expectedNull,
          expectedErr5, "Test 5, sort from new to old");

  /* Test 6 */
  (void) fprintf(stderr, "\nRUNNING TEST 6!\n");
  numFiles = 3;
  char * filenames6[] = {"banana", "orange", "apple"};
  flags = 0x10;
  char * expectedOrder6[] = {"orange", "banana", "apple"};
  expectedNull = 0;
  char expectedErr6[BUFSIZ] = {0};
          
  runTest(numFiles, filenames6, flags, expectedOrder6, expectedNull,
          expectedErr6, "Test 4, reverse filename sort");
}


/*
 * Function Name: runTest()
 * Function Prototype: void runTest( unsigned int bank[], char * expectedOutput,
                                     char * testDesc );
 * Description:  Helper function to actually run a test of displayLights.
 *               Prints test description (as specified by testDesc), and
 *               calls displayLights, handling segfaults.
 * Parameters:
 *     arg1: unsigned int bank[] -- bank of lights
 *     arg2: char * expectedOutput -- the expected output to be printed by
 *                                    displayLights()
 *     arg3: char * testDesc -- Description of the test being run
 * Side Effects: Outputs the result of the test to stderr
 * Error Conditions: None
 * Return Value: None
 */
static void runTest( int numFiles, char * filenames[], unsigned int flags, 
              char * expectedOrder[],
              int expectedNull, char * expectedErr, char * testDesc ){
  /* 
   * Begin setup to capture stderr to a file.  You aren't expected to know how
   * to do this, but it never hurts to learn!
   */
  testFilePtr = fopen( testFileName, "w+" );
  int saveErr = dup(fileno(stderr));
  if ( testFilePtr == NULL ) {
    perror( "Could not open test file" );
    exit( 1 );
  }

  if ( dup2( fileno( testFilePtr ), fileno( stderr ) ) == -1 ) {
    perror( "Could not duplicate stderr file descriptor" );
    exit( 1 );
  }
  /* End setup to capture stdout */

  /* buffer for comparing output */
  char buf[BUFSIZ] = {0};

  /* Print test description */
  (void) fprintf( stdout, "%s\n", testDesc );

  /* Sort the files and flush stderr */
  FILE ** sortedFiles = sortFiles(numFiles, filenames, flags);
  (void) fflush( stderr );

  /* Reset file pointer */
  (void) fseek( testFilePtr, 0, SEEK_SET );

  /* Read from test file and compare */
  (void) fgets( buf, BUFSIZ, testFilePtr );

  /* Close file when done and restore stderr*/
  (void) fclose( testFilePtr );
  if ( dup2( saveErr, fileno( stderr ) ) == -1 ) {
    perror( "Could not restore stderr file descriptor" );
    exit( 1 );
  }



  /* Real testing starts here */

  /* That any errors printed matched first */
  TEST( strncmp( buf, expectedErr, BUFSIZ ) == 0 );
  if( strncmp( buf, expectedErr, BUFSIZ ) != 0 ){
    (void) fprintf( stderr, "Expected output: %s\n", expectedErr );
    (void) fprintf( stderr, "Actual output: %s\n\n", buf );
  }

  /* check if an error was expected */
  if( expectedNull ){
    TEST( sortedFiles == NULL );

    /* TODO remove print statement below */
  }
  else{
    TEST( sortedFiles != NULL );
    
    int pass = 1;
    /* TODO check that your array of FILE *'s matches what you expected */
    FILE ** testedFile = sortFiles(numFiles, filenames, flags);
    for (int i = 0; i < numFiles; i++) {
      FILE * file = fopen(expectedOrder[i], "r");
      int des = fileno( file );  // get the descriptor of the first file
      // get the descriptor of the tested file
      int testedDes = fileno( testedFile[i] ); 

      struct stat  buf[BUFSIZ];
      struct stat testedBuf[BUFSIZ];

      (void)fstat(des, buf);
      (void)fstat(testedDes, testedBuf);
      if ((buf->st_ino != testedBuf->st_ino) ||
                  (buf->st_dev != testedBuf->st_dev)) {
        pass = 0;
      }

    }

    TEST (pass == 1);
    printf("\nyayyyyy! You did it!\n");
    /* TODO remove print statement below */
  
    free(testedFile);
  }
  
}


int main() {


  (void) fprintf( stderr, "Running tests for sortFiles...\n" );
  testsortFiles();
  (void) fprintf( stderr, "\nDone running tests!\n" );


  return 0;
}
