#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Rows and columns must be >0");
  }
  matrix_ = new double *[rows];
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols]();
  }
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  CheckValidMatrix(other);
  bool result = true;
  int done = 0;
  while (!done) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
      result = false;
      done = 1;
    }
    for (int i = 0; i < rows_ && !done; i++) {
      for (int j = 0; j < cols_; j++) {
        if (std::abs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
          result = false;
          done = 1;
        }
      }
    }
    done = 1;
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  CheckValidMatrix(other);
  SimpleArithmetic(other, 1);
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  CheckValidMatrix(other);
  SimpleArithmetic(other, -1);
}

void S21Matrix::MulNumber(const double num) {
  CheckValidOperator();
  if (!std::isfinite(num)) {
    throw std::invalid_argument("Number must be finite");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  CheckValidMatrix(other);
  if (cols_ != other.rows_) {
    throw std::invalid_argument("Invalid dimensions for multiplication");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = result.matrix_;
  cols_ = other.cols_;
  result.matrix_ = nullptr;
}

S21Matrix S21Matrix::Transpose() {
  CheckValidOperator();
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  CheckValidOperator();
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square");
  }
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = GetMinor(i, j);
      double det = minor.Determinant();
      result(i, j) = ((i + j) % 2 == 0 ? 1 : -1) * det;
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  double result = 0.0;
  CheckValidOperator();
  if (rows_ != cols_) throw std::invalid_argument("Matrix must be square");

  if (rows_ == 1) {
    result = (*this)(0, 0);
  } else if (rows_ == 2) {
    result = (*this)(0, 0) * (*this)(1, 1) - (*this)(1, 0) * (*this)(0, 1);
  } else {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = GetMinor(0, j);
      int sign = (j % 2 == 0) ? 1 : -1;
      result += (*this)(0, j) * sign * minor.Determinant();
    }
  }

  return result;
}
S21Matrix S21Matrix::InverseMatrix() {
  CheckValidOperator();
  double det = Determinant();
  if (det == 0) {
    throw std::runtime_error("Matrix is singular");
  }
  S21Matrix complements = CalcComplements();
  S21Matrix adjugate = complements.Transpose();
  adjugate.MulNumber(1.0 / det);
  return adjugate;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  CheckValidMatrix(other);
  CheckValidDimensions(other);
  S21Matrix result(*this);
  result += other;
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  CheckValidMatrix(other);
  CheckValidDimensions(other);
  S21Matrix result(*this);
  result -= other;
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  CheckValidOperator();
  S21Matrix result(*this);
  result *= num;
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  CheckValidMatrix(other);
  S21Matrix result(*this);
  result *= other;
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  CheckValidMatrix(other);
  return EqMatrix(other);
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  CheckValidMatrix(other);
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices must have the same dimensions");
  }
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  CheckValidMatrix(other);
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices must have the same dimensions");
  }
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  CheckValidOperator();
  MulNumber(num);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  CheckValidMatrix(other);
  if (cols_ != other.rows_) {
    throw std::invalid_argument("Invalid dimensions for multiplication");
  }
  MulMatrix(other);
  return *this;
}

double &S21Matrix::operator()(int i, int j) const {
  CheckValidOperator();
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Index out of bounds");
  }
  return matrix_[i][j];
}
// копирующий опреатор присваивания
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    if (matrix_ != nullptr) {
      for (int i = 0; i < rows_; i++) {
        delete[] matrix_[i];
      }
      delete[] matrix_;
    }
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}
// перемещающий оператор присваивания
S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    if (matrix_ != nullptr) {
      for (int i = 0; i < rows_; i++) {
        delete[] matrix_[i];
      }
      delete[] matrix_;
    }

    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;

    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}
