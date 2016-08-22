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
#include "ArnoldiMethodProcess.h"
#include "MatricesExamples.h"
#include "KernelExecutor.h"
#include "HostMatrixModules.h"
#include "DeviceMatrixModules.h"

class Float {
public:

    Float(floatt value, floatt bound = 0) {
        m_value = value;
        m_bound = bound;
    }

    floatt m_value;
    floatt m_bound;

    bool operator==(const Float& value) {
        return (value.m_value - m_bound <= m_value && m_value <= value.m_value + m_bound)
            || (value.m_value - value.m_bound <= m_value && m_value <= value.m_value + value.m_bound);
    }

};

bool operator==(const Float& value1, const Float& value) {
    return (value.m_value - value1.m_bound <= value1.m_value
        && value1.m_value <= value.m_value + value1.m_bound)
        || (value.m_value - value.m_bound <= value1.m_value
        && value1.m_value <= value.m_value + value.m_bound);
}

class OapArnoldiPackageTests : public testing::Test {
public:

    void EqualsExpectations(floatt* houtput, floatt* doutput, size_t count, floatt bound = 0) {
        for (size_t fa = 0; fa < count; ++fa) {
            Float f1(houtput[fa], bound);
            Float f2(doutput[fa], bound);
            EXPECT_TRUE(f1 == f2);
        }
    }

    api::ArnoldiPackage* arnoldiCpu;
    api::ArnoldiPackage* arnoldiCuda;

    virtual void SetUp() {
        arnoldiCpu = new api::ArnoldiPackage(api::ArnoldiPackage::ARNOLDI_CPU);
    }

    virtual void TearDown() {
        delete arnoldiCpu;
    }
};

TEST_F(OapArnoldiPackageTests, matrices16x16ev2) {
    math::Matrix* m = host::NewReMatrixCopy(16, 16, tm16);
    uintt count = 2;
    uintt h = 4;

    floatt revs[] = {0, 0};
    floatt imvs[] = {0, 0};
    floatt revs1[] = {0, 0};
    floatt imvs1[] = {0, 0};

    arnoldiCpu->setMatrix(m);
    arnoldiCpu->setHDimension(h);
    arnoldiCpu->setEigenvaluesBuffer(revs, imvs, count);
    arnoldiCpu->start();

    host::DeleteMatrix(m);
}

TEST_F(OapArnoldiPackageTests, matrices64x64ev2) {
    math::Matrix* m = host::NewReMatrixCopy(64, 64, tm64);
    uintt count = 2;
    uintt h = 8;

    floatt revs[] = {0, 0};
    floatt imvs[] = {0, 0};
    floatt revs1[] = {0, 0};
    floatt imvs1[] = {0, 0};

    arnoldiCpu->setMatrix(m);
    arnoldiCpu->setHDimension(h);
    arnoldiCpu->setEigenvaluesBuffer(revs, imvs, count);
    arnoldiCpu->start();

    host::DeleteMatrix(m);
}
