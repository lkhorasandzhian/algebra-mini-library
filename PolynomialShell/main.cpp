#include <iostream>
#include <vector>

template<typename T>
class Polynomial {
 private:
  std::vector<T> polynom;

 public:
  using constIter = typename std::vector<T>::const_iterator;

  Polynomial(const std::vector<T> &coefs) : polynom(coefs) {
      size_t last = polynom.size();
      while (!polynom.empty() && polynom[--last] == T()) {
          polynom.pop_back();
      }
      if (polynom.empty()) {
          polynom.push_back(T());
      }
  }

  Polynomial(T coef = T()) {
      polynom.push_back(coef);
  }

  template<typename Iter>
  Polynomial(const Iter begin, const Iter end) {
      Iter copy = begin;
      while (copy != end) {
          polynom.push_back(*copy);
          copy++;
      }
      size_t last = polynom.size();
      while (!polynom.empty() && polynom[--last] == T()) {
          polynom.pop_back();
      }
      if (polynom.empty()) {
          polynom.push_back(T());
      }
  }

  bool operator==(const Polynomial &other) const {
      if (polynom.size() != other.polynom.size()) {
          return false;
      }
      for (size_t i = 0; i < polynom.size(); ++i) {
          if (polynom[i] != other.polynom[i]) {
              return false;
          }
      }
      return true;
  }

  bool operator==(const T &coef) const {
      Polynomial tmp(coef);
      return (*this) == tmp;
  }

  bool operator!=(const Polynomial &other) const {
      return !((*this) == other);
  }

  bool operator!=(const T &coef) const {
      Polynomial tmp(coef);
      return (*this) != tmp;
  }

  Polynomial operator+(Polynomial other) const {
      Polynomial tmp(polynom);
      if (tmp.polynom.size() < other.polynom.size()) {
          auto count = other.polynom.size() - tmp.polynom.size();
          for (size_t i = 0; i < count; ++i) {
              tmp.polynom.push_back(T());
          }
      } else if (tmp.polynom.size() > other.polynom.size()) {
          auto count = tmp.polynom.size() - other.polynom.size();
          for (size_t i = 0; i < count; ++i) {
              other.polynom.push_back(T());
          }
      }
      for (size_t i = 0; i < tmp.polynom.size(); ++i) {
          tmp.polynom[i] += other.polynom[i];
      }
      size_t last = tmp.polynom.size();
      while (!tmp.polynom.empty() && tmp.polynom[--last] == T()) {
          tmp.polynom.pop_back();
      }
      if (tmp.polynom.empty()) {
          tmp.polynom.push_back(T());
      }
      return tmp;
  }

  Polynomial operator+(T coef) const {
      Polynomial tmp(coef);
      return (*this) + tmp;
  }

  friend Polynomial operator+(T coef, Polynomial current) {
      return current + coef;
  }

  Polynomial &operator+=(Polynomial other) {
      if (polynom.size() < other.polynom.size()) {
          auto count = other.polynom.size() - polynom.size();
          for (size_t i = 0; i < count; ++i) {
              polynom.push_back(T());
          }
      } else if (polynom.size() > other.polynom.size()) {
          auto count = polynom.size() - other.polynom.size();
          for (size_t i = 0; i < count; ++i) {
              other.polynom.push_back(T());
          }
      }
      for (size_t i = 0; i < polynom.size(); ++i) {
          polynom[i] += other.polynom[i];
      }
      size_t last = polynom.size();
      while (!polynom.empty() && polynom[--last] == T()) {
          polynom.pop_back();
      }
      if (polynom.empty()) {
          polynom.push_back(T());
      }
      return *this;
  }

  Polynomial &operator+=(T coef) {
      Polynomial tmp(coef);
      (*this) += tmp;
      return *this;
  }

  Polynomial operator-(Polynomial other) const {
      Polynomial tmp(polynom);
      if (tmp.polynom.size() < other.polynom.size()) {
          auto count = other.polynom.size() - tmp.polynom.size();
          for (size_t i = 0; i < count; ++i) {
              tmp.polynom.push_back(T());
          }
      } else if (tmp.polynom.size() > other.polynom.size()) {
          auto count = tmp.polynom.size() - other.polynom.size();
          for (size_t i = 0; i < count; ++i) {
              other.polynom.push_back(T());
          }
      }
      for (size_t i = 0; i < tmp.polynom.size(); ++i) {
          tmp.polynom[i] -= other.polynom[i];
      }
      size_t last = tmp.polynom.size();
      while (!tmp.polynom.empty() && tmp.polynom[--last] == T()) {
          tmp.polynom.pop_back();
      }
      if (tmp.polynom.empty()) {
          tmp.polynom.push_back(T());
      }
      return tmp;
  }

  Polynomial operator-(T coef) const {
      Polynomial tmp(coef);
      return (*this) - tmp;
  }

  Polynomial operator-() {
      Polynomial tmp(*this);
      for (size_t i = 0; i < tmp.polynom.size(); ++i) {
          tmp.polynom[i] *= -1;
      }
      return tmp;
  }

  friend Polynomial operator-(T coef, Polynomial current) {
      return (-current) + coef;
  }

  Polynomial &operator-=(Polynomial other) {
      if (polynom.size() < other.polynom.size()) {
          auto count = other.polynom.size() - polynom.size();
          for (size_t i = 0; i < count; ++i) {
              polynom.push_back(T());
          }
      } else {
          auto count = polynom.size() - other.polynom.size();
          for (size_t i = 0; i < count; ++i) {
              other.polynom.push_back(T());
          }
      }
      for (size_t i = 0; i < polynom.size(); ++i) {
          polynom[i] -= other.polynom[i];
      }
      size_t last = polynom.size();
      while (!polynom.empty() && polynom[--last] == T()) {
          polynom.pop_back();
      }
      if (polynom.empty()) {
          polynom.push_back(T());
      }
      return *this;
  }

  Polynomial &operator-=(T coef) {
      Polynomial tmp(coef);
      (*this) -= tmp;
      return *this;
  }

  T operator[](size_t index) const {
      return index < polynom.size() && index >= 0 ? polynom[index] : T();
  }

  long long Degree() const {
      if (polynom.size() == 1) {
          if (polynom[0] == T()) {
              return -1;
          }
          return 0;
      }
      return static_cast<int>(polynom.size()) - 1;
  }

  constIter begin() const {
      return polynom.cbegin();
  }

  constIter end() const {
      return polynom.cend();
  }
};
