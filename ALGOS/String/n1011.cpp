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
#include <cmath>
using namespace std;
typedef long long lint;


double eps = 1e-8;
int dcmp(double x){
	return (x > eps) - (x < -eps);
}

double a, b, c, d, e, f;
void gao(double& a, double& b, double& d, double& e, double& f){
	if(dcmp(f) == 0){
		return;
	}
	double aa = f, bb = a * 2 - b * 2, cc = -f;
	double t = (-bb + sqrt(bb * bb - 4 * aa * cc)) / 2 / aa;
	t = atan(t);
	double co = cos(t), si = sin(t);
	double ta = a * co * co + b * si * si + f * co * si;
	double tb = a * si * si + b * co * co - f * co * si;
	double te = d * si + e * co;
	double td = d * co - e * si;
	a = ta;
	b = tb;
	f = 0;
	d = td;
	e = te;
}

int main() {
	while(scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f) != EOF){
		for(int i = 0; i < 100000; i++){
			gao(a, b, d, e, f);
			gao(a, c, d, f, e);
			gao(b, c, e, f, d);
		}
		double ans = min(sqrt(1.0 / a), min(sqrt(1.0 / b), sqrt(1.0 / c)));
		printf("%.10lf\n", ans);
	}
	return 0;
}
