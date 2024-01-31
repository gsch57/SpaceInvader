# Compiler
CC      = clang++

# Compiler flags
CXXFLAGS = -g -Wall -std=c++11

# Linker flags
LDFLAGS = -lncurses

# Directories
SRCDIR  = src
INCDIR  = includes
OBJDIR  = obj
BINDIR  = bin

# Target executable name
TARGET  = spaceInvader

# Source files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.hpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Main source file
MAIN_SRC := main.cpp

# Main object file
MAIN_OBJ := $(OBJDIR)/main.o

# Remove command
RM      = rm -f

# Build target
$(BINDIR)/$(TARGET): $(OBJECTS) $(MAIN_OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile main source file
$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Compile sources
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Clean objects
clean:
	$(RM) $(OBJECTS) $(MAIN_OBJ)

# Clean all
fclean: clean
	$(RM) $(BINDIR)/$(TARGET)

# Rebuild
re: fclean all

# PHONY targets
.PHONY: all clean fclean re
