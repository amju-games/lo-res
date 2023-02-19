all:rotate_helper_exe

clean:
	rm rotate_helper_exe *.o ../*.o 

run:
	./rotate_helper_exe  -m rock_outline_2.png -cx 4 -cy 4 
	#./rotate_helper_exe  -m rock_0.png -cx 4 -cy 4 
	#./rotate_helper_exe  -m rock_outline_0.png -cx 4 -cy 4
	#./rotate_helper_exe -n rock_normal_0.png -m rock_0.png -cx 4 -cy 4
	#./rotate_helper_exe -n rock_normal_1.png -m rock_1.png -cx 4 -cy 4
	#./rotate_helper_exe -n rock_normal_2.png -m rock_2.png -cx 4 -cy 4


CC=clang++ 

WARNINGS=-Wall -Wno-deprecated-declarations

INCLUDES=\
  -I..\
  -I../third_party

CFLAGS=-c $(WARNINGS) $(INCLUDES) -std=c++2a -DMACOSX -g -O0

LDFLAGS=-framework OpenGL -framework GLUT

SOURCES=rotate_helper.cpp \
../image_32.cpp \
../image_uv_xform.cpp \
../third_party/lodepng.cpp

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=rotate_helper_exe

rotate_helper_exe: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

