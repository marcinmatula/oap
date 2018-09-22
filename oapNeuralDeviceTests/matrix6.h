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



#ifndef MATRIX6_H
#define MATRIX6_H

const char* QJstr =
    "(columns=32, rows=32) [0.0664717, -0.0144056, -0.104501, 0.0644768, "
    "0.148217, -0.0774458, -0.218025, 0.112951, 0.214421, -0.226367, "
    "-0.0246904, 0.208808, -0.220987, -0.275262, 0.108498, 0.312204, "
    "-0.0546851, -0.298615, 0.0510976, 0.24679, -0.0546116, -0.179148, "
    "0.0432144, 0.151089, -0.0568763, -0.135564, 0.0421952, 0.189685, "
    "0.0450182, -0.24343, 0.077353, -0.417935 | -0.0602413, -0.0976781, "
    "0.0217865, 0.194298, 0.171678, -0.102901, -0.315356, -0.174389, 0.16702, "
    "0.287433, -0.0909189, -0.162864, 0.242098, 0.121235, -0.0831963, "
    "-0.0618316, -0.063824, 0.0436067, 0.0774262, -0.0536754, -0.0660865, "
    "0.112163, 0.125104, -0.0880515, -0.111102, 0.0676433, 0.0978634, "
    "-0.0754149, -0.0714025, 0.375043, 0.175617, -0.53417 | 0.0795767, "
    "-0.228064, -0.0368767, 0.354462, -0.109735, -0.357226, 0.283001, 0.21411, "
    "-0.317458, -0.0714479, 0.193985, 0.040856, -0.207812, 0.0235245, "
    "0.217657, 0.0174898, -0.24876, 0.00505973, 0.221833, -0.0164942, "
    "-0.207176, 0.0706095, 0.108016, -0.0222249, -0.0392993, -0.0678161, "
    "0.176135, -0.128441, -0.245217, 0.162804, 0.0230016, -0.0132215 | "
    "0.00201291, 0.00477404, 0.006524, 0.00727412, -0.00717523, -0.0495962, "
    "-0.0781014, -0.0466083, 0.0210298, 0.0694221, 0.0747979, 0.0579367, "
    "0.0528291, -0.0608714, -0.174459, -0.122204, 0.0553982, 0.254704, "
    "0.295585, 0.0292041, -0.362899, -0.32753, -0.0309905, 0.28362, 0.438548, "
    "0.319416, -0.149952, -0.185146, -0.177929, -0.237656, -0.00391848, "
    "-0.0848995 | 0.0266208, -0.0238396, -0.0336522, 0.0652841, 0.00582978, "
    "-0.0966601, 0.0736161, 0.0437995, -0.083268, -0.0178594, 0.0808064, "
    "-0.0290996, 0.0116301, -0.0745841, 0.171522, -0.189087, 0.000833994, "
    "0.303882, -0.326126, 0.021209, 0.321412, -0.51387, 0.269188, 0.194591, "
    "-0.325032, 0.292594, 0.0590658, 0.0205107, 0.0999502, 0.0212749, "
    "0.0241329, -0.0898445 | 0.0353426, 0.0535498, 0.0262474, -0.00230231, "
    "-0.0287222, -0.0838373, -0.093201, 0.00239242, 0.153917, 0.168318, "
    "-0.000351673, -0.272206, -0.164694, 0.0796432, 0.105551, 0.0483897, "
    "-0.0269386, -0.0993888, -0.128269, 0.0129872, 0.198488, 0.167378, "
    "-0.00941466, -0.212372, -0.0814346, 0.297544, 0.173969, -0.181311, "
    "-0.469505, -0.532962, -0.0538825, -0.00770759 | -0.0475487, -0.0768922, "
    "0.0623784, 0.0505953, -0.0291688, -0.0791756, 0.0432407, 0.156489, "
    "-0.185811, -0.0811786, 0.216476, -0.0309574, -0.0892845, 0.209237, "
    "-0.107664, -0.0641454, 0.0487684, -0.0276659, 0.113772, -0.147612, "
    "-0.022054, 0.230494, 0.0664226, -0.230297, -0.0731748, 0.332006, "
    "-0.352316, 0.202651, 0.447368, -0.287375, 0.0366297, -0.285875 | "
    "-0.040841, -0.011763, 0.0915887, 0.132727, 0.0490484, -0.0283775, "
    "-0.0320224, -0.0343076, -0.105975, -0.106964, 0.0322875, 0.181628, "
    "-0.111878, -0.197797, 0.0647017, 0.163683, 0.0274522, -0.18576, "
    "-0.191483, 0.125175, 0.319425, 0.0333652, -0.302081, -0.139141, 0.320698, "
    "0.406138, -0.204582, -0.278613, -0.0110552, 0.366359, 0.0512877, "
    "-0.0430394 | 0.161642, 0.0853265, -0.257896, -0.333574, 0.109376, "
    "0.450915, 0.137208, -0.335743, -0.234241, 0.199049, 0.299129, -0.08803, "
    "-0.284285, 0.074307, 0.228254, 0.0189016, -0.173619, -0.0571579, "
    "0.102887, 0.0704715, -0.0443547, -0.0321168, 0.0194525, 0.0126466, "
    "0.0128863, 0.0404041, 0.00531895, -0.0201851, -0.0126831, 0.0930043, "
    "0.0628282, -0.209679 | -0.0250496, -0.142556, 0.154572, 0.0269827, "
    "-0.10664, -0.00687985, 0.120191, -0.0806632, -0.000900589, -0.0292668, "
    "0.0301211, 0.0953184, -0.0869428, 0.0111399, 0.16153, -0.301662, "
    "0.0657626, 0.311064, -0.190001, -0.10566, 0.212415, 0.137844, -0.39639, "
    "0.103923, 0.244161, -0.35605, 0.0458473, 0.127994, -0.0916094, -0.164803, "
    "0.0821533, -0.398578 | -0.410499, -0.258494, 0.485249, 0.0417829, "
    "-0.41916, 0.196143, 0.170568, -0.195133, -0.07022, 0.171291, 0.0480878, "
    "-0.104566, -0.00519966, -0.0505761, -0.0863305, 0.198111, 0.0454627, "
    "-0.227524, 0.00148963, 0.182197, -0.0463407, -0.165381, 0.0966534, "
    "0.0824282, -0.071034, -0.015778, 0.0467158, 0.037294, -0.00362421, "
    "-0.0384686, 0.0152511, -0.0778339 | 0.156912, 0.177656, -0.00974948, "
    "-0.130321, -0.11177, 0.104533, 0.188629, -0.0206636, -0.237312, "
    "-0.104907, 0.0521057, 0.337212, 0.200555, -0.348154, -0.360815, 0.117045, "
    "0.243269, 0.0747804, -0.0879869, -0.1812, -0.0510622, 0.176628, 0.164966, "
    "-0.114932, -0.175526, 0.0619076, 0.182148, -0.0769949, -0.24229, "
    "-0.0360408, 0.0596353, -0.247706 | -0.344106, 0.0270788, 0.29919, "
    "-0.283171, 0.0358436, 0.142013, -0.143579, 0.0235707, 0.208364, "
    "-0.270019, -0.0852529, 0.276541, -0.136231, -0.114125, 0.310016, "
    "-0.0969124, -0.298323, 0.234731, 0.176558, -0.215377, -0.0895789, "
    "0.123177, 0.147428, -0.112087, -0.115974, 0.153045, 0.028231, -0.0825203, "
    "-0.0506951, 0.063828, -0.000926019, 0.0332289 | 0.206103, 0.326917, "
    "0.0548907, -0.350042, -0.443834, -0.141431, 0.208466, 0.266166, "
    "0.0879032, -0.117557, -0.287761, -0.170242, 0.155522, 0.183802, "
    "0.0902107, -0.0300414, -0.162697, -0.107762, 0.0858927, 0.160266, "
    "0.0205293, -0.0717208, -0.0481159, 0.0183095, 0.0728615, 0.0786774, "
    "-0.0311154, -0.0380941, 0.00709126, 0.146623, 0.0831594, -0.267809 | "
    "-0.654926, 0.449601, -0.104443, -0.125903, 0.234266, -0.183902, "
    "-0.00894444, 0.224304, -0.242999, 0.00746559, 0.194931, -0.0971091, "
    "-0.0369521, 0.100098, -0.079261, -0.0196328, 0.099297, -0.0481922, "
    "-0.0626274, 0.0825312, 0.00538056, -0.0401104, -0.0481182, 0.0648063, "
    "0.0391651, -0.127634, 0.0877319, -0.0094613, -0.105835, 0.0384059, "
    "0.0278613, -0.091421 | 0.306207, 0.597152, 0.531766, 0.241825, "
    "-0.0113007, -0.112927, -0.161386, -0.153008, -0.0133063, 0.150742, "
    "0.22065, 0.0235256, -0.174548, -0.0299373, 0.0617284, 0.0101327, "
    "-0.000469273, 0.0323479, 0.0171206, -0.0419473, -0.0516944, -0.0102423, "
    "0.0301675, 0.0360304, -0.0295, -0.0998979, -0.0139841, 0.065459, "
    "0.0933853, 0.0371031, -0.0140741, 0.0701918 | -0.261413, 0.310012, "
    "-0.356029, 0.322897, -0.160025, -0.122702, 0.345547, -0.383673, 0.149858, "
    "0.163827, -0.255703, 0.0977158, 0.0458421, -0.204411, 0.14488, 0.0646562, "
    "-0.151023, 0.0531786, 0.0819142, -0.0919251, 0.00759388, 0.0660203, "
    "-0.0109209, -0.0467349, -0.00544956, 0.0689456, -0.108158, 0.0717504, "
    "0.137079, -0.125793, -0.0130624, -0.00719357 | 0.0324282, 0.103217, "
    "0.197888, 0.300258, 0.357994, 0.304535, 0.124291, -0.121448, -0.322288, "
    "-0.363049, -0.309017, -0.0383154, 0.28593, 0.200726, 0.0183432, "
    "-0.114266, -0.184444, -0.0913763, 0.0952509, 0.176932, 0.0487923, "
    "-0.05609, -0.0242379, -0.00591184, -0.0167975, 0.0317544, 0.0463457, "
    "0.00132825, -0.0959184, -0.189478, -0.00831614, -0.0479487 | -0.0793169, "
    "0.157703, -0.275169, 0.386361, -0.441626, 0.397206, -0.251037, 0.0567861, "
    "0.169381, -0.314103, 0.174324, 0.0516808, -0.145669, 0.257927, "
    "-0.0766256, -0.155855, 0.122549, 0.00453508, -0.0438901, 0.0309361, "
    "-0.0266542, -0.00587814, 0.0458739, -0.0122225, -0.0227614, 0.00969488, "
    "0.0610364, -0.0625785, -0.0846586, 0.0981919, 0.0154348, -0.0159688 | "
    "0.0212271, 0.0402425, 0.135243, 0.14982, 0.332495, 0.252277, 0.555611, "
    "0.295393, 0.462974, 0.0609396, -0.0120101, -0.0977, -0.207194, 0.0568888, "
    "-0.0521657, 0.0481676, 0.218234, 0.0235848, -0.0616203, -0.0834226, "
    "-0.113903, -0.00506879, 0.0679603, 0.0272611, 0.0384262, 0.0557659, "
    "-0.0118249, -0.0555828, -0.0173357, 0.122073, 0.0339519, -0.0813018 | "
    "-0.0115184, 0.0560229, -0.0305156, 0.183721, -0.0843865, 0.394887, "
    "-0.183489, 0.52364, -0.203923, 0.318415, -0.076373, -0.189023, 0.163672, "
    "-0.343272, 0.161126, 0.172022, -0.179952, 0.147669, 0.0333932, -0.154908, "
    "0.0411651, 0.0351568, -0.0857269, 0.0370599, 0.0663452, -0.0270105, "
    "-0.0498484, 0.0400077, 0.0514476, -0.0538496, 0.000258339, -0.0262446 | "
    "0.000990508, 0.00370593, 0.00817385, 0.0161682, 0.0283067, 0.0555236, "
    "0.113069, 0.173879, 0.23376, 0.280699, 0.34961, 0.395198, 0.249788, "
    "-0.0128108, -0.180896, -0.304301, -0.323292, -0.11035, 0.172316, "
    "0.336076, 0.223774, -0.0111154, -0.103252, -0.120037, -0.0920528, "
    "-0.00902716, 0.0409847, 0.0243519, -0.00877491, -0.0606629, -0.0212125, "
    "0.0582353 | -0.000249022, 0.000659744, -0.001679, 0.00477413, -0.0162558, "
    "0.0458152, -0.0912214, 0.142386, -0.227586, 0.395894, -0.4815, 0.41259, "
    "-0.301208, 0.141688, 0.112531, -0.294718, 0.269762, -0.13339, -0.0491412, "
    "0.14812, -0.12596, -0.00352733, 0.108588, -0.0501121, -0.0382173, "
    "0.037326, -0.00466377, -0.0078862, 0.000157529, -0.00667098, 5.47433e-05, "
    "-0.00319235 | -8.94131e-06, -1.94161e-05, -0.00010233, -0.0001461, "
    "-0.00130856, -0.00159551, -0.0142244, -0.0170245, -0.0581727, -0.0683278, "
    "-0.231717, -0.275571, -0.479632, -0.278268, -0.496859, -0.1551, "
    "-0.121255, 0.235805, 0.288757, 0.197278, 0.208863, -0.00682357, "
    "-0.0909438, -0.10244, -0.122378, -0.0318387, 0.0484898, 0.029422, "
    "0.0379857, 0.0873234, 0.00787827, 0.006152 | -8.53611e-06, 3.8033e-05, "
    "-7.79979e-05, 0.000457664, -0.00160109, 0.00700102, -0.0113522, "
    "0.0304474, -0.0351375, 0.127931, -0.12233, 0.303435, -0.154315, 0.479127, "
    "-0.308861, 0.474217, -0.320608, 0.158546, -0.0429435, -0.272685, "
    "0.204771, -0.125653, -0.0760125, 0.170913, 0.00356096, -0.00166911, "
    "0.0451132, 0.0023137, -0.0301677, -0.0229028, 0.00180468, -0.0165047 | "
    "1.52706e-07, 7.35603e-07, 2.57857e-06, 1.15828e-05, 5.4883e-05, "
    "0.000253923, 0.000997828, 0.00252091, 0.00597677, 0.0154123, 0.0363366, "
    "0.0750073, 0.117171, 0.159364, 0.260754, 0.363681, 0.440568, 0.421685, "
    "0.418993, 0.337649, 0.171032, 0.000272035, -0.107613, -0.177304, "
    "-0.126878, 0.0022779, 0.0516835, 0.0182603, 0.00206826, 0.0126955, "
    "-0.00331741, 0.0188569 | 9.32549e-10, -4.49617e-09, 2.59245e-08, "
    "-2.14853e-07, 1.65789e-06, -8.2385e-06, 2.60694e-05, -6.17085e-05, "
    "0.000185811, -0.000715496, 0.00209064, -0.00497127, 0.0109301, "
    "-0.0319242, 0.0737559, -0.158375, 0.247856, -0.390367, 0.499148, "
    "-0.479873, 0.334655, -0.115134, -0.172, 0.278469, -0.137459, 0.0756088, "
    "0.125345, -0.00813461, -0.0302506, 0.0366136, 0.0028413, 0.00567844 | "
    "-3.93376e-13, 3.39164e-12, -1.85821e-11, 3.2956e-10, -2.06586e-09, "
    "2.1772e-08, -3.83806e-08, 3.30935e-07, -3.22299e-07, 7.20019e-06, "
    "-7.52179e-06, 9.46769e-05, -7.01859e-05, 0.00115711, -0.000959591, "
    "0.0122216, -0.00357483, 0.0616897, -0.000458833, 0.260685, 0.130687, "
    "0.595779, 0.184483, 0.699693, -0.0432156, 0.152227, -0.0247661, "
    "-0.0505344, 0.0442399, 0.0120244, -0.0102524, 0.0449661 | 1.23723e-13, "
    "-1.33853e-12, 1.71702e-11, -1.8236e-10, 2.87453e-09, -1.38876e-08, "
    "9.52741e-08, -1.54008e-07, 1.40226e-06, -3.85058e-06, 3.08796e-05, "
    "-5.22811e-05, 0.000324751, -0.000726104, 0.00450676, -0.00669432, "
    "0.0300603, -0.0279748, 0.143304, -0.0457347, 0.426184, -0.0205061, "
    "0.66524, -0.132327, 0.435332, -0.286594, -0.218174, -0.0618417, "
    "-0.0918285, -0.0343326, 0.00394242, -0.0284741 | 3.55749e-19, "
    "1.02092e-17, 1.30699e-16, 3.42314e-15, 4.92702e-14, 6.187e-13, "
    "5.21007e-12, 3.2063e-11, 2.10502e-10, 4.55522e-10, 1.09106e-08, "
    "1.40035e-08, 2.88839e-07, 9.48435e-07, 1.44025e-06, 1.84269e-06, "
    "-8.0182e-05, -0.000300221, -0.0018923, -0.00674305, -0.0234451, "
    "-0.0522172, -0.105732, 0.0762624, -0.438173, -0.294079, -0.675357, "
    "-0.452676, -0.180478, -0.0581404, 0.0106656, -0.0641232 | -1.9324e-22, "
    "-5.54554e-21, -7.09946e-20, -1.85942e-18, -2.67632e-17, -3.36073e-16, "
    "-2.83007e-15, -1.74164e-14, -1.14343e-13, 8.44805e-12, -1.74099e-11, "
    "2.28285e-10, -6.19641e-10, 2.71215e-09, -1.63357e-08, 1.03333e-07, "
    "-4.51808e-07, 3.62963e-06, -1.91559e-05, 0.000124779, -0.000564384, "
    "0.00259076, -0.0100797, 0.0277647, -0.0572094, 0.151769, -0.373182, "
    "0.701319, -0.544174, 0.200306, 0.00802032, 0.0734087 | 0 <repeats 26 "
    "times>, 2.32965e-05, -0.000477909, 0.00680699, -0.10683, 0.964538, "
    "0.241263] (length=1024) [0 <repeats 1024 times>] (length=1024) CUDA";

