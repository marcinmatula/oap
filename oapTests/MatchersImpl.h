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

#ifndef MATCHERSIMPL_H
#define MATCHERSIMPL_H

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "MatrixTestAPI.h"
#include "HostInfoCreator.h"

#include "oapHostMatrixUtils.h"
#include "oapHostMatrixUPtr.h"

#include "MatrixPrinter.h"
#include "Utils.h"

using ::testing::PrintToString;
using ::testing::MakeMatcher;
using ::testing::Matcher;
using ::testing::MatcherInterface;
using ::testing::MatchResultListener;

class MatrixValuesAreEqualMatcher : public MatcherInterface<math::Matrix*> {
  floatt m_value;

 public:
  MatrixValuesAreEqualMatcher(floatt value) : m_value(value) {}

  virtual bool MatchAndExplain(math::Matrix* matrix,
                               MatchResultListener* listener) const {
    std::string v;
    matrixUtils::PrintMatrix(v, matrix);
    (*listener) << v;
    return utils::areEqual(matrix, m_value);
  }

  virtual void DescribeTo(::std::ostream* os) const {
    *os << "Matrix values are equal " << m_value;
  }

  virtual void DescribeNegationTo(::std::ostream* os) const {
    *os << "Matrix values are not equal " << m_value;
  }
};

class MatrixIsEqualMatcher : public MatcherInterface<math::Matrix*> {

  protected:
    math::Matrix* m_matrix;
    InfoType m_infoType;

  public:
    MatrixIsEqualMatcher(math::Matrix* matrix, const InfoType& infoType)
      : m_matrix(matrix), m_infoType(infoType)
    {}

    virtual bool MatchAndExplain(math::Matrix* matrix, MatchResultListener* listener) const
    {
      HostInfoCreator infoCreator;
      infoCreator.setExpected(matrix);
      infoCreator.setOutput(m_matrix);
      infoCreator.setInfoType(m_infoType);
      bool isEqual = infoCreator.isEqual(m_infoType.getTolerance());
      std::string msg;
      infoCreator.getInfo(msg);
      (*listener) << msg;
      return isEqual;
    }

    virtual void DescribeTo(::std::ostream* os) const {
      *os << "Matrices are equal.";
    }

    virtual void DescribeNegationTo(::std::ostream* os) const {
      *os << "Matrices are not equal.";
    }
};

class MatrixHasValuesMatcher : public MatcherInterface<math::Matrix*>
{
  protected:
    math::Matrix* m_matrix;
    InfoType m_infoType;

  public:
    MatrixHasValuesMatcher(math::Matrix* matrix, const InfoType& infoType)
      : m_matrix(matrix), m_infoType(infoType)
    {}

    virtual bool MatchAndExplain (math::Matrix* matrix, MatchResultListener* listener) const
    {
      HostInfoCreator infoCreator;
      infoCreator.setExpected(matrix);
      infoCreator.setOutput(m_matrix);
      infoCreator.setInfoType(m_infoType);
      bool hasTheSameValues = infoCreator.hasValues(m_infoType.getTolerance());
      std::string msg;
      infoCreator.getInfo(msg);
      (*listener) << msg;
      return hasTheSameValues;
    }

    virtual void DescribeTo(::std::ostream* os) const {
      *os << "Matrix has equal values.";
    }

    virtual void DescribeNegationTo(::std::ostream* os) const {
      *os << "Matrix has not equal values.";
    }
};

class MatrixIsDiagonalMatcher : public MatcherInterface<math::Matrix*> {
  floatt m_value;
  InfoType m_infoType;

 public:
  MatrixIsDiagonalMatcher (floatt value, const InfoType& infoType) : m_value(value), m_infoType(infoType) {}

  virtual bool MatchAndExplain (math::Matrix* matrix, MatchResultListener* listener) const {
    math::Matrix* diffmatrix = NULL;
    bool isequal = utils::IsDiagonalMatrix((*matrix), m_value, m_infoType.getTolerance(), &diffmatrix);

    std::string matrixStr;
    matrixUtils::PrintMatrix(matrixStr, diffmatrix);

    if (!isequal)
    {
      (*listener) << "Diff is = " << matrixStr;
    }
    oap::host::DeleteMatrix(diffmatrix);
    return isequal;
  }

  virtual void DescribeTo(::std::ostream* os) const {
    *os << "Matrix is diagonal.";
  }

  virtual void DescribeNegationTo(::std::ostream* os) const {
    *os << "Matrix is not diagonal.";
  }
};

class MatrixIsIdentityMatcher : public MatrixIsDiagonalMatcher {
 public:
  MatrixIsIdentityMatcher (const InfoType& infoType) : MatrixIsDiagonalMatcher(1.f, infoType) {}

  virtual void DescribeTo(::std::ostream* os) const {
    *os << "Matrix is identity.";
  }

