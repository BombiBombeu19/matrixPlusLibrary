#include "s21_matrix_oop.h"

// Methods

S21Matrix::S21Matrix() {
  rows_ = 3;
  cols_ = 3;
  create_matrix();
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw out_of_range("ERROR! Incorrect values of the matrix size.");
  }
  rows_ = rows;
  cols_ = cols;
  create_matrix();
}

S21Matrix::S21Matrix(const S21Matrix& other) {  // copy constructor
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  create_matrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {  // move costructor
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;

  this->matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { remove_matrix(); }

// Operations

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool res = true;
  if (this->rows_ == other.rows_ && this->cols_ == other.cols_) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) >= EPS) {
          res = false;
          break;
        }
      }
      if (res == false) break;
    }
  } else {
    res = false;
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (this->rows_ == other.rows_ && this->cols_ == other.cols_) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
      }
    }
  } else {
    throw invalid_argument("ERROR! Different matrix dimensions");
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (this->rows_ == other.rows_ && this->cols_ == other.cols_) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = this->matrix_[i][j] - other.matrix_[i][j];
      }
    }
  } else {
    throw invalid_argument("ERROR! Different matrix dimensions");
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = this->matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw invalid_argument(
        "ERROR! The number of columns of the first matrix is not equal to the "
        "number of rows of the second matrix.");
  }
  S21Matrix result(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < this->cols_; k++) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = result;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(this->cols_, this->rows_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      result.matrix_[j][i] = this->matrix_[i][j];
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  double result = 0;
  if (this->rows_ == this->cols_) {
    if (this->rows_ == 1)
      result = this->matrix_[0][0];
    else if (this->rows_ == 2)
      result = this->matrix_[0][0] * this->matrix_[1][1] -
               this->matrix_[0][1] * this->matrix_[1][0];

    else {
      int k = 0;
      double determinant = 1;
      while (k < this->rows_) {
        double del1 = this->matrix_[k][k];
        for (int i = k + 1; i < this->rows_; i++) {
          double del2 = this->matrix_[i][k] / del1;
          for (int j = k; j < this->cols_; j++) {
            this->matrix_[i][j] =
                this->matrix_[i][j] - this->matrix_[k][j] * del2;
          }
        }
        k++;
      }
      for (int i = 0; i < this->cols_; i++) determinant *= this->matrix_[i][i];
      result = determinant;
    }
  } else {
    throw invalid_argument("ERROR! The matrix is not square.");
  }

  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix B = *this;
  double det = B.Determinant();

  if (det != 0) {
    S21Matrix result(this->rows_, this->cols_);

    if (this->rows_ == 1)
      result.matrix_[0][0] = pow(this->matrix_[0][0], -1);
    else if (this->rows_ == 2) {
      double del = 1 / (this->matrix_[0][0] * this->matrix_[1][1] -
                        this->matrix_[0][1] * this->matrix_[1][0]);
      result.matrix_[0][0] = this->matrix_[1][1] * del;
      result.matrix_[0][1] = (-this->matrix_[0][1]) * del;
      result.matrix_[1][0] = (-this->matrix_[1][0]) * del;
      result.matrix_[1][1] = this->matrix_[0][0] * del;
    }

    else {
      for (int i = 0; i < this->cols_; i++) result.matrix_[i][i] = 1;

      int k = 0;
      while (k < this->cols_) {
        double preob = this->matrix_[k][k];
        for (int i = k; i < this->rows_; i++) {
          this->matrix_[k][i] = this->matrix_[k][i] / preob;
        }
        for (int i = 0; i < this->rows_; i++) {
          result.matrix_[k][i] = result.matrix_[k][i] / preob;
        }

        double del1 = this->matrix_[k][k];
        for (int i = k + 1; i < this->rows_; i++) {
          double del2 = this->matrix_[i][k] / del1;
          for (int j = k; j < this->cols_; j++) {
            this->matrix_[i][j] =
                this->matrix_[i][j] - this->matrix_[k][j] * del2;
          }
          for (int j = 0; j < this->cols_; j++) {
            result.matrix_[i][j] =
                result.matrix_[i][j] - result.matrix_[k][j] * del2;
          }
        }
        k++;
      }

      while (k > 0) {
        k--;
        double preob = this->matrix_[k][k];
        for (int i = k; i >= 0; i--) {
          this->matrix_[k][i] = this->matrix_[k][i] / preob;
        }
        for (int i = this->cols_ - 1; i >= 0; i--) {
          result.matrix_[k][i] = result.matrix_[k][i] / preob;
        }

        double del1 = this->matrix_[k][k];
        for (int i = k - 1; i >= 0; i--) {
          double del2 = this->matrix_[i][k] / del1;
          for (int j = k; j >= 0; j--) {
            this->matrix_[i][j] =
                this->matrix_[i][j] - this->matrix_[k][j] * del2;
          }
          for (int j = this->cols_ - 1; j >= 0; j--) {
            result.matrix_[i][j] =
                result.matrix_[i][j] - result.matrix_[k][j] * del2;
          }
        }
      }
    }
    return result;
  } else {
    throw invalid_argument("ERROR! Matrix determinant is 0.");
  }
}

