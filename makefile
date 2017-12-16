CC    = g++
LIBS  =
INCROOT	= .
INCDIRS = $(shell find $(INCROOT) -type d)
INCLUDES = $(foreach dir, $(INCDIRS), -I $(dir))
SRCROOT	= .
OBJROOT	= ./obj
SRCDIRS := $(shell find $(SRCROOT) -type d)
SOURCES = $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.cpp))
PROGRAM = statemate
OBJDIRS  = $(addprefix $(OBJROOT)/, $(SRCDIRS))
OBJS  = $(addprefix $(OBJROOT)/, $(SOURCES:.cpp=.o))

all:    $(PROGRAM)

$(PROGRAM):     $(OBJS)
	$(CC) $(LIBS) -o $(PROGRAM) $(OBJS) -g

$(OBJROOT)/%.o:  $(SRCROOT)/%.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CC) $(LIBS) -o $@ -c $< $(INCLUDES) -g

clean:; rm -rf $(OBJROOT)/* *~ $(PROGRAM);
