CC = gcc
MAIN = src/arduino_comms.c
INPUT = src/inputPrinter.c
NEWTTT = src/newtictactoe.c

# WINDOWS: use ~ mingw32-make [ command ]
# MAC/LINUS: use ~ make [command]

#OBJECTS 

# arduino_comms.o: arduino_comms.c 

#     $(CC) -c arduino_comms.c -o arduino_comms.o 


ifeq ($(OS), Windows_NT)
	DELETE = del
	EXT=.exe
else 
	UNAME_S:=$(shell uname -s)
	ifeq ($(UNAME_S), Darwin)
		DELETE = rm -f
		EXT=.out
	endif
endif

all: program

program:

	$(CC) -o bin/program$(EXT) $(MAIN) $(INPUT) $(NEWTTT) -lmosquitto

objects: arduino_comms.o inputPrinter.o newtictactoe.o

arduino_comms.o: $(MAIN)
	$(CC) -c $(MAIN) -o obj/arduino_comms.o
input.o: $(INPUT)
	$(CC) -c $(INPUT) -o obj/input.o
newtictactoe.o: $(NEWTTT)
	$(CC) -c $(NEWTTT) -o obj/newtictactoe.o

run: bin/program$(EXT)
	bin/program$(EXT)

objects: obj/

clean: 

	$(DELETE) bin\*$(EXT) obj\*o
