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

#ifndef OAP_HOST_MATRIX_UTILS_H
#define OAP_HOST_MATRIX_UTILS_H

#include "ByteBuffer.h"
#include "Logger.h"

#include "Matrix.h"
#include "MatrixInfo.h"
#include "MatrixEx.h"
#include "MatrixUtils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>

#define PRINT_MATRIX(m) logInfo ("%s %p\n%s %s", #m, m, oap::host::to_string(m).c_str(), oap::host::GetMatrixInfo(m).toString().c_str());
#define PRINT_DIMS_3_2(m) logInfo ("%s dims = {{%u, %u}, {%u, %u}, {%u, %u}} ", #m, m[0][0], m[0][1], m[1][0], m[1][1], m[2][0], m[2][1]);
#define PRINT_DIMS_2_2_2(m) logInfo ("%s dims = {{{%u, %u}, {%u, %u}}, {{%u, %u}, {%u, %u}}} ", #m, m[0][0][0], m[0][0][1], m[0][1][0], m[0][1][1], m[1][0][0], m[1][0][1], m[1][1][0], m[1][1][1]);

namespace oap
{
namespace host
{

/**
 * @brief NewMatrix
 * @param columns
 * @param rows
 * @param value
 * @return
 */
math::Matrix* NewMatrix(uintt columns, uintt rows, floatt value = 0);

math::Matrix* NewMatrixCopyOfArray (uintt columns, uintt rows, const floatt* rearray, const floatt* imarray);
math::Matrix* NewReMatrixCopyOfArray (uintt columns, uintt rows, const floatt* rearray);
math::Matrix* NewImMatrixCopyOfArray (uintt columns, uintt rows, const floatt* imarray);

/**
 * @brief NewMatrix - creates new matrix, which has the same size
 *                    and im and re part like passed matrix. Values
 *                    of output are specyfied by user.
 * @param matrix
 * @param value
 * @return
 */
math::Matrix* NewMatrixRef(const math::Matrix* matrix, floatt value = 0);

/**
 * @brief NewMatrix
 * @param matrix
 * @param columns
 * @param rows
 * @param value
 * @return
 */
math::Matrix* NewMatrix(const math::Matrix* matrix, uintt columns, uintt rows,
                        floatt value = 0);


math::Matrix* NewMatrix(const math::MatrixInfo& matrixInfo, floatt value = 0);

/**
 * @brief NewMatrix
 * @param isre
 * @param isim
 * @param columns
 * @param rows
 * @param value
 * @return
 */
math::Matrix* NewMatrix (bool isre, bool isim, uintt columns, uintt rows, floatt value = 0);

inline math::Matrix* NewHostMatrix (bool isre, bool isim, uintt columns, uintt rows)
{
  return NewMatrix (isre, isim, columns, rows, 0);
}

inline math::Matrix* NewHostMatrixFromMatrixInfo (const math::MatrixInfo& minfo)
{
  return NewMatrix (minfo.isRe, minfo.isIm, minfo.columns(), minfo.rows(), 0);
}

/**
 * @brief NewReMatrix
 * @param columns
 * @param rows
 * @param value
 * @return
 */
math::Matrix* NewReMatrix(uintt columns, uintt rows, floatt value = 0);

/**
 * @brief NewImMatrix
 * @param columns
 * @param rows
 * @param value
 * @return
 */
math::Matrix* NewImMatrix(uintt columns, uintt rows, floatt value = 0);

/**
 * @brief NewMatrix
 * @param text
 * @return
 */
math::Matrix* NewMatrix(const std::string& text);

inline void CopyBuffer(floatt* dst, floatt* src, uintt length)
{
  memcpy(dst, src, length * sizeof(floatt));
}

/**
 * @brief CopyMatrix
 * @param dst
 * @param src
 */
void CopyMatrix(math::Matrix* dst, const math::Matrix* src);

inline void CopyHostMatrixToHostMatrix (math::Matrix* dst, const math::Matrix* src)
{
  CopyMatrix (dst, src);
}

void CopyMatrixDims (math::Matrix* dst, const math::Matrix* src, uintt dims[2][2][2]);

inline void CopyHostMatrixToHostMatrixDims (math::Matrix* dst, const math::Matrix* src, uintt dims[2][2][2])
{
  CopyMatrixDims (dst, src, dims);
}

inline uintt GetColumns (const math::Matrix* matrix)
{
  return matrix->columns;
}

inline uintt GetRows (const math::Matrix* matrix)
{
  return matrix->rows;
}

/**
 * Copy data to dst matrix which has one column and row less than
 * src matrix. Row and column which will be omitted are added as params..
 * @param dst
 * @param src
 * @param column index of column which will be omitted
 * @param row index of row which will be omitted
 */
void Copy(math::Matrix* dst, const math::Matrix* src, uintt column, uintt row);

/**
 * @brief Copy
 * @param dst
 * @param src
 * @param MatrixEx
 */
void Copy(math::Matrix* dst, const math::Matrix* src, const MatrixEx& matrixEx);

/**
 * @brief CopyRe
 * @param dst
 * @param src
 */
void CopyRe(math::Matrix* dst, const math::Matrix* src);

/**
 * @brief CopyIm
 * @param dst
 * @param src
 */
void CopyIm(math::Matrix* dst, const math::Matrix* src);

template<typename T>
void Copy(floatt* dst, T* src, uint length)
{
  debugFunc();
  if (dst == NULL || src == NULL)
  {
    return;
  }
  for (uint idx = 0; idx < length; ++idx)
  {
    dst[idx] = src[idx];
  }
}

template<>
inline void Copy<floatt>(floatt* dst, floatt* src, uint length)
{
  debugFunc();
  if (dst == NULL || src == NULL)
  {
    return;
  }
  memcpy(dst, src, sizeof(floatt) * length);
}

template<typename T>
void Copy(math::Matrix* dst, T* rearray, T* imarray)
{
  Copy(dst->reValues, rearray, dst->columns * dst->rows);
  Copy(dst->imValues, imarray, dst->columns * dst->rows);
}

template<typename T>
void CopyRe(math::Matrix* dst, T* array)
{
  Copy(dst->reValues, array, dst->columns * dst->rows);
}

template<typename T>
void CopyIm(math::Matrix* dst, T* array)
{
  Copy(dst->imValues, array, dst->columns * dst->rows);
}

/**
 * @brief NewMatrixCopy
 * @param matrix
 * @return
 */
math::Matrix* NewMatrixCopy(const math::Matrix* matrix);

template<typename T>
math::Matrix* NewMatrixCopy(uint columns, uint rows, T* reArray, T* imArray)
{
  math::Matrix* output = oap::host::NewMatrix(reArray != NULL, imArray != NULL, columns, rows);
  oap::host::Copy<T>(output, reArray, imArray);
  return output;
}

template<typename T>
math::Matrix* NewReMatrixCopy(uint columns, uint rows, T* reArray)
{
  math::Matrix* output = oap::host::NewMatrix(reArray != NULL, false, columns, rows);
  oap::host::CopyRe<T>(output, reArray);
  return output;
}

template<typename T>
math::Matrix* NewImMatrixCopy(uint columns, uint rows, T* imArray)
{
  math::Matrix* output = oap::host::NewMatrix(false, imArray != NULL, columns, rows);
  oap::host::CopyIm<T>(output, imArray);
  return output;
}

/**
 * @brief DeleteMatrix
 * @param matrix
 */
void DeleteMatrix(const math::Matrix* matrix);

/**
 * @brief GetReValue
 * @param matrix
 * @param column
 * @param row
 * @return
 */
floatt GetReValue(const math::Matrix* matrix, uintt column, uintt row);

/**
 * @brief SetReValue
 * @param matrix
 * @param column
 * @param row
 * @param value
 */
void SetReValue(const math::Matrix* matrix, uintt column, uintt row,
                floatt value);

/**
 * @brief GetImValue
 * @param matrix
 * @param column
 * @param row
 * @return
 */
floatt GetImValue(const math::Matrix* matrix, uintt column, uintt row);

/**
 * @brief SetImValue
 * @param matrix
 * @param column
 * @param row
 * @param value
 */
void SetImValue(const math::Matrix* matrix, uintt column, uintt row, floatt value);

std::string GetMatrixStr(const math::Matrix* matrix);

inline std::string to_string (const math::Matrix* matrix)
{
  return GetMatrixStr (matrix);
}

void ToString(std::string& str, const math::Matrix* matrix);

void PrintMatrix(FILE* stream, const matrixUtils::PrintArgs& args, const math::Matrix* matrix);
void PrintMatrix(FILE* stream, const math::Matrix* matrix, const matrixUtils::PrintArgs& args = matrixUtils::PrintArgs());

void PrintMatrix(const matrixUtils::PrintArgs& args, const math::Matrix* matrix);
void PrintMatrix(const math::Matrix* matrix, const matrixUtils::PrintArgs& args = matrixUtils::PrintArgs());

bool PrintMatrixToFile(const std::string& path, const matrixUtils::PrintArgs& args, const math::Matrix* matrix);
bool PrintMatrixToFile(const std::string& path, const math::Matrix* matrix, const matrixUtils::PrintArgs& args = matrixUtils::PrintArgs());

/**
 * @brief PrintImMatrix
 * @param stream
 * @param matrix
 */
void PrintImMatrix(FILE* stream, const math::Matrix* matrix);

/**
 * @brief PrintImMatrix
 * @param matrix
 */
void PrintImMatrix(const math::Matrix* matrix);

/**
 * @brief PrintImMatrix
 * @param text
 * @param matrix
 */
void PrintImMatrix(const std::string& text, const math::Matrix* matrix);

void SetVector(math::Matrix* matrix, uintt column, math::Matrix* vector);

void SetVector(math::Matrix* matrix, uintt column, floatt* revector,
               floatt* imvector, uintt length);

/**
 * @brief SetReVector
 * @param matrix
 * @param column
 * @param vector
 * @param length
 */
void SetReVector(math::Matrix* matrix, uintt column, floatt* vector,
                 uintt length);

/**
 * @brief SetTransposeReVector
 * @param matrix
 * @param row
 * @param vector
 * @param length
 */
void SetTransposeReVector(math::Matrix* matrix, uintt row, floatt* vector,
                          uintt length);

/**
 * @brief SetImVector
 * @param matrix
 * @param column
 * @param vector
 * @param length
 */
void SetImVector(math::Matrix* matrix, uintt column, floatt* vector,
                 uintt length);

/**
 * @brief SetTransposeImVector
 * @param matrix
 * @param row
 * @param vector
 * @param length
 */
void SetTransposeImVector(math::Matrix* matrix, uintt row, floatt* vector,
                          uintt length);

/**
 * @brief SetReVector
 * @param matrix
 * @param column
 * @param vector
 */
void SetReVector(math::Matrix* matrix, uintt column, floatt* vector);

/**
 * @brief SetTransposeReVector
 * @param matrix
 * @param row
 * @param vector
 */
void SetTransposeReVector(math::Matrix* matrix, uintt row, floatt* vector);

/**
 * @brief SetImVector
 * @param matrix
 * @param column
 * @param vector
 */
void SetImVector(math::Matrix* matrix, uintt column, floatt* vector);

/**
 * @brief SetTransposeImVector
 * @param matrix
 * @param row
 * @param vector
 */
void SetTransposeImVector(math::Matrix* matrix, uintt row, floatt* vector);

void GetVector(math::Matrix* vector, math::Matrix* matrix, uintt column);

void GetVector(floatt* revector, floatt* imvector, uint length,
               math::Matrix* matrix, uint column);

void GetTransposeVector(math::Matrix* vector, math::Matrix* matrix, uint column);

void GetTransposeReVector(math::Matrix* vector, math::Matrix* matrix, uint column);

void GetTransposeImVector(math::Matrix* vector, math::Matrix* matrix, uint column);

/**
 * @brief GetReVector
 * @param vector
 * @param length
 * @param matrix
 * @param column
 */
void GetReVector(floatt* vector, uint length, math::Matrix* matrix, uint column);

/**
 * @brief GetTransposeReVector
 * @param vector
 * @param length
 * @param matrix
 * @param row
 */
void GetTransposeReVector(floatt* vector, uint length, math::Matrix* matrix, uint row);

/**
 * @brief GetImVector
 * @param vector
 * @param length
 * @param matrix
 * @param column
 */
void GetImVector(floatt* vector, uint length, math::Matrix* matrix, uint column);

/**
 * @brief GetTransposeImVector
 * @param vector
 * @param length
 * @param matrix
 * @param row
 */
void GetTransposeImVector(floatt* vector, uint length, math::Matrix* matrix, uint row);

/**
 * @brief GetReVector
 * @param vector
 * @param matrix
 * @param column
 */
void GetReVector(floatt* vector, math::Matrix* matrix, uint column);

/**
 * @brief GetTransposeReVector
 * @param vector
 * @param matrix
 * @param row
 */
void GetTransposeReVector(floatt* vector, math::Matrix* matrix, uint row);

/**
 * @brief GetImVector
 * @param vector
 * @param matrix
 * @param column
 */
void GetImVector(floatt* vector, math::Matrix* matrix, uint column);

/**
 * @brief GetTransposeImVector
 * @param vector
 * @param matrix
 * @param row
 */
void GetTransposeImVector(floatt* vector, math::Matrix* matrix, uint row);

/**
 * @brief SetIdentity
 * @param matrix
 */
void SetIdentity(math::Matrix* matrix);

/**
 * @brief SetIdentityMatrix
 * @param matrix
 */
void SetIdentityMatrix(math::Matrix* matrix);

/**
 * @brief SmallestDiff
 * @param matrix
 * @param matrix1
 * @return
 */
floatt SmallestDiff(math::Matrix* matrix, math::Matrix* matrix1);

/**
 * @brief LargestDiff
 * @param matrix
 * @param matrix1
 * @return
 */
floatt LargestDiff(math::Matrix* matrix, math::Matrix* matrix1);

/**
 * @brief GetTrace
 * @param matrix
 * @return
 */
floatt GetTrace(math::Matrix* matrix);

/**
 * @brief SetReZero
 * @param matrix
 */
void SetReZero(math::Matrix* matrix);

/**
 * @brief SetImZero
 * @param matrix
 */
void SetImZero(math::Matrix* matrix);

/**
 * @brief SetZero
 * @param matrix
 */
void SetZero(math::Matrix* matrix);

/**
 * @brief IsEquals
 * @param matrix
 * @param matrix1
 * @param diff
 * @return
 */
bool IsEquals(math::Matrix* matrix, math::Matrix* matrix1, floatt diff = 0.1);

/**
 * @brief SetSubs
 * @param matrix
 * @param subcolumns
 * @param subrows
 */
void SetSubs(math::Matrix* matrix, uintt subcolumns, uintt subrows);

/**
 * @brief SetSubColumns
 * @param matrix
 * @param subcolumns
 */
void SetSubColumns(math::Matrix* matrix, uintt subcolumns);

/**
 * @brief SetSubRows
 * @param matrix
 * @param subrows
 */
void SetSubRows(math::Matrix* matrix, uintt subrows);

/**
 * @brief SetSubsSafe
 * @param matrix
 * @param subcolumns
 * @param subrows
 */
void SetSubsSafe(math::Matrix* matrix, uintt subcolumns, uintt subrows);

/**
 * @brief SetSubColumnsSafe
 * @param matrix
 * @param subcolumns
 */
void SetSubColumnsSafe(math::Matrix* matrix, uintt subcolumns);

/**
 * @brief SetSubRowsSafe
 * @param matrix
 * @param subrows
 */
void SetSubRowsSafe(math::Matrix* matrix, uintt subrows);

/**
 * @brief SetDiagonalMatrix
 * @param matrix
 * @param a
 */
void SetDiagonalMatrix(math::Matrix* matrix, floatt a);

/**
 * @brief SetDiagonalReMatrix
 * @param matrix
 * @param a
 */
void SetDiagonalReMatrix(math::Matrix* matrix, floatt a);

/**
 * @brief SetDiagonalImMatrix
 * @param matrix
 * @param a
 */
void SetDiagonalImMatrix(math::Matrix* matrix, floatt a);

math::MatrixInfo CreateMatrixInfo (const math::Matrix* matrix);

math::MatrixInfo GetMatrixInfo (const math::Matrix* matrix);

math::Matrix* ReadMatrix(const std::string& path);

math::Matrix* ReadRowVector(const std::string& path, size_t index);

math::Matrix* ReadColumnVector(const std::string& path, size_t index);

void CopyReBuffer (math::Matrix* houput, math::Matrix* hinput);

/**
 * @brief Save matrix to file
 * 4 byte - size of boolean variable
 * 4 byte - size of uintt variable (where uintt - oap specyfied during compilation type)
 * 4 byte - size of floatt variable (where floatt - oap specyfied during compilation type)
 * size of uintt - count of columnts
 * size of uintt - count of rows
 * size of boolean - is re section
 * size of boolean - is im section
 * if the first boolean is true:
 *  columns * rows * sizeoffloatt - re part of matrix
 * if the second boolean is true:
 *  columns * rows * sizeoffloatt - im part of matrix
 */
bool WriteMatrix(const std::string& path, const math::Matrix* matrix);

inline bool IsReMatrix(math::Matrix* m)
{
  return m != NULL && m->reValues != NULL;
}

inline bool IsImMatrix(math::Matrix* m)
{
  return m != NULL && m->imValues != NULL;
}

void CopySubMatrix(math::Matrix* dst, const math::Matrix* src, uintt cindex, uintt rindex);

math::Matrix* NewSubMatrix (const math::Matrix* orig, uintt cindex, uintt rindex, uintt clength, uintt rlength);

math::Matrix* GetSubMatrix (const math::Matrix* orig, uintt cindex, uintt rindex, math::Matrix* matrix);

void SaveMatrix (const math::Matrix* matrix, utils::ByteBuffer& buffer);
void SaveMatrixInfo (const math::MatrixInfo& minfo, utils::ByteBuffer& buffer);

math::Matrix* LoadMatrix (const utils::ByteBuffer& buffer);
math::MatrixInfo LoadMatrixInfo (const utils::ByteBuffer& buffer);

void CopyArrayToMatrix (math::Matrix* matrix, const floatt* rebuffer, const floatt* imbuffer);
void CopyArrayToReMatrix (math::Matrix* matrix, const floatt* buffer);
void CopyArrayToImMatrix (math::Matrix* matrix, const floatt* buffer);

inline void SetReValueToMatrix (math::Matrix* matrix, floatt value, size_t idx = 0)
{
  matrix->reValues[idx] = value;
}

inline void SetReValuesToMatrix (math::Matrix* matrix, const std::vector<floatt>& vec)
{
  debugAssert (vec.size() <= matrix->columns * matrix->rows);
  memcpy (matrix->reValues, vec.data(), sizeof(floatt) * vec.size());
}

inline void SetReValuesToMatrix (math::Matrix* matrix, floatt* array, size_t length)
{
  debugAssert (length <= matrix->columns * matrix->rows);
  memcpy (matrix->reValues, array, sizeof(floatt) * length);
}

template<typename Tuple, size_t Tidx = 0>
void SetReValuesToMatrix (math::Matrix* matrix, const std::vector<Tuple>& vecl)
{
  std::vector<floatt> vec;
  vec.reserve (vecl.size());
  for (auto it = vecl.begin(); it != vecl.end(); ++it)
  {
    vec.push_back (std::get<Tidx>(*it));
  }

  SetReValuesToMatrix (matrix, vec.data(), vec.size());
}

inline floatt* GetValue(floatt* const* ptr)
{
  return *ptr;
}

}
namespace generic
{
inline void initDims (uintt dims[2][2][2], const math::MatrixInfo& dist, const math::MatrixInfo& src)
{
  dims[0][0][0] = 0;
  dims[0][0][1] = dist.columns();

  dims[0][1][0] = 0;
  dims[0][1][1] = dist.rows();

  dims[1][0][0] = 0;
  dims[1][0][1] = src.columns();

  dims[1][1][0] = 0;
  dims[1][1][1] = src.rows();
}

inline void initDims (uintt dims[2][2][2], const math::MatrixInfo& minfo)
{
  initDims (dims, minfo, minfo);
}

inline void initDims (uintt dims[2][2][2], const math::Matrix* matrix)
{
  initDims (dims, oap::host::GetMatrixInfo (matrix));
}

const uintt g_srcIdx = 1;
const uintt g_dstIdx = 0;

inline void setColumnIdx (uintt v, uintt dims[2][2])
{
  dims[0][0] = v;
}

inline void setRowIdx (uintt v, uintt dims[2][2])
{
  dims[1][0] = v;
}

inline void setColumns (uintt v, uintt dims[2][2])
{
  dims[0][1] = v;
}

inline void setRows (uintt v, uintt dims[2][2])
{
  dims[1][1] = v;
}

inline uintt getColumnIdx (uintt dims[2][2])
{
  return dims[0][0];
}

inline uintt getRowIdx (uintt dims[2][2])
{
  return dims[1][0];
}

inline uintt getColumns (uintt dims[2][2])
{
  return dims[0][1];
}

inline uintt getRows (uintt dims[2][2])
{
  return dims[1][1];
}

inline math::MatrixInfo check_CopyMatrixToMatrix (const math::MatrixInfo& dstInfo, const math::MatrixInfo& srcInfo)
{
  debugAssert (dstInfo.columns() == srcInfo.columns());
  debugAssert (dstInfo.rows() == srcInfo.rows());
  debugAssert (dstInfo.isRe == srcInfo.isRe);
  debugAssert (dstInfo.isIm == srcInfo.isIm);

  return dstInfo;
}

inline math::MatrixInfo check_CopyMatrixToMatrixDims (const math::MatrixInfo& dstInfo, const math::MatrixInfo& srcInfo, uintt dims[2][2][2])
{
  debugAssert (getRows (dims[g_srcIdx]) == getRows (dims[g_dstIdx]));
  debugAssert (getColumns (dims[g_srcIdx]) == getColumns (dims[g_dstIdx]));
  debugAssert (dstInfo.isRe == srcInfo.isRe);
  debugAssert (dstInfo.isIm == srcInfo.isIm);

  debugAssert (getColumnIdx (dims[g_srcIdx]) + getColumns (dims[g_srcIdx]) <= srcInfo.columns());
  debugAssert (getRowIdx (dims[g_srcIdx]) + getRows (dims[g_srcIdx]) <= srcInfo.rows());

  debugAssert (getColumnIdx (dims[g_dstIdx]) + getColumns (dims[g_dstIdx]) <= dstInfo.columns());
  debugAssert (getRowIdx (dims[g_dstIdx]) + getRows (dims[g_dstIdx]) <= dstInfo.rows());

  return dstInfo;
}

template<typename CopyBuffer, typename MatrixMemoryApi>
void copyMatrixToMatrix (math::Matrix* dst, const math::Matrix* src, CopyBuffer&& copyBuffer, MatrixMemoryApi& dstApi, MatrixMemoryApi& srcApi, bool check = true)
{
  math::MatrixInfo minfo;
  math::MatrixInfo dstInfo = dstApi.getMatrixInfo (dst);

  if (check)
  {
    math::MatrixInfo srcInfo = srcApi.getMatrixInfo (src);
    minfo = check_CopyMatrixToMatrix (dstInfo, srcInfo);
  }
  else
  {
    minfo = dstInfo;
  }

  uintt length = minfo.rows() * minfo.columns();

  auto copyValues = [&](floatt* const* ptr, floatt* const* ptr1)
  {
    floatt* values = dstApi.transferValueToHost (ptr);
    floatt* values1 = srcApi.transferValueToHost (ptr1);

    copyBuffer (values, values1, sizeof(floatt) * length);
  };

  if (minfo.isRe)
  {
    copyValues (&dst->reValues, &src->reValues);
  }

  if (minfo.isIm)
  {
    copyValues (&dst->imValues, &src->imValues);
  }
}

template<typename CopyBuffer, typename MatrixApi>
void copyMatrixToMatrixDims (math::Matrix* dst, const math::Matrix* src, uintt dims[2][2][2], CopyBuffer&& copyBuffer, MatrixApi& dstApi, MatrixApi& srcApi)
{
  math::MatrixInfo minfo;
  auto dstInfo = dstApi.getMatrixInfo (dst);
  auto srcInfo = srcApi.getMatrixInfo (src);

  minfo = check_CopyMatrixToMatrixDims (dstInfo, srcInfo, dims);

  uintt length = getColumns (dims[g_dstIdx]);

  uintt dstOffset = getColumnIdx (dims[g_dstIdx]) + dstInfo.columns() * getRowIdx (dims[g_dstIdx]);
  uintt srcOffset = getColumnIdx (dims[g_srcIdx]) + srcInfo.columns() * getRowIdx (dims[g_srcIdx]);

  auto copyValues = [&](floatt* const* ptr, floatt* const* ptr1)
  {
    floatt* values = dstApi.transferValueToHost (ptr);
    floatt* values1 = srcApi.transferValueToHost (ptr1);

    for (uintt row = 0; row < getRows (dims[g_dstIdx]); ++row)
    {
      floatt* V = values + dstOffset + dstInfo.columns() * row;
      floatt* V1 = values1 + srcOffset + srcInfo.columns() * row;
      copyBuffer (V, V1, sizeof(floatt) * length);
    }
  };

  if (minfo.isRe)
  {
    copyValues (&dst->reValues, &src->reValues);
  }

  if (minfo.isIm)
  {
    copyValues (&dst->imValues, &src->imValues);
  }
}

}
}

#endif /* OAP_HOST_MATRIX_UTILS_H */
