# lores - minimal graphics library for lo res games
# Copyright (C) 2024 Juliet Colman 

# Source files directory
SRCDIR := source
INCDIR := include
# Thirdparty source dir
THIRD_PARTY_SRCDIR := source/third_party
TESTDIR := unit_tests
BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj
DEPDIR := $(BUILDDIR)/dep

# Target library name
TARGET := $(BUILDDIR)/liblores.a
# Unit test exe
TEST_EXE := lores_tests_exe
TEST_TARGET := $(BUILDDIR)/$(TEST_EXE)

# Include dir for unit tests
TESTS_INCLUDE := -I$(SRCDIR)

# Third party includes
THIRD_PARTY_INCLUDE := -I$(THIRD_PARTY_SRCDIR)

# Flags for compiling
CXXFLAGS := -std=c++20 -Wall -I$(INCDIR) $(THIRD_PARTY_INCLUDE) $(TESTS_INCLUDE)

# Source files
SRCS := $(wildcard $(SRCDIR)/*.cpp)
THIRD_PARTY_SRCS := $(wildcard $(THIRD_PARTY_SRCDIR)/*.cpp)
TEST_SRCS := $(wildcard $(TESTDIR)/*.cpp)

# Object files
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
THIRD_PARTY_OBJS := $(patsubst $(THIRD_PARTY_SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(THIRD_PARTY_SRCS))
TEST_OBJS := $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(TEST_SRCS))

# Dependencies
DEPS := $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)


# Platform detection
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin) # macOS
    # Add Mac-specific flags or configurations if needed
    LDFLAGS=-framework Carbon -framework OpenGL -framework GLUT
    CXXFLAGS += -DMACOSX -DGL_SILENCE_DEPRECATION -DLO_RES_USE_OPENGL
    CXX := clang++
else ifeq ($(OS), Windows_NT) # Windows
    # Add Windows-specific flags or configurations if needed
else ifneq ("$(wildcard /proc/device-tree/model)","") # Raspberry Pi
    # Add Raspberry Pi-specific flags or configurations if needed
    CXXFLAGS += -DRASPBERRY_PI -DLO_RES_USE_FRAMEBUFFER
    CXX := g++
endif

# Default rule
all: $(TARGET) $(TEST_TARGET)

tests: $(TEST_TARGET)

$(TARGET): $(OBJS) $(THIRD_PARTY_OBJS)
	ar rcs $@ $^

$(TEST_TARGET): $(TEST_OBJS) $(THIRD_PARTY_OBJS) $(filter-out $(OBJDIR)/main.o,$(OBJS))
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $^


# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR) $(DEPDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c -o $@ $<

$(OBJDIR)/%.o: $(THIRD_PARTY_SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp | $(OBJDIR) $(DEPDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c -o $@ $<

$(OBJDIR) $(DEPDIR):
	mkdir -p $@

clean:
	@rm -rf $(TARGET) $(TEST_TARGET) $(BUILDDIR)

runtests:
	cd $(BUILDDIR); ./$(TEST_EXE); cd ..

-include $(DEPS)

.PHONY: all clean

