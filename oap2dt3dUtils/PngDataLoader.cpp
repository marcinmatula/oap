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

#include "PngDataLoader.h"
#include "Exceptions.h"

namespace oap {

PngDataLoader::PngDataLoader(IPngFile* ifile, const std::string& path)
    : m_ifile(ifile) {
  load(path);
}

PngDataLoader::~PngDataLoader() {
  if (m_ifile != NULL) {
    m_ifile->freeBitmap();
  }
}

void PngDataLoader::load(const std::string& path) {
  m_ifile->open(path.c_str());

  m_ifile->loadBitmap();

  m_ifile->close();
}

Pixel PngDataLoader::getPixel(unsigned int x, unsigned int y) const {
  return m_ifile->getPixel(x, y);
}
}
