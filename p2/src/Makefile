TEST=../tests/input10.txt,../tests/input20.txt,../tests/input30.txt,../tests/input40.txt,../tests/input50.txt,../tests/input60.txt,../tests/input70.txt,../tests/input80.txt,../tests/input90.txt,../tests/input100.txt

make:
	g++ -std=c++11 -O3 -Wall kruskal.cpp -lm -g -o proj2

clean:
	rm -f proj2

tests:
	hyperfine --export-json data.json --runs 100 --parameter-list TEST $(TEST) './proj2 < {TEST}'

exec:
	./proj2

run:
	clean make exec