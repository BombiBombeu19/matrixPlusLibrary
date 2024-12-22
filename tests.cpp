#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(Methods, DefaultConstructor) {
  int value = 3;

  S21Matrix matrix1(value, value);
  S21Matrix matrix2{};

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(Methods, DefaultConstructor2) {
  S21Matrix matrix{};

  EXPECT_EQ(matrix.get_rows(), 3);
}

TEST(Methods, DefaultConstructor3) {
  S21Matrix matrix{};

  EXPECT_EQ(matrix.get_cols(), 3);
}

TEST(Methods, Constructor1) {
  int value = 3;

  S21Matrix matrix(value, value);

  EXPECT_EQ(matrix.get_cols(), 3);
}

TEST(Methods, Constructor2) {
  int rows = 1;
  int cols = 9;

  S21Matrix matrix(rows, cols);

  EXPECT_EQ(matrix.get_rows(), 1);
}

TEST(Methods, Constructor3) {
  EXPECT_THROW(S21Matrix matrix(-1, -9), std::out_of_range);
}

TEST(Methods, CopyConstructor) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, matrix.get_value(i, j));
    }
  }

  S21Matrix result(matrix);

  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(Methods, MoveConstructor) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix(rows, cols);
  S21Matrix copy(matrix);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, matrix.get_value(i, j));
    }
  }

  S21Matrix result(std::move(matrix));

  EXPECT_EQ(matrix.get_cols(), 0);
  EXPECT_EQ(matrix.get_rows(), 0);
  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(Operations, EqMatrix1) {
  int value = rand() % 100 + 1;

  S21Matrix matrix1(value, value);
  S21Matrix matrix2(value, value);

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(Operations, EqMatrix2) {
  S21Matrix matrix1{};
  S21Matrix matrix2{};

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(Operations, EqMatrix3) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols + 1);

  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(Operations, SumMatrix1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix1.set_value(i, j, (double)rand() / 1919 + 0.1);
      matrix2.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, matrix1.get_value(i, j) + matrix2.get_value(i, j));
    }
  }

  matrix1.SumMatrix(matrix2);
  S21Matrix result = matrix1;

  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(Operations, SumMatrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix1.set_value(i, j, 0);
      matrix2.set_value(i, j, 0);
      check.set_value(i, j, matrix1.get_value(i, j) + matrix2.get_value(i, j));
    }
  }

  matrix1.SumMatrix(matrix2);
  S21Matrix result = matrix1;

  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(Operations, SumMatrix3) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix1.set_value(i, j, (double)rand() / 1919 + 0.1);
      matrix2.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, matrix1.get_value(i, j) + matrix2.get_value(i, j));
    }
  }
  check.set_value(1, 1, 9191);

  matrix1.SumMatrix(matrix2);
  S21Matrix result = matrix1;

  EXPECT_FALSE(result.EqMatrix(check));
}

TEST(Operations, SumMatrix4) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols + 1);

  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}

TEST(Operations, SubMatrix1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix1.set_value(i, j, (double)rand() / 1919 + 0.1);
      matrix2.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, matrix1.get_value(i, j) - matrix2.get_value(i, j));
    }
  }

  matrix1.SubMatrix(matrix2);
  S21Matrix result = matrix1;

  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(Operations, SubMatrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix1.set_value(i, j, 0);
      matrix2.set_value(i, j, 0);
      check.set_value(i, j, matrix1.get_value(i, j) - matrix2.get_value(i, j));
    }
  }

  matrix1.SubMatrix(matrix2);
  S21Matrix result = matrix1;

  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(Operations, SubMatrix3) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix1.set_value(i, j, (double)rand() / 1919 + 0.1);
      matrix2.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, matrix1.get_value(i, j) - matrix2.get_value(i, j));
    }
  }
  check.set_value(1, 1, 9191);

  matrix1.SubMatrix(matrix2);
  S21Matrix result = matrix1;

  EXPECT_FALSE(result.EqMatrix(check));
}

TEST(Operations, SubMatrix4) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols + 1);

  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}

TEST(Operations, MulNumber1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  double num = (double)rand() / 1919 + 0.1;

  S21Matrix matrix(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, matrix.get_value(i, j) * num);
    }
  }

  matrix.MulNumber(num);
  S21Matrix result = matrix;

  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(Operations, MulNumber2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  double num = (double)rand() / 1919 + 0.1;

  S21Matrix matrix(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, 0);
    }
  }

  matrix.MulNumber(num);
  S21Matrix result = matrix;

  EXPECT_FALSE(result.EqMatrix(check));
}

