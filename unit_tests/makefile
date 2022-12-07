all:lores_tests_exe

clean:
	rm lores_tests *.o ../*.o geom/*.o ../geom/*.o ../macosx/*.o utils/*.o ../md3/*.o

run:
	cp lores_tests ../../assets/; cd ../../assets/; ./lores_tests; cd -
# NB run tests from assets/ dir, so we can load assets within the tests


CC=clang++

WARNINGS=-Wall -Wno-deprecated-declarations

INCLUDES=\
  -I..

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++11   -DMACOSX

LDFLAGS=-framework OpenGL -framework GLUT

SOURCES=blit_region_tests.cpp \
blit_tests.cpp \
catch_test_main.cpp \
../image.cpp \
../lodepng.cpp \
../palette.cpp \
../screen.cpp \
../sprite.cpp \
../timer.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lores_tests

lores_tests_exe: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

