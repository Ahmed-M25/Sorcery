CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD
SRCDIR = src
INCDIR = include
OBJDIR = obj

SOURCES = $(shell find $(SRCDIR) -name "*.cc")
OBJECTS = $(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)
DEPENDS = $(OBJECTS:.o=.d)
EXEC = sorcery

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cc | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(EXEC)

-include $(DEPENDS)
