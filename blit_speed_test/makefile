all:blit_speed_test_exe

clean:
	rm blit_speed_test *.o ../*.o 

run:
	./blit_speed_test


CC=clang++

WARNINGS=-Wall -Wno-deprecated-declarations

INCLUDES=\
  -I..\
  -I../third_party

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++2a -DALGEBRA3IOSTREAMS -DMACOSX -O2 

LDFLAGS=

SOURCES=main.cpp \
../image_32.cpp \
../third_party/lodepng.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=blit_speed_test

blit_speed_test_exe: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

