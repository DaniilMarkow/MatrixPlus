#include "../s21_matrix_oop.h"

TEST(Mutators, SetRowsNotInitialized) {
  S21Matrix test;
  EXPECT_THROW(test.SetRows(3), std::runtime_error);
}

TEST(Mutators, SetColsNotInitialized) {
  S21Matrix test;
  EXPECT_THROW(test.SetCols(3), std::runtime_error);
}

TEST(Mutators, SetColsAfterInvalidSetMatrix) {
  S21Matrix test;
  EXPECT_THROW(test.setMatrix(nullptr, 0, 0), std::invalid_argument);
}

TEST(Mutators, SetRowsLargeMatrix) {
  S21Matrix test(2, 2);
  test(0, 0) = 1.0;
  test.SetRows(3);
  EXPECT_DOUBLE_EQ(test(0, 0), 1.0);
  EXPECT_EQ(test.GetRows(), 3);
}
TEST(MatrixConstructor, InvalidRowsAndCols) {
  EXPECT_THROW({ S21Matrix m(0, 5); }, std::invalid_argument);

  EXPECT_THROW({ S21Matrix m(5, 0); }, std::invalid_argument);

  EXPECT_THROW({ S21Matrix m(0, 0); }, std::invalid_argument);

  EXPECT_THROW({ S21Matrix m(-1, 5); }, std::invalid_argument);

  EXPECT_THROW({ S21Matrix m(5, -3); }, std::invalid_argument);

  EXPECT_THROW({ S21Matrix m(-2, -2); }, std::invalid_argument);
}
TEST(Mutators, SetColsNegative) {
  S21Matrix test(2, 2);
  EXPECT_THROW(test.SetCols(-1), std::invalid_argument);
}

TEST(Mutators, SetRowsZero) {
  S21Matrix test(2, 2);
  EXPECT_THROW(test.SetRows(0), std::invalid_argument);
}

TEST(Operations, EqMatrixNotInitialized) {
  S21Matrix test;
  S21Matrix other(1, 1);
  EXPECT_THROW(test.EqMatrix(other), std::runtime_error);
}

TEST(Operations, SumMatrixNotInitialized) {
  S21Matrix test;
  S21Matrix other(1, 1);
  EXPECT_THROW(test.SumMatrix(other), std::runtime_error);
}

TEST(Operations, SubMatrixNotInitialized) {
  S21Matrix test;
  S21Matrix other(1, 1);
  EXPECT_THROW(test.SubMatrix(other), std::runtime_error);
}

TEST(Operations, MulNumberNotInitialized) {
  S21Matrix test;
  EXPECT_THROW(test.MulNumber(2.0), std::runtime_error);
}
TEST(Operations, MulNumberZeroIsInfinte) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  EXPECT_THROW(a.MulNumber(std::numeric_limits<double>::infinity()),
               std::invalid_argument);
}
TEST(Operations, MulNumberNaNThrows) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  const double nan_value = NAN;
  EXPECT_THROW(a.MulNumber(nan_value), std::invalid_argument);

  EXPECT_THROW(a.MulNumber(std::numeric_limits<double>::quiet_NaN()),
               std::invalid_argument);
}
TEST(Operations, MulMatrixNotInitialized) {
  S21Matrix test;
  S21Matrix other(1, 1);
  EXPECT_THROW(test.MulMatrix(other), std::runtime_error);
}

TEST(Operations, TransposeNotInitialized) {
  S21Matrix test;
  EXPECT_THROW(test.Transpose(), std::runtime_error);
}

TEST(Operations, CalcComplementsNotInitialized) {
  S21Matrix test;
  EXPECT_THROW(test.CalcComplements(), std::runtime_error);
}

TEST(Operations, DeterminantNotInitialized) {
  S21Matrix test;
  EXPECT_THROW(test.Determinant(), std::runtime_error);
}

TEST(Operations, InverseMatrixNotInitialized) {
  S21Matrix test;
  EXPECT_THROW(test.InverseMatrix(), std::runtime_error);
}

TEST(Operations, EqMatrixDifferentDimensions) {
  S21Matrix a(2, 2);
  S21Matrix b(1, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  b(0, 0) = 1.0;
  b(0, 1) = 2.0;
  EXPECT_FALSE(a.EqMatrix(b));
}
TEST(Operations, SubMatrixDifferentDimensions) {
  S21Matrix a(2, 2);
  S21Matrix b(1, 2);
  EXPECT_THROW(a.SubMatrix(b), std::invalid_argument);
}

TEST(Operations, MulMatrixInvalidDimensions) {
  S21Matrix a(2, 1);
  S21Matrix b(2, 1);
  EXPECT_THROW(a.MulMatrix(b), std::invalid_argument);
}
TEST(Operators, PlusDifferentDimensions) {
  S21Matrix a(2, 3);
  S21Matrix b(3, 2);
  EXPECT_THROW(a + b, std::invalid_argument);
}
TEST(Operations, CalcComplementsNonSquare) {
  S21Matrix a(2, 3);
  EXPECT_THROW(a.CalcComplements(), std::invalid_argument);
}

TEST(Operations, DeterminantNonSquare) {
  S21Matrix a(2, 3);
  EXPECT_THROW(a.Determinant(), std::invalid_argument);
}

TEST(Operations, InverseMatrixSingular) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 2.0;
  a(1, 1) = 4.0;
  EXPECT_THROW(a.InverseMatrix(), std::runtime_error);
}