void S21Matrix::SetRows(int new_rows) {
  if (new_rows < 1) {
    throw std::invalid_argument("Rows of matrix should be more or equal 1");
  }
  if (matrix_ == nullptr) {
    throw std::runtime_error("Matrix not initialized");
  }
  if (cols_ <= 0) {
    throw std::invalid_argument("Columns must be > 0");
  }
  if (new_rows != rows_) {
    S21Matrix new_matrix(new_rows, cols_);
    int rows_to_copy = std::min(rows_, new_rows);
    for (int i = 0; i < rows_to_copy; i++) {
      std::copy(matrix_[i], matrix_[i] + cols_, new_matrix.matrix_[i]);
    }
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = new_matrix.matrix_;
    rows_ = new_rows;
    cols_ = new_matrix.cols_;

    new_matrix.matrix_ = nullptr;
    new_matrix.rows_ = 0;
    new_matrix.cols_ = 0;
  }
}

void S21Matrix::SetCols(int new_cols) {
  if (new_cols < 1) {
    throw std::invalid_argument("Columns of matrix must be >= 1");
  }
  if (matrix_ == nullptr) {
    throw std::runtime_error("Matrix not initialized");
  }
  if (rows_ <= 0) {
    throw std::invalid_argument("Rows must be > 0");
  }
  if (new_cols != cols_) {
    S21Matrix new_matrix(rows_, new_cols);
    int cols_to_copy = std::min(cols_, new_cols);
    for (int i = 0; i < rows_; i++) {
      std::copy(matrix_[i], matrix_[i] + cols_to_copy, new_matrix.matrix_[i]);
    }
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = new_matrix.matrix_;
    cols_ = new_cols;
    rows_ = new_matrix.rows_;

    new_matrix.matrix_ = nullptr;
    new_matrix.cols_ = 0;
    new_matrix.rows_ = 0;
  }
}

int S21Matrix::GetCols() const { return cols_; }

int S21Matrix::GetRows() const { return rows_; }

double **S21Matrix::getMatrix() const { return matrix_; }

void S21Matrix::setMatrix(double **values, int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Rows and columns must be >0");
  }
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  rows_ = rows;
  cols_ = cols;
  if (values == nullptr) {
    matrix_ = nullptr;
  } else {
    matrix_ = new double *[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = values[i][j];
      }
    }
  }
}

S21Matrix S21Matrix::GetMinor(int excluded_row, int excluded_col) const {
  if (excluded_row < 0 || excluded_row >= rows_ || excluded_col < 0 ||
      excluded_col >= cols_) {
    throw std::out_of_range("Invalid excluded row or column");
  }
  S21Matrix minor(rows_ - 1, cols_ - 1);
  int mi = 0;

  for (int i = 0; i < rows_; i++) {
    if (i != excluded_row) {
      int mj = 0;
      for (int j = 0; j < cols_; j++) {
        if (j != excluded_col) {
          minor(mi, mj) = (*this)(i, j);
          mj++;
        }
      }
      mi++;
    }
  }
  return minor;
}

void S21Matrix::SimpleArithmetic(const S21Matrix &other, short sign) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices must have the same dimensions");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (!std::isfinite(matrix_[i][j]) ||
          !std::isfinite(other.matrix_[i][j])) {
        throw std::runtime_error("Invalid matrix values");
      }
      matrix_[i][j] = matrix_[i][j] + sign * other.matrix_[i][j];
    }
  }
}

void S21Matrix::CheckValidMatrix(const S21Matrix &other) const {
  if (matrix_ == nullptr || other.matrix_ == nullptr) {
    throw std::runtime_error("Matrix not initialized");
  }
  if (rows_ <= 0 || cols_ <= 0 || other.rows_ <= 0 || other.cols_ <= 0) {
    throw std::invalid_argument("Rows and columns must be >0");
  }
}

void S21Matrix::CheckValidOperator() const {
  if (matrix_ == nullptr) {
    throw std::runtime_error("Matrix not initialized");
  }
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument("Rows and columns must be >0");
  }
}

void S21Matrix::CheckValidDimensions(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices must have the same dimensions");
  }
}
