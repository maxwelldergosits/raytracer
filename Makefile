.PHONY=clean
CPP=clang++
SRC=src/
OBJ=obj/
BIN=bin/
TEST=test
TEST_BIN=test_bin
DIR=$(shell pwd)/include
SOURCES=$(addprefix $(SRC), triangle.cpp util.cpp sphere.cpp)
OBJECTS := $(patsubst $(SRC)%.cpp, $(OBJ)%.o, $(SOURCES))
CPP_FLAGS= -I$(DIR) -Wall -Wno-unused-function -g -std=c++11 -stdlib=libc++ -I/opt/local/include/opencv -I/opt/local/include
MAIN=ray-tracer
LD_FLAGS=\
-L/opt/local/lib -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core -lopencv_hal
EXEC=$(BIN)$(MAIN)
MAIN_SRC=$(SRC)$(MAIN).cpp
TEST_FLAGS=-lgtest_main -lgtest -lpthread
UNAME := $(shell uname)

TEST_SRCS=$(wildcard $(TEST)/*.cpp)
TESTS := $(patsubst $(TEST)/%.cpp, $(TEST_BIN)/%, $(TEST_SRCS))

all: $(SOURCES) $(EXEC)
test: $(TESTS) run_tests

run_tests:
	$(foreach x,$(TESTS),./$(x);)

$(OBJECTS): obj/%.o: src/%.cpp
	$(CPP) $(CPP_FLAGS) -c $< -o $@

$(TESTS): $(TEST_BIN)/%: $(TEST)/%.cpp $(OBJECTS)
	$(CPP) $(CPP_FLAGS) $(OBJECTS) $< -o $@ $(TEST_FLAGS) $(LD_FLAGS)

$(EXEC): $(MAIN_SRC) $(OBJECTS)
	$(CPP) $(CPP_FLAGS) $(OBJECTS) $< -o $@ $(LD_FLAGS)


clean:
	rm -f $(OBJECTS)
	rm -rf $(TEST_BIN)/*

