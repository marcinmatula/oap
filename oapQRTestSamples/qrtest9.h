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



#ifndef QRTEST9
#define QRTEST9

// Generated from ArnoldiPackage procedure. Step 200.
namespace samples {

namespace qrtest9 {

const char* matrix =
    "[-12.63870,  -3.92898,  -0.00026,   0.00000,   0.00001,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
        -3.92898,  12.63870,   0.00084,  -0.00001,  -0.00004,   0.00001,   0.00001,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
        -0.00026,   0.00084, -11.67820,   0.18177,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
         0.00000,  -0.00001,   0.18177,  11.65770,   0.25931,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
         0.00001,  -0.00004,   0.00000,   0.25931, -11.47130,   1.10154,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
         0.00000,   0.00001,   0.00000,   0.00000,   1.10154,  11.37040,   0.30136,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
         0.00000,   0.00001,   0.00000,   0.00000,   0.00000,   0.30136, -11.27630,   0.16825,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.16825,  11.02330,   0.01708,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.01708,  10.76630,   0.24823,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.24823, -10.38440,  -0.00627,   0.00003,  -0.00003,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,  -0.00627, -10.05180,   0.00069,  -0.00071,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00003,   0.00069,   6.40451,  -7.09442,   0.00070,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,  -0.00003,  -0.00071,  -7.09442,  -6.42864,   0.00071,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00070,   0.00071,   8.85346,   0.00210,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00210,  -8.40461,   0.31537,   0.00000,   0.00002,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.31537,   8.34881,  -0.00097,   0.00001,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,  -0.00097,  -7.92412,  -0.00095,  -0.00009,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00002,   0.00001,  -0.00095,   6.94773,  -0.01069,   0.00003,   0.00002,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,  -0.00001,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,  -0.00009,  -0.01069,  -6.67728,   0.00080,   0.00049,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00003,   0.00080,   5.29722,   3.08931,   0.00049,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,  -0.00001,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00002,   0.00049,   3.08931,  -5.29228,  -0.00079,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00049,  -0.00079,   5.47115,  -0.00099,   0.00000,   0.00001,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,  -0.00002,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,  -0.00099,  -4.85082,  -0.00015,   0.00089,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,  -0.00001,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,  -0.00015,  -2.80193,   3.14070,  -0.00051,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,  -0.00002,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00001,   0.00089,   3.14070,   2.76650,   0.00078,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,  -0.00001,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,  -0.00051,   0.00078,   3.56246,   0.00097,  -0.00003,   0.00000,   0.00000,   0.00001,  -0.00003,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00097,  -2.88135,  -0.00074,   0.00030,   0.00001,  -0.00002,   0.00003,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,  -0.00003,  -0.00074,  -2.17876,   0.03096,   0.00055,  -0.00017,   0.00007,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00030,   0.03096,   2.07236,  -0.00063,   0.00064,  -0.00008,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00001,   0.00055,  -0.00063,   1.37088,  -0.00068,   0.00016,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00001,  -0.00002,  -0.00017,   0.00064,  -0.00068,  -0.79311,   0.00043,\
         0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,   0.00000,  -0.00001,   0.00000,  -0.00001,   0.00000,  -0.00002,  -0.00001,  -0.00002,  -0.00001,  -0.00003,   0.00003,   0.00007,  -0.00008,   0.00016,   0.00043,  -0.06922]";

const char* qref =
    "[-0.95492, -0.29686,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        -0.29686,  0.95492,  0.00007,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        -0.00002,  0.00006, -0.99988,  0.01556,  0.00034, -0.00003,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.01556,  0.99963,  0.02213, -0.00212, -0.00006,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.02224, -0.99518,  0.09551,  0.00252, -0.00004,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.09556,  0.99508,  0.02625, -0.00039,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.02637, -0.99954,  0.01491, -0.00002,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.01491,  0.99989, -0.00155, -0.00004,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00155,  0.99973,  0.02305, -0.00001,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.02305, -0.99973,  0.00060,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, -0.00060, -1.00000,  0.00010,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00007,  0.67009, -0.74228,  0.00001,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, -0.00007, -0.74228, -0.67009,  0.00010,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00007,  0.00007,  1.00000,  0.00024, -0.00001,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00024, -0.99930,  0.03750,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.03750,  0.99930, -0.00012,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, -0.00012, -1.00000, -0.00012,  0.00001,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, -0.00012,  1.00000, -0.00154, -0.00001,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, -0.00001, -0.00154, -1.00000,  0.00014,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00012,  0.86383,  0.50378,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00007,  0.50378, -0.86383, -0.00015,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00008, -0.00013,  1.00000, -0.00018,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, -0.00018, -1.00000,  0.00016,  0.00010,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, -0.00003, -0.66572,  0.74621, -0.00022,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00018,  0.74621,  0.66572, -0.00003,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, -0.00001,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, -0.00012,  0.00019,  1.00000,  0.00027, -0.00001,  0.00000,  0.00000,  0.00000, -0.00001,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00027, -1.00000,  0.00026,  0.00010,  0.00000,  0.00001, -0.00001,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, -0.00001, -0.00026, -0.99990,  0.01421,  0.00026,  0.00008, -0.00003,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00010,  0.01421,  0.99990,  0.00030,  0.00031, -0.00004,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00025, -0.00030,  1.00000, -0.00049,  0.00012,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, -0.00001, -0.00008,  0.00031, -0.00049, -1.00000, -0.00054,\
         0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, -0.00001,  0.00000, -0.00001,  0.00001,  0.00003, -0.00004,  0.00012,  0.00054, -1.00000]";

const char* rref =
    "[13.23532,  0.00000,  0.00023,  0.00000, -0.00001,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000, 13.23532,  0.00014, -0.00002, -0.00001,  0.00001,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000, 11.67961, -0.00032,  0.00404,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000,  0.00000, 11.66200,  0.00414,  0.02449,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000,  0.00000,  0.00000, 11.52698, -0.00965,  0.02880,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000, 11.42758,  0.00251,  0.00444,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, 11.28154, -0.00377,  0.00025,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, 11.02460,  0.03376,  0.00038,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, 10.76912,  0.00880, -0.00014,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, 10.38736,  0.01234,  0.00001,  0.00003,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, 10.05179,  0.00025,  0.00069,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  9.55764,  0.01791,  0.00059,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  9.57381, -0.00034, -0.00001,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  8.85346,  0.00011,  0.00007,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  8.41052, -0.00209, -0.00004,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  8.35476, -0.00005,  0.00003,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  7.92412,  0.00012,  0.00017,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  6.94774, -0.00042,  0.00006,  0.00002,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, -0.00001,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  6.67729,  0.00006, -0.00051,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  6.13224,  0.00249,  0.00046,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  6.12797,  0.00022,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, -0.00001,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  5.47115, -0.00011,  0.00000,  0.00001,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, -0.00002,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  4.85082,  0.00082, -0.00048,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00001,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  4.20890, -0.02644,  0.00049,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00001,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  4.18531,  0.00080,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000, -0.00003,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  3.56246,  0.00019, -0.00001,  0.00000,  0.00000,  0.00001, -0.00003,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  2.88135,  0.00131, -0.00009,  0.00000,  0.00003, -0.00003,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  2.17898, -0.00151, -0.00021,  0.00025, -0.00007,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  2.07259, -0.00104,  0.00039, -0.00008,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  1.37088, -0.00028,  0.00015,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.79311, -0.00046,\
        0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.06922]";
}
}

#endif  // QRTEST9\
