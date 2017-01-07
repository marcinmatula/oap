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

#include "EigenCalculator.h"
#include "Exceptions.h"
#include "HostMatrixModules.h"
#include "ArnoldiProceduresImpl.h"

namespace oap {

EigenCalculator::EigenCalculator()
    : m_eigensCount(2),
      m_dataLoader(NULL),
      m_revalues(NULL),
      m_eigenvectors(NULL) {}

EigenCalculator::~EigenCalculator() {
  destroyEigenvalues();
  destroyEigenvectors();
}

void EigenCalculator::setDataLoader(DataLoader* dataLoader) {
  m_dataLoader = dataLoader;
}

void EigenCalculator::calculate() {
  checkIfInitialized();

  ArnUtils::MatrixInfo matrixInfo = m_dataLoader->createMatrixInfo();

  m_cuHArnoldi = new CuHArnoldiDefault();
  m_cuHArnoldi->setSortType(ArnUtils::SortLargestReValues);

  initializeEigenvalues();
  initializeEigenvectors();

  const unsigned int hdim = 32;

  m_cuHArnoldi->setOutputsEigenvalues(m_revalues, NULL);
  m_cuHArnoldi->setOutputsEigenvectors(m_eigenvectors);

  m_cuHArnoldi->execute(hdim, m_eigensCount, matrixInfo);
}

void EigenCalculator::getEigenvalues(floatt* revalues) const {
  checkIfInitialized();

  memcpy(revalues, m_revalues, sizeof(floatt) * m_eigensCount);
}

void EigenCalculator::getEigenvectors(math::Matrix* eigenvectors) const {
  checkIfInitialized();

  host::CopyMatrix(eigenvectors, m_eigenvectors);
}

void EigenCalculator::checkIfInitialized() const {
  if (!isInitialized()) {
    throw oap::exceptions::NotInitialzed();
  }
}

bool EigenCalculator::isInitialized() const { return m_dataLoader != NULL; }

void EigenCalculator::checkOutOfRange(size_t v, size_t max) const {
  if (v >= max) {
    throw oap::exceptions::OutOfRange(v, max);
  }
}

void EigenCalculator::initializeEigenvalues() {
  destroyEigenvalues();
  m_revalues = new floatt[m_eigensCount];
}

void EigenCalculator::initializeEigenvectors() {
  destroyEigenvectors();
  ArnUtils::MatrixInfo matrixInfo = m_dataLoader->createMatrixInfo();
  m_eigenvectors =
      host::NewReMatrix(m_eigensCount, matrixInfo.m_matrixDim.rows);
}

void EigenCalculator::destroyEigenvalues() {
  delete[] m_revalues;
  m_revalues = NULL;
}

void EigenCalculator::destroyEigenvectors() {
  host::DeleteMatrix(m_eigenvectors);
  m_eigenvectors = NULL;
}
}
