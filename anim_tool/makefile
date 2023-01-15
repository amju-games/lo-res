all:anim_tool_exe

clean:
	rm animtool *.o ../*.o 

run:
	./animtool -i walk-r-4.png -cx 4 -cy 1 -t 0.3


CC=clang++

WARNINGS=-Wall -Wno-deprecated-declarations

INCLUDES=\
  -I..

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++2a -DMACOSX

LDFLAGS=-framework OpenGL -framework GLUT

SOURCES=anim_tool.cpp \
../blit.cpp \
../font.cpp \
../image_8.cpp \
../lodepng.cpp \
../palette.cpp \
../render_image_opengl.cpp \
../sprite.cpp \
../sprite_sheet.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=animtool

anim_tool_exe: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

