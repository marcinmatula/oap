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

#ifndef CUMAGNITUDEOPTPROCEDURES_H
#define	CUMAGNITUDEOPTPROCEDURES_H

#include "CuCore.h"
#include "CuMagnitudeUtils.h"
#include "CuMatrixUtils.h"
#include <stdio.h>
#include "Matrix.h"
#include "MatrixEx.h"

__hostdevice__ void CUDA_magnitudeOptRealMatrix (floatt* sum, math::Matrix* matrix1, floatt* buffer)
{
  HOST_INIT();
  uintt xlength = aux_GetLength(blockIdx.x, blockDim.x, matrix1->columns);
  uintt ylength = aux_GetLength(blockIdx.y, blockDim.y, matrix1->rows);
  uintt sharedLength = xlength * ylength;
  uintt sharedIndex = threadIdx.y * xlength + threadIdx.x;
  cuda_MagnitudeRealOpt(buffer, sharedIndex, matrix1);
  threads_sync();
  do
  {
    cuda_SumValues(buffer, sharedIndex, sharedLength, xlength, ylength);
    sharedLength = sharedLength / 2;
    threads_sync();
  }
  while (sharedLength > 1);
  if (threadIdx.x == 0 && threadIdx.y == 0)
  {
    sum[gridDim.x * blockIdx.y + blockIdx.x] = buffer[0];
  }
}

__hostdevice__ void CUDA_magnitudeOptReMatrix (floatt* sum, math::Matrix* matrix1, floatt* buffer)
{
  HOST_INIT();
  uintt xlength = aux_GetLength(blockIdx.x, blockDim.x, matrix1->columns);
  uintt ylength = aux_GetLength(blockIdx.y, blockDim.y, matrix1->rows);
  uintt sharedLength = xlength * ylength;
  uintt sharedIndex = threadIdx.y * xlength + threadIdx.x;
  cuda_MagnitudeReOpt(buffer, sharedIndex, matrix1);
  threads_sync();
  do
  {
    cuda_SumValues(buffer, sharedIndex, sharedLength, xlength, ylength);
    sharedLength = sharedLength / 2;
    threads_sync();
  }
  while (sharedLength > 1);
  if (threadIdx.x == 0 && threadIdx.y == 0)
  {
    sum[gridDim.x * blockIdx.y + blockIdx.x] = buffer[0];
  }
}

__hostdevice__ void CUDA_magnitudeOptImMatrix (floatt* sum, math::Matrix* matrix1, floatt* buffer)
{
  HOST_INIT();
  uintt xlength = aux_GetLength(blockIdx.x, blockDim.x, matrix1->columns);
  uintt ylength = aux_GetLength(blockIdx.y, blockDim.y, matrix1->rows);
  uintt sharedLength = xlength * ylength;
  uintt sharedIndex = threadIdx.y * xlength + threadIdx.x;
  cuda_MagnitudeImOpt(buffer, sharedIndex, matrix1);
  threads_sync();
  do
  {
    cuda_SumValues(buffer, sharedIndex, sharedLength, xlength, ylength);
    sharedLength = sharedLength / 2;
    threads_sync();
  }
  while (sharedLength > 1);
  if (threadIdx.x == 0 && threadIdx.y == 0)
  {
    sum[gridDim.x * blockIdx.y + blockIdx.x] = buffer[0];
  }
}

__hostdevice__ void CUDA_magnitudeOpt (floatt* sum, math::Matrix* matrix1, floatt* buffer)
{
  HOST_INIT();
  bool isre = matrix1->reValues != NULL;
  bool isim = matrix1->imValues != NULL;
  if (isre && isim)
  {
    CUDA_magnitudeOptRealMatrix(sum, matrix1, buffer);
  }
  else if (isre)
  {
    CUDA_magnitudeOptReMatrix(sum, matrix1, buffer);
  }
  else if (isim)
  {
    CUDA_magnitudeOptImMatrix(sum, matrix1, buffer);
  }
}

__hostdevice__ floatt CUDA_calcMagnitudeOptEx (math::Matrix* matrix1, floatt* buffer, uintt column, uintt row, uintt columns, uintt rows)
{
  HOST_INIT();
  THREAD_INDICES_INIT();
  bool isre = matrix1->reValues != NULL;
  bool isim = matrix1->imValues != NULL;

  uintt xlength = aux_GetLength(blockIdx.x, blockDim.x, columns);
  uintt ylength = aux_GetLength(blockIdx.y, blockDim.y, rows);

  uintt sharedLength = xlength * ylength;
  uintt sharedIndex = threadIdx.y * xlength + threadIdx.x - (row * xlength + column);

  if (isre && isim)
  {
    cuda_MagnitudeRealMatrixOptEx (buffer, sharedIndex, matrix1, column, row, columns, rows);
  }
  else if (isre)
  {
    cuda_MagnitudeReMatrixOptEx (buffer, sharedIndex, matrix1, column, row, columns, rows);
  }
  else if (isim)
  {
    cuda_MagnitudeImMatrixOptEx (buffer, sharedIndex, matrix1, column, row, columns, rows);
  }
  
  threads_sync();

  do
  {
    cuda_SumValues (buffer, sharedIndex, sharedLength, xlength, ylength, column, row);
    sharedLength = sharedLength / 2;
    threads_sync();
  }
  while (sharedLength > 1);

  floatt sum = buffer[0];

  return sum;
}

__hostdevice__ void CUDA_magnitudeOptEx (floatt* sum, math::Matrix* matrix1, floatt* buffer, uintt column, uintt row, uintt columns, uintt rows)
{
  HOST_INIT();

  floatt v = CUDA_calcMagnitudeOptEx (matrix1, buffer, column, row, columns, rows);

  if (threadIdx.x == 0 && threadIdx.y == 0)
  {
    sum[gridDim.x * blockIdx.y + blockIdx.x] = v;
  }
  threads_sync();
}

#endif	/* CUMAGNITUDEPROCEDURES_H */
