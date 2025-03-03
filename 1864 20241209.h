#ifndef MATRIX_H_
#define MATRIX_H_

#include <exception>
// just include whatever you want

namespace sjtu {

class MatrixSizeError : public std::exception {
 public:
  const char* what() noexcept {
    return "matrix size mismatch";
  }
};
class MatrixIndexingError : public std::exception {
 public:
  const char* what() noexcept {
    return "invalid matrix indexing";
  }
};

template <typename T>
class Matrix {
 private:
  int h, w;
  // TODO: choose your way to store elements in the matrix
  T **mat;
  /*for (int i = 0; i < h; i++)
    mat[i] = new int *[w];*/
  void release() {
    for (int i = 0; i < h; i++) {
      delete[] mat[i];
    }
    delete[] mat;
  }

public:
  int height() const {
    return h;
  }
  int width() const {
    return w;
  }
  Matrix() = delete;
  Matrix(int h_, int w_, T* seq = nullptr) {
    // TODO
    h = h_;
    w = w_;
    mat = new T *[h];
    for (int i = 0; i < h; i++) {
      mat[i] = new T [w];
      for (int j = 0; j < w; j++) {
        if(seq)
          mat[i][j] = seq[i * w + j];
        else
          mat[i][j] = T();
      }
    }
  }
  Matrix(const Matrix& o) {
    // TODO
    h = o.h;
    w = o.w;
    mat = new T *[h];
    for (int i = 0; i < h; i++) {
      mat[i] = new T [w];
      for (int j = 0; j < w; j++)
        mat[i][j] = o.mat[i][j];
    }
  }

  bool operator== (const Matrix& rhs) {
    if (h == rhs.h && w == rhs.w)
    {
      for (int i = 0; i < h; i++) 
        for (int j = 0; j < w; j++) 
            if(mat[i][j] != rhs.mat[i][j])
              return false;
      return true;
    }
    return false;
  }

  Matrix& operator= (const Matrix& rhs) {
    // TODO
    if(this == &rhs)
      return *this;
    release();
    h = rhs.h;
    w = rhs.w;
    mat = new T *[h];
    for (int i = 0; i < h; i++) {
      mat[i] = new T[w];
      for (int j = 0; j < w; j++)
        mat[i][j] = rhs.mat[i][j];
    }
    return *this;
  }

  T& operator() (int row, int col) {
    // TODO
    row--;
    col--;
    if(row < 0 || row >= h || col < 0 || col >= w)
      throw MatrixIndexingError();
    else
      return mat[row][col];
  }

  const T& operator() (int row, int col) const {
    // TODO
    row--;
    col--;
    if(row < 0 || row >= h || col < 0 || col >= w)
      throw MatrixIndexingError();
    else
      return mat[row][col];
  }

  Matrix operator* (const Matrix& rhs) const {
    // TODO
    if(w != rhs.h)
      throw MatrixSizeError();
    Matrix ans(h, rhs.w);
    for (int i = 0; i < h; i++)
      for (int j = 0; j < rhs.w; j++) {
        T temp = T();
        for (int k = 0; k < w; k++)
        {
          temp = temp + mat[i][k] * rhs.mat[k][j];
        }
        ans.mat[i][j] = temp;
      }
    return ans;
  }

  Matrix operator+ (const Matrix& rhs) const {
    // TODO
    if(h == rhs.h && w == rhs.w) {
      Matrix ans(h, w);
      for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
          ans.mat[i][j] = mat[i][j] + rhs.mat[i][j];
      return ans;
    }
    else if (h == 1 && rhs.w == 1) {
      Matrix ans(rhs.h, w);
      for (int i = 0; i < rhs.h; i++)
        for (int j = 0; j < w; j++)
          ans.mat[i][j] = mat[0][j] + rhs.mat[i][0];
      return ans;
    }
    else if (w == 1 && rhs.h == 1)
    {
       Matrix ans(h, rhs.w);
      for (int i = 0; i < h; i++)
        for (int j = 0; j < rhs.w; j++)
          ans.mat[i][j] = rhs.mat[0][j] + mat[i][0];
      return ans;
    }
    else
    {
      throw MatrixSizeError();
    }
  }

  ~Matrix() {
    release();
  }
};

} // namespace sjtu

#endif // MATRIX_H_
