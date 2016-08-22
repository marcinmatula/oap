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




// Copyright 2008, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: wan@google.com (Zhanyong Wan)

// Google Mock - a framework for writing C++ mock classes.
//
// This file tests code in gmock.cc.

#include <string>
#include "gtest/gtest.h"
#include "MockUtils.h"
#include "MatrixProcedures.h"
#include "MathOperationsCpu.h"
#include "HostMatrixModules.h"
#include "DeviceMatrixModules.h"
#include "KernelExecutor.h"

class OapCompareCudaTests : public testing::Test {
public:

    math::Matrix* output;
    math::Matrix* eq_output;
    CuMatrix* cuMatrix;
    CUresult status;

    virtual void SetUp() {
        status = CUDA_SUCCESS;
        device::Context::Instance().create();
        output = NULL;
        eq_output = NULL;
        cuMatrix = new CuMatrix();
    }

    virtual void TearDown() {
        device::Context::Instance().destroy();
        delete cuMatrix;
        if (output != NULL && eq_output != NULL) {
            EXPECT_THAT(output, MatrixIsEqual(eq_output));
        }
        host::DeleteMatrix(output);
        host::DeleteMatrix(eq_output);
    }
};

TEST_F(OapCompareCudaTests, CompareReMatrixTest1) {
    floatt hArray[] = {
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 1, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 0, 1, 0, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    math::Matrix* matrix1 = device::NewDeviceMatrix(true, false, 10, 10);
    math::Matrix* matrix2 = device::NewDeviceMatrix(true, false, 10, 10);
    device::CopyHostArraysToDeviceMatrix(matrix1, hArray, NULL);
    device::CopyHostArraysToDeviceMatrix(matrix2, hArray, NULL);

    bool resultVer1 = cuMatrix->compare(matrix1, matrix2);
    uintt outcomeVer1 = cuMatrix->getCompareOperationSum();
    bool resultVer2 = cuMatrix->compareVer2(matrix1, matrix2);
    uintt outcomeVer2 = cuMatrix->getCompareOperationSum();

    device::DeleteDeviceMatrix(matrix1);
    device::DeleteDeviceMatrix(matrix2);

    EXPECT_TRUE(resultVer1);
    EXPECT_TRUE(resultVer2);
    EXPECT_EQ(outcomeVer2, outcomeVer1);
}

TEST_F(OapCompareCudaTests, CompareReMatrixTest1Fail) {
    floatt hArray1[] = {
        1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 1, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 0, 1, 0, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    floatt hArray2[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    math::Matrix* matrix1 = device::NewDeviceMatrix(true, false, 10, 10);
    math::Matrix* matrix2 = device::NewDeviceMatrix(true, false, 10, 10);
    device::CopyHostArraysToDeviceMatrix(matrix1, hArray1, NULL);
    device::CopyHostArraysToDeviceMatrix(matrix2, hArray2, NULL);

    bool resultVer1 = cuMatrix->compare(matrix1, matrix2);
    uintt outcomeVer1 = cuMatrix->getCompareOperationSum();
    bool resultVer2 = cuMatrix->compareVer2(matrix1, matrix2);
    uintt outcomeVer2 = cuMatrix->getCompareOperationSum();

    device::DeleteDeviceMatrix(matrix1);
    device::DeleteDeviceMatrix(matrix2);

    EXPECT_FALSE(resultVer1);
    EXPECT_FALSE(resultVer2);
    EXPECT_EQ(outcomeVer2, outcomeVer1);
}

TEST_F(OapCompareCudaTests, CompareReMatrixTestBigData) {

    uintt columns = 50;
    uintt rows = 32;

    math::Matrix* matrix1 = device::NewDeviceMatrix(true, false, columns, rows);
    math::Matrix* matrix2 = device::NewDeviceMatrix(true, false, columns, rows);

    bool resultVer1 = cuMatrix->compare(matrix1, matrix2);
    uintt outcomeVer1 = cuMatrix->getCompareOperationSum();
    bool resultVer2 = cuMatrix->compareVer2(matrix1, matrix2);
    uintt outcomeVer2 = cuMatrix->getCompareOperationSum();

    device::DeleteDeviceMatrix(matrix1);
    device::DeleteDeviceMatrix(matrix2);

    EXPECT_TRUE(resultVer1);
    EXPECT_TRUE(resultVer2);
    EXPECT_EQ(outcomeVer2, outcomeVer1);
}

TEST_F(OapCompareCudaTests, CompareReMatrixTestBigData1) {

    uintt columns = 50;
    uintt rows = 50;

    math::Matrix* matrix1 = device::NewDeviceMatrix(true, false, columns, rows);
    math::Matrix* matrix2 = device::NewDeviceMatrix(true, false, columns, rows);

    bool resultVer1 = cuMatrix->compare(matrix1, matrix2);
    uintt outcomeVer1 = cuMatrix->getCompareOperationSum();
    bool resultVer2 = cuMatrix->compareVer2(matrix1, matrix2);
    uintt outcomeVer2 = cuMatrix->getCompareOperationSum();

    device::DeleteDeviceMatrix(matrix1);
    device::DeleteDeviceMatrix(matrix2);

    EXPECT_TRUE(resultVer1);
    EXPECT_TRUE(resultVer2);
    EXPECT_EQ(outcomeVer2, outcomeVer1);
}

TEST_F(OapCompareCudaTests, CompareReMatrixTestBigData2) {

    uintt columns = 70;
    uintt rows = 70;

    math::Matrix* matrix1 = device::NewDeviceMatrix(true, false, columns, rows);
    math::Matrix* matrix2 = device::NewDeviceMatrix(true, false, columns, rows);

    bool resultVer1 = cuMatrix->compare(matrix1, matrix2);
    uintt outcomeVer1 = cuMatrix->getCompareOperationSum();
    bool resultVer2 = cuMatrix->compareVer2(matrix1, matrix2);
    uintt outcomeVer2 = cuMatrix->getCompareOperationSum();

    device::DeleteDeviceMatrix(matrix1);
    device::DeleteDeviceMatrix(matrix2);

    EXPECT_TRUE(resultVer1);
    EXPECT_TRUE(resultVer2);
    EXPECT_EQ(outcomeVer2, outcomeVer1);
}

TEST_F(OapCompareCudaTests, CompareReMatrixTestBigData3) {

    uintt columns = 111;
    uintt rows = 111;

    math::Matrix* matrix1 = device::NewDeviceMatrix(true, false, columns, rows);
    math::Matrix* matrix2 = device::NewDeviceMatrix(true, false, columns, rows);

    bool resultVer1 = cuMatrix->compare(matrix1, matrix2);
    uintt outcomeVer1 = cuMatrix->getCompareOperationSum();
    bool resultVer2 = cuMatrix->compareVer2(matrix1, matrix2);
    uintt outcomeVer2 = cuMatrix->getCompareOperationSum();

    device::DeleteDeviceMatrix(matrix1);
    device::DeleteDeviceMatrix(matrix2);

    EXPECT_TRUE(resultVer1);
    EXPECT_TRUE(resultVer2);
    EXPECT_EQ(outcomeVer2, outcomeVer1);
}

TEST_F(OapCompareCudaTests, CompareReMatrixTestBigData3Fail) {

    uintt columns = 111;
    uintt rows = 111;

    math::Matrix* matrix1 = device::NewDeviceMatrix(true, false, columns, rows);
    math::Matrix* matrix2 = device::NewDeviceMatrix(true, false, columns, rows);

    CudaUtils::SetReValue(matrix1, columns * rows - 1, 10);

    bool resultVer1 = cuMatrix->compare(matrix1, matrix2);
    uintt outcomeVer1 = cuMatrix->getCompareOperationSum();
    bool resultVer2 = cuMatrix->compareVer2(matrix1, matrix2);
    uintt outcomeVer2 = cuMatrix->getCompareOperationSum();

    device::DeleteDeviceMatrix(matrix1);
    device::DeleteDeviceMatrix(matrix2);

    EXPECT_FALSE(resultVer1);
    EXPECT_FALSE(resultVer2);
    EXPECT_EQ(outcomeVer2, outcomeVer1);
}

TEST_F(OapCompareCudaTests, CompareReMatrixTestBigData4) {

    uintt columns = 1000;
    uintt rows = 1000;

    math::Matrix* matrix1 = device::NewDeviceMatrix(true, false, columns, rows);
    math::Matrix* matrix2 = device::NewDeviceMatrix(true, false, columns, rows);

    bool resultVer1 = cuMatrix->compare(matrix1, matrix2);
    uintt outcomeVer1 = cuMatrix->getCompareOperationSum();
    bool resultVer2 = cuMatrix->compareVer2(matrix1, matrix2);
    uintt outcomeVer2 = cuMatrix->getCompareOperationSum();

    device::DeleteDeviceMatrix(matrix1);
    device::DeleteDeviceMatrix(matrix2);

    EXPECT_TRUE(resultVer1);
    EXPECT_TRUE(resultVer2);
    EXPECT_EQ(outcomeVer2, outcomeVer1);
}

TEST_F(OapCompareCudaTests, CompareReMatrixTestBigData4Fail) {

    uintt columns = 1000;
    uintt rows = 1000;

    math::Matrix* matrix1 = device::NewDeviceMatrix(true, false, columns, rows);
    math::Matrix* matrix2 = device::NewDeviceMatrix(true, false, columns, rows);

    CudaUtils::SetReValue(matrix1, columns * rows - 1, 10);

    bool resultVer1 = cuMatrix->compare(matrix1, matrix2);
    uintt outcomeVer1 = cuMatrix->getCompareOperationSum();
    bool resultVer2 = cuMatrix->compareVer2(matrix1, matrix2);
    uintt outcomeVer2 = cuMatrix->getCompareOperationSum();

    device::DeleteDeviceMatrix(matrix1);
    device::DeleteDeviceMatrix(matrix2);

    EXPECT_FALSE(resultVer1);
    EXPECT_FALSE(resultVer2);
    EXPECT_EQ(outcomeVer2, outcomeVer1);
}

TEST_F(OapCompareCudaTests, CompareReMatrixTest5Fail) {

    uintt columns = 11;
    uintt rows = 11;

    math::Matrix* matrix1 = device::NewDeviceMatrix(true, false, columns, rows);
    math::Matrix* matrix2 = device::NewDeviceMatrix(true, false, columns, rows);

    CudaUtils::SetReValue(matrix1, columns * rows - 1, 10);

    bool resultVer1 = cuMatrix->compare(matrix1, matrix2);
    uintt outcomeVer1 = cuMatrix->getCompareOperationSum();
    bool resultVer2 = cuMatrix->compareVer2(matrix1, matrix2);
    uintt outcomeVer2 = cuMatrix->getCompareOperationSum();

    device::DeleteDeviceMatrix(matrix1);
    device::DeleteDeviceMatrix(matrix2);

    EXPECT_FALSE(resultVer1);
    EXPECT_FALSE(resultVer2);
    EXPECT_EQ(outcomeVer2, outcomeVer1);
}
