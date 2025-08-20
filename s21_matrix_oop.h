#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <stdexcept>

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;
  void CheckValidMatrix(const S21Matrix &other) const;
  void CheckValidOperator() const;
  void CheckValidDimensions(const S21Matrix &other) const;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(const double num) const;
  S21Matrix operator*(const S21Matrix &other) const;
  bool operator==(const S21Matrix &other) const;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);
  S21Matrix &operator*=(const S21Matrix &other);
  double &operator()(int i, int j) const;
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;

  void SetRows(int new_rows);
  void SetCols(int new_cols);
  int GetRows() const;
  int GetCols() const;

  void setMatrix(double **values, int rows, int cols);
  double **getMatrix() const;
  S21Matrix GetMinor(int excluded_row, int excluded_col) const;
  void SimpleArithmetic(const S21Matrix &other, short sign);
};
#endif