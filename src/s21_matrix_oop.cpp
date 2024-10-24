#include "s21_matrix_oop.h"

//-------------Конструкторы-------------------

/**
 * @brief Базовый конструктор
 */
S21Matrix::S21Matrix() : S21Matrix(3, 3) {}

/**
 * @brief Параметризованный конструктор
 * @param rows Количество строк в новой матрице
 * @param cols Количество столбцов в новой матрице
 */
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) not_exist();
  allocate_mem();
  for (int r = 0; r < rows_; r++) {
    for (int c = 0; c < cols_; c++) {
      matrix_[r][c] = 0;
    }
  }
}

/**
 * @brief Конструктор копирования
 * @param other Матрица, на основе которой будет производится копирование в
 * текущий объект
 */
S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  allocate_mem();
  copy_matrix(other);
}

/**
 * @brief Конструктор переноса
 * @param other Матрица, на основе которой будет производится копирование в
 * текущий объект. Далее эта матрица удалится
 */
S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = other.cols_ = 0;
}

/**
 * @brief Деструктор текущей матрицы
 */
S21Matrix::~S21Matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
  }
}

/**
 * @brief accessor: Взятие значения строк (из private)
 * @return Количество строк в матрице
 */
int S21Matrix::acc_rows() { return rows_; }

/**
 * @brief accessor: Взятие значения столбцов(из private)
 * @return Количество столбцов в матрице
 */
int S21Matrix::acc_cols() { return cols_; }

/**
 * @brief mutator: Изменение количества строк и столбцов в текущей матрице
 * @param rows Количество строк в новой матрице, в которую будет "мутировать"
 * текущая
 * @param cols Количество столбцов в новой матрице, в которую будет "мутировать"
 * текущая
 */
void S21Matrix::mutator(int rows, int cols) {
  if (rows <= 0 && cols <= 0) not_exist();
  S21Matrix temp(rows, cols);
  for (int m = 0; m < rows; m++) {
    for (int n = 0; n < cols; n++) {
      if (m < rows_ && n < cols_) {
        temp.matrix_[m][n] = this->matrix_[m][n];
      } else {
        temp.matrix_[m][n] = 0;
      }
    }
  }
  *this = temp;
}

//-------------Операции над матрицами-------------------

/**
 * @brief Проверяет матрицы на равенство между собой
 * @param other Другая матрица, с которой сравнивается текущая
 * @return 1 - YES (матрицы равны), 0 - NO (матрицы не равны)
 */
bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) not_same_size();
  int code = YES;
  for (int m = 0; m < rows_ && code != NO; m++) {
    for (int n = 0; n < cols_ && code != NO; n++) {
      if (fabs(this->matrix_[m][n] - other.matrix_[m][n]) > SCI_NOT) code = NO;
    }
  }
  return code;
}

/**
 * @brief Прибавляет вторую матрицу к текущей
 * @param other Вторая матрица - слагаемое
 */
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) not_same_size();
  for (int m = 0; m < rows_; m++) {
    for (int n = 0; n < cols_; n++) {
      matrix_[m][n] += other.matrix_[m][n];
    }
  }
}

/**
 * @brief Вычитает из текущей матрицы другую
 * @param other Матрица - вычитаемая
 *
 */
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) not_same_size();
  for (int m = 0; m < rows_; m++) {
    for (int n = 0; n < cols_; n++) {
      matrix_[m][n] -= other.matrix_[m][n];
    }
  }
}

/**
 * @brief Умножает текущую матрицу на число
 * @param num Вещественное число - второй множитель
 */
void S21Matrix::MulNumber(const double num) {
  for (int m = 0; m < rows_; m++) {
    for (int n = 0; n < cols_; n++) {
      matrix_[m][n] *= num;
    }
  }
}

/**
 * @brief Умножает текущую матрицу на вторую
 * @param other Вторая матрица - множитель
 */
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) not_equal();
  S21Matrix res(rows_, other.cols_);
  for (int m = 0; m < rows_; m++) {
    for (int n = 0; n < other.cols_; n++) {
      for (int k = 0; k < cols_; k++) {
        res.matrix_[m][n] += matrix_[m][k] * other.matrix_[k][n];
      }
    }
  }
  *this = res;
}

/**
 * @brief Создает новую транспонированную матрицу из текущей
 * @return Итоговая транспонированная матрица
 */
S21Matrix S21Matrix::Transpose() {
  S21Matrix temp(cols_, rows_);
  for (int m = 0; m < temp.rows_; m++) {
    for (int n = 0; n < temp.cols_; n++) {
      temp.matrix_[m][n] = matrix_[n][m];
    }
  }
  return temp;
}

/**
 * @brief Вычисляет определитель текущей матрицы
 * @return Вещественное число - определитель
 */