TEST(Operations, MulMatrix1) {
  int rows = rand() % 100 + 1;
  int rows_cols = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, rows_cols);
  S21Matrix matrix2(rows_cols, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows_cols; j++) {
      matrix1.set_value(i, j, (double)rand() / 1919 + 0.1);
    }
  }

  for (int i = 0; i < rows_cols; i++) {
    for (int j = 0; j < cols; j++) {
      matrix2.set_value(i, j, (double)rand() / 1919 + 0.1);
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double sum = 0.0;
      for (int k = 0; k < rows_cols; k++) {
        sum += matrix1.get_value(i, k) * matrix2.get_value(k, j);
      }
      check.set_value(i, j, sum);
    }
  }

  matrix1.MulMatrix(matrix2);
  S21Matrix result = matrix1;

  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(Operations, MulMatrix2) {
  int rows = rand() % 100 + 1;
  int rows_cols = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, rows_cols);
  S21Matrix matrix2(rows_cols, rows);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows_cols; j++) {
      matrix1.set_value(i, j, (double)rand() / 1919 + 0.1);
    }
  }

  for (int i = 0; i < rows_cols; i++) {
    for (int j = 0; j < cols; j++) {
      matrix2.set_value(i, j, (double)rand() / 1919 + 0.1);
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      for (int k = 0; k < rows_cols; k++) {
        check.set_value(i, j,
                        matrix1.get_value(i, k) * matrix2.get_value(k, j));
      }
    }
  }
  check.set_value(1, 1, 0);

  matrix1.MulMatrix(matrix2);
  S21Matrix result = matrix1;

  EXPECT_FALSE(result.EqMatrix(check));
}

TEST(Operations, MulMatrix3) {
  S21Matrix matrix1(3, 4);
  S21Matrix matrix2(5, 6);

  EXPECT_THROW(matrix1.MulMatrix(matrix2), std::invalid_argument);
}

TEST(Operations, Transpose1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix(rows, cols);
  S21Matrix check(cols, rows);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double value = (double)rand() / 1919 + 0.1;
      matrix.set_value(i, j, value);
      check.set_value(j, i, value);
    }
  }

  S21Matrix result = matrix.Transpose();

  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(Operations, Transpose2) {
  S21Matrix matrix{};
  S21Matrix check{};

  for (int i = 0; i < matrix.get_rows(); i++) {
    for (int j = 0; j < matrix.get_cols(); j++) {
      matrix.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, matrix.get_value(j, i));
    }
  }

  matrix.set_value(0, 0, 1);
  matrix.set_value(0, 1, 5);
  matrix.set_value(0, 2, 7);
  matrix.set_value(1, 0, 1);
  matrix.set_value(1, 1, 4.3);
  matrix.set_value(1, 2, 4);
  matrix.set_value(2, 0, 5);
  matrix.set_value(2, 1, 1);
  matrix.set_value(2, 2, 6);

  check.set_value(0, 0, 1);
  check.set_value(0, 1, 1);
  check.set_value(0, 2, 5);
  check.set_value(1, 0, 5);
  check.set_value(1, 1, 4.3);
  check.set_value(1, 2, 1);
  check.set_value(2, 0, 7);
  check.set_value(2, 1, 4);
  check.set_value(2, 2, 6);

  S21Matrix result = matrix.Transpose();

  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(Operations, Transpose3) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix(rows, cols);
  S21Matrix check(cols, rows);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double value = (double)rand() / 1919 + 0.1;
      matrix.set_value(i, j, value);
      check.set_value(j, i, value);
    }
  }

  check.set_value(1, 1, 9191);

  S21Matrix result = matrix.Transpose();

  EXPECT_FALSE(result.EqMatrix(check));
}

TEST(Operations, Determinant1) {
  S21Matrix matrix{};
  double check = -51.7;

  matrix.set_value(0, 0, 1);
  matrix.set_value(0, 1, 5);
  matrix.set_value(0, 2, 7);
  matrix.set_value(1, 0, 1);
  matrix.set_value(1, 1, 4.3);
  matrix.set_value(1, 2, 4);
  matrix.set_value(2, 0, 5);
  matrix.set_value(2, 1, 1);
  matrix.set_value(2, 2, 6);

  double result = matrix.Determinant();

  EXPECT_NEAR(check, result, 1e-6);
}

TEST(Operations, Determinant2) {
  int num = 1;
  S21Matrix matrix(num, num);
  double check = 0;

  matrix.set_value(0, 0, 0);

  double result = matrix.Determinant();

  EXPECT_EQ(check, result);
}

