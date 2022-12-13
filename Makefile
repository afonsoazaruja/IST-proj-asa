CFLAGS = -O3 -std=c++11 -Wall -g

program:
	g++ $(CFLAGS) proj1.cpp -lm -o program

1:
	g++ $(CFLAGS) projOriginal.cpp -lm -o program

clean:
	rm -f program program1

exec:
	./program

run: clean program exec

new: clean 1 exec
