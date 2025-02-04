/*
 * Copyright 2016 - 2019 Marcin Matula
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

#ifndef OAP_CUPROCEDURESAPI_H
#define OAP_CUPROCEDURESAPI_H

#include <map>
#include <sstream>

#include "CudaBuffer.h"
#include "HostBuffer.h"

#include "Matrix.h"
#include "MatrixEx.h"
#include "CudaUtils.h"
#include "KernelExecutor.h"

#include "oapCudaMatrixUtils.h"

#include "RecToSquareApi.h"

#include "GenericCoreApi.h"

#define CHECK_MATRIX(m) debugAssertMsg (m != NULL, "Matrix is nullptr.");

namespace oap
{

class CuProceduresApi
{
 public:
  CuProceduresApi();
  virtual ~CuProceduresApi();

  CuProceduresApi(const CuProceduresApi&) = delete;
  CuProceduresApi(CuProceduresApi&&) = delete;
  CuProceduresApi& operator=(const CuProceduresApi&) = delete;
  CuProceduresApi& operator=(CuProceduresApi&&) = delete;

  inline void addDotProduct(math::Matrix* output, math::Matrix* params0, math::Matrix* params1);

  inline void tensorProduct(math::Matrix* output, math::Matrix* params0, math::Matrix* params1);


  void tensorProduct (math::Matrix* output, math::Matrix* params0, math::Matrix* params1, uintt dims[3][2]);

  inline void tensorProduct (math::Matrix* output, math::Matrix* params0, math::Matrix* params1, uintt outputD[2], uintt matrix1D[2], uintt matrix2D[2])
  {

    uintt dims[3][2] = {{outputD[0], outputD[1]}, {matrix1D[0], matrix1D[1]}, {matrix2D[0], matrix2D[1]}};
    tensorProduct (output, params0, params1, dims);
  }

  inline void hadamardProduct(math::Matrix* output, math::Matrix* params0, math::Matrix* params1);

  /**
   *  @brief Calculates hadamard product of matrix and vector of the second matrix.
   *  @param output - output matrix (dimension n columns x n rows)
   *  @param params0 - matrix (dimension n columns x n rows)
   *  @param params1 - vector of the second matrix. The second matrix consists of repeated column vector (dimenstion must be 1 columns x n rows).
   *
   *           |a00 a10 a20|                 |v0 v0 v0|                                               |v0|
   *  output = |a01 a11 a21| hadamardProduct |v1 v1 v1| where a__ are values of params0 and params1 = |v1|
   *           |a02 a12 a22|                 |v2 v2 v2|                                               |v2|
   *
   *  Example of use: oapPartialHadamardProductTests.cpp
   */
  inline void hadamardProductVec(math::Matrix* output, math::Matrix* params0, math::Matrix* params1);

  void dotProduct (math::Matrix* output, math::Matrix* params0, math::Matrix* params1);

  void dotProductShared (math::Matrix* output, math::Matrix* params0, math::Matrix* params1);

  void addDotProduct(math::Matrix* output, math::Matrix* params0, math::Matrix* params1, uintt columns, uintt rows);
  void tensorProduct(math::Matrix* output, math::Matrix* params0, math::Matrix* params1, uintt columns, uintt rows);
  void hadamardProduct(math::Matrix* output, math::Matrix* params0, math::Matrix* params1, uintt columns, uintt rows);
  void hadamardProductVec(math::Matrix* output, math::Matrix* params0, math::Matrix* params1, uintt columns, uintt rows);

  void calculateQTHQ(math::Matrix* output, math::Matrix* H, math::Matrix* Q,
                     math::Matrix* aux);

  inline void dotProductEx(math::Matrix* output, math::Matrix* params0, math::Matrix* params1, MatrixEx* matrixEx);

  /**
   * If output and matrix2 have more rows than columns of matrix1, then next following rows will be multiply as separated matrix.
   * This process will be continue to end of output's rows.
   *
   * If C = A * B and rows of A are lower than rows of C and
   * columns of A are lower than rows of B fo example:
   *
   *              B00 B01 B02
   *              B10 B11 B12
   *              B20 B21 B22
   *              B30 B31 B32
   *              B40 B41 B42
   *              B50 B51 B52
   *
   * A00 A01 A02  C00 C01 C02
   * A10 A11 A12  C10 C11 C12
   * A20 A21 A22  C20 C21 C22
   *              C30 C31 C32
   *              C40 C41 C42
   *              C50 C51 C52
   *
   * then behaviour of this procedure is
   *
   *              B00 B01 B02
   *              B10 B11 B12
   *              B20 B21 B22
   *              B30 B31 B32
   *              B40 B41 B42
   *              B50 B51 B52
   *
   * A00 A01 A02  C00 C01 C02
   * A10 A11 A12  C10 C11 C12
   * A20 A21 A22  C20 C21 C22
   * A00 A01 A02  C30 C31 C32
   * A10 A11 A12  C40 C41 C42
   * A20 A21 A22  C50 C51 C52
   *
   * so for example
   *
   * C10 = A10 * B00 + A11 * B10 + A12 * B30
   * C40 = A10 * B30 + A11 * B40 + A12 * B50
   *
   */
  void dotProductPeriodic (math::Matrix* output, math::Matrix* matrix1, math::Matrix* matrix2);

  /**
  * The same like in dotProductPeriodic but dimensions by matrices are defined by user.
  */
  void dotProductDimPeriodic (math::Matrix* output, math::Matrix* matrix1, math::Matrix* matrix2, uintt dims[3][2], uintt periodicRows);

  void dotProductDimPeriodic (math::Matrix* output, math::Matrix* matrix1, math::Matrix* matrix2, uintt dims[3][2])
  {
    uintt periodicRows = oap::cuda::GetRows(matrix1);
    dotProductDimPeriodic (output, matrix1, matrix2, dims, periodicRows);
  }

  void dotProduct (math::Matrix* output, math::Matrix* matrix1, math::Matrix* matrix2, uintt dims[3][2]);

  void dotProduct (math::Matrix* output, math::Matrix* matrix1, math::Matrix* matrix2,
                   uintt outputD[2], uintt matrix1D[2], uintt matrix2D[2])
  {
    uintt dims[3][2] = {{outputD[0], outputD[1]}, {matrix1D[0], matrix1D[1]}, {matrix2D[0], matrix2D[1]}};

    dotProduct (output, matrix1, matrix2, dims);
  }

  void dotProductEx(math::Matrix* output, math::Matrix* params0,
                    math::Matrix* params1, MatrixEx* matrixEx, uintt columns,
                    uintt rows);

  inline void dotProductOpt(math::Matrix* output, math::Matrix* params0,
                            math::Matrix* params1);

  void dotProductOpt(math::Matrix* output, math::Matrix* params0,
                     math::Matrix* params1, uintt ocolumns, uintt orows,
                     uintt p1rows, uintt p2columns);

  void dotProductExOpt(math::Matrix* output, math::Matrix* params0,
                       math::Matrix* params1, MatrixEx* matrixEx);

  void transposeEx(math::Matrix* output, math::Matrix* params0,
                         MatrixEx* matrixEx);

  void transpose(math::Matrix* output, math::Matrix* params0);

  void conjugateTranspose(math::Matrix* output, math::Matrix* params0);

  inline void substract(math::Matrix* output, math::Matrix* params0, math::Matrix* params1);
  inline void addSubstract(math::Matrix* output, math::Matrix* params0, math::Matrix* params1);

  void crossEntropy(math::Matrix* output, math::Matrix* params0, math::Matrix* params1);

  void substract(math::Matrix* output, math::Matrix* params0, math::Matrix* params1, uintt columns, uintt rows);
  void addSubstract(math::Matrix* output, math::Matrix* params0, math::Matrix* params1, uintt columns, uintt rows);

  inline void add(math::Matrix* output, math::Matrix* params0,
                  math::Matrix* params1);

  void add(math::Matrix* output, math::Matrix* params0, math::Matrix* params1,
           uintt columns, uintt rows);

  void setVector(math::Matrix* output, uintt column, math::Matrix* params0,
                 uintt length);

  void getVector(math::Matrix* vector, uintt length, math::Matrix* matrix,
                 uintt column);

  void getVector(math::Matrix* vector, math::Matrix* matrix, uintt column);

  void magnitude (floatt& output, math::Matrix* params0);

  void sum (floatt& reoutput, floatt& imoutput, math::Matrix* matrix);
  void sum (floatt& reoutput, math::Matrix* matrix);
  //void sumShared (floatt& output, math::Matrix* params0);

  void magnitudeOpt(floatt& output, math::Matrix* params0);

  void magnitudeOptVer2(floatt& output, math::Matrix* params0);

  void magnitude2(floatt& output, math::Matrix* params0);

  void magnitude2Opt(floatt& output, math::Matrix* params0);

  void magnitude2OptVer2(floatt& output, math::Matrix* params0);

  void multiplyReConstant(math::Matrix* v, math::Matrix* f, floatt re);

  void multiplyConstant(math::Matrix* v, math::Matrix* f, floatt re, floatt im);

  void setDiagonal(math::Matrix* matrix, floatt re, floatt im);

  void setIdentity(math::Matrix* matrix);

  void setZeroMatrix(math::Matrix* matrix);

  bool compare(math::Matrix* matrix1, math::Matrix* matrix2, floatt tolerance = 0);

  bool compareVer2(math::Matrix* matrix1, math::Matrix* matrix2, floatt tolerance = 0);

  // Sigmoid function and derivatives
  void sigmoid (math::Matrix* matrix);
  void sigmoid (math::Matrix* matrix, uintt dim[2]);
  void sigmoid (math::Matrix* matrix, uintt dim[2][2]);

  void sigmoid (math::Matrix* output, math::Matrix* matrix);
  void sigmoid (math::Matrix* output, math::Matrix* matrix, uintt dim[2]);
  void sigmoid (math::Matrix* output, math::Matrix* matrix, uintt dim[2][2]);

  void dsigmoid (math::Matrix* omatrix, math::Matrix* imatrix);
  void dsigmoid (math::Matrix* omatrix, math::Matrix* imatrix, uintt dim[2]);
  void dsigmoid (math::Matrix* omatrix, math::Matrix* imatrix, uintt dim[2][2]);

  void multiplyDSigmoid (math::Matrix* omatrix, math::Matrix* matrix);
  void multiplyDSigmoid (math::Matrix* omatrix, math::Matrix* matrix, uintt dim[2]);
  void multiplyDSigmoid (math::Matrix* omatrix, math::Matrix* matrix, uintt dim[2][2]);

  // Linear function and derivatives
  void linear (math::Matrix* output, math::Matrix* matrix);
  void linear (math::Matrix* output, math::Matrix* matrix, uintt dim[2]);
  void linear (math::Matrix* output, math::Matrix* matrix, uintt dim[2][2]);

  void dlinear (math::Matrix* output, math::Matrix* matrix);
  void dlinear (math::Matrix* output, math::Matrix* matrix, uintt dim[2]);
  void dlinear (math::Matrix* output, math::Matrix* matrix, uintt dim[2][2]);

  // Tanh/tanh function and derivatives
  void tanh (math::Matrix* output, math::Matrix* matrix);
  void tanh (math::Matrix* output, math::Matrix* matrix, uintt dim[2]);
  void tanh (math::Matrix* output, math::Matrix* matrix, uintt dim[2][2]);

  void dtanh (math::Matrix* output, math::Matrix* matrix);
  void dtanh (math::Matrix* output, math::Matrix* matrix, uintt dim[2]);
  void dtanh (math::Matrix* output, math::Matrix* matrix, uintt dim[2][2]);

  // Sin/sin function and derivatives
  void sin (math::Matrix* output, math::Matrix* matrix);
  void sin (math::Matrix* output, math::Matrix* matrix, uintt dim[2]);
  void sin (math::Matrix* output, math::Matrix* matrix, uintt dim[2][2]);

  void dsin (math::Matrix* output, math::Matrix* matrix);
  void dsin (math::Matrix* output, math::Matrix* matrix, uintt dim[2]);
  void dsin (math::Matrix* output, math::Matrix* matrix, uintt dim[2][2]);

  void multiplyDSin (math::Matrix* output, math::Matrix* matrix);
  void multiplyDSin (math::Matrix* output, math::Matrix* matrix, uintt dim[2]);
  void multiplyDSin (math::Matrix* output, math::Matrix* matrix, uintt dim[2][2]);

  inline void cos (math::Matrix* output, math::Matrix* matrix)
  {
    dsin (output, matrix);
  }

  floatt getCompareOperationSum() const;

  void QRGR(math::Matrix* Q, math::Matrix* R, math::Matrix* H, math::Matrix* R1,
            math::Matrix* Q1, math::Matrix* G, math::Matrix* GT);

  void QRHT (math::Matrix* Q, math::Matrix* R, math::Matrix* A, math::Matrix* V, math::Matrix* VT, math::Matrix* P, math::Matrix* VVT);

  bool isUpperTriangular(math::Matrix* matrix);

  void calcTriangularH (math::Matrix* H, math::Matrix* Q, math::Matrix* R,
                        math::Matrix* aux1, math::Matrix* aux2, math::Matrix* aux3,
                        math::Matrix* aux4, math::Matrix* aux5, math::Matrix* aux6);

  void calcTriangularHStep (math::Matrix* H, math::Matrix* Q, math::Matrix* R,
                            math::Matrix* aux1, math::Matrix* aux2, math::Matrix* aux3,
                            math::Matrix* aux4, math::Matrix* aux5, math::Matrix* aux6);

  std::string getMsgStatus() const;

 private:
  enum QRType { NORMAL, OPT };
  enum Type { HOST, CUDA };

  bool m_cuStatus;

  int* m_doutputIsTriangular;
  floatt* m_magnitudeOutput;

  bool m_isIntialized;
  oap::cuda::Kernel m_kernel;
  uintt m_maxThreadsPerBlock;
  floatt m_compareOperationOutput;

  uintt m_columns;
  uintt m_rows;

  bool m_isSetColumns;
  bool m_isSetRows;

  uint m_blocks[2];
  uint m_threads[2];

  void init();

  void calculateDims (uint blocks[2], uint threads[2], uintt w, uintt h);
  void prepareDims (uintt w, uintt h);

  enum Types
  {
    MATRIX,
    SCALAR
  };

  bool execute(const char* functionName, uintt w, uintt h, void** params, uintt sharedMemory, bool _prepareDims = true);


  void qrProcedure(QRType qrType, math::Matrix* Q, math::Matrix* R,
                   math::Matrix* A, math::Matrix* AT, math::Matrix* P,
                   math::Matrix* I, math::Matrix* v, math::Matrix* vt,
                   math::Matrix* vvt);

  floatt compareProcedure(const char* cuKernelName, math::Matrix* matrix1,
                        math::Matrix* matrix2, uintt w, uintt h, uintt wthreads,
                        uintt hthreads);

  floatt magnitude2Procedure(const char* cuKernelName, math::Matrix* matrix1,
                             uintt wthreads, uintt hthreads);

  floatt magnitude2Procedure_GetOutput(uint blocks[2], uintt outputSize) const;

  void deallocKernelArrays ();

  inline void resetFlags() {
    m_isSetRows = false;
    m_isSetColumns = false;
  }
