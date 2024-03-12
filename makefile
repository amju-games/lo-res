# lores - minimal graphics library for lo res games
# Copyright (C) 2024 Juliet Colman 

# Source files directory
SRCDIR := source
# Thirdparty source dir
THIRD_DIR := source/third_party
TESTDIR := unit_tests
BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj
OBJTHDIR := $(OBJDIR)/third_party
DEPDIR := $(BUILDDIR)/dep

# Target executable name
TARGET := $(BUILDDIR)/liblores.a
TEST_EXE := lores_tests_exe
TEST_TARGET := $(TESTDIR)/$(TEST_EXE)

# Include dir for unit tests
TESTS_INCLUDE := -I$(SRCDIR)

# Third party includes
TH_INCLUDE := -I$(THIRD_DIR)

# Flags for compiling
CXXFLAGS := -std=c++20 -Wall $(TH_INCLUDE) $(TESTS_INCLUDE)

# Source files
SRCS := $(wildcard $(SRCDIR)/*.cpp)
THIRD_PARTY_SRCS := $(wildcard $(SRCDIR)/third_party/*.cpp)
TEST_SRCS := $(wildcard $(TESTDIR)/*.cpp)

# Object files
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
THIRD_PARTY_OBJS := $(patsubst $(SRCDIR)/third_party/%.cpp,$(OBJDIR)/%.o,$(THIRD_PARTY_SRCS))
TEST_OBJS := $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(TEST_SRCS))

# Dependencies
DEPS := $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)


# Platform detection
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin) # macOS
    # Add Mac-specific flags or configurations if needed
    LDFLAGS=-framework Carbon -framework OpenGL -framework GLUT
    CXXFLAGS += -DMACOSX -DGL_SILENCE_DEPRECATION
    CXX := clang++
else ifeq ($(OS), Windows_NT) # Windows
    # Add Windows-specific flags or configurations if needed
else ifneq ("$(wildcard /proc/device-tree/model)","") # Raspberry Pi
    # Add Raspberry Pi-specific flags or configurations if needed
    CXXFLAGS += -DRASPBERRY_PI
    CXX := g++
endif

# Default rule
all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJS) $(THIRD_PARTY_OBJS)
	ar rcs $@ $^

$(TEST_TARGET): $(TEST_OBJS) $(THIRD_PARTY_OBJS) $(filter-out $(OBJDIR)/main.o,$(OBJS))
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR) $(DEPDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/third_party/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp | $(OBJDIR) $(DEPDIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c -o $@ $<

$(OBJDIR) $(DEPDIR):
	mkdir -p $@

clean:
	@rm -rf $(TARGET) $(TEST_TARGET) $(BUILDDIR)

runtests:
	cd $(TESTDIR); ./$(TEST_EXE); cd ..

-include $(DEPS)

.PHONY: all clean