TEST(Operations, Determinant3) {
  int num = 2;
  S21Matrix matrix(num, num);
  double check = 6.908;

  matrix.set_value(0, 0, 0.56);
  matrix.set_value(0, 1, -4.5);
  matrix.set_value(1, 0, 1);
  matrix.set_value(1, 1, 4.3);

  double result = matrix.Determinant();

  EXPECT_NEAR(check, result, 1e-6);
}

TEST(Operations, Determinant4) {
  S21Matrix matrix(1, 9);

  EXPECT_THROW(matrix.Determinant(), std::invalid_argument);
}

TEST(Operations, InverseMatrix1) {
  int num = 1;
  S21Matrix matrix(num, num);
  S21Matrix check(num, num);

  matrix.set_value(0, 0, 0.5);
  check.set_value(0, 0, 2);

  S21Matrix result = matrix.InverseMatrix();

  EXPECT_TRUE(check.EqMatrix(result));
}

TEST(Operations, InverseMatrix2) {
  int num = 2;
  S21Matrix matrix(num, num);
  S21Matrix check(num, num);

  matrix.set_value(0, 0, 2);
  matrix.set_value(0, 1, 3);
  matrix.set_value(1, 0, 1);
  matrix.set_value(1, 1, 4);

  check.set_value(0, 0, 0.8);
  check.set_value(0, 1, -0.6);
  check.set_value(1, 0, -0.2);
  check.set_value(1, 1, 0.4);

  S21Matrix result = matrix.InverseMatrix();

  EXPECT_TRUE(check.EqMatrix(result));
}

TEST(Operations, InverseMatrix3) {
  int num = 2;
  S21Matrix matrix(num, num);
  S21Matrix check(num, num);

  matrix.set_value(0, 0, 2);
  matrix.set_value(0, 1, 3);
  matrix.set_value(1, 0, 1);
  matrix.set_value(1, 1, 4);

  check.set_value(0, 0, 0.8);
  check.set_value(0, 1, -0.6);
  check.set_value(1, 0, -0.2);
  check.set_value(1, 1, 19);

  S21Matrix result = matrix.InverseMatrix();

  EXPECT_FALSE(check.EqMatrix(result));
}

TEST(Operations, InverseMatrix4) {
  int num = 2;
  S21Matrix matrix(num, num);

  matrix.set_value(0, 0, 1);
  matrix.set_value(0, 1, 1);
  matrix.set_value(1, 0, 1);
  matrix.set_value(1, 1, 1);

  EXPECT_THROW(matrix.InverseMatrix(), std::invalid_argument);
}

TEST(Operations, CalcComplements1) {
  S21Matrix matrix{};
  S21Matrix check{};

  matrix.set_value(0, 0, 1);
  matrix.set_value(0, 1, 2);
  matrix.set_value(0, 2, 3);
  matrix.set_value(1, 0, 0);
  matrix.set_value(1, 1, 4);
  matrix.set_value(1, 2, 2);
  matrix.set_value(2, 0, 5);
  matrix.set_value(2, 1, 2);
  matrix.set_value(2, 2, 1);

  check.set_value(0, 0, 0);
  check.set_value(0, 1, 10);
  check.set_value(0, 2, -20);
  check.set_value(1, 0, 4);
  check.set_value(1, 1, -14);
  check.set_value(1, 2, 8);
  check.set_value(2, 0, -8);
  check.set_value(2, 1, -2);
  check.set_value(2, 2, 4);

  S21Matrix result = matrix.CalcComplements();

  EXPECT_TRUE(check.EqMatrix(result));
}

TEST(Operations, CalcComplements2) {
  int num = 2;
  S21Matrix matrix(num, num);
  S21Matrix check(num, num);

  matrix.set_value(0, 0, -4);
  matrix.set_value(0, 1, 5.63);
  matrix.set_value(1, 0, 7.651);
  matrix.set_value(1, 1, 3);

  check.set_value(0, 0, 3);
  check.set_value(0, 1, -7.651);
  check.set_value(1, 0, -5.63);
  check.set_value(1, 1, -4);

  S21Matrix result = matrix.CalcComplements();

  EXPECT_TRUE(check.EqMatrix(result));
}

TEST(Operations, CalcComplements3) {
  int num = 2;
  S21Matrix matrix(num, num);
  S21Matrix check(num, num);

  matrix.set_value(0, 0, -4);
  matrix.set_value(0, 1, 5.63);
  matrix.set_value(1, 0, 7.651);
  matrix.set_value(1, 1, 3);

  check.set_value(0, 0, 3);
  check.set_value(0, 1, -7.651);
  check.set_value(1, 0, -5.63);
  check.set_value(1, 1, 19);

  S21Matrix result = matrix.CalcComplements();

  EXPECT_FALSE(check.EqMatrix(result));
}

