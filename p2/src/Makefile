TEST=../tests/input010.txt,../tests/input020.txt,../tests/input030.txt,../tests/input040.txt,../tests/input050.txt,../tests/input060.txt,../tests/input070.txt,../tests/input080.txt,../tests/input090.txt,../tests/input100.txt

make:
	g++ -std=c++11 -O3 -Wall kruskal.cpp -lm -g -o proj2

clean:
	rm -f proj2

tests:
	hyperfine --export-json ../report/data.json --warmup 1 --runs 100 --parameter-list TEST $(TEST) './proj2 < {TEST}'

exec:
	./proj2

run:
	clean make exec