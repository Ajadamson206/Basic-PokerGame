CC=g++

WD=src/

Poker: $(WD)*
	$(CC) $(WD)main.cpp src/gl.c -o Poker -lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl -lfreetype

debug: $(WD)*.c $(WD)*.h
	$(CC) $(WD)*.c -o Poker -lGL -lglfw -lX11 -lpthread -lXrandr -lXi -ldl -DDEBUG -g --no-pie


clean:
	rm -f Poker