TEST(Operations, CalcComplements4) {
  S21Matrix matrix(1, 9);

  EXPECT_THROW(matrix.CalcComplements(), std::invalid_argument);
}

TEST(Operators, Equals) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, matrix.get_value(i, j));
    }
  }

  S21Matrix result = matrix;

  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(Operators, Plus1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix1.set_value(i, j, (double)rand() / 1919 + 0.1);
      matrix2.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, matrix1.get_value(i, j) + matrix2.get_value(i, j));
    }
  }

  S21Matrix result = matrix1 + matrix2;

  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(Operators, Plus2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix1.set_value(i, j, 0);
      matrix2.set_value(i, j, 0);
      check.set_value(i, j, matrix1.get_value(i, j) + matrix2.get_value(i, j));
    }
  }

  S21Matrix result = matrix1 + matrix2;

  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(Operators, Plus3) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix1.set_value(i, j, (double)rand() / 1919 + 0.1);
      matrix2.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, matrix1.get_value(i, j) + matrix2.get_value(i, j));
    }
  }
  check.set_value(1, 1, 9191);

  S21Matrix result = matrix1 + matrix2;

  EXPECT_FALSE(result.EqMatrix(check));
}

TEST(Operators, Plus4) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols + 1);

  EXPECT_THROW(matrix1 + matrix2, std::invalid_argument);
}

TEST(Operators, Minus1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix1.set_value(i, j, (double)rand() / 1919 + 0.1);
      matrix2.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, matrix1.get_value(i, j) - matrix2.get_value(i, j));
    }
  }

  S21Matrix result = matrix1 - matrix2;

  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(Operators, Minus2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix1.set_value(i, j, 0);
      matrix2.set_value(i, j, 0);
      check.set_value(i, j, matrix1.get_value(i, j) - matrix2.get_value(i, j));
    }
  }

  S21Matrix result = matrix1 - matrix2;

  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(Operators, Minus3) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix1.set_value(i, j, (double)rand() / 1919 + 0.1);
      matrix2.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, matrix1.get_value(i, j) - matrix2.get_value(i, j));
    }
  }
  check.set_value(1, 1, 9191);

  S21Matrix result = matrix1 - matrix2;

  EXPECT_FALSE(result.EqMatrix(check));
}

TEST(Operators, Minus4) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols + 1);

  EXPECT_THROW(matrix1 - matrix2, std::invalid_argument);
}

TEST(Operators, Assignment1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix1.set_value(i, j, (double)rand() / 1919 + 0.1);
      matrix2.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, matrix1.get_value(i, j) + matrix2.get_value(i, j));
    }
  }

  matrix1 += matrix2;

  EXPECT_TRUE(matrix1.EqMatrix(check));
}

TEST(Operators, Assignment2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols + 1);

  EXPECT_THROW(matrix1 += matrix2, std::invalid_argument);
}

TEST(Operators, SubtractAND1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix1.set_value(i, j, (double)rand() / 1919 + 0.1);
      matrix2.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, matrix1.get_value(i, j) - matrix2.get_value(i, j));
    }
  }

  matrix1 -= matrix2;

  EXPECT_TRUE(matrix1.EqMatrix(check));
}

TEST(Operators, SubtractAND2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols + 1);

  EXPECT_THROW(matrix1 -= matrix2, std::invalid_argument);
}

TEST(Operators, Сomparison1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols);

  EXPECT_EQ(matrix1.EqMatrix(matrix2), matrix1 == matrix2);
}

TEST(Operators, Сomparison2) {
  S21Matrix matrix1{};
  S21Matrix matrix2{};

  EXPECT_EQ(matrix1.EqMatrix(matrix2), matrix1 == matrix2);
}

TEST(Operators, Сomparison3) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, cols);
  S21Matrix matrix2(rows, cols + 1);

  EXPECT_EQ(matrix1.EqMatrix(matrix2), matrix1 == matrix2);
}

TEST(Operators, AsteriskNum1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  double num = (double)rand() / 1919 + 0.1;

  S21Matrix matrix(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, matrix.get_value(i, j) * num);
    }
  }

  S21Matrix result = matrix * num;

  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(Operators, AsteriskNum2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  double num = (double)rand() / 1919 + 0.1;

  S21Matrix matrix(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, 0);
    }
  }

  S21Matrix result = matrix * num;

  EXPECT_FALSE(result.EqMatrix(check));
}

