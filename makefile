all: app.exe test.exe
app.exe: main.o str_processing.o
	gcc -o app.exe main.o str_processing.o

app.out: main.o str_processing.o
	gcc -o app.out main.o str_processing.o

main.o: main.c exit_codes.h str_processing.c
	gcc -std=c99 -Wall -Werror -c -pedantic main.c -lm

test.exe: test.c
	gcc -o test.exe test.c

clean:
	rm *.o*.exe
