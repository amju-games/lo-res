all:rotate_helper_exe

clean:
	rm rotate_helper *.o ../*.o 

run:
	./rotate_helper -n sphere_normal_map_32.png -cx 4 -cy 4


CC=clang++

WARNINGS=-Wall -Wno-deprecated-declarations

INCLUDES=\
  -I..\
  -I../third_party

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++2a -DMACOSX

LDFLAGS=-framework OpenGL -framework GLUT

SOURCES=rotate_helper.cpp \
../image_32.cpp \
../image_uv_xform.cpp \
../third_party/lodepng.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=rotate_helper

rotate_helper_exe: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

