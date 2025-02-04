OAP_PATH := $(PWD)
TMP_PATH := /tmp/Oap

ifndef OAP_GMOCK_PATH
$(error OAP_GMOCK_PATH is not set (should be main directory of gmock set))
endif

ifndef OAP_GTEST_PATH
$(error OAP_GTEST_PATH is not set (should be main directory of gtest set))
endif

ifndef OAP_BUILD_THREADS
$(error OAP_BUILD_THREADS is not set (number of make processes used to build))
endif

$(shell test -d /tmp/Oap/tests_data || mkdir -p /tmp/Oap/tests_data)
$(shell test -d /tmp/Oap/conversion_data || mkdir -p /tmp/Oap/conversion_data)
$(shell test -d /tmp/Oap/host_tests || mkdir -p /tmp/Oap/host_tests)
$(shell test -d /tmp/Oap/host_tests/OapPngFileTests_PrintLetters || mkdir -p /tmp/Oap/host_tests/OapPngFileTests_PrintLetters)
$(shell test -d /tmp/Oap/device_tests || mkdir -p /tmp/Oap/device_tests)

ifdef PROJECT
include $(OAP_PATH)/${PROJECT}
else
include $(OAP_PATH)/project_linux_default.mk
endif

TYPES := OAP_CONFIG_NI_EF

OAP_INCLUDES := oapUtils
OAP_INCLUDES += oapMath
OAP_INCLUDES += oapCuda
OAP_INCLUDES += oapMatrix
OAP_INCLUDES += oapMatrixCpu
OAP_INCLUDES += oapMatrixCuda
OAP_INCLUDES += oapCudaTests
OAP_INCLUDES += ArnoldiPackage
OAP_INCLUDES += oapQRTestSamples
OAP_INCLUDES += oapTests
OAP_INCLUDES += oapCMatrixDataTests
OAP_INCLUDES += oapHostTests
OAP_INCLUDES += oapAppUtils
OAP_INCLUDES += oap2dt3dDevice
OAP_INCLUDES += oapNeuralHost
OAP_INCLUDES += oapNeuralDevice
OAP_INCLUDES += oapNeuralApps
OAP_INCLUDES += oapNeuralRoutinesHost
OAP_INCLUDES += oapNeuralRoutinesHostTest
OAP_INCLUDES += oapNeuralRoutines
OAP_INCLUDES += oapDeviceTestsData
OAP_INCLUDES += oapTestsData
OAP_INCLUDES += oapArnoldiHostTests

TARGET_ARCH := DEVICE_HOST

COMPILE_HOST := 0
COMPILE_DEVICE := 0

ifeq ($(TARGET_ARCH),DEVICE_HOST)
COMPILE_DEVICE := 1
COMPILE_HOST := 1
endif

ifeq ($(TARGET_ARCH),DEVICE)
COMPILE_DEVICE := 1
endif

ifeq ($(TARGET_ARCH),HOST)
COMPILE_HOST := 1
endif


ifeq ($(COMPILE_HOST),1)
OAP_MODULES := oapUtils
OAP_MODULES += oapMath
OAP_MODULES += oapMatrix
OAP_MODULES += oapMatrixCpu
OAP_MODULES += oapCMatrixDataTests
endif

ifeq ($(COMPILE_DEVICE),1)
OAP_MODULES += oapCuda
OAP_MODULES += oapMatrixCuda
OAP_MODULES += oapCudaTests
OAP_MODULES += ArnoldiPackage
OAP_MODULES += oapNeuralDevice
OAP_MODULES += oapDeviceTests
OAP_MODULES += oapArnoldiDeviceTests
endif

ifeq ($(COMPILE_HOST),1)
OAP_MODULES += oapAppUtils
OAP_MODULES += oap2dt3dTests
OAP_MODULES += oap2dt3dFuncTests
endif

ifeq ($(COMPILE_HOST),1)
OAP_MODULES += oapNeuralHost
OAP_MODULES += oapNeuralRoutinesHost
OAP_MODULES += oapNeuralRoutinesHostTests
OAP_MODULES += oapHostTests
OAP_MODULES += oapArnoldiHostTests
endif

ifeq ($(COMPILE_DEVICE),1)
OAP_MODULES += oap2dt3dDevice
OAP_MODULES += oap2dt3dDeviceTests
OAP_MODULES += oap2dt3d
endif

ifeq ($(COMPILE_DEVICE),1)
OAP_MODULES += oapNeural
OAP_MODULES += oapNeuralRoutines
OAP_MODULES += oapNeuralApps
OAP_MODULES += oapNeuralDeviceTests
endif

CU_OAP_MODULES := oapCuda
CU_OAP_MODULES += oapMatrixCuda
CU_OAP_MODULES += oapCudaTests
CU_OAP_MODULES += oapShibataCuda
CU_OAP_MODULES += ArnoldiPackage
CU_OAP_MODULES += oapShibataMgr
CU_OAP_MODULES += oapDeviceTests
