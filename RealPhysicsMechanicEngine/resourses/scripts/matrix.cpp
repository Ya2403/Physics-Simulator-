/*
 * matrix.cpp
 */

#include <stdexcept>
#include <cmath>
#include "matrix.h"

#define EPS 1e-10

using std::ostream;  using std::istream;  using std::endl;
using std::domain_error;

/* PUBLIC MEMBER FUNCTIONS
 ********************************/

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols)
{
    allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = 0;
        }
    }
}

Matrix::Matrix(double** a, int rows, int cols) : rows_(rows), cols_(cols)
{
    allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = a[i][j];
        }
    }
}

Matrix::Matrix() : rows_(1), cols_(1)
{
    allocSpace();
    p[0][0] = 0;
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows_; ++i) {
        delete[] p[i];
    }
    delete[] p;
}

//concatenates n matrix of same format rows*cols
Matrix Matrix::ConcatenateMatrix(Matrix arrayOfMatrix[], int numberOfMatrix, int rows, int cols)
{
    Matrix resMatrix = Matrix(rows * numberOfMatrix, cols);
    for (int i = 0; i < numberOfMatrix; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            for (int k = 0; k < cols; k++)
            {
                resMatrix.p[i* rows + j][k] = arrayOfMatrix[i](j, k);
            }
        }
    }
    return resMatrix;
}

Matrix::Matrix(const Matrix& m) : rows_(m.rows_), cols_(m.cols_)
{
    allocSpace();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = m.p[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& m)
{
    if (this == &m) {
        return *this;
    }

    if (rows_ != m.rows_ || cols_ != m.cols_) {
        for (int i = 0; i < rows_; ++i) {
            delete[] p[i];
        }
        delete[] p;

        rows_ = m.rows_;
        cols_ = m.cols_;
        allocSpace();
    }

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            p[i][j] = m.p[i][j];
        }
    }
    return *this;
}

Matrix Matrix::transpose()
{
    Matrix ret(cols_, rows_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            ret.p[j][i] = p[i][j];
        }
    }
    return ret;
}


/* STATIC CLASS FUNCTIONS
 ********************************/

Matrix Matrix::createIdentity(int size)
{
    Matrix temp(size, size);
    for (int i = 0; i < temp.rows_; ++i) {
        for (int j = 0; j < temp.cols_; ++j) {
            if (i == j) {
                temp.p[i][j] = 1;
            } else {
                temp.p[i][j] = 0;
            }
        }
    }
    return temp;
}

// functions on VECTORS
double Matrix::dotProduct(Matrix a, Matrix b)
{
    double sum = 0;
    for (int i = 0; i < a.rows_; ++i) {
        sum += (a(i, 0) * b(i, 0));
    }
    return sum;
}


Matrix Matrix::MatrixMultiplyByMatrixTransformRight(Matrix a)
{
    Matrix temp(rows_, a.rows_);
    for (int i = 0; i < temp.rows_; ++i) {
        for (int j = 0; j < temp.cols_; ++j) {
            for (int k = 0; k < cols_; ++k) {
                temp.p[i][j] += (p[i][k] *  a.p[j][k]);
            }
        }
    }
    return (temp);

}

Matrix Matrix::MatrixMultiplyByMatrixTransformOnTheLeft(Matrix a)
{
    Matrix temp(cols_, a.cols_);
    for (int i = 0; i < temp.rows_; ++i) {
        for (int j = 0; j < temp.cols_; ++j) {
            for (int k = 0; k < rows_; ++k) {
                temp.p[i][j] += (p[k][i] * a.p[k][j]);
            }
        }
    }
    return (temp);

}


/* PRIVATE HELPER FUNCTIONS
 ********************************/

void Matrix::allocSpace()
{
    p = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
        p[i] = new double[cols_];
    }
}




Matrix Matrix::conjugateGradientSolver(const Matrix& A, const Matrix& B)
{   
    const double NEARZERO = 1.0e-10;
    double TOLERANCE = 1.0e-10;
    Matrix x(A.cols_, 1);


    Matrix residual = B - A * x;
    Matrix search_direction = residual;
    double old_resid_norm = sqrt(residual.MatrixMultiplyByMatrixTransformOnTheLeft(residual)(0,0));
   

    while(old_resid_norm > TOLERANCE)
    {
        Matrix A_search_direction = A * search_direction;
        double step_size = pow(old_resid_norm,2) /( (search_direction.transpose() * A_search_direction)(0, 0));
        x = x + step_size * search_direction;

        residual = residual - step_size * A_search_direction;
        double new_resid_norm = sqrt(residual.MatrixMultiplyByMatrixTransformOnTheLeft(residual)(0, 0));
        search_direction = residual + ((new_resid_norm / old_resid_norm) * (new_resid_norm / old_resid_norm)) * search_direction;
        old_resid_norm = new_resid_norm;
    }
    return x;       
}


/* NON-MEMBER FUNCTIONS
 ********************************/

Matrix operator+(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    for (int i = 0; i < m1.rows_; ++i) {
        for (int j = 0; j < m1.cols_; ++j) {
            m1.p[i][j] += m2.p[i][j];
        }
    }
    return temp;
}

Matrix operator-(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1);
    for(int i = 0; i < m1.rows_; ++i) {
        for (int j = 0; j < m1.cols_; ++j) {
            m1.p[i][j] -= m2.p[i][j];
        }
    }
    return temp;
}

Matrix operator*(const Matrix& m1, const Matrix& m2)
{
    Matrix temp(m1.rows_, m2.cols_);
    for (int i = 0; i < temp.rows_; ++i) {
        for (int j = 0; j < temp.cols_; ++j) {
            for (int k = 0; k < m1.cols_; ++k) {
                temp.p[i][j] += (m1.p[i][k] * m2.p[k][j]);
            }
        }
    }
    return (temp);
}

Matrix operator*(const Matrix& m, double num)
{
    Matrix temp(m);
    for (int i = 0; i < m.rows_; ++i) {
        for (int j = 0; j < m.cols_; ++j) {
            m.p[i][j] *= num;
        }
    }
    return temp;
}

Matrix operator*(double num, const Matrix& m)
{
    return (m * num);
}

ostream& operator<<(ostream& os, const Matrix& m)
{
    for (int i = 0; i < m.rows_; ++i) {
        os << m.p[i][0];
        for (int j = 1; j < m.cols_; ++j) {
            os << " " << m.p[i][j];
        }
        os << endl;
    }
    return os;
}

istream& operator>>(istream& is, Matrix& m)
{
    for (int i = 0; i < m.rows_; ++i) {
        for (int j = 0; j < m.cols_; ++j) {
            is >> m.p[i][j];
        }
    }
    return is;
}