TEST(Operations, AsteriskMatrix1) {
  int rows = rand() % 100 + 1;
  int rows_cols = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, rows_cols);
  S21Matrix matrix2(rows_cols, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows_cols; j++) {
      matrix1.set_value(i, j, (double)rand() / 1919 + 0.1);
    }
  }

  for (int i = 0; i < rows_cols; i++) {
    for (int j = 0; j < cols; j++) {
      matrix2.set_value(i, j, (double)rand() / 1919 + 0.1);
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double sum = 0.0;
      for (int k = 0; k < rows_cols; k++) {
        sum += matrix1.get_value(i, k) * matrix2.get_value(k, j);
      }
      check.set_value(i, j, sum);
    }
  }

  S21Matrix result = matrix1 * matrix2;

  EXPECT_TRUE(result.EqMatrix(check));
}

TEST(Operations, AsteriskMatrix2) {
  S21Matrix matrix1(3, 4);
  S21Matrix matrix2(5, 6);

  EXPECT_THROW(matrix1 * matrix2, std::invalid_argument);
}

TEST(Operators, MultiplyANDNum1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  double num = (double)rand() / 1919 + 0.1;

  S21Matrix matrix(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, matrix.get_value(i, j) * num);
    }
  }

  matrix *= num;

  EXPECT_TRUE(matrix.EqMatrix(check));
}

TEST(Operators, MultiplyANDNum2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  double num = (double)rand() / 1919 + 0.1;

  S21Matrix matrix(rows, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix.set_value(i, j, (double)rand() / 1919 + 0.1);
      check.set_value(i, j, 0);
    }
  }

  matrix *= num;

  EXPECT_FALSE(matrix.EqMatrix(check));
}

TEST(Operations, MultiplyANDMatrix1) {
  int rows = rand() % 100 + 1;
  int rows_cols = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, rows_cols);
  S21Matrix matrix2(rows_cols, cols);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows_cols; j++) {
      matrix1.set_value(i, j, (double)rand() / 1919 + 0.1);
    }
  }

  for (int i = 0; i < rows_cols; i++) {
    for (int j = 0; j < cols; j++) {
      matrix2.set_value(i, j, (double)rand() / 1919 + 0.1);
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double sum = 0.0;
      for (int k = 0; k < rows_cols; k++) {
        sum += matrix1.get_value(i, k) * matrix2.get_value(k, j);
      }
      check.set_value(i, j, sum);
    }
  }

  matrix1 *= matrix2;

  EXPECT_TRUE(matrix1.EqMatrix(check));
}

TEST(Operations, MultiplyANDMatrix2) {
  int rows = rand() % 100 + 1;
  int rows_cols = rand() % 100 + 1;
  int cols = rand() % 100 + 1;

  S21Matrix matrix1(rows, rows_cols);
  S21Matrix matrix2(rows_cols, rows);
  S21Matrix check(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows_cols; j++) {
      matrix1.set_value(i, j, (double)rand() / 1919 + 0.1);
    }
  }

  for (int i = 0; i < rows_cols; i++) {
    for (int j = 0; j < cols; j++) {
      matrix2.set_value(i, j, (double)rand() / 1919 + 0.1);
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      for (int k = 0; k < rows_cols; k++) {
        check.set_value(i, j,
                        matrix1.get_value(i, k) * matrix2.get_value(k, j));
      }
    }
  }
  check.set_value(1, 1, 0);

  matrix1 *= matrix2;

  EXPECT_FALSE(matrix1.EqMatrix(check));
}

TEST(Operations, MultiplyANDMatrix3) {
  S21Matrix matrix1(3, 4);
  S21Matrix matrix2(5, 6);

  EXPECT_THROW(matrix1 *= matrix2, std::invalid_argument);
}

TEST(Operators, Brackets1) {
  S21Matrix matrix{};

  EXPECT_EQ(matrix(1, 1), 0);
}

TEST(Operators, Brackets2) {
  S21Matrix matrix{};

  matrix.set_value(1, 1, 9);

  EXPECT_EQ(matrix(1, 1), 9);
}

TEST(Operators, Brackets3) {
  S21Matrix matrix{};

  EXPECT_THROW(matrix(1, 9), std::out_of_range);
}

int main(int argc, char *argv[]) {
  // Передаем параметры командной строки в gtest
  testing::InitGoogleTest(&argc, argv);

  // Запускаем все тесты
  return RUN_ALL_TESTS();
}
