CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic

main.exe: functions.o main.o
	$(CC) -o $@ $^

main.o: main.c functions.h
	$(CC) $(CFLAGS) -c $<

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o *.exe