private:

  static uintt GetColumns(const math::Matrix* matrix);
  static uintt GetRows(const math::Matrix* matrix);

  oap::TBuffer<floatt, oap::Type::CUDA> m_dcompareOutputBuffer;
  oap::TBuffer<floatt, oap::Type::CUDA> m_dcompareBuffer;
  oap::TBuffer<floatt, oap::Type::HOST> m_hcompareOutputBuffer;
  oap::TBuffer<floatt, oap::Type::CUDA> m_magnitudeBuffer;
  oap::TBuffer<floatt, oap::Type::CUDA> m_dmagnitudeOutputBuffer;
  oap::TBuffer<floatt, oap::Type::CUDA> m_dmagnitudeBuffer;
  oap::TBuffer<floatt, oap::Type::HOST> m_hmagnitudeOutputBuffer;
  oap::TBuffer<int, oap::Type::CUDA> m_disuppertriangularOutputBuffer;
  oap::TBuffer<int, oap::Type::HOST> m_hisuppertriangularOutputBuffer;
  oap::TBuffer<floatt, oap::Type::CUDA> m_dqrSums;
  oap::TBuffer<floatt, oap::Type::CUDA> m_dqrBuffer;
  oap::TBuffer<floatt, oap::Type::CUDA> m_dsumsReBuffer;
  oap::TBuffer<floatt, oap::Type::CUDA> m_dsumsImBuffer;
  oap::TBuffer<floatt, oap::Type::HOST> m_hsumsReBuffer;
  oap::TBuffer<floatt, oap::Type::HOST> m_hsumsImBuffer;

  MatrixEx* m_dMatrixEx = nullptr;
  std::map<size_t, uint*> m_kernelArrays;

  uintt* createKernelArray (uintt* hostArray, size_t length)
  {
    auto it = m_kernelArrays.find (length);
    if (it == m_kernelArrays.end ())
    {
      uintt* kernelArray = static_cast<uintt*>(CudaUtils::AllocDeviceMem (length * sizeof(uintt)));
      m_kernelArrays[length] = kernelArray;
    }

    uintt* array = m_kernelArrays [length];
    CudaUtils::CopyHostToDevice (array, hostArray, length * sizeof(uintt));

    return array;
  }

  MatrixEx* createDeviceMatrixEx(const MatrixEx& host)
  {
    if (m_dMatrixEx == nullptr)
    {
      m_dMatrixEx = oap::cuda::NewDeviceMatrixExCopy (host);
    }

    CudaUtils::CopyHostToDevice (m_dMatrixEx, &host, sizeof(MatrixEx));
    return m_dMatrixEx;
  }

  oap::generic::BasicMatrixApi<decltype(oap::cuda::GetMatrixInfo)> m_bmApi;
  std::function<void()> m_preExecCallback;//(std::bind(&CuProceduresApi::resetFlags, this)
  std::function<uintt*(uintt*, uintt)> m_createKernelArray;
};