double S21Matrix::Determinant() {
  if (rows_ != cols_) not_square();
  int is_nul_det = 1;
  double result = 1;
  for (int m = 0; m < rows_ && is_nul_det == 1; m++) {
    if (matrix_[m][0] != 0) is_nul_det = 0;
  }
  if (!is_nul_det && rows_ > 2) {
    S21Matrix copy(*this);
    copy.TriangMatrix(result);
    if (result != 0) {
      for (int mult = 0; mult < copy.rows_; mult++) {
        result *= copy.matrix_[mult][mult];
      }
    }
  } else if (!is_nul_det && rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else if (!is_nul_det && rows_ == 1) {
    result = matrix_[0][0];
  } else
    result = 0;
  if (result == 0) result = fabs(result);
  return result;
}

/**
 * @brief Зануляет нижнюю левую половину от главной диагонали
 * @param result Результирующее значение детерминанта
 */
void S21Matrix::TriangMatrix(double& result) {
  for (int g = 0; g < (rows_ - 1) && result != 0; g++) {
    if (!FinfDiagNullElem(g)) {
      for (int r = g + 1; r < rows_; r++) {
        double k = matrix_[r][g] / matrix_[g][g];
        if (k != 0) {
          for (int c = g; c < cols_; c++) {
            matrix_[r][c] -= matrix_[g][c] * k;
          }
        }
      }
    } else
      result = 0;
  }
}

/**
 * @brief Ищет нулевой элемент на главной диагонали
 * Если нашел, то пытается поменять строчку на строку,
 * где нет нулевого элемента со сменой знака
 * @param g столбец, по которому смотрим на главную диагональ
 * @return 0 - ОК (если не было 0 на главной диагонали или замена прошла
 * успешно), 1 - ERROR (не нашли строку ненулевую, не с чем поменять местами)
 */
bool S21Matrix::FinfDiagNullElem(int g) {
  bool code = OK;
  if (matrix_[g][g] == 0) {
    int flag = 1;
    for (int r = g + 1; r < rows_; r++) {
      if (matrix_[r][g] != 0) {
        flag = 0;
        S21Matrix temp(*this);
        for (int c = 0; c < cols_; c++) {
          temp.matrix_[g][c] = (-1) * matrix_[r][c];
          matrix_[r][c] = matrix_[g][c];
          matrix_[g][c] = temp.matrix_[g][c];
        }
      }
    }
    if (flag) code = ERROR;
  }
  return code;
}

/**
 * @brief Вычисляет матрицу алгебраических дополнений текущей матрицы и
 * возвращает ее
 */
S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) not_square();
  S21Matrix result(*this);
  if (rows_ > 1) {
    S21Matrix mini_matrix(rows_ - 1, cols_ - 1);
    for (int r = 0; r < result.rows_; r++) {
      for (int c = 0; c < result.cols_; c++) {
        mini_matrix = CreateMiniMatrix(r, c);
        result.matrix_[r][c] = mini_matrix.Determinant();
        result.matrix_[r][c] *= pow(-1, r + c);
      }
    }
  } else if (rows_ == 1)
    result.matrix_[0][0] = 1;
  return result;
}

/**
 * @brief Создает мини-матрицу из текущей путем вычеркивания строк и столбцов
 * для расчета матрицы алгебраических дополнений
 * @param r Вычеркиваемая строка текущей матрицы
 * @param c Вычеркиваемый столбец текущей матрицы
 */
S21Matrix S21Matrix::CreateMiniMatrix(int r, int c) {
  S21Matrix mini(rows_ - 1, cols_ - 1);
  int min_r = -1, min_c = -1;
  for (int rowM = 0; rowM < rows_; rowM++) {
    if (rowM != r) {
      min_r++;
      for (int columnM = 0; columnM < cols_; columnM++) {
        if (columnM != c) {
          min_c++;
          mini.matrix_[min_r][min_c] = matrix_[rowM][columnM];
        }
      }
      min_c = -1;
    }
  }
  return mini;
}

/**
 * @brief Вычисляет и возвращает обратную матрицу на основе текущей
 */
S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (det == 0) null_determinant();
  S21Matrix res(rows_, cols_);
  if (rows_ > 1) {
    S21Matrix calc_comp(rows_, cols_), trans(cols_, rows_);
    calc_comp = CalcComplements();
    trans = calc_comp.Transpose();
    trans.MulNumber(1 / det);
    res = trans;
  } else if (rows_ == 1) {
    res.mutator(1, 1);
    res.matrix_[0][0] = 1 / matrix_[0][0];
  }
  return res;
}

//-------------Перегрузки-------------------

/**
 * @brief Перегрузка (==) Проверка на равенство матриц (EqMatrix)
 * @param other Ссылка на сравниваемую матрицу
 * @return 1 - матрицы равны, 0 - матрицы не равны
 */
bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

/**
 * @brief Перегрузка (=) присвоение матрице значений другой матрицы
 * @param other Матрица, значение которой хотим присвоить
 * @return Матрица, которой присвоили значение
 */
S21Matrix S21Matrix::operator=(const S21Matrix& other) {
  this->~S21Matrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  allocate_mem();
  copy_matrix(other);
  return *this;
}