TEST(Operations, OperatorParenthesisOutOfBounds) {
  S21Matrix a(2, 2);
  EXPECT_THROW(a(-1, 0), std::out_of_range);
  EXPECT_THROW(a(2, 0), std::out_of_range);
  EXPECT_THROW(a(0, -1), std::out_of_range);
  EXPECT_THROW(a(0, 2), std::out_of_range);
}

TEST(Operations, OperatorParenthesisNotInitialized) {
  S21Matrix a;
  EXPECT_THROW(a(0, 0), std::runtime_error);
}

TEST(Operations, OperatorAddAssignNotInitialized) {
  S21Matrix a;
  S21Matrix b(1, 1);
  EXPECT_THROW(a += b, std::runtime_error);
}

TEST(Operations, OperatorSubAssignNotInitialized) {
  S21Matrix a;
  S21Matrix b(1, 1);
  EXPECT_THROW(a -= b, std::runtime_error);
}

TEST(Operations, OperatorMulAssignNotInitialized) {
  S21Matrix a;
  S21Matrix b(1, 1);
  EXPECT_THROW(a *= b, std::runtime_error);
}

TEST(Operations, OperatorMulAssignNumberNotInitialized) {
  S21Matrix a;
  EXPECT_THROW(a *= 2.0, std::runtime_error);
}

