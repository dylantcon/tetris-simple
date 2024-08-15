# Makefile for building the Tetris game using SDL

# Compiler to use
CXX = g++
# Flags for compilation - Include SDL header directory
CXXFLAGS = -Wall -g -I/usr/include/SDL
# Libraries to link - Specify SDL and SDL_gfx libraries
LDFLAGS = -lSDL -lSDL_gfx

# Executable name
EXEC = connolly-tetris-simple
# Source files
SOURCES = main.cpp game.cpp board.cpp io.cpp pieces.cpp
# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Clean up
clean:
	rm -f $(OBJECTS) $(EXEC)

# Rebuild everything
rebuild: clean all

# For debugging makefile
print-%:
	@echo '$*=$($*)'
