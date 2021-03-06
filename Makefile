CC = g++
CFLAGS = -g -Wall -std=c++11
CPPFLAGS = -lsfml-window -lsfml-system -lsfml-graphics

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=obj/.o)

SRCDIR   = src
OBJDIR   = obj

all : Monopoly

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
#INCLUDES := $(wildcard $(SRCDIR)/*.hpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

#main.o: main.cpp app.hpp
Monopoly : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o Monopoly $(CPPFLAGS)

.PHONY: clean
clean:
	rm -f Monopoly $(OBJECTS)
