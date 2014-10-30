#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <ctime>
using namespace std;
typedef long long lint;

const int MAX_N = 250000 + 10;


int a[MAX_N], n;
void qsort(int l, int r){
	if(r - l <= 1) return;

	int p = rand() % (r - l) + l;
	// [l, s] <= v < [t, r)
	int s = l, t = r - 1, v = a[p];
	while(s <= t){
		while(a[s] < v) s++;
		while(a[t] > v) t--;
		if(s <= t){
			swap(a[s], a[t]);
			s++, t--;
		}
	}

	qsort(l, t + 1);
	qsort(s, r);
}

int main() {
	while(scanf("%d", &n) == 1){
		srand(time(NULL));
		for(int i = 0; i < n; i++){
			scanf("%d", &a[i]);
		}
		qsort(0, n);
/*
		for(int i = 0; i < n; i++){
			cerr<<a[i]<<" ";
		}cerr<<endl;
		*/

		if(n & 1) printf("%.1lf\n", 1.0 * a[n / 2]);
		else {
			printf("%.1lf\n", (0.0 + a[n / 2] + a[n / 2 - 1]) / 2);
		}
	}
	return 0;
}
