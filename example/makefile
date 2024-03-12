# lores - minimal graphics library for lo res games
# Copyright (C) 2024 Juliet Colman 

# Source files directory
SRCDIR := source
BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj
DEPDIR := $(BUILDDIR)/dep

# Example exe
EXE := lores_example_exe
TARGET := $(BUILDDIR)/$(EXE)

# Include dir 
INCLUDE := -I../source -I../source/third_party

# Flags for compiling
CXXFLAGS := -std=c++20 -Wall $(INCLUDE)

# Source files
SRCS := $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Dependencies
DEPS := $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)

# Platform detection
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin) # macOS
    # Add Mac-specific flags or configurations if needed
    LDFLAGS=-framework Carbon -framework OpenGL -framework GLUT ../build/liblores.a
    CXXFLAGS += -DMACOSX -DGL_SILENCE_DEPRECATION -DLO_RES_USE_OPENGL
    CXX := clang++
else ifeq ($(OS), Windows_NT) # Windows
    # Add Windows-specific flags or configurations if needed
else ifneq ("$(wildcard /proc/device-tree/model)","") # Raspberry Pi
    # Add Raspberry Pi-specific flags or configurations if needed
    LDFLAGS=-L../build -llores
    CXXFLAGS += -DRASPBERRY_PI -DLO_RES_USE_FRAMEBUFFER
    CXX := g++
endif

# Default rule
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR) $(DEPDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c -o $@ $<

$(OBJDIR) $(DEPDIR):
	mkdir -p $@

clean:
	@rm -rf $(TARGET) $(BUILDDIR)

run:
	./$(TARGET)

-include $(DEPS)

.PHONY: all clean

