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
#include "oglaCudaStub.h"
#include "MockUtils.h"
#include "MatrixProcedures.h"
#include "MathOperationsCpu.h"
#include "HostMatrixModules.h"
#include "KernelExecutor.h"
#include "CuMatrixProcedures/CuQRProcedures.h"
#include "qrtest1.h"
#include "qrtest2.h"
#include "qrtest3.h"

class OglaQRTests : public OglaCudaStub {
 public:
  virtual void SetUp() {}

  virtual void TearDown() {}

  class QRStub : public KernelStub {
   public:
    math::Matrix* m_matrix;
    math::Matrix* m_eq;
    math::Matrix* m_er;
    QRStub(math::Matrix* eq, math::Matrix* er, math::Matrix* matrix)
        : m_eq(eq), m_er(er), m_matrix(matrix) {}
    virtual ~QRStub() {}

    virtual math::Matrix* getQ() const = 0;
    virtual math::Matrix* getR() const = 0;
  };

  class QRGRStub : public QRStub {
   public:
    math::Matrix* m_q;
    math::Matrix* m_r;
    math::Matrix* m_temp1;
    math::Matrix* m_temp2;
    math::Matrix* m_temp3;
    math::Matrix* m_temp4;

    QRGRStub(math::Matrix* eq_q, math::Matrix* eq_r, math::Matrix* matrix)
        : QRStub(eq_q, eq_r, matrix) {
      m_q = host::NewMatrix(eq_q);
      m_r = host::NewMatrix(eq_r);
      m_temp1 = host::NewMatrix(matrix);
      m_temp2 = host::NewMatrix(matrix);
      m_temp3 = host::NewMatrix(matrix);
      m_temp4 = host::NewMatrix(matrix);
      calculateDims(m_matrix->columns, m_matrix->rows);
    }

    virtual ~QRGRStub() {
      //Pop(m_q);
      //EXPECT_THAT(m_q, WereSetAllRe());
      //Pop(m_r);
      //EXPECT_THAT(m_r, WereSetAllRe());
      //Pop(m_temp1);
      //EXPECT_THAT(m_temp1, WereSetAllRe());
      //Pop(m_temp2);
      //EXPECT_THAT(m_temp2, WereSetAllRe());
      //Pop(m_temp3);
      //EXPECT_THAT(m_temp3, WereSetAllRe());
      /*Pop(m_temp4);
      EXPECT_THAT(m_temp4, WereSetAllRe());*/
      host::DeleteMatrix(m_q);
      host::DeleteMatrix(m_r);
      host::DeleteMatrix(m_temp1);
      host::DeleteMatrix(m_temp2);
      host::DeleteMatrix(m_temp3);
      host::DeleteMatrix(m_temp4);
    }

    void execute(const dim3& threadIdx) {
      CUDA_QRGR(m_q, m_r, m_matrix, m_temp1, m_temp2, m_temp3, m_temp4);
    }

    virtual math::Matrix* getQ() const { return m_q; }
    virtual math::Matrix* getR() const { return m_r; }
  };

  class QRHTStub : public QRStub {
   public:
    math::Matrix* Q;
    math::Matrix* R;
    math::Matrix* A;
    math::Matrix* AT;
    floatt sum;
    floatt* buffer;
    math::Matrix* P;
    math::Matrix* I;
    math::Matrix* v;
    math::Matrix* vt;
    math::Matrix* vvt;

    QRHTStub(math::Matrix* eq_q, math::Matrix* eq_r, math::Matrix* matrix)
        : QRStub(eq_q, eq_r, matrix) {
      R = host::NewMatrix(eq_r);
      Q = host::NewMatrix(eq_q);
      A = host::NewMatrix(matrix);
      AT = host::NewMatrix(matrix);
      P = host::NewMatrix(matrix);
      I = host::NewMatrix(matrix);
      v = host::NewMatrix(matrix, 1, matrix->rows);
      vt = host::NewMatrix(matrix, matrix->columns, 1);
      vvt = host::NewMatrix(matrix);
      buffer = new floatt[matrix->columns * matrix->rows];
    }

    virtual ~QRHTStub() {
      host::DeleteMatrix(R);
      host::DeleteMatrix(Q);
      host::DeleteMatrix(A);
      host::DeleteMatrix(AT);
      host::DeleteMatrix(P);
      host::DeleteMatrix(I);
      host::DeleteMatrix(v);
      host::DeleteMatrix(vt);
      host::DeleteMatrix(vvt);
      delete[] buffer;
    }

    void execute(const dim3& threadIdx) {
      CUDA_QRHT(R, Q, A, AT, &sum, buffer, P, I, v, vt, vvt);
    }

    virtual math::Matrix* getQ() const { return Q; }
    virtual math::Matrix* getR() const { return R; }
  };

  void ExpectThatQRIsEqual(QRStub* qrStub, math::Matrix* eq_q,
                           math::Matrix* eq_r) {
    EXPECT_THAT(qrStub->getQ(), MatrixIsEqual(eq_q));
    EXPECT_THAT(qrStub->getR(), MatrixIsEqual(eq_r));
  }

  void executeTest(const std::string& matrixStr, const std::string& qrefStr,
                   const std::string& rrefStr) {
    math::Matrix* matrix = host::NewMatrix(matrixStr);
    math::Matrix* eq_q = host::NewMatrix(qrefStr);
    math::Matrix* eq_r = host::NewMatrix(rrefStr);

    QRGRStub qrgrStub(matrix, eq_q, eq_r);
    QRHTStub qrhtStub(matrix, eq_q, eq_r);

    executeKernelAsync(&qrgrStub);
    executeKernelAsync(&qrhtStub);

    ExpectThatQRIsEqual(&qrgrStub, eq_q, eq_r);
    ExpectThatQRIsEqual(&qrhtStub, eq_q, eq_r);

    host::DeleteMatrix(matrix);
    host::DeleteMatrix(eq_q);
    host::DeleteMatrix(eq_r);
  }
};

TEST_F(OglaQRTests, Test1) {
  executeTest(host::qrtest1::matrix, host::qrtest1::qref, host::qrtest1::rref);
}

TEST_F(OglaQRTests, Test2) {
  executeTest(host::qrtest2::matrix, host::qrtest2::qref, host::qrtest2::rref);
}

TEST_F(OglaQRTests, Test3) {
  executeTest(host::qrtest3::matrix, host::qrtest3::qref, host::qrtest3::rref);
}
