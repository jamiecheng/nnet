//
// Created by jamie on 6/30/17.
//

#ifndef NET_MATRIX_HPP
#define NET_MATRIX_HPP

#include <valarray>
#include <string>
#include <vector>
#include <vector>
#include <functional>
#include <random>

class Matrix {
    friend std::ostream &operator<<(std::ostream &os, const Matrix &m) {
        return os << Matrix::toString(m);
    }

    friend Matrix operator+(double lhs, const Matrix &rhs) {
        return Matrix::perform(rhs, [lhs](double input) -> double { return input + lhs; });
    }

    friend Matrix operator+(Matrix lhs, Matrix rhs) {
        if (lhs.colums() != rhs.colums() || lhs.rows() != rhs.rows())
            throw std::runtime_error("matrices do not have equal sizes");

        Matrix tmp(lhs.rows(), lhs.colums());
        for (int i = 0; i < tmp.rows(); i++) {
            for (int j = 0; j < tmp.colums(); j++) {
                tmp[i][j] = lhs[i][j] + rhs[i][j];
            }
        }

        return tmp;
    }

    friend Matrix operator-(double lhs, const Matrix &rhs) {
        return Matrix::perform(rhs, [lhs](double input) -> double { return lhs - input; });
    }

    friend Matrix operator-(Matrix lhs, Matrix rhs) {
        if (lhs.colums() != rhs.colums() || lhs.rows() != rhs.rows())
            throw std::runtime_error("matrices do not have equal sizes");

        Matrix tmp(lhs.rows(), lhs.colums());
        for (int i = 0; i < tmp.rows(); i++) {
            for (int j = 0; j < tmp.colums(); j++) {
                tmp[i][j] = lhs[i][j] - rhs[i][j];
            }
        }

        return tmp;
    }

    friend Matrix operator*(double lhs, const Matrix &rhs) {
        return Matrix::perform(rhs, [lhs](double input) -> double { return input * lhs; });
    }

    friend Matrix operator*(Matrix lhs, Matrix rhs) {
        if (lhs.colums() != rhs.colums() || lhs.rows() != rhs.rows())
            throw std::runtime_error("matrices do not have equal sizes");

        Matrix tmp(lhs.rows(), lhs.colums());
        for (int i = 0; i < tmp.rows(); i++) {
            for (int j = 0; j < tmp.colums(); j++) {
                tmp[i][j] = lhs[i][j] * rhs[i][j];
            }
        }

        return tmp;
    }

    friend Matrix operator/(double lhs, const Matrix &rhs) {
        return Matrix::perform(rhs, [lhs](double input) -> double { return lhs / input; });
    }

public:
    using matrix_type = std::vector<std::vector<double>>;

    Matrix(unsigned long rows, unsigned long colums) : matrix_(rows, std::vector<double>(colums)) {}

    Matrix(const std::vector<std::vector<double>> &matrix) : matrix_(matrix) {}

    static Matrix exp(Matrix m) {
        return perform(m, [](double input) -> double { return std::exp(input); });
    }

    static Matrix dot(Matrix m1, Matrix m2) {
        matrix_type vMatrix;

        for (auto row : m1.matrix()) {
            std::vector<double> values;

            for (int i = 0; i < m2.colums(); i++) {
                auto rowAr = std::valarray<double>(row.data(), row.size());
                auto colAr = std::valarray<double>(m2.column(i).data(), m2.column(i).size());
                values.push_back((rowAr * colAr).sum());
            }

            vMatrix.push_back(values);
        }

        return Matrix(vMatrix);
    }

    static double mean(Matrix m) {
        double mean{};

        // sum
        for(int i = 0; i < m.rows(); i++) {
            for(int j = 0; j < m.colums(); j++) {
                mean += std::abs(m[i][j]);
            }
        }

        return mean / (m.rows() * m.colums());
    }

    static Matrix randomize(Matrix m, int min, int max) {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_real_distribution<double> uni(min, max);

        return Matrix::perform(m, [&uni, &rng](double input) -> double {
            return uni(rng);
        });
    }

    static Matrix perform(Matrix m, std::function<double(double)> alg) {
        Matrix tmp(m.rows(), m.colums());

        for (int i = 0; i < m.rows(); i++) {
            for (int j = 0; j < m.colums(); j++) {
                tmp[i][j] = alg(m[i][j]);
            }
        }

        return Matrix(tmp);
    }

    static std::string toString(Matrix matrix) {
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

    std::vector<double> column(int index) {
        if (index >= colums()) throw std::range_error("column index out of range");

        std::vector<double> tmp;

        for (auto row : matrix_) {
            tmp.push_back(row[index]);
        }

        return tmp;
    }

    Matrix transpons() {
        Matrix tmp(colums(), rows());

        for(int j = 0; j < colums(); j++) {
            tmp[j] = column(j);
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
