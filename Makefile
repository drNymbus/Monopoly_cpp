CC = g++
CFLAGS = -g -Wall -std=c++11

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=obj/.o)

SRCDIR   = src
OBJDIR   = obj

all : Monopoly

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.hpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

Monopoly : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o Monopoly

.PHONY: clean
clean:
	rm -f Monopoly $(OBJECTS)
