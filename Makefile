n64-emulator: main.o
	gcc main.o -o n64-emulator

main.o: main.c
	gcc main.c -c
