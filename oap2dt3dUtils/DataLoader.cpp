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

#include "DataLoader.h"
#include "Exceptions.h"
#include "PngFile.h"
#include "Config.h"
#include "HostMatrixModules.h"

#include <sstream>
#include <functional>

namespace oap {

DataLoader::DataLoader(const Images& images, bool dealocateImages)
    : m_images(images), m_deallocateImages(dealocateImages) {
  load();
}

DataLoader::~DataLoader() { destroyImages(); }

math::Matrix* DataLoader::createMatrix(const Images& images) {
  const size_t refLength = images[0]->getLength();
  floatt* floatsvec = new floatt[refLength];

  math::Matrix* hostMatrix = host::NewReMatrix(images.size(), refLength);

  for (size_t fa = 0; fa < images.size(); ++fa) {
    Image* it = images[fa];
    const size_t length = it->getLength();
    if (refLength != length) {
      delete[] floatsvec;
      host::DeleteMatrix(hostMatrix);
      throw oap::exceptions::NotIdenticalLengths(refLength, length);
    }
    it->getFloattVector(floatsvec);
    host::SetReVector(hostMatrix, fa, floatsvec, refLength);
  }

  delete[] floatsvec;

  return hostMatrix;
}

math::Matrix* DataLoader::createMatrix() const {
  return DataLoader::createMatrix(m_images);
}

ArnUtils::MatrixInfo DataLoader::createMatrixInfo() const {
  const uintt width = m_images.size();
  const uintt height = m_images[0]->getLength();

  return ArnUtils::MatrixInfo(true, false, width, height);
}

std::string DataLoader::constructAbsPath(const std::string& dirPath) {
  std::string path;

  if (dirPath[0] != '/') {
    path = utils::Config::getPathInOap(dirPath.c_str());
  } else {
    path = dirPath;
  }

  if (path[path.length() - 1] != '/') {
    path = path + '/';
  }

  return path;
}

std::string DataLoader::constructImagePath(const std::string& absPath,
                                           const std::string& nameBase,
                                           size_t index, size_t count) {
  std::string imagePath = absPath;
  imagePath = imagePath + nameBase;

  std::stringstream sstream;

  size_t width = 0;
  size_t temp = count;
  while (temp >= 10) {
    ++width;
    temp = temp / 10;
  }

  if (width > 0) {
    sstream.width(width);
    sstream.fill('0');
  }

  sstream << index;

  imagePath = imagePath + sstream.str();

  return imagePath;
}

void DataLoader::load() {
  oap::OptSize optWidth;
  oap::OptSize optHeight;
  executeLoadProcess(optWidth, optHeight, 0, m_images.size());
}

void DataLoader::executeLoadProcess(const oap::OptSize& optWidthRef,
                                    const oap::OptSize& optHeightRef,
                                    size_t begin, size_t end) {
  oap::OptSize optWidth = optWidthRef;
  oap::OptSize optHeight = optHeightRef;

  std::function<void(Image*, const oap::OptSize&)> setHeightFunc =
      &Image::setOptHeight;

  std::function<void(Image*, const oap::OptSize&)> setWidthFunc =
      &Image::setOptWidth;

  bool needreload = false;
  bool previousneedreload = false;

  std::function<void(std::function<void(Image*, const oap::OptSize&)>&,
                     oap::Image*, oap::OptSize&, oap::OptSize&)>
      verifyReloadConds = [&needreload, &previousneedreload](
          std::function<void(Image*, const oap::OptSize&)>& setter,
          oap::Image* image, oap::OptSize& optSize, oap::OptSize& osize) {

        if (osize.optSize < optSize.optSize) {
          setter(image, osize);
          needreload = true;
        } else if (optSize.optSize == 0) {
          optSize = osize;
        } else if (osize.optSize > optSize.optSize) {
          previousneedreload = true;
          optSize = osize;
        }
      };

  for (size_t fa = begin; fa < end; ++fa) {
    Image* image = m_images[fa];

    loadImage(image);

    oap::OptSize owidth = image->getWidth();

    oap::OptSize oheight = image->getHeight();

    needreload = false;
    previousneedreload = false;

    verifyReloadConds(setWidthFunc, image, optWidth, owidth);
    verifyReloadConds(setHeightFunc, image, optHeight, oheight);

    if (needreload) {
      image->freeBitmap();

      loadImage(image);
    }

    if (previousneedreload) {
      freeBitmaps(begin, fa);
      executeLoadProcess(optWidth, optHeight, begin, fa);
    }
  }
}

void DataLoader::loadImage(oap::Image* image) const {
  image->open();
  image->loadBitmap();
  image->close();
}

void DataLoader::freeBitmaps(size_t begin, size_t end) {
  for (size_t fa = begin; fa < end; ++fa) {
    m_images[fa]->freeBitmap();
  }
}

void DataLoader::destroyImages() {
  for (size_t fa = 0; fa < m_images.size(); ++fa) {
    if (m_images[fa] != NULL) {
      m_images[fa]->freeBitmap();
    }
    if (m_deallocateImages) {
      delete m_images[fa];
    }
  }
  m_images.clear();
}
}
