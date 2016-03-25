CC = g++

SOURCES = main.cpp vec4.cpp mat4.cpp
EXECUTABLE = main
OBJECTS = $(SOURCES: .cpp = .o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -lgtest -lpthread 
del:
	rm -f &(EXECUTABLE) *.o
