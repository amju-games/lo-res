all:anim_tool_exe

clean:
	rm animtool *.o ../*.o 

run:
	./animtool -i player_walk_1.png -cx 8 -cy 1 -t 0.15
	#./animtool -i ../rotate_helper/output.png -cx 4 -cy 4 -t 0.1


CC=clang++

WARNINGS=-Wall -Wno-deprecated-declarations

INCLUDES=\
  -I../include\
  -I../source/third_party

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++2a -DMACOSX

LDFLAGS=-framework OpenGL -framework GLUT

SRCDIR=../source
SOURCES=anim_tool.cpp \
$(SRCDIR)/image_8.cpp \
$(SRCDIR)/image_32.cpp \
$(SRCDIR)/palette.cpp \
$(SRCDIR)/render_image_opengl.cpp \
$(SRCDIR)/sprite.cpp \
$(SRCDIR)/third_party/lodepng.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=animtool

anim_tool_exe: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

