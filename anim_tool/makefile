all:anim_tool_exe

clean:
	rm anim_tool *.o ../*.o 

run:
	./anim_tool -i ../example/assets/font1.png -cx 16 -cy 4 -t 0.5


CC=clang++

WARNINGS=-Wall -Wno-deprecated-declarations

INCLUDES=\
  -I..

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++2a -DMACOSX

LDFLAGS=-framework OpenGL -framework GLUT

SOURCES=anim_tool.cpp \
../font.cpp \
../image_8.cpp \
../lodepng.cpp \
../palette.cpp \
../render_image_opengl.cpp \
../sprite.cpp \
../sprite_sheet.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=anim_tool

anim_tool_exe: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

