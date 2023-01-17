all:lores_tests_exe

clean:
	rm lores_tests *.o ../*.o 

run:
	./lores_tests


CC=clang++

WARNINGS=-Wall -Wno-deprecated-declarations

INCLUDES=\
  -I..

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++2a -DMACOSX -O0 -g

LDFLAGS=-framework OpenGL -framework GLUT

SOURCES=blit_region_tests.cpp \
blit_tests.cpp \
catch_test_main.cpp \
pixel_intersect_tests.cpp \
../blit.cpp \
../image_8.cpp \
../lodepng.cpp \
../palette.cpp \
../sprite.cpp \
../sprite_sheet.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lores_tests

lores_tests_exe: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

