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

#include "Image.h"
#include "Exceptions.h"

#include <memory>

namespace oap
{

Image::Image(const std::string& path)
  : m_isOpen(false), m_path(path), m_loadedBitmap(false)
{
  size_t index = m_path.find_last_of("/");

  m_fileName = m_path.substr(index + 1);
  m_filePath = m_path.substr(0, index);
}

Image::~Image() {}

bool Image::read(void* buffer, size_t size)
{
  return read(buffer, 1, size);
}

void Image::loadBitmap()
{
  if (!isOpened ())
  {
    open();
  }

  if (!m_loadedBitmap)
  {
    m_loadedBitmap = true;
    loadBitmapProtected();
  }
}

void Image::freeBitmap()
{
  if (m_loadedBitmap)
  {
    m_loadedBitmap = false;
    freeBitmapProtected();
  }
}

void Image::open()
{
  if (isOpened())
  {
    return;
  }

  if (m_path.find(std::string(".") + getSufix()) == std::string::npos)
  {
    m_path = m_path + ".";
    m_path = m_path + getSufix();
  }

  if (openProtected(m_path) == false)
  {
    close();
    throw oap::exceptions::FileNotExist(m_path);
  }

  if (isCorrectFormat() == false)
  {
    close();
    throw oap::exceptions::NotCorrectFormat(m_path, getSufix());
  }

  m_isOpen = true;
}

bool Image::isOpened() const
{
  return m_isOpen;
}
bool Image::isLoaded() const
{
  return m_loadedBitmap;
}

pixel_t Image::getPixel(unsigned int x, unsigned int y) const
{
  unsigned int height = getHeight().optSize;
  unsigned int width = getWidth().optSize;
  if (x >= width)
  {
    throw exceptions::OutOfRange(x, width);
  }
  if (y >= height)
  {
    throw exceptions::OutOfRange(y, height);
  }
  return getPixelProtected(x, y);
}

size_t Image::getLength() const
{
  return getOutputWidth().optSize * getOutputHeight().optSize;
}

bool Image::getPixelsVector(pixel_t* pixels) const
{
  if (m_loadedBitmap)
  {
    getPixelsVectorProtected(pixels);
    return true;
  }
  return false;
}

void Image::getFloattVector(floatt* vector) const
{
  const size_t length = getLength();
  std::unique_ptr<pixel_t[]> pixelsUPtr(new pixel_t[length]);
  pixel_t* pixels = pixelsUPtr.get();
  pixel_t max = Image::getPixelMax();
  this->getPixelsVector(pixels);
  for (size_t fa = 0; fa < length; ++fa)
  {
    vector[fa] = oap::Image::convertPixelToFloatt(pixels[fa]);
  }
}

void Image::close()
{
  closeProtected();
  m_isOpen = false;
}

pixel_t Image::m_MaxPixel = Image::getPixelMax();

pixel_t Image::convertRgbToPixel(unsigned char r, unsigned char g,
                                 unsigned char b)
{
  pixel_t rgb = r;
  rgb = rgb << 8;
  rgb |= g;
  rgb = rgb << 8;
  rgb |= b;
  return rgb;
}

floatt Image::convertPixelToFloatt(pixel_t pixel)
{
  return static_cast<floatt>(pixel) / static_cast<floatt>(Image::m_MaxPixel);
}

floatt Image::convertRgbToFloatt(unsigned char r, unsigned char g,
                                 unsigned char b)
{
  pixel_t pixel = convertRgbToPixel(r, g, b);
  return convertPixelToFloatt(pixel);
}

pixel_t Image::getPixelMax()
{
  return convertRgbToPixel(255, 255, 255);
}

std::string Image::getFileName() const
{
  return m_fileName;
}

std::string Image::getFilePath() const
{
  return m_filePath;
}

bool Image::save(const std::string& prefix, const std::string& path)
{
  std::string filename = this->getFileName();

  filename = prefix + filename;

  std::string filepath = path + "/" + filename;

  return save (filepath);
}

bool Image::save(const std::string& path)
{
  onSave (path);
  this->open ();
  this->loadBitmap ();
  return saveProtected (path);
}

}
