include ../project_generic.mk
include module.mk
OAP_INCLUDES_PATHS := $(addprefix -I$(OAP_PATH)/, $(OAP_INCLUDES))
CU_FILES := $(wildcard *.cu)
CPP_FILES := $(wildcard *.cpp)
OCPP_FILES := $(addprefix build/$(MODE)/$(PLATFORM)/,$(notdir $(CPP_FILES:.cpp=.o)))
D_FILES := $(addprefix build/$(MODE)/$(PLATFORM)/,$(notdir $(CPP_FILES:.cpp=.d)))
OCU_FILES := $(addprefix build/$(MODE)/$(PLATFORM)/,$(notdir $(CU_FILES:.cu=.o)))
INCLUDE_DIRS := -I/usr/local/cuda/include -I/usr/include $(OAP_INCLUDES_PATHS)
INCLUDE_DIRS += $(INCLUDE_PATHS)
NVCC_INCLUDE_DIRS := -I/usr/local/cuda/include
LIBS_DIRS := -L/usr/lib/nvidia-current -L/usr/lib -L/usr/local/cuda/lib64
LIBS := $(EXTRA_LIBS)
SANITIZER_LINKING :=
SANITIZER_COMPILATION :=
CXXOPTIONS :=

ifeq ($(MODE), DebugSanitizer)
	SANITIZER_LINKING := -fsanitize=address -fno-omit-frame-pointer
	SANITIZER_COMPILATION := -fsanitize=address -fno-omit-frame-pointer
	CXXOPTIONS += -c -g3 -DDEBUG -DSMS_TEST -DOAP_PATH=$(OAP_PATH) -DTMP_PATH=$(TMP_PATH) -D$(TYPES) -fPIC
	CXXOPTIONS += $(EXTRA_CXXOPTIONS) $(USER_CXXOPTIONS) # -include $(D_FILES)
	NVCCOPTIONS := -g -G -DDEBUG -DSMS_TEST -DOAP_PATH=$(OAP_PATH) -DTMP_PATH=$(TMP_PATH) -D$(TYPES)
	NVCCOPTIONS += $(EXTRA_NVCCOPTIONS) $(USER_NVCCOPTIONS)
endif

ifeq ($(MODE), Debug)
	SANITIZER_LINKING :=
	SANITIZER_COMPILATION :=
	CXXOPTIONS += -c -g3 -DDEBUG -DOAP_PATH=$(OAP_PATH) -DTMP_PATH=$(TMP_PATH) -D$(TYPES) -fPIC
	CXXOPTIONS += $(EXTRA_CXXOPTIONS) $(USER_CXXOPTIONS) # -include $(D_FILES)
	NVCCOPTIONS := -g -G -DDEBUG -DDOAP_PATH=$(OAP_PATH) -DTMP_PATH=$(TMP_PATH) -D$(TYPES)
	NVCCOPTIONS += $(EXTRA_NVCCOPTIONS) $(USER_NVCCOPTIONS)
endif

ifeq ($(MODE), Release)
	SANITIZER_LINKING :=
	SANITIZER_COMPILATION :=
	CXXOPTIONS += -c -O2 -DOAP_PATH=$(OAP_PATH) -DTMP_PATH=$(TMP_PATH) -D$(TYPES) -fPIC
	CXXOPTIONS += $(EXTRA_CXXOPTIONS) $(USER_CXXOPTIONS) # -include $(D_FILES)
	NVCCOPTIONS := -O2 -DOAP_PATH=$(OAP_PATH) -DTMP_PATH=$(TMP_PATH) -D$(TYPES)
	NVCCOPTIONS += $(EXTRA_NVCCOPTIONS) $(USER_NVCCOPTIONS)
endif
