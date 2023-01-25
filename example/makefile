all:lores_example_exe

clean:
	rm lores_example *.o ../*.o 

run:
	./lores_example


CC=clang++

WARNINGS=-Wall -Wno-deprecated-declarations

INCLUDES=\
  -I..\
  -I../third_party

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++2a -DMACOSX -O0 -g

LDFLAGS=-framework OpenGL -framework GLUT

SOURCES=main.cpp \
../font.cpp \
../image_8.cpp \
../image_32.cpp \
../image_filter.cpp \
../image_colour_xform.cpp \
../image_uv_xform.cpp \
../third_party/lodepng.cpp \
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

