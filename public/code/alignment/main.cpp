#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <list>
#include "time.hpp"

#define N 1000000
#define R 7

using namespace std;

struct block {
	int64_t bytes8[M];
};

int main() {
	struct block * ar[R];
	int times[R] = {0};
	int sum = 0;
	list<int64_t> l;
	
	Time t;
	t.start();

	//Trying to clean a part of the cache
	for (int i = 0; i < 1000000; ++i)
		l.push_back(i);

	for (int i = 0; i < R; ++i)
		ar[i] = (struct block *) aligned_alloc(pow(2,i+1),sizeof(struct block)*N);


	for (int i = 0; i < R; ++i) {
		t.set();
		
		for (int j = 0; j < N; j += 100)
			//Load all the block
			for (int k = 0; k < M; ++k)
				sum += ar[i][j].bytes8[k];

		t.set();
		times[i] += t.lastDiff();
		free(ar[i]);
	}

	for (int i = 0; i < R; ++i)
		cout << times[i] << " ";
	
	cout << endl;

	//To avoid unwanted compiling optimization
	return sum + l.back();
}