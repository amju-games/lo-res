all:lores_example_exe

clean:
	rm lores_example *.o ../*.o 

run:
	./lores_example


CC=clang++

WARNINGS=-Wall -Wno-deprecated-declarations

INCLUDES=\
  -I..

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++2a -DMACOSX -O0 -g

LDFLAGS=-framework OpenGL -framework GLUT

SOURCES=main.cpp \
../blit.cpp \
../font.cpp \
../image_8.cpp \
../image_32.cpp \
../image_scale.cpp \
../lodepng.cpp \
../palette.cpp \
../render_image_opengl.cpp \
../sprite.cpp \
../sprite_sheet.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lores_example

lores_example_exe: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

