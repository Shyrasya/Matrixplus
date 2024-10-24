#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

//-------------Constructors-------------------

TEST(Costructors_tests, default_constructor) {
  S21Matrix def;
  EXPECT_EQ(3, def.acc_rows());
  EXPECT_EQ(3, def.acc_cols());
}

TEST(Costructors_tests, parametr_constructor) {
  S21Matrix param(4, 2);
  EXPECT_EQ(4, param.acc_rows());
  EXPECT_EQ(2, param.acc_cols());
}

TEST(Costructors_tests, parametr_constructor_not_exist) {
  EXPECT_THROW(S21Matrix param(-5, 3), std::invalid_argument);
}

TEST(Costructors_tests, copy_constructor) {
  S21Matrix a(2, 2);
  a.sequent_filling(1, 2);
  S21Matrix b(a);
  ASSERT_TRUE(a == b);
}

TEST(Costructors_tests, move_constructor) {
  S21Matrix a(3, 2);
  a.sequent_filling(1, 2);
  S21Matrix b(std::move(a));
  EXPECT_EQ(a.acc_rows(), 0);
  EXPECT_EQ(a.acc_cols(), 0);
}

//-------------Mutator-------------------

TEST(Mutator_tests, mutator_minus) {
  S21Matrix a;
  a.sequent_filling(1, 1);
  a.mutator(2, 2);
  S21Matrix b(2, 2);
  b(0, 0) = 1;
  b(0, 1) = 2;

  b(1, 0) = 4;
  b(1, 1) = 5;
  ASSERT_TRUE(a == b);
}

TEST(Mutator_tests, mutator_plus) {
  S21Matrix a(1, 1);
  a(0, 0) = 5;
  a.mutator(2, 2);
  S21Matrix b(2, 2);
  b(0, 0) = 5;
  b(0, 1) = 0;

  b(1, 0) = 0;
  b(1, 1) = 0;
  ASSERT_TRUE(a == b);
}

TEST(Mutator_tests, mutator_not_exist) {
  S21Matrix a;
  EXPECT_THROW(a.mutator(-5, 2), std::invalid_argument);
}

//-------------Operations-------------------

//-------------EqMatrix---------------------

TEST(Operations_tests, EqMatrix_not_same_size) {
  S21Matrix a(4, 4);
  S21Matrix b(2, 2);
  EXPECT_THROW(a == b, std::invalid_argument);
}

TEST(Operations_tests, EqMatrix_same_sizes_null) {
  S21Matrix a(4, 2);
  S21Matrix b(4, 2);
  ASSERT_TRUE(a == b);
}

TEST(Operations_tests, EqMatrix_same_sizes) {
  S21Matrix a(3, 5);
  S21Matrix b(3, 5);
  a.sequent_filling(1, 5);
  b.sequent_filling(1, 5);
  ASSERT_TRUE(a == b);
}

TEST(Operations_tests, EqMatrix_same_sizes_dif_inside) {
  S21Matrix a(3, 5);
  S21Matrix b(3, 5);
  a.sequent_filling(2, 3);
  b.sequent_filling(5, 3);
  ASSERT_FALSE(a == b);
}

TEST(Operations_tests, EqMatrix_same_sizes_small_inside) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a.sequent_filling(1.555556, 1);
  b.sequent_filling(1.555555, 1);
  ASSERT_FALSE(a == b);
}

//-------------SumMatrix-------------------

TEST(Operations_tests, SumMatrix_equal) {
  S21Matrix a(2, 4);
  S21Matrix b(2, 4);
  S21Matrix c(2, 4);
  a.sequent_filling(2, 1);
  b.sequent_filling(3, 1);
  a.SumMatrix(b);
  c.sequent_filling(5, 2);
  ASSERT_TRUE(a == c);
}

TEST(Operations_tests, SumMatrix_not_same_size) {
  S21Matrix a(2, 4);
  S21Matrix b(3, 4);
  EXPECT_THROW(a.SumMatrix(b), std::invalid_argument);
}

//-------------SubMatrix-------------------

