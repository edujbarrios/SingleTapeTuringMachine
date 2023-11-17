# Compiler and linker options
CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++11
LDFLAGS =

# Source files
SRCS = main.cc turing_machine.cc tape.cc

# Object files directory
OBJDIR = objects

# Object files
OBJS = $(SRCS:.cc=.o)
OBJS := $(addprefix $(OBJDIR)/,$(OBJS))

# Executable file
EXEC = tm_simulator

# Targets
all: $(OBJDIR) $(EXEC)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
