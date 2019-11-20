#include <iostream>
#include <list>
#include <vector>
#include <cstdint>
#include <cmath>

#include "time.hpp"

#define N 100000

using namespace std;

struct block {
	int32_t z[M];
};

typedef struct block type;

int main() {
	Time t;
	int t1 = 0;
	int t2 = 0;
	vector<type> v;
	list<type> l;

	t.start();
	for (int i = 0; i < N; ++i) {
		type r;
		v.push_back({r});
	}

	t.set();
	t1 = t.lastDiff();

	for (int i = 0; i < N; ++i) {
		type r;
		l.push_back({r});
	}

	t.set();
	t2 = t.lastDiff();

	#ifndef ANALYSIS
		cout << "Time" << endl;
		cout << "t1: " << t1 << " t2: " << t2 << endl;
		cout << "Memory" << endl;
		cout << "t1: " << v.capacity()*sizeof(type) << " t2: " << (16+sizeof(type))*N << endl;
	#else
		cout << sizeof(type) << " " << t1 << " " << t2 << " ";
		int aux = 8 * ceil(sizeof(type)/8.0);
		cout << v.capacity()*sizeof(type) << " " << l.size()*(16+aux) << endl;
	#endif

	//To avoid too much compiler optimization
	int useless = v[v.size()-1].z[0] + l.back().z[0];
	return useless;
}