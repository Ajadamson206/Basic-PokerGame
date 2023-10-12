CC=gcc

WD=src/

Poker: $(WD)*.c $(WD)*.h
	$(CC) $(WD)*.c -o Poker -lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl

clean:
	rm -f Poker