/*
 * Copyright 2016, 2017 Marcin Matula
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



#ifndef MATRIX2
#define MATRIX2

const char* matrix2Str =
    " (columns=32, rows=32) [-9.93782, 1.59322, -4.60266e-07, -1.78099e-09, "
    "8.51384e-08, 7.76407e-10, 3.18795e-09, -3.28654e-11, 4.69999e-12, "
    "-9.6828e-12, -1.02354e-12, 2.74855e-15, 7.51651e-16, -8.32664e-15, "
    "2.04112e-15, 1.54831e-14, -1.04305e-15, -2.09559e-15, -5.71776e-15, "
    "4.96158e-15, -2.6448e-15, -2.50102e-15, -8.73535e-15, -2.07871e-15, "
    "-2.45828e-15, 8.2916e-15, 4.87831e-15, 4.96321e-15, 3.1052e-15, "
    "6.41789e-15, 8.99873e-16, 3.4479e-12 | 1.59322, 9.93781, 0.000946462, "
    "3.66231e-06, -0.000175073, -1.59653e-06, -6.55551e-06, 6.756e-08, "
    "-9.63429e-09, 1.99168e-08, 2.11194e-09, 8.37746e-13, 1.87008e-12, "
    "3.09311e-15, 1.11887e-14, -9.21583e-15, -7.56992e-15, 4.57741e-15, "
    "1.30757e-14, -4.38027e-15, 5.29521e-15, 7.9184e-15, -6.23427e-15, "
    "-5.74986e-15, -2.57e-15, 2.41031e-16, -8.58738e-15, -2.23254e-15, "
    "-3.15961e-15, 3.73508e-15, -1.08351e-14, 4.0064e-12 | -4.60266e-07, "
    "0.000946462, -9.00423, 0.0378132, -3.0951e-07, -4.1956e-05, 4.93412e-08, "
    "-9.70881e-09, 5.11757e-11, 3.01399e-11, 6.70356e-14, -3.58821e-13, "
    "1.21296e-14, -1.1688e-14, -2.42523e-15, -4.86697e-15, -2.43759e-15, "
    "2.49589e-14, -1.21196e-14, -1.14924e-15, 1.43955e-14, 1.08126e-14, "
    "-3.17143e-15, -1.08979e-15, -2.6865e-15, -3.14858e-16, -1.27044e-15, "
    "6.46726e-16, -5.87008e-15, -4.99772e-14, 1.08284e-13, 2.38092e-08 | "
    "-1.78099e-09, 3.66231e-06, 0.0378132, 8.99938, 0.000996345, 2.00411e-05, "
    "-2.35688e-08, 6.61929e-09, 9.65249e-10, 5.68175e-10, 1.26678e-12, "
    "6.21421e-13, -4.47589e-15, 5.81278e-15, 4.86399e-15, 9.44419e-16, "
    "1.00505e-14, 3.75933e-14, -3.14481e-14, 1.4961e-15, -2.34708e-16, "
    "-4.08893e-15, 8.01633e-16, -3.95706e-16, -1.46042e-15, 2.28164e-15, "
    "-5.60633e-16, 6.66474e-15, -3.90593e-15, -1.5966e-14, 1.93528e-13, "
    "4.31495e-08 | 8.51384e-08, -0.000175073, -3.0951e-07, 0.000996345, "
    "-8.96125, -0.00099081, 1.16521e-06, -1.56786e-07, 5.75642e-10, "
    "3.38842e-10, 7.55374e-13, -3.49012e-12, 1.11476e-13, -2.70591e-14, "
    "-1.16662e-14, 1.3188e-15, -1.88226e-15, 1.06778e-13, -1.11493e-13, "
    "-4.28965e-15, -2.91587e-15, -2.80826e-15, -1.37848e-15, 3.1948e-15, "
    "4.01056e-15, 2.49067e-15, -1.3612e-16, 1.23244e-14, -1.08597e-15, "
    "-2.51711e-13, 6.00002e-13, 1.19165e-07 | 7.76396e-10, -1.59653e-06, "
    "-4.1956e-05, 2.00411e-05, -0.00099081, 8.7658, -0.00099739, 5.49644e-06, "
    "2.06686e-07, 1.21663e-07, 2.70631e-10, 3.49619e-11, -1.12647e-12, "
    "2.28355e-13, 6.46078e-14, 6.77622e-15, -7.0692e-15, 2.71621e-13, "
    "-2.49333e-13, 8.40415e-15, -1.64556e-15, 2.76701e-15, 2.70306e-16, "
    "7.6876e-15, -1.00423e-15, -4.09284e-15, -3.97994e-15, 5.38639e-15, "
    "2.04397e-15, -3.20993e-14, 4.4205e-13, 7.90345e-08 | 3.18795e-09, "
    "-6.55551e-06, 4.93412e-08, -2.35688e-08, 1.16521e-06, -0.00099739, "
    "-8.63325, 0.000996876, -2.73718e-07, -1.61121e-07, -3.58418e-10, "
    "3.55545e-10, -1.14058e-11, 1.42485e-12, 4.67206e-13, -4.75164e-14, "
    "6.71492e-15, -7.28919e-13, 6.99541e-13, 6.07596e-15, -9.77612e-15, "
    "-3.1815e-15, 4.67392e-15, -3.02016e-15, -5.90891e-15, 1.81329e-17, "
    "-3.92944e-15, -1.00819e-14, -4.82764e-15, 2.7412e-13, -6.28391e-13, "
    "-9.30319e-08 | -3.28546e-11, 6.756e-08, -9.70881e-09, 6.61929e-09, "
    "-1.56786e-07, 5.49644e-06, 0.000996876, 8.39106, 0.000843743, "
    "0.000496659, 1.10483e-06, 1.71505e-08, -5.50068e-10, 4.51615e-11, "
    "1.4871e-11, 9.0104e-13, -1.95719e-13, 6.57373e-12, -6.34223e-12, "
    "2.26704e-14, -1.46128e-14, 3.11919e-15, -7.48525e-17, 7.54355e-15, "
    "1.62397e-15, -1.38715e-15, 6.8569e-15, 4.65568e-14, 3.5285e-15, "
    "-9.9526e-14, 1.302e-12, 1.64948e-07 | 4.68522e-12, -9.63429e-09, "
    "5.12044e-11, 9.65248e-10, 5.75635e-10, 2.06686e-07, -2.73718e-07, "
    "0.000843743, 8.10003, -0.000997578, 0.000402591, 7.75617e-07, "
    "-2.48765e-08, 8.71492e-10, 2.86831e-10, 9.86235e-12, -2.10833e-12, "
    "2.25949e-11, -2.17553e-11, 4.77135e-14, -2.77097e-14, 3.22254e-15, "
    "1.14754e-14, 1.39789e-14, 3.01946e-15, -2.51834e-15, -4.33764e-15, "
    "3.51389e-14, -3.90489e-15, -6.09376e-14, 8.10222e-13, 7.82386e-08 | "
    "-9.68553e-12, 1.99168e-08, 3.01409e-11, 5.68181e-10, 3.3884e-10, "
    "1.21663e-07, -1.61121e-07, 0.000496659, -0.000997578, -7.94635, "
    "0.000911304, 2.65973e-05, -8.53057e-07, 1.81141e-08, 5.9623e-09, "
    "-1.49227e-10, 3.20062e-11, -1.82221e-10, 1.75537e-10, 4.59553e-13, "
    "-2.20129e-13, 8.38264e-15, 9.79502e-16, -8.05471e-14, -9.44719e-15, "
    "7.41884e-15, -5.21476e-15, -1.35502e-13, 3.80736e-15, 1.32781e-12, "
    "-2.98814e-12, -2.26676e-07 | -1.027e-12, 2.11196e-09, 6.70898e-14, "
    "1.2641e-12, 7.53747e-13, 2.70644e-10, -3.58418e-10, 1.10483e-06, "
    "0.000402591, 0.000911304, -7.75662, -0.000963512, 3.09029e-05, "
    "-3.84722e-07, -1.26632e-07, 2.23619e-09, -4.79623e-10, 1.25318e-09, "
    "-1.20727e-09, -2.86965e-12, 1.38194e-12, 8.09464e-16, -2.27069e-15, "
    "2.85016e-13, 2.51799e-14, -4.17797e-16, -7.12732e-15, 3.55925e-13, "
    "-1.43539e-14, -2.86523e-12, 6.41162e-12, 4.01194e-07 | -4.11683e-16, "
    "8.38166e-13, -3.68611e-13, 6.22524e-13, -3.49729e-12, 3.4961e-11, "
    "3.55543e-10, 1.71505e-08, 7.75617e-07, 2.65973e-05, -0.000963512, "
    "7.40496, 0.000982379, 6.08187e-05, 2.00186e-05, 1.91428e-07, "
    "-4.10576e-08, 2.70014e-08, -2.60123e-08, 5.40937e-11, -2.61437e-11, "
    "-2.42064e-14, 6.33282e-16, 2.30322e-12, 3.28527e-13, 8.31453e-15, "
    "-2.52916e-15, 1.34451e-12, -4.59117e-14, -6.7364e-13, 1.41095e-11, "
    "6.62109e-07 | -8.79904e-16, 1.87418e-12, 1.18212e-14, -1.98605e-14, "
    "1.12112e-13, -1.12125e-12, -1.14033e-11, -5.5007e-10, -2.48765e-08, "
    "-8.53057e-07, 3.09029e-05, 0.000982379, -7.23513, 0.000944388, "
    "0.000310847, -1.9998e-06, 4.2892e-07, -1.36282e-07, 1.3129e-07, "
    "2.39807e-10, -1.15919e-10, -9.88604e-14, -7.08165e-15, -6.04133e-12, "
    "-8.50352e-13, -9.7123e-15, 1.33575e-14, -2.60923e-12, 7.87612e-14, "
    "1.25668e-11, -2.72739e-11, -9.76575e-07 | 9.26968e-18, -6.70297e-16, "
    "-3.98197e-15, 7.38627e-15, -3.36644e-14, 2.27387e-13, 1.42759e-12, "
    "4.51596e-11, 8.71491e-10, 1.81141e-08, -3.84722e-07, 6.08187e-05, "
    "0.000944388, 6.76779, -0.00099333, 0.000379077, -8.1305e-05, 3.20642e-06, "
    "-3.08897e-06, 4.65576e-09, -2.25029e-09, -1.99155e-12, -9.9126e-14, "
    "3.78574e-11, 5.32947e-12, 5.30207e-14, -5.80114e-14, 5.62772e-12, "
    "-1.91635e-13, -7.67729e-13, 2.88777e-11, 6.64437e-07 | 1.17745e-16, "
    "3.79709e-15, -1.2931e-15, 2.613e-15, -1.12073e-14, 7.48187e-14, "
    "4.69928e-13, 1.48642e-11, 2.86853e-10, 5.96229e-09, -1.26632e-07, "
    "2.00186e-05, 0.000310847, -0.00099333, -6.67952, 0.000873777, "
    "-0.000187409, 4.79466e-06, -4.61902e-06, -6.28385e-09, 3.03721e-09, "
    "2.68009e-12, 1.44249e-13, 3.65953e-11, 5.16127e-12, 5.34508e-14, "
    "-5.83418e-14, 4.7603e-12, -1.53094e-13, -1.27485e-11, 2.6767e-11, "
    "5.05694e-07 | -2.08124e-17, -5.83974e-17, 1.88398e-16, 4.22368e-16, "
    "1.6558e-15, 8.79824e-15, -3.99528e-14, 8.99058e-13, 9.86516e-12, "
    "-1.49234e-10, 2.23619e-09, 1.91428e-07, -1.9998e-06, 0.000379077, "
    "0.000873777, 6.21013, -0.000994105, 0.000195383, -0.000188226, "
    "2.09799e-07, -1.01403e-07, -8.98093e-11, -4.8741e-12, 4.14141e-10, "
    "5.83057e-11, 4.78356e-13, -5.05102e-13, 1.75573e-11, -5.84658e-13, "
    "-1.75414e-13, 4.5482e-11, 5.30958e-07 | -6.54713e-17, -4.43866e-17, "
    "-8.3975e-17, -2.12131e-16, -3.52597e-16, -1.79071e-15, 8.60075e-15, "
    "-1.92781e-13, -2.11595e-12, 3.2008e-11, -4.79621e-10, -4.10576e-08, "
    "4.2892e-07, -8.1305e-05, -0.000187409, -0.000994105, -6.15967, "
    "0.000668187, -0.000643711, -6.55522e-07, 3.16838e-07, 2.80625e-10, "
    "1.51922e-11, 9.87473e-10, 1.39021e-10, 1.1674e-12, -1.24528e-12, "
    "3.93871e-11, -1.30934e-12, -5.83458e-11, 1.18383e-10, 1.16889e-06 | "
    "4.3657e-18, 2.10872e-17, 1.70203e-14, 3.28371e-14, 1.11815e-13, "
    "2.6833e-13, -7.26467e-13, 6.57462e-12, 2.25927e-11, -1.82214e-10, "
    "1.25318e-09, 2.70014e-08, -1.36282e-07, 3.20642e-06, 4.79466e-06, "
    "0.000195383, 0.000668187, 5.49209, -0.000985621, 0.000663108, "
    "-0.000320504, -2.83868e-07, -1.53673e-08, 8.68384e-08, 1.22264e-08, "
    "6.57706e-11, -7.01185e-11, 6.00394e-10, -1.99664e-11, 1.90738e-11, "
    "5.84227e-10, 2.58037e-06 | 5.2517e-17, 3.44936e-17, -1.63151e-14, "
    "-3.15053e-14, -1.07622e-13, -2.58367e-13, 6.99833e-13, -6.3339e-12, "
    "-2.17651e-11, 1.7554e-10, -1.20727e-09, -2.60123e-08, 1.3129e-07, "
    "-3.08897e-06, -4.61902e-06, -0.000188226, -0.000643711, -0.000985621, "
    "-5.38458, -0.000599587, 0.000289803, 2.56676e-07, 1.38952e-08, "
    "5.20156e-08, 7.3235e-09, 4.02992e-11, -4.29742e-11, 3.05124e-10, "
    "-1.01503e-11, -1.71703e-10, 3.27688e-10, 1.10582e-06 | 1.39462e-17, "
    "-2.03079e-17, -9.01716e-17, 1.8665e-16, -6.21972e-16, 9.28464e-16, "
    "2.519e-15, 2.1134e-14, 6.3812e-14, 4.58486e-13, -2.86918e-12, "
    "5.40913e-11, 2.39807e-10, 4.65575e-09, -6.28385e-09, 2.09799e-07, "
    "-6.55522e-07, 0.000663108, -0.000599587, -4.7858, -0.000996836, "
    "0.000388914, -1.88986e-05, 4.6713e-06, 6.57693e-07, 2.46536e-09, "
    "-2.62849e-09, 4.96821e-09, -1.65245e-10, -1.19261e-09, 2.15291e-09, "
    "2.8176e-06 | -4.74154e-18, 5.717e-17, 3.02082e-17, -1.4997e-16, "
    "1.19225e-16, -5.32047e-16, -1.25541e-15, -1.05248e-14, -3.09741e-14, "
    "-2.21597e-13, 1.38674e-12, -2.61444e-11, -1.15907e-10, -2.25029e-09, "
    "3.03722e-09, -1.01403e-07, 3.16838e-07, -0.000320504, 0.000289803, "
    "-0.000996836, 4.71525, -0.000840849, 4.08597e-05, -1.06281e-05, "
    "-1.49637e-06, -4.97047e-09, 5.29937e-09, -8.38851e-09, 2.79003e-10, "
    "-2.08754e-10, -2.44427e-09, -3.25086e-06 | -1.21103e-17, 7.58896e-17, "
    "-1.93496e-17, -4.7793e-17, -8.54394e-17, 1.91047e-16, -4.20255e-17, "
    "1.04422e-16, -3.69083e-17, -2.69149e-16, 1.34762e-15, -2.30334e-14, "
    "-1.02672e-13, -1.99312e-12, 2.69011e-12, -8.98122e-11, 2.80621e-10, "
    "-2.83868e-07, 2.56676e-07, 0.000388914, -0.000840849, 4.2307, "
    "-0.000987199, 0.000261434, 3.68084e-05, 8.88276e-08, -9.47055e-08, "
    "4.78995e-08, -1.59316e-09, 7.64078e-10, 5.94592e-09, 3.36996e-06 | "
    "-8.07888e-17, 5.40988e-17, -1.15842e-16, 1.97528e-16, -2.18624e-16, "
    "-3.08412e-17, 2.79513e-16, -1.32428e-16, -3.00761e-17, 1.19e-16, "
    "2.34848e-17, -1.3017e-15, -5.59521e-15, -1.08034e-13, 1.45618e-13, "
    "-4.86199e-12, 1.51915e-11, -1.53673e-08, 1.38952e-08, -1.88986e-05, "
    "4.08597e-05, -0.000987199, -3.98669, 0.000907053, 0.000127708, "
    "2.91153e-07, -3.10419e-07, 9.91535e-08, -3.29789e-09, -6.875e-09, "
    "1.13435e-08, 3.48945e-06 | -4.64841e-17, 3.48728e-17, 1.34054e-16, "
    "4.42371e-16, 9.54972e-16, 1.33434e-15, -2.31742e-15, 1.12242e-14, "
    "1.62903e-14, -7.5582e-14, 2.85826e-13, 2.31238e-12, -6.04094e-12, "
    "3.78472e-11, 3.6597e-11, 4.1415e-10, 9.87475e-10, 8.68384e-08, "
    "5.20156e-08, 4.6713e-06, -1.06281e-05, 0.000261434, 0.000907053, "
    "-3.32009, 0.000971786, -0.00011985, 0.00012778, -4.29051e-06, "
    "1.42704e-07, 8.43456e-08, -1.26272e-07, -8.99017e-06 | -6.09507e-18, "
    "-2.3e-17, 2.84638e-17, 1.56066e-16, 1.25166e-16, 1.84149e-16, "
    "-3.96248e-16, 1.74192e-15, 2.42391e-15, -1.05958e-14, 4.00715e-14, "
    "3.25721e-13, -8.50556e-13, 5.32876e-12, 5.15265e-12, 5.83101e-11, "
    "1.39031e-10, 1.22264e-08, 7.3235e-09, 6.57693e-07, -1.49637e-06, "
    "3.68084e-05, 0.000127708, 0.000971786, 3.139, 0.00060782, -0.000648041, "
    "1.31953e-05, -4.38882e-07, 4.67765e-08, 1.67492e-07, 9.30877e-06 | "
    "3.32503e-17, -3.00154e-17, 2.49709e-17, -6.29415e-17, 9.82659e-17, "
    "-6.08325e-17, 8.59616e-17, -1.00818e-16, -6.95474e-17, -1.35208e-16, "
    "7.39398e-16, 4.88085e-15, -1.21852e-14, 5.73553e-14, 5.63772e-14, "
    "4.72184e-13, 1.16672e-12, 6.57714e-11, 4.03078e-11, 2.46536e-09, "
    "-4.97047e-09, 8.88276e-08, 2.91153e-07, -0.00011985, 0.00060782, 2.49605, "
    "0.000993514, 0.000664275, -2.20941e-05, 6.48645e-07, 1.50693e-06, "
    "1.42784e-05 | 1.72939e-17, 4.11824e-18, 4.62741e-17, -2.52498e-16, "
    "1.63615e-16, 1.24323e-16, -2.88054e-16, -1.23271e-17, -1.66859e-16, "
    "1.40751e-16, -6.30925e-16, -5.10613e-15, 1.32154e-14, -6.12218e-14, "
    "-5.98596e-14, -5.03718e-13, -1.24364e-12, -7.01235e-11, -4.29752e-11, "
    "-2.6285e-09, 5.29937e-09, -9.47055e-08, -3.10419e-07, 0.00012778, "
    "-0.000648041, 0.000993514, -2.47312, 0.000547532, -1.82112e-05, "
    "-1.71487e-06, 2.19832e-06, 1.57987e-05 | 6.78087e-17, -9.47016e-18, "
    "1.97387e-15, 3.7729e-15, 1.0468e-14, 1.1114e-14, -1.52628e-14, "
    "4.57329e-14, 3.79058e-14, -1.36628e-13, 3.55822e-13, 1.34459e-12, "
    "-2.60671e-12, 5.63856e-12, 4.76061e-12, 1.75569e-11, 3.93871e-11, "
    "6.00396e-10, 3.05127e-10, 4.96822e-09, -8.38851e-09, 4.78995e-08, "
    "9.91535e-08, -4.29051e-06, 1.31953e-05, 0.000664275, 0.000547532, "
    "-1.75195, -0.00095422, 0.00011997, -0.000123757, -6.01355e-05 | "
    "2.30561e-17, -8.90471e-17, -6.12097e-17, 8.24482e-17, -3.07252e-16, "
    "-2.33937e-16, 4.6175e-16, -1.26889e-15, -1.22405e-15, 4.55649e-15, "
    "-1.18807e-14, -4.46709e-14, 8.67813e-14, -1.87519e-13, -1.5831e-13, "
    "-5.84125e-13, -1.30991e-12, -1.99696e-11, -1.01487e-11, -1.65245e-10, "
    "2.79006e-10, -1.59316e-09, -3.29789e-09, 1.42704e-07, -4.38882e-07, "
    "-2.20941e-05, -1.82112e-05, -0.00095422, 1.496, -0.000506527, -0.0004609, "
    "-0.000102821 | 1.26245e-16, 3.75875e-17, -4.85395e-14, -1.72605e-14, "
    "-2.54235e-13, -3.66643e-14, 2.7116e-13, -9.70975e-14, -5.48603e-14, "
    "1.32308e-12, -2.87278e-12, -6.76877e-13, 1.25649e-11, -7.66378e-13, "
    "-1.27439e-11, -1.85744e-13, -5.83482e-11, 1.90751e-11, -1.71699e-10, "
    "-1.19261e-09, -2.08751e-10, 7.64081e-10, -6.875e-09, 8.43456e-08, "
    "4.67765e-08, 6.48645e-07, -1.71487e-06, 0.00011997, -0.000506527, "
    "-0.867371, 0.000996845, 0.000336219 | -6.86816e-18, -1.47926e-16, "
    "1.15182e-13, 1.95609e-13, 5.99413e-13, 4.41458e-13, -6.30895e-13, "
    "1.30309e-12, 8.1694e-13, -2.98186e-12, 6.41308e-12, 1.411e-11, "
    "-2.72775e-11, 2.88728e-11, 2.67686e-11, 4.5486e-11, 1.18386e-10, "
    "5.84228e-10, 3.27682e-10, 2.15291e-09, -2.44428e-09, 5.94592e-09, "
    "1.13435e-08, -1.26272e-07, 1.67492e-07, 1.50693e-06, 2.19832e-06, "
    "-0.000123757, -0.0004609, 0.000996845, 0.793135, 0.000569634 | "
    "3.4447e-12, 4.00181e-12, 2.38092e-08, 4.31495e-08, 1.19165e-07, "
    "7.90345e-08, -9.30319e-08, 1.64948e-07, 7.82386e-08, -2.26676e-07, "
    "4.01194e-07, 6.62109e-07, -9.76575e-07, 6.64437e-07, 5.05694e-07, "
    "5.30958e-07, 1.16889e-06, 2.58037e-06, 1.10582e-06, 2.8176e-06, "
    "-3.25086e-06, 3.36996e-06, 3.48945e-06, -8.99017e-06, 9.30877e-06, "
    "1.42784e-05, 1.57987e-05, -6.01355e-05, -0.000102821, 0.000336219, "
    "0.000569634, -0.136563] (length=1024) [0 <repeats 1024 times>] "
    "(length=1024) CUDA";

#endif  // MATRIX2
