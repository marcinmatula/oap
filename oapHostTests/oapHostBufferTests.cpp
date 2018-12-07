/*
 * Copyright 2016 - 2018 Marcin Matula
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

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "HostBuffer.h"

template<typename T>
class TBuffer : public utils::Buffer<T, utils::HostMemUtl>
{
  public:
  
  template<typename Arg>
  uintt convertSize() const
  {
    return utils::Buffer<T, utils::HostMemUtl>::template convertSize<Arg>();
  }
};

class OapHostBufferTests : public testing::Test {
 public:
  OapHostBufferTests() {}

  virtual ~OapHostBufferTests() {}

  virtual void SetUp() {}

  virtual void TearDown() {}
};

TEST_F(OapHostBufferTests, SimpleBufferTest)
{
  oap::host::HostBuffer<int> buffer;
  for (int value = 0; value < 10000; ++value)
  {
    buffer.push_back (value);
  }

  for (int value = 0; value < 10000; ++value)
  {
    EXPECT_EQ(value, buffer.get(value));
  }

  for (int value = 10000 - 1; value >= 0; --value)
  {
    EXPECT_EQ(value, buffer.get(value));
  }
}

TEST_F(OapHostBufferTests, ConvertSizeTest)
{
  TBuffer<int> tbuffer;
  TBuffer<char> tbuffer1;
  EXPECT_EQ(sizeof(double) / sizeof(int), tbuffer.template convertSize<double>());
  EXPECT_EQ(sizeof(double) / sizeof(char), tbuffer1.template convertSize<double>());
  EXPECT_EQ(sizeof(int) / sizeof(char), tbuffer1.template convertSize<int>());
}

TEST_F(OapHostBufferTests, ConvertBufferTest)
{
  oap::host::HostBuffer<int> buffer;
  std::vector<uintt> indices;

  for (int value = 0; value < 10000; ++value)
  {
    floatt v = value + .5;
    indices.push_back (buffer.push_back (v));
  }

  for (int value = 0; value < 10000 * 2; value = value + 2)
  {
    floatt expected = (value / 2.) + .5;
    EXPECT_EQ(expected, buffer.get<floatt>(value));
  }

  for (int value = 10000 * 2 - 2; value >= 0; value = value - 2)
  {
    floatt expected = (value / 2.) + .5;
    EXPECT_EQ(expected, buffer.get<floatt>(value));
  }

  for (uintt idx = 0; idx < indices.size(); idx++)
  {
    uintt idx1 = indices[idx];
    floatt expected = (idx) + .5;
    EXPECT_EQ(expected, buffer.get<floatt>(idx1));
  }
}

