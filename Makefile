.PHONY:clean
CC=clang++

CV_CPPFLAGS=-I/opt/local/include/opencv -I/opt/local/include
CV_LDFLAGS=-L/opt/local/lib -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core -lopencv_hal

CCFLAGS= -std=c++11 $(CV_CPPFLAGS)

LDFLAGS=$(CV_LDFLAGS)

default: ray-tracer

ray-tracer.o: ray-tracer.cpp ray-tracer.h
	$(CC) -c ray-tracer.cpp -o ray-tracer.o $(CCFLAGS)

ray-tracer: ray-tracer.o
	$(CC) $(LDFLAGS) ray-tracer.o -o ray-tracer $(MAGIK_CCFLAGS)

test-util:
	$(CC) -c test-util.cpp -o test-util.o $(CCFLAGS)
	$(CC) $(LDFLAGS) test-util.o -o test $(MAGIK_CCFLAGS)

clean:
	rm -f ray-tracer.o
	rm -f test-util.o
	rm -f ray-tracer
	rm -f test
