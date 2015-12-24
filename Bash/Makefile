# Purpose of this script is to allow easy compiling of a C++ project.

# Source directories separated by space
SRCDIR   = ./ src/

# Directory where object files will be placed
OBJDIR   = obj/

# Include directories separated by space
INCDIR   = include/

# Directory where binary file will be placed
BINDIR   = bin/

# Name of the result file
TARGET   = app

# Retrive list of the source files
SRC      = $(wildcard $(addsuffix *.cpp,$(SRCDIR)))

# Generate list of the object files
OBJ      = $(addprefix $(OBJDIR), $(patsubst %.cpp, %.o, $(notdir $(SRC))))

VPATH    = $(SRCDIR)

# Compiler
CXX      = g++

# Compilation flags
CXXFLAGS = -g -Wall -MMD

$(TARGET): $(OBJ)
	@echo Linking object files...
	@mkdir -p $(BINDIR)
	@$(CXX) $(CXXFLAGS) -o $(BINDIR)$@ $(OBJ)

$(OBJDIR)%.o: %.cpp
	@echo Compiling $< in $@...
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CXXFLAGS) $(addprefix -I,$(INCDIR)) -c -o $@ $<

.PHONY: clean

clean:
	@$(RM) -r $(OBJDIR)
	@$(RM) -r $(BINDIR)
