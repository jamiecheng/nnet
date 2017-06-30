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

    friend Array operator+(double lhs, const Array &rhs) {
        return Array::perform(rhs, [lhs](double input) -> double { return input + lhs; });
    }

    friend Array operator+(Array lhs, Array rhs) {
        if (lhs.colums() != rhs.colums() || lhs.rows() != rhs.rows())
            throw std::runtime_error("arrays do not have equal sizes");

        Array tmp(lhs.rows(), lhs.colums());
        for (int i = 0; i < tmp.rows(); i++) {
            for (int j = 0; j < tmp.colums(); j++) {
                tmp[i][j] = lhs[i][j] + rhs[i][j];
            }
        }

        return tmp;
    }

    friend Array operator-(double lhs, const Array &rhs) {
        return Array::perform(rhs, [lhs](double input) -> double { return lhs - input; });
    }

    friend Array operator-(Array lhs, Array rhs) {
        if (lhs.colums() != rhs.colums() || lhs.rows() != rhs.rows())
            throw std::runtime_error("arrays do not have equal sizes");

        Array tmp(lhs.rows(), lhs.colums());
        for (int i = 0; i < tmp.rows(); i++) {
            for (int j = 0; j < tmp.colums(); j++) {
                tmp[i][j] = lhs[i][j] - rhs[i][j];
            }
        }

        return tmp;
    }

    friend Array operator*(double lhs, const Array &rhs) {
        return Array::perform(rhs, [lhs](double input) -> double { return input * lhs; });
    }

    friend Array operator*(Array lhs, Array rhs) {
        if (lhs.colums() != rhs.colums() || lhs.rows() != rhs.rows())
            throw std::runtime_error("arrays do not have equal sizes");

        Array tmp(lhs.rows(), lhs.colums());
        for (int i = 0; i < tmp.rows(); i++) {
            for (int j = 0; j < tmp.colums(); j++) {
                tmp[i][j] = lhs[i][j] * rhs[i][j];
            }
        }

        return tmp;
    }

    friend Array operator/(double lhs, const Array &rhs) {
        return Array::perform(rhs, [lhs](double input) -> double { return lhs / input; });
    }

public:
    using matrix_type = std::vector<std::vector<double>>;

    // ---------------------------- constructors ----------------------------
    Array(unsigned long rows, unsigned long colums) : matrix_(rows, std::vector<double>(colums)) {}

    explicit Array(std::vector<std::vector<double>> matrix) : matrix_(std::move(matrix)) {}

    // ---------------------------- math functions ----------------------------
    static Array exp(Array m) {
        return perform(std::move(m), [](double input) -> double { return std::exp(input); });
    }

    static Array dot(Array m1, Array m2) {
        matrix_type vMatrix(m1.rows());

        for (int j = 0; j < m1.rows(); j++) {
            std::vector<double> values(m2.colums());

            for (int i = 0; i < m2.colums(); i++) {
                values[i] = std::inner_product(m1[j].begin(), m1[j].end(), m2.column(i).begin(), 0.0);
            }

            vMatrix[j] = values;
        }

        return Array(vMatrix);
    }

    static double mean(Array m) {
        double mean{};

        for (int i = 0; i < m.rows(); i++) {
            for (int j = 0; j < m.colums(); j++) {
                mean += std::abs(m[i][j]);
            }
        }

        return mean / (m.rows() * m.colums());
    }

    static Array randomize(const Array &m, int min, int max) {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_real_distribution<double> uni(min, max);

        return Array::perform(std::move(m), [&uni, &rng](double input) -> double {
            return uni(rng);
        });
    }

    static Array perform(Array m, const std::function<double(double)> &alg) {
        Array tmp(m.rows(), m.colums());

        for (int i = 0; i < m.rows(); i++) {
            for (int j = 0; j < m.colums(); j++) {
                tmp[i][j] = alg(m[i][j]);
            }
        }

        return Array(tmp);
    }

    static std::string toString(const Array &matrix) {
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

    Array transpons() {
        Array tmp(colums(), rows());

        for (int j = 0; j < colums(); j++) {
            tmp[j] = column(j);
        }

        return tmp;
    }

    // ---------------------------- acces functions ----------------------------
    std::vector<double> column(int index) {
        if (index >= colums()) throw std::range_error("column index out of range");

        std::vector<double> tmp(rows());

        for (int i = 0; i < rows(); i++) {
            tmp[i] = matrix_[i][index];
        }

        return tmp;
    }

    unsigned long rows() const { return matrix_.size(); }

    unsigned long colums() const { return matrix_[0].size(); }

    std::vector<std::vector<double>> matrix() const { return matrix_; }

    std::vector<double> &operator[](int index) { return matrix_[index]; }

private:
    matrix_type matrix_;
};

#endif //NET_MATRIX_HPP