  virtual void DescribeNegationTo(::std::ostream* os) const {
    *os << "Matrix is not identity.";
  }
};

class MatrixTestAPIMatcher : public MatcherInterface<math::Matrix*> {
  bool (*m_checker)(const math::Matrix* matrix);
  uintt (*m_getter)(const math::Matrix* matrix);

 public:
  MatrixTestAPIMatcher(bool (*checker)(const math::Matrix* matrix),
                       uintt (*getter)(const math::Matrix* matrix))
      : m_getter(getter), m_checker(checker) {}

  virtual bool MatchAndExplain(math::Matrix* matrix,
                               MatchResultListener* listener) const {
    bool is = (*m_checker)(matrix);
    if (!is) {
      uintt count = (*m_getter)(matrix);
      (*listener) << "were set " << count << " elements";
    }
    return is;
  }

  virtual void DescribeTo(::std::ostream* os) const {
    *os << "were set all elements.";
  }

  virtual void DescribeNegationTo(::std::ostream* os) const {
    *os << "were not set all elemets.";
  }
};

class SetAllRe : public MatrixTestAPIMatcher {
 public:
  SetAllRe()
      : MatrixTestAPIMatcher(test::wasSetAllRe, test::getSetValuesCountRe) {}
};

class SetAllIm : public MatrixTestAPIMatcher {
 public:
  SetAllIm()
      : MatrixTestAPIMatcher(test::wasSetAllIm, test::getSetValuesCountIm) {}
};

class GetAllRe : public MatrixTestAPIMatcher {
 public:
  GetAllRe()
      : MatrixTestAPIMatcher(test::wasGetAllRe, test::getGetValuesCountRe) {}
};

class GetAllIm : public MatrixTestAPIMatcher {
 public:
  GetAllIm()
      : MatrixTestAPIMatcher(test::wasGetAllIm, test::getGetValuesCountIm) {}
};

template <typename T>
class BufferSumIsEqualMatcher : public MatcherInterface<T> {
 protected:
  T* m_buffer;
  size_t m_length;
  T m_expectedSum;
  std::string m_extra;
  std::string m_stringRepresentation;

 public:
  BufferSumIsEqualMatcher(T* buffer, size_t length,
                          const std::string& extra = "")
      : m_buffer(buffer), m_length(length) {
    matrixUtils::PrintArray<T>(m_stringRepresentation, m_buffer, m_length);
    m_expectedSum = utils::getSum(m_buffer, m_length);
    m_extra = extra;
  }

  virtual bool MatchAndExplain(T actualSum,
                               MatchResultListener* listener) const {
    (*listener) << m_stringRepresentation;
    return m_expectedSum == actualSum;
  }

  virtual void DescribeTo(::std::ostream* os) const {
    *os << "Sum of array is equal " << m_expectedSum << m_extra;
  }

  virtual void DescribeNegationTo(::std::ostream* os) const {
    *os << "Sum of array is not equal " << m_expectedSum << m_extra;
  }
};

template <typename T>
class BufferSumIsEqualMatcherSum : public BufferSumIsEqualMatcher<T> {
 public:
  BufferSumIsEqualMatcherSum(T expectedSum, T* buffer, size_t length,
                             const std::string& extra = "")
      : BufferSumIsEqualMatcher<T>(buffer, length, extra) {
    BufferSumIsEqualMatcher<T>::m_expectedSum = expectedSum;
  }

  virtual bool MatchAndExplain(T actualSum,
                               MatchResultListener* listener) const {
    std::string v;
    matrixUtils::PrintArray(v, BufferSumIsEqualMatcher<T>::m_buffer, BufferSumIsEqualMatcher<T>::m_length);
    (*listener) << v;
    return BufferSumIsEqualMatcher<T>::m_expectedSum == actualSum;
  }
};

class MatrixContainsDiagonalValuesMatcher
    : public MatcherInterface<math::Matrix*> {
  math::Matrix* m_matrix;
  InfoType m_infoType;

  Complex getComplex(math::Matrix* matrix, uintt index) const {
    floatt re = 0, im = 0;
    if (matrix->reValues) {
      re = matrix->reValues[index * matrix->columns + index];
    }
    if (matrix->imValues) {
      im = matrix->imValues[index * matrix->columns + index];
    }
    return Complex(re, im);
  }

 public:
  MatrixContainsDiagonalValuesMatcher(math::Matrix* matrix)
      : m_matrix(matrix) {}

  virtual bool MatchAndExplain(math::Matrix* matrix,
                               MatchResultListener* listener) const {
    if (matrix->columns != m_matrix->columns &&
        matrix->rows != m_matrix->rows) {
      return false;
    }

    std::vector<Complex> values;

    for (uintt fa = 0; fa < m_matrix->columns; ++fa) {
      values.push_back(getComplex(m_matrix, fa));
    }
    for (uintt fa = 0; fa < matrix->columns; ++fa) {
      Complex complex = getComplex(matrix, fa);
      if (std::find(values.begin(), values.end(), complex) == values.end()) {
        return false;
      }
    }

    return true;
  }

  virtual void DescribeTo(::std::ostream* os) const { *os << "Matrix contains diagonal values."; }

  virtual void DescribeNegationTo(::std::ostream* os) const {
    *os << "Matrix does not contain diagonal values..";
  }
};

