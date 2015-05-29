CSRCS=GeometryTest.cpp texturedGeometry.cpp

CFLAGS = -g -c -O2 -DLINUX

INCLUDE = -I. -I/usr/include/ -I/usr/include/X11/ -I/usr/local/include/GL 
#INCOSG = -I/usr/local/OSG/OSG2.0/OpenSceneGraph/include
INCOSG = -I/usr/include/osg
LDLIBS = -lm -ldl -lGL -lGLU -lpthread -lXext -lX11 -lstdc++ -lOpenThreads

LDFLAGS =  -L. -L/usr/lib -L/usr/X11R6/lib # -L/usr/local/lib
#LDOSG = -L/usr/local/OSG/OSG2.0/OpenSceneGraph/lib -losg -losgViewer -losgSim
LDOSG = -L/usr/lib/osgPlugins-2.8.2 -losg -losgViewer -losgSim -losgGA -losgDB
COBJS=$(patsubst %.cpp,%.o,$(CSRCS))
EXE=$(patsubst %.cpp,%,$(CSRCS))

CC = g++

all: $(EXE)

GeometryTest: GeometryTest.o
	cc -o GeometryTest GeometryTest.o $(INCLUDE) $(INCOSG) $(LDFLAGS) $(LDLIBS) $(LDOSG)

texturedGeometry: texturedGeometry.o
	cc -o texturedGeometry texturedGeometry.o $(INCLUDE) $(INCOSG) $(LDFLAGS) $(LDLIBS) $(LDOSG)

$(COBJS): %.o : %.cpp 
	$(CC) $(CFLAGS) -o $@ $< 