inline void CuProceduresApi::addDotProduct(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
#ifdef CU_PROCEDURES_API_PRINT
  debug(__func__);
#endif
#ifdef DEBUG
  CHECK_MATRIX(output);
  CHECK_MATRIX(params0);
  CHECK_MATRIX(params1);
#endif
  const uintt output_columns = CudaUtils::GetColumns(output);
  const uintt output_rows = CudaUtils::GetRows(output);

  addDotProduct(output, params0, params1, output_columns, output_rows);
}

inline void CuProceduresApi::tensorProduct(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
#ifdef CU_PROCEDURES_API_PRINT
  debug(__func__);
#endif
#ifdef DEBUG
  CHECK_MATRIX(output);
  CHECK_MATRIX(params0);
  CHECK_MATRIX(params1);
#endif

  const uintt output_columns = CudaUtils::GetColumns(output);
  const uintt output_rows = CudaUtils::GetRows(output);

  tensorProduct (output, params0, params1, output_columns, output_rows);
}

inline void CuProceduresApi::hadamardProduct(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
#ifdef CU_PROCEDURES_API_PRINT
  debug(__func__);
#endif
#ifdef DEBUG
  CHECK_MATRIX(output);
  CHECK_MATRIX(params0);
  CHECK_MATRIX(params1);
#endif

  const uintt output_columns = CudaUtils::GetColumns(output);
  const uintt output_rows = CudaUtils::GetRows(output);

  hadamardProduct (output, params0, params1, output_columns, output_rows);
}