TEST(Operations_tests, SubMatrix_equal) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  a.sequent_filling(3, 1);
  b.sequent_filling(2, 1);
  a.SubMatrix(b);
  c(0, 0) = 1;
  c(0, 1) = 1;

  c(1, 0) = 1;
  c(1, 1) = 1;
  ASSERT_TRUE(a == c);
}

TEST(Operations_tests, SubMatrix_not_same_size) {
  S21Matrix a(2, 4);
  S21Matrix b(3, 4);
  EXPECT_THROW(a.SumMatrix(b), std::invalid_argument);
}

//-------------MulNumber-------------------

TEST(Operations_tests, MulNumber_equal) {
  S21Matrix a(2, 4);
  S21Matrix b(2, 4);
  double number = 2;
  a.sequent_filling(2, 1);
  b.sequent_filling(4, 2);
  a.MulNumber(number);
  ASSERT_TRUE(a == b);
}

//-------------MulMatrix-------------------

TEST(Operations_tests, MulMatrix_equal) {
  S21Matrix a(2, 4);
  S21Matrix b(4, 2);
  S21Matrix c(2, 2);
  a.sequent_filling(2, 1);
  b.sequent_filling(2, 1);
  c(0, 0) = 80;
  c(0, 1) = 94;

  c(1, 0) = 160;
  c(1, 1) = 190;
  a.MulMatrix(b);
  ASSERT_TRUE(a == c);
}

TEST(Operations_tests, MulMatrix_invalid_argum) {
  S21Matrix a(2, 4);
  S21Matrix b(3, 2);
  EXPECT_THROW(a.MulMatrix(b), std::invalid_argument);
}

//-------------Transpose-------------------

TEST(Operations_tests, Transpose_equal) {
  S21Matrix a(2, 4);
  S21Matrix c(4, 2);
  a.sequent_filling(2, 1);
  c(0, 0) = 2;
  c(0, 1) = 6;

  c(1, 0) = 3;
  c(1, 1) = 7;

  c(2, 0) = 4;
  c(2, 1) = 8;

  c(3, 0) = 5;
  c(3, 1) = 9;
  S21Matrix trans = a.Transpose();
  ASSERT_TRUE(trans == c);
}

//-------------Determinant-------------------

TEST(Operations_tests, Determinant_without_0elem_0det) {
  S21Matrix a;
  double res = 0, check = 0;
  a.sequent_filling(1, 1);
  res = a.Determinant();
  EXPECT_EQ(res, check);
}

TEST(Operations_tests, Determinant_no_change_rows_0det) {
  S21Matrix c;
  double res = 0, check = 0;
  c(0, 1) = 1;
  c(0, 2) = 2;
  c(1, 1) = 3;

  c(1, 2) = 4;
  c(2, 1) = 5;
  c(2, 2) = 6;
  res = c.Determinant();
  EXPECT_EQ(res, check);
}

TEST(Operations_tests, Determinant_0in_diag_change_rows) {
  S21Matrix c;
  double res = 0, check = -32;
  c(0, 0) = 2;
  c(0, 1) = 4;
  c(0, 2) = 6;

  c(1, 0) = 7;
  c(1, 1) = 0;
  c(1, 2) = 9;

  c(2, 0) = 0;
  c(2, 1) = 1;
  c(2, 2) = 2;
  res = c.Determinant();
  EXPECT_EQ(res, check);
}

TEST(Operations_tests, Determinant_matrix_2on2) {
  S21Matrix c(2, 2);
  double res = 0, check = -18;
  c(0, 0) = 2;
  c(0, 1) = 4;

  c(1, 0) = 7;
  c(1, 1) = 5;
  res = c.Determinant();
  EXPECT_EQ(res, check);
}

TEST(Operations_tests, Determinant_matrix_1on1) {
  S21Matrix c(1, 1);
  double res = 0, check = 1;
  c(0, 0) = 1;

  res = c.Determinant();
  EXPECT_EQ(res, check);
}

TEST(Operations_tests, Determinant_matrix_not_square) {
  S21Matrix c(2, 3);
  EXPECT_THROW(c.Determinant(), std::invalid_argument);
}

