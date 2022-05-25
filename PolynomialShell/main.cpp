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

  Polynomial operator*(Polynomial other) const {
      Polynomial res((T()));
      res.polynom.resize(polynom.size() * other.polynom.size());
      for (size_t i = 0; i < polynom.size(); ++i) {
          for (size_t j = 0; j < other.polynom.size(); ++j) {
              res.polynom[i + j] += polynom[i] * other.polynom[j];
          }
      }
      size_t last = res.polynom.size();
      while (!res.polynom.empty() && res.polynom[--last] == T()) {
          res.polynom.pop_back();
      }
      if (res.polynom.empty()) {
          res.polynom.push_back(T());
      }
      return res;
  }

  Polynomial operator*(T coef) const {
      Polynomial tmp(coef);
      return (*this) * tmp;
  }

  friend Polynomial operator*(T coef, Polynomial current) {
      return current * coef;
  }

  Polynomial &operator*=(Polynomial other) {
      *this = (*this) * other;
      return *this;
  }

  Polynomial &operator*=(T coef) {
      Polynomial tmp(coef);
      (*this) *= tmp;
      return *this;
  }

  T operator()(T arg) const {
      T res = T();
      for (size_t i = 0; i < polynom.size(); ++i) {
          T numeric = T(1);
          for (size_t j = 0; j < i; ++j) {
              numeric *= arg;
          }
          res += polynom[i] * numeric;
      }
      return res;
  }

  friend std::ostream &operator<<(std::ostream &out, const Polynomial &current) {
      for (long long i = static_cast<long long>(current.polynom.size()) - 1; i >= 0; --i) {
          if (current.polynom.size() == 1) {
              out << current.polynom[0];
          } else {
              if (current.polynom[i] != T(0)) {
                  if (current.polynom[i] > T(0)) {
                      if (current.polynom[i] != T(1)) {
                          if (i == static_cast<long long>(current.polynom.size()) - 1) {
                              if (i == 1) {
                                  out << current.polynom[i] << "*x";
                              } else if (i == 0) {
                                  out << current.polynom[i];
                              } else {
                                  out << current.polynom[i] << "*x^" << i;
                              }
                          } else {
                              if (i == 1) {
                                  out << "+" << current.polynom[i] << "*x";
                              } else if (i == 0) {
                                  out << "+" << current.polynom[i];
                              } else {
                                  out << "+" << current.polynom[i] << "*x^" << i;
                              }
                          }
                      } else {
                          if (i == static_cast<long long>(current.polynom.size()) - 1) {
                              if (i == 1) {
                                  out << "x";
                              } else if (i == 0) {
                                  out << "1";
                              } else {
                                  out << "x^" << i;
                              }
                          } else {
                              if (i == 1) {
                                  out << "+x";
                              } else if (i == 0) {
                                  out << "+1";
                              } else {
                                  out << "+x^" << i;
                              }
                          }
                      }
                  } else if (current.polynom[i] < T(0)) {
                      if (current.polynom[i] != T(-1)) {
                          if (i == 1) {
                              out << current.polynom[i] << "*x";
                          } else if (i == 0) {
                              out << current.polynom[i];
                          } else {
                              out << current.polynom[i] << "*x^" << i;
                          }
                      } else {
                          if (i == 1) {
                              out << "-x";
                          } else if (i == 0) {
                              out << "-1";
                          } else {
                              out << "-x^" << i;
                          }
                      }
                  }
              }
          }
      }
      return out;
  }

  friend Polynomial operator&(Polynomial first, Polynomial second) {
      Polynomial res((T()));
      for (size_t i = 0; i < first.polynom.size(); ++i) {
          Polynomial pre_res((T(1)));
          for (size_t j = 0; j < i; ++j) {
              pre_res *= second;
          }
          res += first.polynom[i] * pre_res;
      }
      return res;
  }
};
