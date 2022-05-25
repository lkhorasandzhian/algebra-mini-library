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
};