TEST(Operations_tests, Determinant_change_rows_0in_diag) {
  S21Matrix c;
  double res = 0, check = 130;
  c(0, 0) = 0;
  c(0, 1) = 4;
  c(0, 2) = 6;

  c(1, 0) = 7;
  c(1, 1) = 0;
  c(1, 2) = 9;

  c(2, 0) = 4;
  c(2, 1) = 1;
  c(2, 2) = 2;
  res = c.Determinant();
  EXPECT_EQ(res, check);
}

TEST(Operations_tests, Determinant_cannot_change_rows_det0) {
  S21Matrix c;
  double res = 0, check = 0;
  c(0, 0) = 1;
  c(0, 1) = 4;
  c(0, 2) = 3;

  c(1, 0) = 0;
  c(1, 1) = 0;
  c(1, 2) = 3;

  c(2, 0) = 0;
  c(2, 1) = 0;
  c(2, 2) = 2;
  res = c.Determinant();
  EXPECT_EQ(res, check);
}

//-------------CalcComplements-------------------

TEST(Operations_tests, CalcComplements_matrix_2on2) {
  S21Matrix c(2, 2);
  S21Matrix check(2, 2);
  c(0, 0) = 1;
  c(0, 1) = 2;

  c(1, 0) = 3;
  c(1, 1) = 4;

  check(0, 0) = 4;
  check(0, 1) = -3;

  check(1, 0) = -2;
  check(1, 1) = 1;

  S21Matrix res = c.CalcComplements();
  ASSERT_TRUE(res == check);
}

TEST(Operations_tests, CalcComplements_matrix_3on3) {
  S21Matrix c;
  S21Matrix check;
  c(0, 0) = 1;
  c(0, 1) = 2;
  c(0, 2) = 3;

  c(1, 0) = 4;
  c(1, 1) = 5;
  c(1, 2) = 6;

  c(2, 0) = 7;
  c(2, 1) = 8;
  c(2, 2) = 9;

  check(0, 0) = -3;
  check(0, 1) = 6;
  check(0, 2) = -3;

  check(1, 0) = 6;
  check(1, 1) = -12;
  check(1, 2) = 6;

  check(2, 0) = -3;
  check(2, 1) = 6;
  check(2, 2) = -3;

  S21Matrix res = c.CalcComplements();
  ASSERT_TRUE(res == check);
}

TEST(Operations_tests, CalcComplements_matrix_1on1) {
  S21Matrix c(1, 1);
  S21Matrix check(1, 1);
  c(0, 0) = 5;
  check(0, 0) = 1;

  S21Matrix res = c.CalcComplements();
  ASSERT_TRUE(res == check);
}

TEST(Operations_tests, CalcComplements_matrix_not_square) {
  S21Matrix c(1, 2);
  EXPECT_THROW(c.CalcComplements(), std::invalid_argument);
}

//-------------InverseMatrix-------------------

TEST(Operations_tests, InverseMatrix_matrix_3on3) {
  S21Matrix c;
  S21Matrix check;
  c(0, 0) = 2;
  c(0, 1) = 5;
  c(0, 2) = 7;

  c(1, 0) = 6;
  c(1, 1) = 3;
  c(1, 2) = 4;

  c(2, 0) = 5;
  c(2, 1) = -2;
  c(2, 2) = -3;

  check(0, 0) = 1;
  check(0, 1) = -1;
  check(0, 2) = 1;

  check(1, 0) = -38;
  check(1, 1) = 41;
  check(1, 2) = -34;

  check(2, 0) = 27;
  check(2, 1) = -29;
  check(2, 2) = 24;

  S21Matrix res = c.InverseMatrix();
  ASSERT_TRUE(res == check);
}

TEST(Operations_tests, InverseMatrix_matrix_2on2) {
  S21Matrix c(2, 2);
  S21Matrix check(2, 2);
  c(0, 0) = 5;
  c(0, 1) = 4;

  c(1, 0) = 3;
  c(1, 1) = 2;

  check(0, 0) = -1;
  check(0, 1) = 2;

  check(1, 0) = 1.5;
  check(1, 1) = -2.5;

  S21Matrix res = c.InverseMatrix();
  ASSERT_TRUE(res == check);
}

