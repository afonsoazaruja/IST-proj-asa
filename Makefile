CFLAGS = -O3 -std=c++11 -Wall

program:
	g++ $(CFLAGS) proj1.cpp -lm -o program

clean:
	rm -f program

run:
	./program