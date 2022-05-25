#include <iostream>
#include <vector>

template<typename T>
class Matrix {
 private:
  std::vector<std::vector<T>> field;

 public:
  Matrix(const std::vector<std::vector<T>> &data) {
      field.reserve(data.size());
      for (size_t i = 0; i < data.size(); ++i) {
          std::vector<T> tmp;
          tmp.reserve(data[0].size());
          for (size_t j = 0; j < data[0].size(); ++j) {
              tmp.push_back(data[i][j]);
          }
          field.push_back(tmp);
      }
  }

  friend std::ostream &operator<<(std::ostream &out, const Matrix &m) {
      for (size_t i = 0; i < m.size().first; ++i) {
          for (size_t j = 0; j < m.size().second; ++j) {
              out << m.field[i][j];
              if (j != m.size().second - 1) {
                  out << "\t";
              }
          }
          if (i != m.size().first - 1) {
              out << "\n";
          }
      }
      return out;
  }

  const std::pair<size_t, size_t> size() const {
      return std::make_pair(field.size(), field[0].size());
  }

  Matrix &operator+=(const Matrix &other) {
      for (size_t i = 0; i < this->size().first; ++i) {
          for (size_t j = 0; j < this->size().second; ++j) {
              this->field[i][j] += other.field[i][j];
          }
      }
      return *this;
  }

  Matrix operator+(const Matrix &other) const {
      Matrix tmp(*this);
      tmp += other;
      return tmp;
  }

  template<typename numeric>
  Matrix &operator*=(const numeric &scalar) {
      for (size_t i = 0; i < this->size().first; ++i) {
          for (size_t j = 0; j < this->size().second; ++j) {
              this->field[i][j] *= scalar;
          }
      }
      return *this;
  }

  template<typename numeric>
  Matrix operator*(const numeric &scalar) const {
      Matrix tmp(*this);
      tmp *= scalar;
      return tmp;
  }

  Matrix &transpose() {
      Matrix tmp(*this);
      field.resize(tmp.field[0].size());
      for (size_t i = 0; i < field.size(); ++i) {
          field[i].resize(tmp.field.size());
          for (size_t j = 0; j < field[0].size(); ++j) {
              field[i][j] = tmp.field[j][i];
          }
      }
      return *this;
  }

  Matrix transposed() const {
      Matrix tmp(*this);
      tmp.field.resize(field[0].size());
      for (size_t i = 0; i < tmp.field.size(); ++i) {
          tmp.field[i].resize(field.size());
          for (size_t j = 0; j < tmp.field[0].size(); ++j) {
              tmp.field[i][j] = field[j][i];
          }
      }
      return tmp;
  }

  Matrix &operator*=(const Matrix &other) {
      Matrix tmp(*this);
      for (size_t i = 0; i < tmp.field.size(); ++i) {
          field[i].resize(other.field[0].size());
          std::vector<T> cash(field[i].size(), 0);
          field[i].swap(cash);
          for (size_t j = 0; j < other.field[0].size(); ++j) {
              for (size_t k = 0; k < tmp.field[0].size(); ++k) {
                  field[i][j] += tmp.field[i][k] * other.field[k][j];
              }
          }
      }
      return *this;
  }

  Matrix operator*(const Matrix &other) const {
      Matrix tmp(*this);
      tmp *= other;
      return tmp;
  }
};