TEST(Operations_tests, InverseMatrix_null_determinant) {
  S21Matrix c;
  c(0, 0) = 1;
  c(0, 1) = 4;
  c(0, 2) = 3;

  c(1, 0) = 0;
  c(1, 1) = 0;
  c(1, 2) = 3;

  c(2, 0) = 0;
  c(2, 1) = 0;
  c(2, 2) = 2;
  EXPECT_THROW(c.InverseMatrix(), std::invalid_argument);
}

TEST(Operations_tests, InverseMatrix_not_square_matrix) {
  S21Matrix c(1, 2);
  c(0, 0) = 5;
  c(0, 1) = 4;

  EXPECT_THROW(c.InverseMatrix(), std::invalid_argument);
}

TEST(Operations_tests, InverseMatrix_matrix_1on1) {
  S21Matrix c(1, 1);
  S21Matrix check(1, 1);
  c(0, 0) = 5;
  check(0, 0) = 0.2;

  S21Matrix res = c.InverseMatrix();
  ASSERT_TRUE(res == check);
}

//-------------Overloads-------------------

TEST(Overloads_tests, operator_assign) {
  S21Matrix c;
  c(0, 0) = 1;
  c(0, 1) = 4;
  c(0, 2) = 3;

  c(1, 0) = 0;
  c(1, 1) = 0;
  c(1, 2) = 3;

  c(2, 0) = 0;
  c(2, 1) = 0;
  c(2, 2) = 2;
  S21Matrix check;
  check = c;

  ASSERT_TRUE(c == check);
}

TEST(Overloads_tests, operator_equal) {
  S21Matrix c(2, 2);
  c(0, 0) = 1;
  c(0, 1) = 4;

  c(1, 0) = 3;
  c(1, 1) = 0;

  S21Matrix check(2, 2);
  check(0, 0) = 1;
  check(0, 1) = 4;

  check(1, 0) = 3;
  check(1, 1) = 0;

  EXPECT_EQ(c == check, 1);
}

TEST(Overloads_tests, operator_sum) {
  S21Matrix c(2, 2);
  c(0, 0) = 1;
  c(0, 1) = 4;

  c(1, 0) = 3;
  c(1, 1) = 0;

  S21Matrix check(2, 2);
  check(0, 0) = 1;
  check(0, 1) = 1;

  check(1, 0) = 1;
  check(1, 1) = 1;

  S21Matrix sum(2, 2);
  sum = c + check;

  S21Matrix res(2, 2);
  res(0, 0) = 2;
  res(0, 1) = 5;

  res(1, 0) = 4;
  res(1, 1) = 1;

  ASSERT_TRUE(sum == res);
}

TEST(Overloads_tests, operator_sub) {
  S21Matrix c(2, 2);
  c(0, 0) = 1;
  c(0, 1) = 4;

  c(1, 0) = 3;
  c(1, 1) = 0;

  S21Matrix check(2, 2);
  check(0, 0) = 1;
  check(0, 1) = 1;

  check(1, 0) = 1;
  check(1, 1) = 1;

  S21Matrix sum(2, 2);
  sum = c - check;

  S21Matrix res(2, 2);
  res(0, 0) = 0;
  res(0, 1) = 3;

  res(1, 0) = 2;
  res(1, 1) = -1;

  ASSERT_TRUE(sum == res);
}

TEST(Overloads_tests, operator_mult_numb_num_second) {
  S21Matrix c(2, 2);
  double num = 5;
  c(0, 0) = 1;
  c(0, 1) = 4;

  c(1, 0) = 3;
  c(1, 1) = 0;

  S21Matrix check(2, 2);
  check = c * num;

  S21Matrix res(2, 2);
  res(0, 0) = 5;
  res(0, 1) = 20;

  res(1, 0) = 15;
  res(1, 1) = 0;

  ASSERT_TRUE(check == res);
}

