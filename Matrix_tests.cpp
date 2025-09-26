#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; r++){
    for(int c = 0; c < width; c++){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

//this test checks if the matrix is initialized properly with 0s
TEST(test_init) {
  Matrix mat;
  Matrix_init(&mat, 1, 2);
  
  int width = Matrix_width(&mat);
  int height = Matrix_height(&mat);

  ASSERT_EQUAL(Matrix_width(&mat), 1);
  ASSERT_EQUAL(Matrix_height(&mat), 2);

  for(int r = 0; r < height; r++){
    for(int c = 0; c < width; c++){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), 0);
    }
  }
}
//this test checks if the matrix fills the border with a value correctly
TEST(test_fill_border) {
  Matrix mat;
  Matrix_init(&mat, 5, 5);
  Matrix_fill_border(&mat, 7);

  int width = Matrix_width(&mat);
  int height = Matrix_height(&mat);

  for (int col = 0; col < width; ++col) {
    ASSERT_EQUAL(*Matrix_at(&mat, 0, col), 7);        
    ASSERT_EQUAL(*Matrix_at(&mat, height - 1, col), 7); 
  }

  for (int row = 0; row < height; ++row) {
    ASSERT_EQUAL(*Matrix_at(&mat, row, 0), 7);       
    ASSERT_EQUAL(*Matrix_at(&mat, row, width - 1), 7); 
  }
}

//this test checks if the max function returns the correct maximum value
TEST(test_max) {
  Matrix mat;
  Matrix_init(&mat, 2, 2);
  *Matrix_at(&mat, 0, 0) = -3;
  *Matrix_at(&mat, 0, 1) = 11;
  *Matrix_at(&mat, 1, 0) = 7;
  *Matrix_at(&mat, 1, 1) = 7;
  ASSERT_EQUAL(Matrix_max(&mat), 11);
}

//this test checks if the col of min value in row function returns the correct value
TEST(test_column_of_min_value_in_row) {
  Matrix mat;
  Matrix_init(&mat, 2, 2);
  *Matrix_at(&mat, 0, 0) = -3;
  *Matrix_at(&mat, 0, 1) = 11;
  *Matrix_at(&mat, 1, 0) = 7;
  *Matrix_at(&mat, 1, 1) = 7;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 0, 2), 0);
}
//this is an edge case for the col of min value in row function because of the tie
TEST(test_column_of_min_value_in_row2) {
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = 4;
  *Matrix_at(&mat, 0, 1) = 2;
  *Matrix_at(&mat, 0, 2) = 9;
  *Matrix_at(&mat, 0, 3) = 2; // should return left col 1
  *Matrix_at(&mat, 0, 4) = 5;

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 0, 5), 1);
}
//this test checks if the min value in row function returns the correct minimum value
TEST(test_min_value_in_row) {
  Matrix mat;
  Matrix_init(&mat, 4, 1);
  *Matrix_at(&mat, 0, 0) = 8;
  *Matrix_at(&mat, 0, 1) = 3;
  *Matrix_at(&mat, 0, 2) = 6;
  *Matrix_at(&mat, 0, 3) = 7;

  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 0, 4), 3);
}
//this test checks if the min value in row function returns the correct minimum value
TEST(test_min_value_in_row_negative) {
  Matrix mat;
  Matrix_init(&mat, 4, 1);
  *Matrix_at(&mat, 0, 0) = -1;
  *Matrix_at(&mat, 0, 1) = 3;
  *Matrix_at(&mat, 0, 2) = 6;
  *Matrix_at(&mat, 0, 3) = 7;

  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 0, 4), -1);
}

//this test checks if the const matrix at function returns the correct value
TEST(test_const_matrix_at) {
  Matrix mat;
  Matrix_init(&mat, 2, 2);
  *Matrix_at(&mat, 1, 1) = 12;

  const Matrix *cons = &mat;
  ASSERT_EQUAL(*Matrix_at(cons, 1, 1), 12);
}

//this test checks if the print function prints the matrix correctly
TEST(test_matrix_print) {
    Matrix mat;
    Matrix_init(&mat, 1, 1);
    *Matrix_at(&mat, 0, 0) = 42;
    ostringstream expected;
    expected << "1 1\n42 \n";
    ostringstream actual;
    Matrix_print(&mat, actual);
    ASSERT_EQUAL(expected.str(), actual.str());
}
//this test checks if the matrix is initialized properly (large))
TEST(test_init_large) {
  Matrix mat;
  Matrix_init(&mat, 100, 2000);
  
  int width = Matrix_width(&mat);
  int height = Matrix_height(&mat);

  ASSERT_EQUAL(Matrix_width(&mat), 100);
  ASSERT_EQUAL(Matrix_height(&mat), 2000);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), 0);
    }
  }
}
//this test checks if the max function returns the correct max value when all values are negative
TEST(test_max_all_negative) {
  Matrix mat;
  Matrix_init(&mat, 2, 2);
  *Matrix_at(&mat, 0, 0) = -5;
  *Matrix_at(&mat, 0, 1) = -3;
  *Matrix_at(&mat, 1, 0) = -7;
  *Matrix_at(&mat, 1, 1) = -10;
  ASSERT_EQUAL(Matrix_max(&mat), -3);
}


// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

TEST_MAIN() // Do NOT put a semicolon here
