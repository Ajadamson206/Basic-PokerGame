CC=gcc

WD=src/

Poker: $(WD)*.c $(WD)*.h
	$(CC) $(WD)*.c -o Poker -lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl

debug: $(WD)*.c $(WD)*.h
	$(CC) $(WD)*.c -o Poker -lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl -DDEBUG -g --no-pie


clean:
	rm -f Poker