inline void CuProceduresApi::hadamardProductVec(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
#ifdef CU_PROCEDURES_API_PRINT
  debug(__func__);
#endif
#ifdef DEBUG
  CHECK_MATRIX(output);
  CHECK_MATRIX(params0);
  CHECK_MATRIX(params1);
#endif

  const uintt output_columns = CudaUtils::GetColumns(output);
  const uintt output_rows = CudaUtils::GetRows(output);

  hadamardProductVec (output, params0, params1, output_columns, output_rows);
}

inline void CuProceduresApi::dotProductEx(math::Matrix* output, math::Matrix* params0,
                                   math::Matrix* params1, MatrixEx* matrixEx) {
  const uintt columns = CudaUtils::GetColumns(matrixEx);
  const uintt rows = CudaUtils::GetRows(matrixEx);
  dotProductEx(output, params0, params1, matrixEx, columns, rows);
}

inline void CuProceduresApi::dotProductOpt(math::Matrix* output, math::Matrix* params0,
                                    math::Matrix* params1) {
  const uintt ocolumns = oap::cuda::GetColumns(output);
  const uintt orows = oap::cuda::GetRows(output);
  const uintt p1rows = oap::cuda::GetRows(params0);
  const uintt p2columns = oap::cuda::GetColumns(params1);
  dotProductOpt(output, params0, params1, ocolumns, orows, p1rows, p2columns);
}

inline void CuProceduresApi::substract(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  const uintt columns = oap::cuda::GetColumns(output);
  const uintt rows = oap::cuda::GetRows(output);
  substract(output, params0, params1, columns, rows);
}

inline void CuProceduresApi::addSubstract(math::Matrix* output, math::Matrix* params0, math::Matrix* params1)
{
  const uintt columns = oap::cuda::GetColumns(output);
  const uintt rows = oap::cuda::GetRows(output);
  addSubstract(output, params0, params1, columns, rows);
}

inline void CuProceduresApi::add(math::Matrix* output, math::Matrix* params0,
                          math::Matrix* params1) {
  const uintt columns = oap::cuda::GetColumns(output);
  const uintt rows = oap::cuda::GetRows(output);
  add(output, params0, params1, columns, rows);
}

}

#endif /* MATRIXPROCEDURES_H */
