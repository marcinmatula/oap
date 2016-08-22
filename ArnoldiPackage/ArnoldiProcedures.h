/*
 * Copyright 2016 Marcin Matula
 *
 * This file is part of Oap.
 *
 * Oap is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Oap is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Oap.  If not, see <http://www.gnu.org/licenses/>.
 */



#ifndef OAP_CU_ARNOLDIPROCEDURES_H
#define OAP_CU_ARNOLDIPROCEDURES_H

#include <vector>
#include "MatrixEx.h"
#include "Matrix.h"
#include "KernelExecutor.h"
#include "MatrixProcedures.h"

namespace ArnUtils {

bool SortLargestValues(const Complex& i, const Complex& j);

bool SortLargestReValues(const Complex& i, const Complex& j);

bool SortLargestImValues(const Complex& i, const Complex& j);

bool SortSmallestValues(const Complex& i, const Complex& j);

bool SortSmallestReValues(const Complex& i, const Complex& j);

bool SortSmallestImValues(const Complex& i, const Complex& j);

typedef bool (*SortType)(const Complex& i, const Complex& j);

enum Type { DEVICE, HOST };

class MatrixInfo {
 public:
  MatrixInfo();
  MatrixInfo(bool _isRe, bool _isIm, uintt _columns, uintt _rows);
  math::MatrixDim m_matrixDim;
  bool isRe;
  bool isIm;
};
}

class CuHArnoldi {
  void initVvector();

  bool continueProcedure();

  inline void switchPointer(math::Matrix** a, math::Matrix** b) {
    math::Matrix* temp = *b;
    *b = *a;
    *a = temp;
  }

  void calculateTriangularHInDevice();
  void calculateTriangularH();

  void (CuHArnoldi::*m_calculateTriangularHPtr)();

  inline void setCalculateTriangularHPtr(uintt k) {
    if (true || k > 32) {
      m_calculateTriangularHPtr = &CuHArnoldi::calculateTriangularH;
    } else {
      m_calculateTriangularHPtr = &CuHArnoldi::calculateTriangularHInDevice;
    }
  }

  void calculateTriangularHEigens(uintt unwantedCount);

  /**
   * @brief executeArnoldiFactorization
   * @param init
   * @param initj
   * @param dMatrixEx
   * @param m_rho
   * @return true - should continue, false  - finish algorithm
   */
  bool executeArnoldiFactorization(bool init, intt initj, MatrixEx** dMatrixEx,
                                   floatt rho);

  bool shouldBeReallocated(const ArnUtils::MatrixInfo& m1,
                           const ArnUtils::MatrixInfo& m2) const;

  void isConverged() const;

 public:
  CuHArnoldi();

  virtual ~CuHArnoldi();

  void setRho(floatt rho = 1. / 3.14);

  void setBLimit(floatt blimit);

  void setSortType(ArnUtils::SortType sortType);

  void setOutputs(math::Matrix* outputs);

  void execute(uintt k, uintt wantedCount,
               const ArnUtils::MatrixInfo& matrixInfo,
               ArnUtils::Type matrixType = ArnUtils::DEVICE);

 protected:
  CuMatrix m_cuMatrix;
  math::Matrix* w;
  math::Matrix* f;
  math::Matrix* f1;
  math::Matrix* vh;
  math::Matrix* h;
  math::Matrix* s;
  math::Matrix* vs;
  math::Matrix* V;
  math::Matrix* transposeV;
  math::Matrix* V1;
  math::Matrix* V2;
  math::Matrix* H;
  math::Matrix* HC;
  math::Matrix* H1;
  math::Matrix* H2;
  math::Matrix* A1;
  math::Matrix* A2;
  math::Matrix* I;
  math::Matrix* v;
  math::Matrix* QT;
  math::Matrix* Q1;
  math::Matrix* Q2;
  math::Matrix* R1;
  math::Matrix* R2;
  math::Matrix* HO;
  math::Matrix* HO1;
  math::Matrix* Q;
  math::Matrix* QJ;
  math::Matrix* q;
  math::Matrix* q1;
  math::Matrix* q2;
  math::Matrix* GT;
  math::Matrix* G;
  math::Matrix* EV;
  math::Matrix* EV1;
  math::Matrix* EQ1;
  math::Matrix* EQ2;
  math::Matrix* EQ3;

 private:
  ArnUtils::MatrixInfo m_matrixInfo;
  ArnUtils::Type m_matrixType;

  math::Matrix* m_outputs;
  ArnUtils::Type m_outputsType;

  bool m_wasAllocated;

  uintt m_k;
  floatt m_rho;
  floatt m_blimit;
  std::vector<Complex> wanted;
  std::vector<Complex> unwanted;
  std::vector<uintt> wantedIndecies;
  std::vector<Complex> notSorted;
  ArnUtils::SortType m_sortType;

  void* m_image;
  device::Kernel m_kernel;

  uintt m_transposeVcolumns;
  uintt m_hrows;
  uintt m_scolumns;
  uintt m_vscolumns;
  uintt m_vsrows;
  uintt m_vrows;
  uintt m_qrows;
  uintt m_Hcolumns;
  uintt m_Hrows;
  uintt m_H1columns;
  uintt m_Qrows;
  uintt m_Qcolumns;

  void alloc(const ArnUtils::MatrixInfo& matrixInfo, uintt k);
  void alloc1(const ArnUtils::MatrixInfo& matrixInfo, uintt k);
  void alloc2(const ArnUtils::MatrixInfo& matrixInfo, uintt k);
  void alloc3(const ArnUtils::MatrixInfo& matrixInfo, uintt k);
  void dealloc1();
  void dealloc2();
  void dealloc3();

 public:
  enum MultiplicationType { TYPE_EIGENVECTOR, TYPE_WV };

 protected:
  virtual void multiply(math::Matrix* w, math::Matrix* v,
                        MultiplicationType mt) = 0;
};

class CuHArnoldiDefault : public CuHArnoldi {
 public:
  /**
 * @brief Set device matrix to calculate its eigenvalues and eigenvectors.
 * @param A
 */
  void setMatrix(math::Matrix* A) { m_A = A; }

 protected:
  void multiply(math::Matrix* w, math::Matrix* v,
                CuHArnoldi::MultiplicationType mt);

 private:
  math::Matrix* m_A;
};

class CuHArnoldiCallback : public CuHArnoldi {
 public:
  typedef void (*MultiplyFunc)(math::Matrix* w, math::Matrix* v, void* userData,
                               CuHArnoldi::MultiplicationType mt);

  void setCallback(MultiplyFunc multiplyFunc, void* userData);

 protected:
  void multiply(math::Matrix* w, math::Matrix* v,
                CuHArnoldi::MultiplicationType mt);

 private:
  MultiplyFunc m_multiplyFunc;
  void* m_userData;
};

#endif /* CUPROCEDURES_H */