TEST(Operations, MulMatrixNormal) {
  S21Matrix a(2, 3);
  S21Matrix b(3, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(0, 2) = 3.0;
  a(1, 0) = 4.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.0;
  b(0, 0) = 1.0;
  b(0, 1) = 2.0;
  b(1, 0) = 3.0;
  b(1, 1) = 4.0;
  b(2, 0) = 5.0;
  b(2, 1) = 6.0;
  S21Matrix result = a * b;
  EXPECT_DOUBLE_EQ(result(0, 0), 22.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 28.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 49.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 64.0);
}

TEST(Operations, TransposeNormal) {
  S21Matrix a(2, 3);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(0, 2) = 3.0;
  a(1, 0) = 4.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.0;
  S21Matrix result = a.Transpose();
  EXPECT_EQ(result.GetRows(), 3);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(result(2, 0), 3.0);
  EXPECT_DOUBLE_EQ(result(2, 1), 6.0);
}

TEST(Operations, CalcComplementsNormal) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  S21Matrix result = a.CalcComplements();
  EXPECT_DOUBLE_EQ(result(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(result(0, 1), -3.0);
  EXPECT_DOUBLE_EQ(result(1, 0), -2.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 1.0);
}

TEST(Operations, DeterminantNormal) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  EXPECT_DOUBLE_EQ(a.Determinant(), -2.0);
}

TEST(Operations, InverseMatrixNormal) {
  S21Matrix a(2, 2);
  a(0, 0) = 4.0;
  a(0, 1) = 7.0;
  a(1, 0) = 2.0;
  a(1, 1) = 6.0;
  S21Matrix result = a.InverseMatrix();
  EXPECT_NEAR(result(0, 0), 0.6, 1e-7);
  EXPECT_NEAR(result(0, 1), -0.7, 1e-7);
  EXPECT_NEAR(result(1, 0), -0.2, 1e-7);
  EXPECT_NEAR(result(1, 1), 0.4, 1e-7);
}

TEST(Operations, OperatorParenthesisRead) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  EXPECT_DOUBLE_EQ(a(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(a(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(a(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(a(1, 1), 4.0);
}

TEST(Operations, OperatorAddAssignNormal) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  b(0, 0) = 1.0;
  b(0, 1) = 1.0;
  b(1, 0) = 1.0;
  b(1, 1) = 1.0;
  a += b;
  EXPECT_DOUBLE_EQ(a(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(a(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(a(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(a(1, 1), 5.0);
}

TEST(Operations, OperatorSubAssignNormal) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(1, 0) = 2.0;
  a(1, 1) = 2.0;
  b(0, 0) = 1.0;
  b(0, 1) = 1.0;
  b(1, 0) = 1.0;
  b(1, 1) = 1.0;
  a -= b;
  EXPECT_DOUBLE_EQ(a(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(a(0, 1), 1.0);
  EXPECT_DOUBLE_EQ(a(1, 0), 1.0);
  EXPECT_DOUBLE_EQ(a(1, 1), 1.0);
}

TEST(Operations, OperatorMulAssignNumberNormal) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  a *= 2.0;
  EXPECT_DOUBLE_EQ(a(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(a(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(a(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(a(1, 1), 8.0);
}
TEST(Mutators, SetColsDecrease) {
  S21Matrix m(2, 3);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 0) = 4;
  m(1, 1) = 5;
  m(1, 2) = 6;
  m.SetCols(2);
  EXPECT_EQ(m.GetCols(), 2);
  EXPECT_DOUBLE_EQ(m(0, 1), 2);
  EXPECT_DOUBLE_EQ(m(1, 1), 5);
}

TEST(Mutators, SetRowsWithZeroPadding) {
  S21Matrix m(1, 2);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m.SetRows(2);
  EXPECT_DOUBLE_EQ(m(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(m(1, 1), 0.0);
}

TEST(Operations, CalcComplements3x3) {
  S21Matrix m(3, 3);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 0) = 0;
  m(1, 1) = 4;
  m(1, 2) = 5;
  m(2, 0) = 1;
  m(2, 1) = 0;
  m(2, 2) = 6;

  S21Matrix result = m.CalcComplements();
  EXPECT_DOUBLE_EQ(result(0, 0), 24);
  EXPECT_DOUBLE_EQ(result(0, 1), 5);
  EXPECT_DOUBLE_EQ(result(0, 2), -4);
}

TEST(Operations, FloatingPointPrecision) {
  S21Matrix a(2, 2);
  a(0, 0) = 0.1;
  a(0, 1) = 0.2;
  a(1, 0) = 0.3;
  a(1, 1) = 0.4;

  S21Matrix b = a * 3.0;
  EXPECT_NEAR(b(0, 0), 0.3, 1e-10);
  EXPECT_NEAR(b(0, 1), 0.6, 1e-10);
}

TEST(Operators, AssignmentOperator) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  S21Matrix b;
  b = a;
  EXPECT_DOUBLE_EQ(b(0, 0), 1);
}
TEST(Operators, MoveAssignmentOperator) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  S21Matrix b;
  b = std::move(a);
  EXPECT_DOUBLE_EQ(b(0, 0), 1);
  EXPECT_EQ(a.GetRows(), 0);
}
TEST(Operations, EqMatrixPrecision) {
  S21Matrix a(1, 1);
  S21Matrix b(1, 1);
  a(0, 0) = 0.1 + 0.2;
  b(0, 0) = 0.3;

  EXPECT_TRUE(a.EqMatrix(b));
}
TEST(Operations, MulNumberZero) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  a.MulNumber(0);
  EXPECT_DOUBLE_EQ(a(0, 0), 0);
  EXPECT_DOUBLE_EQ(a(1, 1), 0);
}
TEST(Operations, MulNumberOne) {
  S21Matrix a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  a.MulNumber(1);
  EXPECT_DOUBLE_EQ(a(0, 0), 1);
  EXPECT_DOUBLE_EQ(a(1, 1), 4);
}
TEST(Operations, OperatorMulAssignMatrixNormal) {
  S21Matrix a(2, 3);
  S21Matrix b(3, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(0, 2) = 3.0;
  a(1, 0) = 4.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.0;
  b(0, 0) = 1.0;
  b(0, 1) = 2.0;
  b(1, 0) = 3.0;
  b(1, 1) = 4.0;
  b(2, 0) = 5.0;
  b(2, 1) = 6.0;
  a *= b;
  EXPECT_DOUBLE_EQ(a(0, 0), 22.0);
  EXPECT_DOUBLE_EQ(a(0, 1), 28.0);
  EXPECT_DOUBLE_EQ(a(1, 0), 49.0);
  EXPECT_DOUBLE_EQ(a(1, 1), 64.0);
}

TEST(Constructors, CopyConstructor) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  S21Matrix b(a);
  EXPECT_DOUBLE_EQ(b(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(b(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(b(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(b(1, 1), 4.0);
  a(0, 0) = 5.0;
  EXPECT_DOUBLE_EQ(b(0, 0), 1.0);
}

TEST(Mutators, SetRowsDecrease) {
  S21Matrix m(3, 2);
  m(0, 0) = 1;
  m(1, 0) = 2;
  m(2, 0) = 3;
  m.SetRows(2);
  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_DOUBLE_EQ(m(1, 0), 2);
}

TEST(Mutators, SetColsWithZeroPadding) {
  S21Matrix m(2, 2);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m.SetCols(3);
  EXPECT_DOUBLE_EQ(m(0, 2), 0.0);
}

TEST(Operations, Determinant3x3) {
  S21Matrix m(3, 3);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 0) = 4;
  m(1, 1) = 5;
  m(1, 2) = 6;
  m(2, 0) = 7;
  m(2, 1) = 8;
  m(2, 2) = 9;
  EXPECT_DOUBLE_EQ(m.Determinant(), 0.0);
}

// TEST(Operators, SelfAssignment) {
//   S21Matrix m(2, 2);
//   m(0, 0) = 1;
//   m = m;
//   EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
// }

TEST(Constructors, MoveConstructor) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  S21Matrix b(std::move(a));
  EXPECT_DOUBLE_EQ(b(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(b(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(b(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(b(1, 1), 4.0);
  EXPECT_EQ(a.GetRows(), 0);
  EXPECT_EQ(a.GetCols(), 0);
  EXPECT_EQ(a.getMatrix(), nullptr);
}
TEST(Operators, PlusOperatorNormal) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);

  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;

  b(0, 0) = 5.0;
  b(0, 1) = 6.0;
  b(1, 0) = 7.0;
  b(1, 1) = 8.0;

  S21Matrix result = a + b;

  EXPECT_DOUBLE_EQ(result(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 12.0);
}

TEST(Operators, PlusOperatorDifferentDimensions) {
  S21Matrix a(2, 2);
  S21Matrix b(1, 2);

  EXPECT_THROW(a + b, std::invalid_argument);
}

TEST(Operators, PlusOperatorNotInitialized) {
  S21Matrix a;
  S21Matrix b(1, 1);

  EXPECT_THROW(a + b, std::runtime_error);
}

TEST(Operators, MinusOperatorNormal) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);

  a(0, 0) = 5.0;
  a(0, 1) = 6.0;
  a(1, 0) = 7.0;
  a(1, 1) = 8.0;

  b(0, 0) = 1.0;
  b(0, 1) = 2.0;
  b(1, 0) = 3.0;
  b(1, 1) = 4.0;

  S21Matrix result = a - b;

  EXPECT_DOUBLE_EQ(result(0, 0), 4.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 4.0);
}

TEST(Operators, MinusOperatorDifferentDimensions) {
  S21Matrix a(2, 3);
  S21Matrix b(2, 2);

  EXPECT_THROW(a - b, std::invalid_argument);
}

TEST(Operators, MinusOperatorNotInitialized) {
  S21Matrix a(1, 1);
  S21Matrix b;

  EXPECT_THROW(a - b, std::runtime_error);
}

TEST(Operators, PlusMinusCombination) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);

  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;

  b(0, 0) = 5.0;
  b(0, 1) = 6.0;
  b(1, 0) = 7.0;
  b(1, 1) = 8.0;

  c(0, 0) = 1.0;
  c(0, 1) = 1.0;
  c(1, 0) = 1.0;
  c(1, 1) = 1.0;

  S21Matrix result = (a + b) - c;

  EXPECT_DOUBLE_EQ(result(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 7.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 9.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 11.0);
}
TEST(Operators, EqualityOperatorTrue) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);

  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;

  b(0, 0) = 1.0;
  b(0, 1) = 2.0;
  b(1, 0) = 3.0;
  b(1, 1) = 4.0;

  EXPECT_TRUE(a == b);
}

TEST(Operators, EqualityOperatorFalse) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);

  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;

  b(0, 0) = 1.1;
  b(0, 1) = 2.0;
  b(1, 0) = 3.0;
  b(1, 1) = 4.0;

  EXPECT_FALSE(a == b);
}

// TEST(Operators, EqualityOperatorNotInitialized) {
//   S21Matrix a;
//   S21Matrix b(1, 1);

//   EXPECT_THROW(a == b, std::runtime_error);
// }

TEST(Operators, EqualityOperatorPrecision) {
  S21Matrix a(1, 1);
  S21Matrix b(1, 1);

  a(0, 0) = 0.1 + 0.2;
  b(0, 0) = 0.3;

  EXPECT_TRUE(a == b);
}

TEST(Operators, EqualityOperatorSelfComparison) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;

  EXPECT_TRUE(a == a);
}
TEST(Operations, CopyAssignmentNormal) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  S21Matrix b(1, 1);
  b = a;
  EXPECT_DOUBLE_EQ(b(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(b(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(b(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(b(1, 1), 4.0);
  a(0, 0) = 5.0;
  EXPECT_DOUBLE_EQ(b(0, 0), 1.0);
}

TEST(Operations, MoveAssignmentNormal) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  S21Matrix b(1, 1);
  b = std::move(a);
  EXPECT_DOUBLE_EQ(b(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(b(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(b(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(b(1, 1), 4.0);
  EXPECT_EQ(a.GetRows(), 0);
  EXPECT_EQ(a.GetCols(), 0);
  EXPECT_EQ(a.getMatrix(), nullptr);
}
TEST(Mutators, SetRowsNormal) {
  S21Matrix test(2, 2);
  test(0, 0) = 1.0;
  test(0, 1) = 2.0;
  test(1, 0) = 3.0;
  test(1, 1) = 4.0;
  test.SetRows(3);
  EXPECT_DOUBLE_EQ(test(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(test(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(test(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(test(1, 1), 4.0);
  EXPECT_EQ(test.GetRows(), 3);
}

TEST(Mutators, SetRowsNormalIncrease) {
  S21Matrix test(2, 2);
  test(0, 0) = 1.0;
  test(0, 1) = 2.0;
  test(1, 0) = 3.0;
  test(1, 1) = 4.0;
  test.SetRows(3);
  EXPECT_EQ(test.GetRows(), 3);
  EXPECT_EQ(test.GetCols(), 2);
  EXPECT_DOUBLE_EQ(test(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(test(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(test(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(test(1, 1), 4.0);
  EXPECT_DOUBLE_EQ(test(2, 0), 0.0);
  EXPECT_DOUBLE_EQ(test(2, 1), 0.0);
}

TEST(Mutators, SetRowsNormalDecrease) {
  S21Matrix test(3, 2);
  test(0, 0) = 1.0;
  test(0, 1) = 2.0;
  test(1, 0) = 3.0;
  test(1, 1) = 4.0;
  test(2, 0) = 5.0;
  test(2, 1) = 6.0;
  test.SetRows(2);
  EXPECT_EQ(test.GetRows(), 2);
  EXPECT_EQ(test.GetCols(), 2);
  EXPECT_DOUBLE_EQ(test(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(test(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(test(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(test(1, 1), 4.0);
  EXPECT_THROW(test(2, 0), std::out_of_range);
}

TEST(Mutators, SetRowsNoChange) {
  S21Matrix test(2, 2);
  test(0, 0) = 1.0;
  test(0, 1) = 2.0;
  test(1, 0) = 3.0;
  test(1, 1) = 4.0;
  test.SetRows(2);
  EXPECT_EQ(test.GetRows(), 2);
  EXPECT_EQ(test.GetCols(), 2);
  EXPECT_DOUBLE_EQ(test(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(test(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(test(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(test(1, 1), 4.0);
}

TEST(Mutators, SetRowsInvalidArgumentZero) {
  S21Matrix test(2, 2);
  EXPECT_THROW(test.SetRows(0), std::invalid_argument);
}

TEST(Mutators, SetRowsInvalidArgumentNegative) {
  S21Matrix test(2, 2);
  EXPECT_THROW(test.SetRows(-1), std::invalid_argument);
}

TEST(Mutators, SetColsNormalIncrease) {
  S21Matrix test(2, 2);
  test(0, 0) = 1.0;
  test(0, 1) = 2.0;
  test(1, 0) = 3.0;
  test(1, 1) = 4.0;
  test.SetCols(3);
  EXPECT_EQ(test.GetRows(), 2);
  EXPECT_EQ(test.GetCols(), 3);
  EXPECT_DOUBLE_EQ(test(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(test(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(test(0, 2), 0.0);
  EXPECT_DOUBLE_EQ(test(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(test(1, 1), 4.0);
  EXPECT_DOUBLE_EQ(test(1, 2), 0.0);
}

TEST(Mutators, SetColsNormalDecrease) {
  S21Matrix test(2, 3);
  test(0, 0) = 1.0;
  test(0, 1) = 2.0;
  test(0, 2) = 3.0;
  test(1, 0) = 4.0;
  test(1, 1) = 5.0;
  test(1, 2) = 6.0;
  test.SetCols(2);
  EXPECT_EQ(test.GetRows(), 2);
  EXPECT_EQ(test.GetCols(), 2);
  EXPECT_DOUBLE_EQ(test(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(test(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(test(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(test(1, 1), 5.0);
  EXPECT_THROW(test(0, 2), std::out_of_range);
}

TEST(Mutators, SetColsNoChange) {
  S21Matrix test(2, 2);
  test(0, 0) = 1.0;
  test(0, 1) = 2.0;
  test(1, 0) = 3.0;
  test(1, 1) = 4.0;
  test.SetCols(2);
  EXPECT_EQ(test.GetRows(), 2);
  EXPECT_EQ(test.GetCols(), 2);
  EXPECT_DOUBLE_EQ(test(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(test(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(test(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(test(1, 1), 4.0);
}

TEST(Mutators, SetColsInvalidArgumentZero) {
  S21Matrix test(2, 2);
  EXPECT_THROW(test.SetCols(0), std::invalid_argument);
}

TEST(Mutators, SetColsInvalidArgumentNegative) {
  S21Matrix test(2, 2);
  EXPECT_THROW(test.SetCols(-1), std::invalid_argument);
}
TEST(Mutators, GetRowsInitial) {
  S21Matrix test(2, 3);
  EXPECT_EQ(test.GetRows(), 2);
}

TEST(Mutators, GetRowsAfterSetRows) {
  S21Matrix test(2, 2);
  test.SetRows(3);
  EXPECT_EQ(test.GetRows(), 3);
}

TEST(Mutators, GetRowsNotInitialized) {
  S21Matrix test;
  EXPECT_EQ(test.GetRows(), 0);
}

TEST(Mutators, GetColsInitial) {
  S21Matrix test(2, 3);
  EXPECT_EQ(test.GetCols(), 3);
}

TEST(Mutators, GetColsAfterSetCols) {
  S21Matrix test(2, 2);
  test.SetCols(3);
  EXPECT_EQ(test.GetCols(), 3);
}

TEST(Mutators, GetColsNotInitialized) {
  S21Matrix test;
  EXPECT_EQ(test.GetCols(), 0);
}
TEST(Operations, OperatorPlusNormal) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  b(0, 0) = 1.0;
  b(0, 1) = 1.0;
  b(1, 0) = 1.0;
  b(1, 1) = 1.0;
  S21Matrix result = a + b;
  EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 5.0);
}

TEST(Operations, OperatorPlusDifferentDimensions) {
  S21Matrix a(2, 2);
  S21Matrix b(1, 2);
  EXPECT_THROW(a + b, std::invalid_argument);
}

TEST(Operations, OperatorPlusIdentity) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  S21Matrix b(a);
  S21Matrix result = a + b;
  EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 8.0);
}
TEST(Operations, OperatorMinusNormal) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(1, 0) = 2.0;
  a(1, 1) = 2.0;
  b(0, 0) = 1.0;
  b(0, 1) = 1.0;
  b(1, 0) = 1.0;
  b(1, 1) = 1.0;
  S21Matrix result = a - b;
  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 1.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 1.0);
}

TEST(Operations, OperatorMinusDifferentDimensions) {
  S21Matrix a(2, 2);
  S21Matrix b(1, 2);
  EXPECT_THROW(a - b, std::invalid_argument);
}

TEST(Operations, OperatorMinusZeroResult) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  b(0, 0) = 1.0;
  b(0, 1) = 2.0;
  b(1, 0) = 3.0;
  b(1, 1) = 4.0;
  S21Matrix result = a - b;
  EXPECT_DOUBLE_EQ(result(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 0.0);
}
TEST(Operations, OperatorMulMatrixNormal) {
  S21Matrix a(2, 3);
  S21Matrix b(3, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(0, 2) = 3.0;
  a(1, 0) = 4.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.0;
  b(0, 0) = 1.0;
  b(0, 1) = 2.0;
  b(1, 0) = 3.0;
  b(1, 1) = 4.0;
  b(2, 0) = 5.0;
  b(2, 1) = 6.0;
  S21Matrix result = a * b;
  EXPECT_DOUBLE_EQ(result(0, 0), 22.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 28.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 49.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 64.0);
}

TEST(Operations, OperatorMulNumberNormal) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  S21Matrix result = a * 2.0;
  EXPECT_DOUBLE_EQ(result(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 8.0);
}

TEST(Operations, OperatorMulMatrixInvalidDimensions) {
  S21Matrix a(2, 1);
  S21Matrix b(2, 1);
  EXPECT_THROW(a * b, std::invalid_argument);
}
TEST(Operations, OperatorEqEqualMatrices) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  b(0, 0) = 1.0;
  b(0, 1) = 2.0;
  b(1, 0) = 3.0;
  b(1, 1) = 4.0;
  EXPECT_TRUE(a == b);
}

TEST(Operations, OperatorEqDifferentDimensions) {
  S21Matrix a(2, 2);
  S21Matrix b(1, 2);
  EXPECT_FALSE(a == b);
}

TEST(Operations, OperatorEqDifferentValues) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  b(0, 0) = 1.0;
  b(0, 1) = 2.0;
  b(1, 0) = 3.0;
  b(1, 1) = 5.0;
  EXPECT_FALSE(a == b);
}
TEST(Operations, OperatorAssignNormal) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  b = a;
  EXPECT_DOUBLE_EQ(b(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(b(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(b(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(b(1, 1), 4.0);
  a(0, 0) = 5.0;
  EXPECT_DOUBLE_EQ(b(0, 0), 1.0);
}

TEST(Operations, OperatorAssignSmallerMatrix) {
  S21Matrix a(3, 3);
  S21Matrix b(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(0, 2) = 3.0;
  a(1, 0) = 4.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.0;
  a(2, 0) = 7.0;
  a(2, 1) = 8.0;
  a(2, 2) = 9.0;
  b = a;
  EXPECT_EQ(b.GetRows(), 3);
  EXPECT_EQ(b.GetCols(), 3);
  EXPECT_DOUBLE_EQ(b(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(b(1, 1), 5.0);
  EXPECT_DOUBLE_EQ(b(2, 2), 9.0);
}

// TEST(Operations, OperatorAssignSelf) {
//   S21Matrix a(2, 2);
//   a(0, 0) = 1.0;
//   a(0, 1) = 2.0;
//   a(1, 0) = 3.0;
//   a(1, 1) = 4.0;
//   S21Matrix& const ref = a;
//   a = ref;
//   EXPECT_DOUBLE_EQ(a(0, 0), 1.0);
//   EXPECT_DOUBLE_EQ(a(0, 1), 2.0);
//   EXPECT_DOUBLE_EQ(a(1, 0), 3.0);
//   EXPECT_DOUBLE_EQ(a(1, 1), 4.0);
// }

TEST(Operations, OperatorAddAssignDifferentDimensions) {
  S21Matrix a(2, 2);
  S21Matrix b(1, 2);
  EXPECT_THROW(a += b, std::invalid_argument);
}

TEST(Operations, OperatorAddAssignSelf) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  a += a;
  EXPECT_DOUBLE_EQ(a(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(a(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(a(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(a(1, 1), 8.0);
}

TEST(Operations, OperatorSubAssignDifferentDimensions) {
  S21Matrix a(2, 2);
  S21Matrix b(1, 2);
  EXPECT_THROW(a -= b, std::invalid_argument);
}

TEST(Operations, OperatorSubAssignSelf) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  S21Matrix b = a;
  a -= b;
  EXPECT_DOUBLE_EQ(a(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(a(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(a(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(a(1, 1), 0.0);
}

TEST(Operations, OperatorMulAssignMatrixInvalidDimensions) {
  S21Matrix a(2, 1);
  S21Matrix b(2, 1);
  EXPECT_THROW(a *= b, std::invalid_argument);
}
TEST(Operations, OperatorParenthesisReadWrite) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  EXPECT_DOUBLE_EQ(a(0, 0), 1.0);
  a(1, 1) = 4.0;
  EXPECT_DOUBLE_EQ(a(1, 1), 4.0);
}

TEST(Operations, OperatorParenthesisBoundary) {
  S21Matrix a(2, 2);
  a(1, 1) = 4.0;
  EXPECT_DOUBLE_EQ(a(1, 1), 4.0);
  a(0, 0) = 1.0;
  EXPECT_DOUBLE_EQ(a(0, 0), 1.0);
}
TEST(Operations, EqMatrixEqual) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  b(0, 0) = 1.0;
  b(0, 1) = 2.0;
  b(1, 0) = 3.0;
  b(1, 1) = 4.0;
  EXPECT_TRUE(a.EqMatrix(b));
}

TEST(Operations, EqMatrixDifferentValues) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  b(0, 0) = 1.0;
  b(0, 1) = 2.0;
  b(1, 0) = 3.0;
  b(1, 1) = 5.0;
  EXPECT_FALSE(a.EqMatrix(b));
}
TEST(Operations, SumMatrixNormal) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  b(0, 0) = 1.0;
  b(0, 1) = 1.0;
  b(1, 0) = 1.0;
  b(1, 1) = 1.0;
  a.SumMatrix(b);
  EXPECT_DOUBLE_EQ(a(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(a(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(a(1, 0), 4.0);
  EXPECT_DOUBLE_EQ(a(1, 1), 5.0);
}

TEST(Operations, SumMatrixDifferentDimensions) {
  S21Matrix a(2, 2);
  S21Matrix b(1, 2);
  EXPECT_THROW(a.SumMatrix(b), std::invalid_argument);
}

TEST(Operations, SumMatrixSelf) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  a.SumMatrix(a);
  EXPECT_DOUBLE_EQ(a(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(a(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(a(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(a(1, 1), 8.0);
}
TEST(Operations, SubMatrixNormal_2) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 2.0;
  a(0, 1) = 2.0;
  a(1, 0) = 2.0;
  a(1, 1) = 2.0;
  b(0, 0) = 1.0;
  b(0, 1) = 1.0;
  b(1, 0) = 1.0;
  b(1, 1) = 1.0;
  a.SubMatrix(b);
  EXPECT_DOUBLE_EQ(a(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(a(0, 1), 1.0);
  EXPECT_DOUBLE_EQ(a(1, 0), 1.0);
  EXPECT_DOUBLE_EQ(a(1, 1), 1.0);
}

TEST(Operations, SubMatrixSelf) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  a.SubMatrix(a);
  EXPECT_DOUBLE_EQ(a(0, 0), 0.0);
  EXPECT_DOUBLE_EQ(a(0, 1), 0.0);
  EXPECT_DOUBLE_EQ(a(1, 0), 0.0);
  EXPECT_DOUBLE_EQ(a(1, 1), 0.0);
}
TEST(Operations, MulNumberPositive) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  a.MulNumber(2.0);
  EXPECT_DOUBLE_EQ(a(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(a(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(a(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(a(1, 1), 8.0);
}

TEST(Operations, MulNumberNegative) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  a.MulNumber(-1.0);
  EXPECT_DOUBLE_EQ(a(0, 0), -1.0);
  EXPECT_DOUBLE_EQ(a(0, 1), -2.0);
  EXPECT_DOUBLE_EQ(a(1, 0), -3.0);
  EXPECT_DOUBLE_EQ(a(1, 1), -4.0);
}

TEST(Operations, MulNumberIdentity) {
  S21Matrix a(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  a.MulNumber(1.0);
  EXPECT_DOUBLE_EQ(a(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(a(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(a(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(a(1, 1), 4.0);
}

TEST(Operations, MulMatrixIdentity) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;
  b(0, 0) = 1.0;
  b(0, 1) = 0.0;
  b(1, 0) = 0.0;
  b(1, 1) = 1.0;
  a.MulMatrix(b);
  EXPECT_DOUBLE_EQ(a(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(a(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(a(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(a(1, 1), 4.0);
}
TEST(Operations, TransposeOneByOne) {
  S21Matrix a(1, 1);
  a(0, 0) = 5.0;
  S21Matrix result = a.Transpose();
  EXPECT_EQ(result.GetRows(), 1);
  EXPECT_EQ(result.GetCols(), 1);
  EXPECT_DOUBLE_EQ(result(0, 0), 5.0);
}

TEST(Operations, TransposeRectangular) {
  S21Matrix a(1, 3);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(0, 2) = 3.0;
  S21Matrix result = a.Transpose();
  EXPECT_EQ(result.GetRows(), 3);
  EXPECT_EQ(result.GetCols(), 1);
  EXPECT_DOUBLE_EQ(result(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(result(2, 0), 3.0);
}

TEST(Operations, CalcComplementsThreeByThree) {
  S21Matrix a(3, 3);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(0, 2) = 3.0;
  a(1, 0) = 0.0;
  a(1, 1) = 4.0;
  a(1, 2) = 5.0;
  a(2, 0) = 1.0;
  a(2, 1) = 0.0;
  a(2, 2) = 6.0;
  S21Matrix result = a.CalcComplements();
  EXPECT_DOUBLE_EQ(result(0, 0), 24.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 5.0);
  EXPECT_DOUBLE_EQ(result(0, 2), -4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), -12.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 3.0);
  EXPECT_DOUBLE_EQ(result(1, 2), 2.0);
  EXPECT_DOUBLE_EQ(result(2, 0), -2.0);
  EXPECT_DOUBLE_EQ(result(2, 1), -5.0);
  EXPECT_DOUBLE_EQ(result(2, 2), 4.0);
}

TEST(Operations, DeterminantThreeByThree) {
  S21Matrix a(3, 3);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(0, 2) = 3.0;
  a(1, 0) = 4.0;
  a(1, 1) = 5.0;
  a(1, 2) = 6.0;
  a(2, 0) = 7.0;
  a(2, 1) = 8.0;
  a(2, 2) = 9.0;
  EXPECT_DOUBLE_EQ(a.Determinant(), 0.0);
}

TEST(Operations, InverseMatrixThreeByThree) {
  S21Matrix a(3, 3);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(0, 2) = 3.0;
  a(1, 0) = 0.0;
  a(1, 1) = 4.0;
  a(1, 2) = 5.0;
  a(2, 0) = 1.0;
  a(2, 1) = 0.0;
  a(2, 2) = 6.0;
  S21Matrix result = a.InverseMatrix();
  EXPECT_NEAR(result(0, 0), 1.0909090909090909, 1e-7);    // 24/22
  EXPECT_NEAR(result(0, 1), -0.5454545454545454, 1e-7);   // -12/22
  EXPECT_NEAR(result(0, 2), -0.09090909090909091, 1e-7);  // -2/22
  EXPECT_NEAR(result(1, 0), 0.22727272727272727, 1e-7);   // 5/22
  EXPECT_NEAR(result(1, 1), 0.13636363636363635, 1e-7);   // 3/22
  EXPECT_NEAR(result(1, 2), -0.22727272727272727, 1e-7);  // -5/22
  EXPECT_NEAR(result(2, 0), -0.18181818181818182, 1e-7);  // -4/22
  EXPECT_NEAR(result(2, 1), 0.09090909090909091, 1e-7);   // 2/22
  EXPECT_NEAR(result(2, 2), 0.18181818181818182, 1e-7);   // 4/22
}
TEST(MatrixMutators, SetRowsIncrease) {
  S21Matrix m(2, 3);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(0, 2) = 3.0;
  m(1, 0) = 4.0;
  m(1, 1) = 5.0;
  m(1, 2) = 6.0;

  m.SetRows(4);

  EXPECT_EQ(m.GetRows(), 4);
  EXPECT_EQ(m.GetCols(), 3);

  EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m(1, 2), 6.0);

  for (int j = 0; j < 3; ++j) {
    EXPECT_DOUBLE_EQ(m(2, j), 0.0);
    EXPECT_DOUBLE_EQ(m(3, j), 0.0);
  }
}

TEST(MatrixMutators, SetRowsDecrease) {
  S21Matrix m(3, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;
  m(2, 0) = 5.0;
  m(2, 1) = 6.0;

  m.SetRows(1);

  EXPECT_EQ(m.GetRows(), 1);
  EXPECT_EQ(m.GetCols(), 2);

  EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m(0, 1), 2.0);
}

TEST(MatrixMutators, SetRowsInvalid) {
  S21Matrix m(2, 2);
  EXPECT_THROW(m.SetRows(0), std::invalid_argument);
  EXPECT_THROW(m.SetRows(-5), std::invalid_argument);
}
TEST(MatrixMutators, SetColsIncrease) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  m.SetCols(4);

  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_EQ(m.GetCols(), 4);

  EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m(1, 1), 4.0);

  for (int i = 0; i < 2; ++i) {
    EXPECT_DOUBLE_EQ(m(i, 2), 0.0);
    EXPECT_DOUBLE_EQ(m(i, 3), 0.0);
  }
}

TEST(MatrixMutators, SetColsDecrease) {
  S21Matrix m(2, 3);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(0, 2) = 3.0;
  m(1, 0) = 4.0;
  m(1, 1) = 5.0;
  m(1, 2) = 6.0;

  m.SetCols(1);

  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_EQ(m.GetCols(), 1);

  EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m(1, 0), 4.0);
}

TEST(MatrixMutators, SetColsInvalid) {
  S21Matrix m(2, 2);
  EXPECT_THROW(m.SetCols(0), std::invalid_argument);
  EXPECT_THROW(m.SetCols(-3), std::invalid_argument);
}
TEST(MatrixMutators, SetRowsSameSize) {
  S21Matrix m(3, 3);
  m.SetRows(3);
  EXPECT_EQ(m.GetRows(), 3);
}

TEST(MatrixMutators, SetColsSameSize) {
  S21Matrix m(3, 3);
  m.SetCols(3);
  EXPECT_EQ(m.GetCols(), 3);
}

TEST(MatrixMutators, SetRowsAndColsCombined) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;

  m.SetRows(3);
  m.SetCols(1);

  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 1);

  EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(m(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(m(2, 0), 0.0);
}
TEST(MatrixMutators, SetRowsPreservesCols) {
  S21Matrix m(2, 3);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 0) = 4;
  m(1, 1) = 5;
  m(1, 2) = 6;

  m.SetRows(4);

  EXPECT_EQ(m.GetRows(), 4);
  EXPECT_EQ(m.GetCols(), 3);
  EXPECT_EQ(m(0, 2), 3);
}

TEST(MatrixMutators, SetRowsValidCases) {
  S21Matrix m(2, 3);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 0) = 4;
  m(1, 1) = 5;
  m(1, 2) = 6;

  EXPECT_NO_THROW(m.SetRows(4));
  EXPECT_EQ(m.GetRows(), 4);
  EXPECT_EQ(m(0, 1), 2);
  EXPECT_EQ(m(2, 0), 0);

  EXPECT_NO_THROW(m.SetRows(1));
  EXPECT_EQ(m.GetRows(), 1);
  EXPECT_EQ(m(0, 2), 3);
}
TEST(MatrixOperations, SimpleArithmeticWithNaN) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);

  const double nan_value = std::numeric_limits<double>::quiet_NaN();
  a(0, 0) = 1.0;
  a(0, 1) = nan_value;
  a(1, 0) = 3.0;
  a(1, 1) = 4.0;

  b(0, 0) = 5.0;
  b(0, 1) = 6.0;
  b(1, 0) = 7.0;
  b(1, 1) = 8.0;

  EXPECT_THROW(a.SimpleArithmetic(b, 1), std::runtime_error);
}

TEST(MatrixOperations, SimpleArithmeticWithInfinity) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);

  const double inf = std::numeric_limits<double>::infinity();
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = inf;
  a(1, 1) = 4.0;

  b(0, 0) = 5.0;
  b(0, 1) = 6.0;
  b(1, 0) = 7.0;
  b(1, 1) = 8.0;

  EXPECT_THROW(a.SimpleArithmetic(b, 1), std::runtime_error);
}

TEST(MatrixOperations, SimpleArithmeticWithNegativeInfinity) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);

  const double neg_inf = -std::numeric_limits<double>::infinity();
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(1, 0) = 3.0;
  a(1, 1) = neg_inf;

  b(0, 0) = 5.0;
  b(0, 1) = 6.0;
  b(1, 0) = 7.0;
  b(1, 1) = 8.0;

  EXPECT_THROW(a.SimpleArithmetic(b, -1), std::runtime_error);
}
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}