S21Matrix S21Matrix::CalcComplements() {
  if (this->rows_ != this->cols_) {
    throw invalid_argument("ERROR! The matrix is not square.");
  }

  S21Matrix result(this->rows_, this->cols_);
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      S21Matrix minor(this->rows_ - 1, this->cols_ - 1);
      int m = 0, n = 0;
      for (int row = 0; row < this->rows_; ++row) {
        if (row == i) continue;
        for (int col = 0; col < this->cols_; ++col) {
          if (col == j) continue;
          minor.set_value(m, n, this->matrix_[row][col]);
          ++n;
        }
        ++m;
        n = 0;
      }
      double minorDeterminant = minor.Determinant();
      double cofactor = minorDeterminant * ((i + j) % 2 == 0 ? 1 : -1);
      result.set_value(i, j, cofactor);
    }
  }
  return result;
}

// Operators

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    delete[] this->matrix_;

    this->rows_ = other.rows_;
    this->cols_ = other.cols_;

    create_matrix();
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return this->EqMatrix(other);
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

double S21Matrix::operator()(int rows, int cols) {
  if (rows >= this->rows_ || cols >= this->cols_ || rows < 0 || cols < 0) {
    throw out_of_range("ERROR! Index is outside the matrix");
  }
  return this->matrix_[rows][cols];
}

// My Functions

void S21Matrix::create_matrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = 0;
    }
  }
}

void S21Matrix::remove_matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      if (matrix_[i] != nullptr) {
        delete (matrix_[i]);
        matrix_[i] = nullptr;
      }
    }
    delete (matrix_);
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

int S21Matrix::get_rows() { return this->rows_; }

int S21Matrix::get_cols() { return this->cols_; }

void S21Matrix::set_value(int rows, int cols, double num) {
  if (rows >= this->rows_ || cols >= this->cols_ || rows < 0 || cols < 0) {
    throw out_of_range("ERROR! Index is outside the matrix");
  }
  matrix_[rows][cols] = num;
}

double S21Matrix::get_value(int rows, int cols) {
  if (rows >= this->rows_ || cols >= this->cols_ || rows < 0 || cols < 0) {
    throw out_of_range("ERROR! Index is outside the matrix");
  }
  return matrix_[rows][cols];
}

void S21Matrix::set_rows(int rows) {
  if (rows <= 0) {
    throw out_of_range("ERROR! Value is outside the matrix");
  }
  if (rows != rows_) {
    S21Matrix tmp(rows, cols_);
    for (int i = 0; i < min(rows, rows_); i++) {
      for (int j = 0; j < cols_; j++) {
        tmp.matrix_[i][j] = this->matrix_[i][j];
      }
    }
    *this = move(tmp);
  }
}

void S21Matrix::set_cols(int cols) {
  if (cols <= 0) {
    throw out_of_range("ERROR! Value is outside the matrix");
  }
  if (cols != cols_) {
    S21Matrix tmp(rows_, cols);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < min(cols, cols_); j++) {
        tmp.matrix_[i][j] = this->matrix_[i][j];
      }
    }
    *this = move(tmp);
  }
}
