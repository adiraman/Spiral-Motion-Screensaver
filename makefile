CC = gcc
CXX = g++
CFLAGS = -I/usr/include/SDL2/ -I./include/ -Wall -pedantic
LDFLAGS = -lSDL2 -lSDL2_mixer

SRCDIRS = ./src
BUILDDIR = ./obj
TARGETDIR = ./exec
SRCEXT = C

SOURCES = $(shell find $(SRCDIRS) -type f -name *.$(SRCEXT))
#SOURCES = main.C screen.C
OBJECTS = $(patsubst $(SRCDIRS)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

EXECUTABLE = main
TARGET =$(TARGETDIR)/$(EXECUTABLE)
RM = rm -f

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJECTS): $(SOURCES)
	$(CXX) $(CFLAGS) -c $^
	mv *.o $(BUILDDIR)/

clean:
	$(RM) $(OBJECTS)

realclean:
	$(RM) $(TARGET) $(OBJECTS) *.out *.o
