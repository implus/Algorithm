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

const double eps = 1e-8;
int dcmp(double x){
	return (x > eps) - (x < -eps);
}

double m[3][3];

/*
int main() {
	double a, b, c, d, e, f;
	while(scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f) == 6){
		m[0][0] = a; m[0][1] = f / 2; m[0][2] = e / 2;
		m[1][0] = f / 2; m[1][1] = b; m[1][2] = d / 2;
		m[2][0] = e / 2; m[2][1] = d / 2; m[2][2] = c;

		double a1 = m[0][0];
		double a2 = m[0][0] * m[1][1] - m[0][1] * m[1][0];
		double a = m[0][0], b = m[0][1], c = m[0][2], 
			   d = m[1][0], e = m[1][1], f = m[1][2],
			   g = m[2][0], h = m[2][1], i = m[2][2];
		double a3 = a * e * i + b * f * g + c * d * h - 
					c * e * g - f * h * a - i * b * d;
		double x1 = a1, x2 = a2 / a1, x3 = a3 / a2;
		cerr<<"x1 = "<<x1<<" x2 = "<<x2<<" x3 = "<<x3<<endl;
		double ans = sqrt(1.0 / x1);
		ans = min(ans, sqrt(1.0 / x2));
		ans = min(ans, sqrt(1.0 / x3));
		printf("%.10lf\n", ans);
	}
	return 0;
}
*/