/**
 * @brief Перегрузка (+) cложение двух матриц
 * @param other Прибавляемая матрица, второе слагаемое
 * @return Матрица, содержащая результат суммы
 */
S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

/**
 * @brief Перегрузка (-) вычитание одной матрицы из другой
 * @param other Вычитаемая матрица
 * @return Матрица, содержащая результат разности
 */
S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

/**
 * @brief Перегрузка (*) Присвоение умножения (MulMatrix) (объект на объект)
 * @param other Второй множитель
 * @return Матрица, содержащая результат произведения матриц
 */
S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

/**
 * @brief Перегрузка (*), дружественные операторы. Присвоение умножения
 * (MulNumber) (объект на число)
 * @param other Матрица - первый множитель
 * @param num Число - второй множитель
 * @return Матрица, содержащая результат произведения матрицы на число
 */
S21Matrix operator*(const S21Matrix& other, double num) {
  S21Matrix res(other);
  res.MulNumber(num);
  return res;
}

/**
 * @brief Перегрузка (*), дружественные операторы. Присвоение умножения
 * (MulNumber) (число на объект)
 * @param num Число - первый множитель
 * @param other Матрица - второй множитель
 * @return Матрица, содержащая результат произведения числа на матрицу
 */
S21Matrix operator*(double num, const S21Matrix& other) {
  S21Matrix res(other);
  res.MulNumber(num);
  return res;
}

/**
 * @brief Перегрузка (+=) Присвоение сложения (SumMatrix)
 * @param other Вторая матрица - слагаемое
 * @return Ссылка на текущую матрицу, уже содержащую результат сложения
 */
S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

/**
 * @brief Перегрузка (-=) Присвоение разности (SubMatrix)
 * @param other Вторая матрица - вычитаемое
 * @return Ссылка на текущую матрицу, уже содержащую результат разности
 */
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

/**
 * @brief Перегрузка (*=) Присвоение умножения MulNumber
 * @param other Вещественной число - второй множитель
 * @return Ссылка на текущую матрицу, уже содержащую результат произведения
 */
S21Matrix& S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

/**
 * @brief Перегрузка (*=) Присвоение умножения MulMatrix
 * @param other Вторая матрица - множитель
 * @return Ссылка на текущую матрицу, уже содержащую результат произведения
 */
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

/**
 * @brief Перегрузка (int i, int j) Индексация по элементам матрицы (строка,
 * колонка)
 * @param rows Требуемая строчка в матрице
 * @param cols Требуемый столбец в матрице
 * @return Число, содержащееся в матрице по искомой строке и столбцу
 */
double& S21Matrix::operator()(int rows, int cols) {
  if (rows >= rows_ || cols >= cols_ || rows < 0 || cols < 0) not_range();
  return matrix_[rows][cols];
}

/**
 * @brief Выделение памяти на матрицу
 */
void S21Matrix::allocate_mem() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
}

/**
 * @brief Заполнение матрицы с консоли
 */
void S21Matrix::fill_matrix() {
  for (int m = 0; m < rows_; m++) {
    for (int n = 0; n < cols_; n++) {
      cin >> this->matrix_[m][n];
    }
  }
}

/**
 * @brief Вывод-печать матрицы в консоль
 */
void S21Matrix::print_matrix() {
  for (int m = 0; m < rows_; m++) {
    for (int n = 0; n < cols_; n++) {
      cout << this->matrix_[m][n] << " ";
    }
    cout << endl;
  }
}

/**
 * @brief Заполняет пошагово (step) матрицу числами от введенного старта и далее
 * числа +1
 * @param fill_start Число, с которого начинем заполнять матрицу
 * @param step Шаг заполнения матрицы (плюсуемое значение)
 */
void S21Matrix::sequent_filling(double fill_start, double step) {
  for (int m = 0; m < rows_; m++) {
    for (int n = 0; n < cols_; n++) {
      this->matrix_[m][n] =
          fill_start;  //тут надо как-то дописать саму передаваемую матрицу
      fill_start += step;
    }
  }
}

/**
 * @brief Копирует в новую матрицу, старую матрицу
 * @param old Старая матрица, которую копируем
 */
void S21Matrix::copy_matrix(const S21Matrix& old) {
  for (int m = 0; m < this->rows_; m++) {
    for (int n = 0; n < this->cols_; n++) {
      this->matrix_[m][n] = old.matrix_[m][n];
    }
  }
}

void S21Matrix::not_square() {
  throw std::invalid_argument("Матрица не является квадратной");
}

void S21Matrix::not_exist() {
  throw std::invalid_argument("Матрица не существует");
}

void S21Matrix::not_same_size() {
  throw std::invalid_argument("Матрицы должны иметь одинаковую размерность");
}

void S21Matrix::not_range() {
  throw std::out_of_range("Индекс за пределами матрицы");
}

void S21Matrix::not_equal() {
  throw std::invalid_argument(
      "Число столбцов первой матрицы не равно числу строк второй матрицы");
}

void S21Matrix::null_determinant() {
  throw std::invalid_argument("Определитель матрицы равен 0");
}