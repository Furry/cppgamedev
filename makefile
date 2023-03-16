# Makefile for SFML project with GCC compiler for Windows and Linux

# Project directories
SRCDIR = src
BUILDDIR = build
STATICDIR = static

# OS detection
ifeq ($(OS),Windows_NT)
	EXE_EXT = .exe
	RM = del /Q /F
	RMDIR = rmdir /Q /S
	MKDIR = mkdir
	CP = xcopy /E /Y /I
	INCLUDE_DIRS = -I/path/to/windows/include
	LIB_DIRS = -L/path/to/windows/libs
else
	EXE_EXT =
	RM = rm -f
	RMDIR = rm -rf
	MKDIR = mkdir -p
	CP = cp -r
	INCLUDE_DIRS = -I/path/to/linux/include
	LIB_DIRS = -L/path/to/linux/libs
endif

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g $(INCLUDE_DIRS)
LDFLAGS = $(LIB_DIRS) -lsfml-graphics -lsfml-window -lsfml-system

# Source and target files
SRC = $(wildcard $(SRCDIR)/**/*.cpp $(SRCDIR)/*.cpp)
OBJ = $(SRC:%.cpp=$(BUILDDIR)/%.o)
TARGET = $(BUILDDIR)/MySFMLApp$(EXE_EXT)

.PHONY: all clean run

all: clean $(TARGET)

$(TARGET): $(OBJ)
	@$(MKDIR) $(dir $@)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@$(CP) ./$(STATICDIR) $(BUILDDIR)

$(BUILDDIR)/%.o: %.cpp
	@$(MKDIR) $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	@$(RMDIR) $(BUILDDIR)
