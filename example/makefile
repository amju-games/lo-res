all:lores_example_exe

clean:
	rm lores_example *.o ../*.o 

run:
	./lores_example


CC=clang++

WARNINGS=-Wall -Wno-deprecated-declarations

INCLUDES=\
  -I..

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++11   -DMACOSX

LDFLAGS=-framework OpenGL -framework GLUT

SOURCES=main.cpp \
../image.cpp \
../lodepng.cpp \
../palette.cpp \
../screen.cpp \
../sprite.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lores_example

lores_example_exe: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

