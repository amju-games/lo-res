all:anim_tool_exe

clean:
	rm animtool *.o ../*.o 

run:
	./animtool -i walk-2.png -cx 8 -cy 1 -t 0.4


CC=clang++

WARNINGS=-Wall -Wno-deprecated-declarations

INCLUDES=\
  -I..\
  -I../third_party

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++2a -DMACOSX

LDFLAGS=-framework OpenGL -framework GLUT

SOURCES=anim_tool.cpp \
../image_8.cpp \
../image_32.cpp \
../palette.cpp \
../render_image_opengl.cpp \
../sprite.cpp \
../third_party/lodepng.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=animtool

anim_tool_exe: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

