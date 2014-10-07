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
using namespace std;
typedef long long lint;

char ch[11111];
char title[111] = "easy_count";

const int MAX_R = 1000000000;

void fileBegin(int fileID, int T){
	sprintf(ch, "%s_%d.in", title, fileID);
	freopen(ch, "w", stdout);
}

void fileClose(){
	fclose(stdout);
}


void genFile(int l, int r, int n){
	printf("%d %d %d\n", l, r, n);
}

int main() {
	srand(time(NULL));
	int id = 1, l, r;

	//1 <= l <= r <= 200, n < 10, 暴力枚举可以通过
	fileBegin(id++, 100);
	l = rand() % 99 + 1, r = l + rand() % 100;
	genFile(l, r, rand() % 10);
	fileClose();

	//1 <= l <= r <= 2000, n < 10, 固定l，r，范围为10^3，暴力可过
	fileBegin(id++, 100);
	genFile(rand() % 100, 1000 + rand() % 1000, rand() % 10);
	fileClose();


	//10000000 <= l <= r <= 10020000, dist == 20000，n < 10 扩展到较高数值，范围不变,暴力可过
	fileBegin(id++, 100); int base = 10000000;
	genFile(base, base + rand() % 20000, rand() % 10);
	fileClose();

	//1 <= l <= r <= 200000, n < 10, 暴力处理
	fileBegin(id++, 100);
	l = rand() % 100000, r = l + 100000 + rand() % 100000;
	genFile(l, r, rand() % 10);
	fileClose();


	//dist = 1e6, n < 10, 暴力可过
	fileBegin(id++, 100); base = 1000000;
	l = rand() % base, r = l + base + rand() % base;
	genFile(l, r, rand() % 10);
	fileClose();

	//dist = 1e7, n < 10, 暴力 + 小贪心 
	fileBegin(id++, 100); base = 10000000;
	l = rand() % base, r = l + base + rand() % base;
	genFile(l, r, rand() % 10);
	fileClose();

	//dist = 1e8, n = 1, 简单的动态规划, 或者技巧贪心也可过
	fileBegin(id++, 100); base = 100000000;
	l = rand() % base, r = l + base + rand() % base;
	genFile(l, r, 1);
	fileClose();

	//dist = 1e8, n < 10, 动态规划 
	fileBegin(id++, 100); base = 100000000;
	l = rand() % base, r = l + base + rand() % base;
	genFile(l, r, rand() % 10);
	fileClose();

	//dist = 1e9, n = 1, 动态规划
	fileBegin(id++, 100); base = 1000000000 / 2;
	l = rand() % base, r = l + base + rand() % base;
	genFile(l, r, 1);
	fileClose();

	//dist = 1e9, n = 0, 动态规划, 贪心0处理比较不方便 
	fileBegin(id++, 100); base = 1000000000 / 2;
	l = rand() % base, r = l + base + rand() % base;
	genFile(l, r, 0);
	fileClose();

	return 0;
}
