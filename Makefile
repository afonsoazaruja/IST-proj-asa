CFLAGS = -O3 -std=c++11 -Wall -g
TEST = tests/teste6x6.txt,tests/teste07x07.txt,tests/teste08x08.txt,tests/teste09x09.txt,tests/teste10x10.txt,tests/teste11x11.txt,tests/teste12x12.txt,tests/teste13x13.txt,tests/teste14x14.txt,tests/teste15x15.txt

program:
	g++ $(CFLAGS) new.cpp -lm -o program

clean:
	rm -f program

exec:
	./program

run: clean program exec

test:
	hyperfine --export-markdown data.md --runs 10 --warmup 2 --parameter-list TEST $(TEST) './program < {TEST}'