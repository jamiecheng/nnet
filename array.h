//
// Created by jamie on 6/30/17.
//

#ifndef NET_MATRIX_HPP
#define NET_MATRIX_HPP

#include <utility>
#include <valarray>
#include <string>
#include <vector>
#include <vector>
#include <functional>
#include <random>

class Array {
  friend std::ostream &operator<<(std::ostream &os, const Array &m) {
    return os << Array::toString(m);
  }

  // ---------------------------- operator functions ----------------------------
  friend inline Array operator+(const Array &lhs, double val) {
    Array tmp = lhs;

    for(int i = 0; i < tmp.rows(); i++) {
        for(int j = 0; j < tmp.colums(); j++) {
            tmp.set(i, j, tmp.get(i, j) + val);
          }
      }

    return tmp;
  }

  friend inline Array operator+(const Array &lhs, const Array &ar) {
    Array tmp = lhs;

    if (tmp.colums() != ar.colums() || tmp.rows() != ar.rows())
      throw std::runtime_error("arrays do not have equal sizes");

    for(int i = 0; i < tmp.rows(); i++) {
        for(int j = 0; j < tmp.colums(); j++) {
            tmp.set(i, j, tmp.get(i, j) + ar.get(i, j));
          }
      }

    return tmp;
  }

  friend inline Array operator-(const Array &lhs, double val) {
    Array tmp = lhs;

    for(int i = 0; i < tmp.rows(); i++) {
        for(int j = 0; j < tmp.colums(); j++) {
            tmp.set(i, j, tmp.get(i, j) - val);
          }
      }

    return tmp;
  }

  friend inline Array operator-(const Array &lhs, const Array &ar) {
    Array tmp = lhs;

    if (tmp.colums() != ar.colums() || tmp.rows() != ar.rows())
      throw std::runtime_error("arrays do not have equal sizes");

    for(int i = 0; i < tmp.rows(); i++) {
        for(int j = 0; j < tmp.colums(); j++) {
            tmp.set(i, j, tmp.get(i, j) - ar.get(i, j));
          }
      }

    return tmp;
  }

  friend inline Array operator*(const Array &lhs, double val) {
    Array tmp = lhs;

    for(int i = 0; i < tmp.rows(); i++) {
        for(int j = 0; j < tmp.colums(); j++) {
            tmp.set(i, j, tmp.get(i, j) * val);
          }
      }

    return tmp;
  }

  friend inline Array operator*(const Array &lhs, const Array &ar) {
    Array tmp = lhs;

    if (tmp.colums() != ar.colums() || tmp.rows() != ar.rows())
      throw std::runtime_error("arrays do not have equal sizes");

    for(int i = 0; i < tmp.rows(); i++) {
        for(int j = 0; j < tmp.colums(); j++) {
            tmp.set(i, j, tmp.get(i, j) * ar.get(i, j));
          }
      }

    return tmp;
  }

  friend inline Array operator/(const Array &lhs, double val) {
    Array tmp = lhs;

    for(int i = 0; i < tmp.rows(); i++) {
        for(int j = 0; j < tmp.colums(); j++) {
            tmp.set(i, j, tmp.get(i, j) / val);
          }
      }

    return tmp;
  }

  friend inline Array operator/(const Array &lhs, const Array& ar) {
    Array tmp = lhs;

    if (tmp.colums() != ar.colums() || tmp.rows() != ar.rows())
      throw std::runtime_error("arrays do not have equal sizes");

    for(int i = 0; i < tmp.rows(); i++) {
        for(int j = 0; j < tmp.colums(); j++) {
            tmp.set(i, j, tmp.get(i, j) / ar.get(i, j));
          }
      }

    return tmp;
  }

  friend Array operator-(double lhs, const Array &rhs) {
    Array tmp = rhs;

    for(int i = 0; i < tmp.rows(); i++) {
        for(int j = 0; j < tmp.colums(); j++) {
            tmp.set(i, j, lhs - rhs.get(i, j));
          }
    }

    return tmp;
  }

  friend Array operator*(double lhs, const Array &rhs) {
    Array tmp = rhs;

    for(int i = 0; i < tmp.rows(); i++) {
        for(int j = 0; j < tmp.colums(); j++) {
            tmp.set(i, j, lhs * rhs.get(i, j));
          }
    }

    return tmp;
  }

  friend Array operator/(double lhs, Array rhs) {
    Array tmp = rhs;

    for(int i = 0; i < tmp.rows(); i++) {
        for(int j = 0; j < tmp.colums(); j++) {
            tmp[i][j] = lhs / rhs[i][j];
          }
    }

    return tmp;
  }

public:
  using array_type = std::vector<std::vector<double>>;

  // ---------------------------- constructors ----------------------------
  Array(unsigned long rows, unsigned long colums) :
    rows_(rows),
    columns_(colums),
    array_(rows, std::vector<double>(colums))
  {}

  explicit Array(const std::vector<std::vector<double>>& matrix) :
    rows_(matrix.size()),
    columns_(matrix.at(0).size()),
    array_(matrix)
  {}

  // ---------------------------- modifiers ----------------------------
  inline static Array exp(const Array &ar) {
    Array tmp = ar;

    for(int i = 0; i < tmp.rows(); i++) {
        for(int j = 0; j < tmp.colums(); j++) {
            tmp.set(i, j, std::exp(tmp.get(i, j)));
          }
      }

    return tmp;
  }

  inline Array dot(const Array &ar) {
    Array tmp(rows(), ar.colums());

    for(int i = 0; i < rows(); i++) {
        for (int j = 0; j < ar.colums(); j++) {
            double sum = 0.0;

            for (int k = 0; k < colums(); k++) {
                sum = sum + get(i, k) * ar.get(k, j);
              }

            tmp.set(i, j, sum);
          }
      }

    return tmp;
  }

  inline static double mean(const Array &m) {
    double mean{};

    for (int i = 0; i < m.rows(); i++) {
        for (int j = 0; j < m.colums(); j++) {
            mean += std::abs(m.get(i, j));
          }
      }

    return mean / (m.rows() * m.colums());
  }

  inline static Array randomize(const Array &m, int min, int max) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<double> uni(min, max);

    Array tmp = m;

    for(int i = 0; i < tmp.rows(); i++) {
        for(int j = 0; j < tmp.colums(); j++) {
            tmp.set(i, j, uni(rng));
          }
    }

    return tmp;
  }

  inline static std::string toString(const Array &matrix) {
    std::string out;

    for (auto row : matrix.matrix()) {
        out += "[ ";
        for (auto value : row) {
            out += std::to_string(value) + " ";
          }
        out += "]\n";
      }

    return out;
  }

  inline Array transpons() {
    Array tmp(colums(), rows());

    for (int j = 0; j < colums(); j++) {
        tmp[j] = column(j);
      }

    return tmp;
  }

  // ---------------------------- acces functions ----------------------------
  inline void set(int r, int c, double val) {
    array_[r][c] = val;
  }

  inline const double &get (int r, int c) const {
    return array_.at(r).at(c);
  }

  inline std::vector<double> column(int index) {
    if (index >= colums()) throw std::range_error("column index out of range");

    std::vector<double> tmp(rows());

    for (int i = 0; i < rows(); i++) {
        tmp[i] = array_[i][index];
      }

    return tmp;
  }

  inline const int &rows() const { return rows_; }

  inline const int &colums() const { return columns_; }

  inline const std::vector<std::vector<double>> &matrix() const { return array_; }

  inline std::vector<double> &operator[](int index) { return array_[index]; }

private:
  int rows_;
  int columns_;
  array_type array_;
};

#endif //NET_MATRIX_HPP