const char* Qstr =
    "(columns=32, rows=32) [-0.954912, -0.296889, 0 <repeats 30 times>, "
    "0.296889, -0.954912, 0 <repeats 32 times>, -0.999959, 0.00901833, "
    "2.63042e-06, -9.39223e-09, -2.04368e-12, 6.01132e-18, 0 <repeats 26 "
    "times>, 0.00901834, 0.999959, 0.000291663, -1.04142e-06, -2.26604e-10, "
    "6.6654e-16, 0 <repeats 27 times>, 0.000291677, -0.999994, 0.00357059, "
    "7.76934e-07, -2.28529e-12, 0 <repeats 28 times>, 0.00357059, 0.999994, "
    "0.000217591, -6.40028e-10, 0 <repeats 29 times>, 0.000217592 | -1, "
    "2.94143e-06, 0 <repeats 30 times>, -2.94143e-06, -1, 0 <repeats 32 "
    "times>, 1, 0 <repeats 32 times>, 1, 0 <repeats 32 times>, 1, 0 <repeats "
    "32 times>, -0.128832, -0.991667, 0 <repeats 30 times>, 0.991667, "
    "-0.128832, 0 <repeats 32 times>, 1, 0 <repeats 32 times>, -0.999995, "
    "-0.00313286, 0 <repeats 30 times>, 0.00313286, -0.999995, 0 <repeats 32 "
    "times>, 1, 0 <repeats 32 times>, 1, 0 <repeats 32 times>, 1, 0 <repeats "
    "32 times> | 0.922941, -0.384941, 0 <repeats 30 times>, 0.384941, "
    "0.922941, 0 <repeats 32 times>, 1, 0 <repeats 32 times>, 1, 0 <repeats 32 "
    "times>, 1, 0 <repeats 32 times>, 1, 0 <repeats 32 times>, 1, 0 <repeats "
    "32 times>, 1, 0 <repeats 32 times>, 1, 0 <repeats 32 times>, 1, 0 "
    "<repeats 32 times>, 1, 0 <repeats 32 times>, 1, 0 <repeats 32 times>, 1] "
    "(length=1024) [0 <repeats 1024 times>] (length=1024) CUDA";

#endif  // MATRIX6_H
