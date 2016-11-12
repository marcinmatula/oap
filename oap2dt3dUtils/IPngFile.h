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

#ifndef IPNGFILE_H
#define IPNGFILE_H

#include <png.h>

namespace oap {

class Pixel {
 public:
  inline Pixel() : r(0), g(0), b(0) { a = 1; }

  inline Pixel(unsigned char _r, unsigned char _g, unsigned char _b)
      : r(_r), g(_g), b(_b) {
    a = 1;
  }

  unsigned char r, g, b;
  unsigned char a;
};

class IPngFile {
 public:
  IPngFile();

  virtual ~IPngFile();

  void open(const char* path);

  bool read(void* buffer, size_t size);

  virtual bool read(void* buffer, size_t repeat, size_t size) = 0;

  virtual void loadBitmap() = 0;

  virtual void freeBitmap() = 0;

  virtual unsigned int getWidth() const = 0;

  virtual unsigned int getHeight() const = 0;

  Pixel getPixel(unsigned int x, unsigned int y) const;

  virtual void close() = 0;

 protected:
  virtual bool openInternal(const char* path) = 0;

  virtual bool isPngInternal() const = 0;

  virtual Pixel getPixelInternal(unsigned int x, unsigned int y) const = 0;
};
}

#endif  // IFILE_H