TEST(Overloads_tests, operator_mult_numb_num_first) {
  S21Matrix c(2, 2);
  double num = 5;
  c(0, 0) = 1;
  c(0, 1) = 4;

  c(1, 0) = 3;
  c(1, 1) = 0;

  S21Matrix check(2, 2);
  check = num * c;

  S21Matrix res(2, 2);
  res(0, 0) = 5;
  res(0, 1) = 20;

  res(1, 0) = 15;
  res(1, 1) = 0;

  ASSERT_TRUE(check == res);
}

TEST(Overloads_tests, operator_mult_matrix) {
  S21Matrix a(3, 1);
  a(0, 0) = 1;
  a(1, 0) = 3;
  a(2, 0) = 5;

  S21Matrix c(1, 3);
  c(0, 0) = 5;
  c(0, 1) = 4;
  c(0, 2) = 3;

  S21Matrix res;
  res = a * c;

  S21Matrix check;
  check(0, 0) = 5;
  check(0, 1) = 4;
  check(0, 2) = 3;

  check(1, 0) = 15;
  check(1, 1) = 12;
  check(1, 2) = 9;

  check(2, 0) = 25;
  check(2, 1) = 20;
  check(2, 2) = 15;

  ASSERT_TRUE(res == check);
}

TEST(Overloads_tests, operator_sum_assign) {
  S21Matrix c(2, 2);
  c(0, 0) = 1;
  c(0, 1) = 4;

  c(1, 0) = 3;
  c(1, 1) = 0;

  S21Matrix check(2, 2);
  check(0, 0) = 1;
  check(0, 1) = 1;

  check(1, 0) = 1;
  check(1, 1) = 1;

  c += check;

  S21Matrix res(2, 2);
  res(0, 0) = 2;
  res(0, 1) = 5;

  res(1, 0) = 4;
  res(1, 1) = 1;

  ASSERT_TRUE(c == res);
}

TEST(Overloads_tests, operator_sub_assign) {
  S21Matrix c(2, 2);
  c(0, 0) = 1;
  c(0, 1) = 4;

  c(1, 0) = 3;
  c(1, 1) = 0;

  S21Matrix check(2, 2);
  check(0, 0) = 1;
  check(0, 1) = 1;

  check(1, 0) = 1;
  check(1, 1) = 1;

  c -= check;

  S21Matrix res(2, 2);
  res(0, 0) = 0;
  res(0, 1) = 3;

  res(1, 0) = 2;
  res(1, 1) = -1;

  ASSERT_TRUE(c == res);
}

TEST(Overloads_tests, operator_mult_assign_num_second) {
  S21Matrix c(2, 2);
  double num = 5;
  c(0, 0) = 1;
  c(0, 1) = 4;

  c(1, 0) = 3;
  c(1, 1) = 0;

  c *= num;

  S21Matrix res(2, 2);
  res(0, 0) = 5;
  res(0, 1) = 20;

  res(1, 0) = 15;
  res(1, 1) = 0;

  ASSERT_TRUE(c == res);
}

TEST(Overloads_tests, operator_mult_assign_matrix_second) {
  S21Matrix a(3, 1);
  a(0, 0) = 1;
  a(1, 0) = 3;
  a(2, 0) = 5;

  S21Matrix c(1, 3);
  c(0, 0) = 5;
  c(0, 1) = 4;
  c(0, 2) = 3;

  a *= c;

  S21Matrix check;
  check(0, 0) = 5;
  check(0, 1) = 4;
  check(0, 2) = 3;

  check(1, 0) = 15;
  check(1, 1) = 12;
  check(1, 2) = 9;

  check(2, 0) = 25;
  check(2, 1) = 20;
  check(2, 2) = 15;

  ASSERT_TRUE(a == check);
}

TEST(Overloads_tests, operator_index) {
  S21Matrix a(2, 1);
  a(0, 0) = 1;
  a(1, 0) = 3;

  EXPECT_EQ(a(0, 0), 1);
  EXPECT_EQ(a(1, 0), 3);
}

TEST(Overloads_tests, operator_index_not_range) {
  S21Matrix a(2, 1);

  EXPECT_THROW(a(-1, 0), std::out_of_range);
}

//-------------main-------------------

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