class StringIsEqualMatcher
    : public MatcherInterface<std::string> {

  std::string m_str2;
  std::string m_path1;
  std::string m_path2;
  public:

  StringIsEqualMatcher(const std::string& str2, const std::string& path1, const std::string& path2) :
    m_str2(str2), m_path1(path1), m_path2(path2) {
  }

  virtual bool MatchAndExplain(std::string str1,
                               MatchResultListener* listener) const {
    bool isequal = str1 == m_str2;

    if (isequal == false) {

      FILE* file = fopen(m_path1.c_str(),"w");
      fwrite(str1.c_str(), str1.size(), 1, file);
      fclose(file);

      file = fopen(m_path2.c_str(),"w");
      fwrite(m_str2.c_str(), m_str2.size(), 1, file);
      fclose(file);
      (*listener) << "Both strings are not equals. Logs in files: " << m_path1 << ", " << m_path2;
    } else {
      (*listener) << "Both strings are equals. No logs files";
    }
    return isequal;
  }

  virtual void DescribeTo(::std::ostream* os) const { *os << "Strings are equal."; }

  virtual void DescribeNegationTo(::std::ostream* os) const {
    *os << "Strings are not equal.";
  }

};

class MatrixIsUpperTriangularMatcher : public MatcherInterface<math::Matrix*> {

  InfoType m_infoType;

  public:
    MatrixIsUpperTriangularMatcher(const InfoType& infoType = InfoType()) {}

    virtual bool MatchAndExplain (math::Matrix* matrix, MatchResultListener* listener) const override
    {
      std::vector<std::tuple<uintt, uintt, floatt>> pairs;

      for (uintt column = 0; column < matrix->columns; ++column)
      {
        for (uintt row = 0; row < matrix->rows; ++row)
        {
          floatt v = GetRe (matrix, column, row);
          if (column < row)
          {
            bool inRange = -m_infoType.getTolerance() < v && v < m_infoType.getTolerance();
            if (!inRange)
            {
              pairs.push_back (std::make_tuple(column, row, v));
            }
          }
        }
      }

      if (!pairs.empty())
      {
        std::stringstream sstream;
        for (const auto& p : pairs)
        {
          sstream << "(" << std::get<0>(p) << ", " << std::get<1>(p) << ", " << std::get<2>(p) << ")";
        }
        (*listener) << "Matrix in not upper trinagular. Invalid entries: " << sstream.str();
      }

      return pairs.empty();
    }

    virtual void DescribeTo(::std::ostream* os) const override
    {
      *os << "Matrix is upper triangular.";
    }

    virtual void DescribeNegationTo(::std::ostream* os) const override
    {
      *os << "Matrix is not upper triangular.";
    }
};

template<typename CalcApi>
class MatrixIsOrthogonalMatcher : public MatcherInterface<math::Matrix*>
{

  CalcApi& m_calcApi;
  InfoType m_infoType;

  public:
    MatrixIsOrthogonalMatcher (CalcApi& calcApi, const InfoType& infoType = InfoType()) : m_calcApi (calcApi), m_infoType (infoType) {}

    virtual bool MatchAndExplain (math::Matrix* matrix, MatchResultListener* listener) const override
    {
      oap::HostMatrixUPtr matrixT = oap::host::NewMatrixCopy (matrix);
      oap::HostMatrixUPtr M = oap::host::NewMatrixRef (matrix);

      m_calcApi.transpose (matrixT, matrix);
      m_calcApi.dotProduct (M, matrixT, matrix);

      math::Matrix* diffmatrix = NULL;
      bool isDiag = utils::IsDiagonalMatrix(*M, 1.f, m_infoType.getTolerance(), &diffmatrix);
      if (!isDiag)
      {
        return false;
      }

      m_calcApi.dotProduct (M, matrix, matrixT);
      return utils::IsDiagonalMatrix (*M, 1.f, m_infoType.getTolerance(), &diffmatrix);
    }

    virtual void DescribeTo(::std::ostream* os) const override
    {
      *os << "Matrix is orthogonal.";
    }

    virtual void DescribeNegationTo(::std::ostream* os) const override
    {
      *os << "Matrix is not orthogonal.";
    }
};

#endif /* MATCHERSIMPL_H */
