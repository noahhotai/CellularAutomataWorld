# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -I./SDL_include -g -Wall
LDFLAGS := -L/opt/homebrew/lib -lSDL2

# Source and output directories
SRCDIR := source
OBJDIR := build
TARGET := sdl_test

# Collect all .cpp files in the source directory
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Phony targets
.PHONY: all clean
