
OBJECTS=main.o \
	plyfile.o

DEFINES=
CXXFLAGS=-g -m64 -Wno-deprecated $(DEFINES) -I/usr/X11R6/include -I/usr/local/include

LIBS=/usr/local/lib64/libglui.a -L/usr/X11R6/lib64 -lglut -lGLU -lGL -lstdc++ -lXmu -lXi

all: project2

clean:
	rm $(OBJECTS)
	rm project2

project2: $(OBJECTS)
	g++ -o project2 $(OBJECTS) $(LIBS)

.SUFFIXES: .cpp

%.o : %.ccp
	g++ -c $(CXXFLAGS) -o $@ $<
