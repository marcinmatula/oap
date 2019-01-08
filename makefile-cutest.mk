include ../makefile-core.mk

OAP_LIBS_PATHS_TEMP = $(shell ls $(OAP_PATH)/dist/$(MODE)/$(PLATFORM)/lib/)
OAP_LIBS_PATHS = $(addprefix $(OAP_PATH)/dist/$(MODE)/$(PLATFORM)/lib/, $(OAP_LIBS_PATHS_TEMP))

dist/$(MODE)/$(PLATFORM)/$(TARGET) : $(OCPP_FILES)
	mkdir -p dist/$(MODE)/$(PLATFORM)/bin/
	$(CXX) -c $(SANITIZER_COMPILATION) $(CXXOPTIONS) -isystem ${GTEST_DIR}/include -I${GTEST_DIR} -pthread ${GTEST_DIR}/src/gtest-all.cc
	$(CXX) -c $(SANITIZER_COMPILATION) $(CXXOPTIONS) -isystem ${GTEST_DIR}/include -I${GTEST_DIR} -pthread ${GTEST_DIR}/src/gtest_main.cc
	$(CXX) -c $(SANITIZER_COMPILATION) $(CXXOPTIONS) -isystem ${OAP_GMOCK_PATH}/include -I${OAP_GMOCK_PATH} -I${GTEST_DIR}/include -pthread -c ${OAP_GMOCK_PATH}/src/gmock-all.cc
	ar -rv libgmock.a gmock-all.o
	ar -rv libgtest.a gtest-all.o gtest_main.o
	$(CXX) $(SANITIZER_LINKING) $(OCPP_FILES) -L/usr/lib -L/usr/local/lib -ldl $(OAP_LIBS_PATHS) $(LIBS_DIRS) $(LIBS) libgtest.a libgmock.a -lpthread -o $@
	cp $@ $(OAP_PATH)/dist/$(MODE)/$(PLATFORM)/bin/
build/$(MODE)/$(PLATFORM)/%.o : %.cpp
	mkdir -p build/$(MODE)/$(PLATFORM)/
	$(CXX) $(SANITIZER_LINKING) $(CXXOPTIONS) -I $(GTEST_DIR)/include -I $(OAP_GMOCK_PATH)/include $(INCLUDE_DIRS) $< -o $@
clean:
	rm -rf dist/$(MODE)/$(PLATFORM)/*
	rm -rf build/$(MODE)/$(PLATFORM)/*
	rm -f libgtest.a
	rm -f libgmock.a
