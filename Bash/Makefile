# Purpose of this script is to allow easy compiling of a C++ project.

# Source directories (.cpp files)
# If there are multiple dictories, separate by spaces
SRCDIR   	= 
# Directory where object files will be placed (.o files)
OBJDIR   	= 
# Compiled target name (executable)
TARGET   	= 
# Error Log
ERRLOG 		= error.log

# Retrive list of the source files
SRCS      = $(wildcard $(addsuffix *.cpp,$(SRCDIR)))
# Generate list of the object files
OBJS      = $(addprefix $(OBJDIR), $(patsubst %.cpp, %.o, $(notdir $(SRCS))))

VPATH    = $(SRCDIR)
# Compiler
CXX      = g++
# Compilation flags
CXXFLAGS = -g -Wall -MMD

# executable
$(TARGET): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# object files; @ makes it so that the commands aren't displayed in the console
$(OBJDIR)%.o: %.cpp
	@mkdir -p $(OBJDIR)
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJDIR)* $(TARGET) $(ERRLOG)
