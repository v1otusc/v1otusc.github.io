#path.txt Real path generated from result
#matrix.txt Complete Matrix
#graph.txt Graph for generating a complete matrix
#pseudo_path.txt Pseudo path generated from TSP Algorithm

help:
	@echo "make matrix (generate virtual edges)"
	@echo "make path (reconstruct the path)"

tsp.out : main.cpp
	@g++ main.cpp -o tsp.out -std=c++11 -O3

matrix : tsp.out
	./tsp.out matrix < graph.txt > matrix.txt

path : tsp.out
	cat graph.txt pseudo_path.txt | ./tsp.out path  > path.txt

clean:
	rm -f matrix.txt *.out