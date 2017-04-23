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
MKDIR_P = mkdir -p

all: directories $(TARGET)

directories: $(TARGETDIR)

$(TARGETDIR):
	$(MKDIR_P) $(TARGETDIR)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJECTS): $(SOURCES)
	$(CXX) $(CFLAGS) -c $^
	$(MKDIR_P) $(BUILDDIR)
	mv *.o $(BUILDDIR)/

clean:
	$(RM) $(OBJECTS)

realclean:
	$(RM) $(TARGET) $(OBJECTS) *.out *.o
