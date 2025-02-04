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

#include "oapCudaMatrixUtils.h"
#include "oapHostMatrixUtils.h"

#include "oapDeviceMatrixUPtr.h"

#include "KernelExecutor.h"
#include "gtest/gtest.h"

class OapDeviceMatrixModuleTests : public testing::Test {
 public:
  virtual void SetUp() { oap::cuda::Context::Instance().create(); }

  virtual void TearDown() { oap::cuda::Context::Instance().destroy(); }

  void setSubMatrixTest(uintt columns, uintt rows, float value,
                        uintt subcolumns, uint subrows, floatt subvalue,
                        uintt column, uintt row) {
    math::Matrix* hmatrix = oap::host::NewMatrix(true, true, columns, rows, value);
    math::Matrix* dmatrix = oap::cuda::NewDeviceMatrixCopyOfHostMatrix(hmatrix);

    math::Matrix* hsubmatrix = oap::host::NewMatrix(true, true, subcolumns, subrows, subvalue);
    math::Matrix* dsubmatrix = oap::cuda::NewDeviceMatrixCopyOfHostMatrix(hsubmatrix);

    oap::cuda::SetMatrix(dmatrix, dsubmatrix, column, row);
    oap::cuda::CopyDeviceMatrixToHostMatrix(hmatrix, dmatrix);

    for (uintt fa = 0; fa < subcolumns; ++fa)
    {
      for (uintt fb = 0; fb < subrows; ++fb)
      {
        EXPECT_EQ(subvalue, hmatrix->reValues[(fa + column) + columns * (row + fb)]);
        EXPECT_EQ(subvalue, hmatrix->imValues[(fa + column) + columns * (row + fb)]);
      }
    }

    oap::cuda::DeleteDeviceMatrix(dmatrix);
    oap::cuda::DeleteDeviceMatrix(dsubmatrix);

    oap::host::DeleteMatrix(hmatrix);
    oap::host::DeleteMatrix(hsubmatrix);
  }
};

TEST_F(OapDeviceMatrixModuleTests, GetColumnsTest) {
  uintt columns = 15;
  uintt rows = 10;
  math::Matrix* matrix = oap::cuda::NewDeviceMatrix(true, true, columns, rows);
  uintt expected = CudaUtils::GetColumns(matrix);
  uintt tested = oap::cuda::GetColumns(matrix);
  EXPECT_EQ(expected, tested);
  EXPECT_EQ(columns, tested);
  oap::cuda::DeleteDeviceMatrix(matrix);
}

TEST_F(OapDeviceMatrixModuleTests, GetRowsTest) {
  uintt columns = 15;
  uintt rows = 10;
  math::Matrix* matrix = oap::cuda::NewDeviceMatrix(true, true, columns, rows);
  uintt expected = CudaUtils::GetRows(matrix);
  uintt tested = oap::cuda::GetRows(matrix);
  EXPECT_EQ(expected, tested);
  EXPECT_EQ(rows, tested);
  oap::cuda::DeleteDeviceMatrix(matrix);
}

TEST_F(OapDeviceMatrixModuleTests, GetRowsGetColumns)
{
  oap::DeviceMatrixUPtr matrix = oap::cuda::NewDeviceMatrix (10, 20);
  EXPECT_EQ(20, oap::cuda::GetRows (matrix));
  EXPECT_EQ(10, oap::cuda::GetColumns (matrix));
}

TEST_F(OapDeviceMatrixModuleTests, SetSubMatrix00) {
  setSubMatrixTest(10, 10, 2.f, 4, 4, 1.5f, 0, 0);
}

TEST_F(OapDeviceMatrixModuleTests, SetSubValue00) {
  setSubMatrixTest(10, 10, 2.f, 1, 1, 1.5f, 0, 0);
}

TEST_F(OapDeviceMatrixModuleTests, SetMatrixExTests) {
  const uintt dMatrixExCount = 5;
  const uintt matrixExElements = sizeof(MatrixEx) / sizeof(uintt);
  const uintt bufferLength = dMatrixExCount * matrixExElements;

  auto testMatrixEx = [matrixExElements](MatrixEx** dMatrixExs, uintt index) {
    MatrixEx hostMatrixEx;
    oap::cuda::GetMatrixEx(&hostMatrixEx, dMatrixExs[index]);
    EXPECT_EQ(index * matrixExElements, hostMatrixEx.column);
    EXPECT_EQ(index * matrixExElements + 1, hostMatrixEx.columns);
    EXPECT_EQ(index * matrixExElements + 2, hostMatrixEx.row);
    EXPECT_EQ(index * matrixExElements + 3, hostMatrixEx.rows);
  };

  uintt buffer[bufferLength];
  for (uintt fa = 0; fa < bufferLength; ++fa) {
    buffer[fa] = fa;
  }

  MatrixEx** dMatrixExs = oap::cuda::NewDeviceMatrixEx(dMatrixExCount);
  oap::cuda::SetMatrixEx(dMatrixExs, buffer, dMatrixExCount);

  for (uintt fa = 0; fa < dMatrixExCount; ++fa) {
    testMatrixEx(dMatrixExs, fa);
  }

  oap::cuda::DeleteDeviceMatrixEx(dMatrixExs);
}

TEST_F(OapDeviceMatrixModuleTests, WriteReadMatrix) {
  uintt columns = 10;
  uintt rows = 10;

  std::string path = "/tmp/Oap/device_tests/test_file";

  math::Matrix* m1 = oap::host::NewMatrix(true, true, columns, rows, 0);

  for (int fa = 0; fa < columns * rows; ++fa) {
    m1->reValues[fa] = fa;
    m1->imValues[fa] = fa;
  }

  math::Matrix* d1 = oap::cuda::NewDeviceMatrixCopyOfHostMatrix(m1);

  bool status = oap::cuda::WriteMatrix(path, d1);

  EXPECT_TRUE(status);

  if (status) {
    math::Matrix* d2 = oap::cuda::ReadMatrix(path);

    math::Matrix* m2 = oap::host::NewMatrix(oap::cuda::GetMatrixInfo(d2));
    oap::cuda::CopyDeviceMatrixToHostMatrix(m2, d2);

    EXPECT_EQ(m2->columns, m1->columns);
    EXPECT_EQ(m2->columns, columns);
    EXPECT_EQ(m2->rows, m1->rows);
    EXPECT_EQ(m2->rows, rows);

    for (int fa = 0; fa < columns * rows; ++fa) {
      EXPECT_EQ(m1->reValues[fa], m2->reValues[fa]);
      EXPECT_EQ(m1->imValues[fa], m2->imValues[fa]);
    }

    oap::host::DeleteMatrix(m2);
    oap::cuda::DeleteDeviceMatrix(d2);
  }
  oap::host::DeleteMatrix(m1);
  oap::cuda::DeleteDeviceMatrix(d1);
}
