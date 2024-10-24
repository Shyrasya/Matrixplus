#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <cmath>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#define SCI_NOT 1e-7

enum code_type { OK, ERROR };  // OK - 0, ERROR - 1
enum code_check { NO, YES };   // NO - 0, YES - 1

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  // Accessors:
  int acc_rows();
  int acc_cols();

  // Mutator:
  void mutator(int rows, int cols);

  // Operations:
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  double Determinant();
  void TriangMatrix(double& result);
  bool FinfDiagNullElem(int g);
  S21Matrix CalcComplements();
  S21Matrix CreateMiniMatrix(int r, int c);
  S21Matrix InverseMatrix();

  // Overloads:
  S21Matrix operator=(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  friend S21Matrix operator*(const S21Matrix& other, double num);
  friend S21Matrix operator*(double num, const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(double num);
  S21Matrix& operator*=(const S21Matrix& other);
  double& operator()(int rows, int cols);

  // Additional Methods:
  void allocate_mem();
  void fill_matrix();
  void print_matrix();
  void sequent_filling(double fill_start, double step);
  void copy_matrix(const S21Matrix& old);
  void not_square();
  void not_exist();
  void not_same_size();
  void not_range();
  void not_equal();
  void null_determinant();
};

#endif