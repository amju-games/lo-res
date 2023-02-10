all:lores_tests_exe

clean:
	rm lores_tests *.o ../*.o 

run:
	./lores_tests


CC=clang++

WARNINGS=-Wall -Wno-deprecated-declarations

INCLUDES=\
  -I..\
  -I../third_party

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++2a -DUNIT_TEST -DMACOSX -O0 -g

LDFLAGS=-framework OpenGL -framework GLUT

SOURCES=\
blit_region_tests.cpp \
blit_tests.cpp \
catch_test_main.cpp \
colour_to_normal_tests.cpp \
filler_tests.cpp \
image_lighting_tests.cpp \
image_region_tests.cpp \
image_uv_xform_tests.cpp \
pixel_intersect_tests.cpp \
../image_8.cpp \
../image_32.cpp \
../image_uv_xform.cpp \
../third_party/lodepng.cpp \
../palette.cpp \
../sprite.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lores_tests

lores_tests_exe: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

