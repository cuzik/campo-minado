CC=gcc
override CFLAGS+= `pkg-config --libs --cflags raylib` -lraylib -framework OpenGL -framework OpenAL -framework Cocoa -fno-omit-frame-pointer
override CFLAGSL+= -Wno-write-strings -O3

SOURCES=\
	main.c\
	core/game.c\
	draw/drawer.c

EXECUTABLE= hocus_pocus

all:
	$(CC) $(SOURCES) $(CFLAGSL) $(CFLAGS) -o $(EXECUTABLE)

.PHONY: clean
clean:
	$(RM) $(EXECUTABLE)
