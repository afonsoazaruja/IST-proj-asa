CFLAGS = -O3 -std=c++11 -Wall

program:
	g++ $(CFLAGS) projOriginal.cpp -lm -o program

clean:
	rm -f program

exec:
	./program

run: clean program exec
