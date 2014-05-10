/*************************************************************************
    > File Name: Monituihuo.cpp
    > Author: implus
    > Mail: 674592809@qq.com
    > Created Time: 一  5/ 5 18:02:59 2014
 ************************************************************************/

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cmath>
#include<map>
#include<string>
#include<set>
#include<queue>
#include<stack>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define ls (rt<<1)
#define rs (rt<<1|1)
#define lson l,m,ls
#define rson m+1,r,rs
//source here 
 
int n; 
struct node{ 
	double  x,y,z; 
}dot[105]; 
double A,B,C; 
double dist(node a,double aa,double bb,double cc){ 
	return (aa*a.x+bb*a.y+cc*a.z)*(aa*a.x+bb*a.y+cc*a.z)/(aa*aa+bb*bb+cc*cc); 
} 
double getDist(double aa,double bb,double cc){ 
	double sum = 0; 
	int i=0; 
	for(i=0;i<n;i++){ 
		sum += dist(dot[i],aa,bb,cc); 
	} 
	//cout<<sum<<endl; 
	//getchar(); 
	return sum; 
} 
int main(){ 
	int t; 
	scanf("%d",&t); 
	int cas = 0; 
	int i,j,k; 
	while(t--){ 
		scanf("%d",&n); 
		double ans = 0; 
		double min = 99999999; 
		double max = -99999999; 
		A = 1;B = 1;C = 1; 
		for(i=0;i<n;i++){ 
			scanf("%lf%lf%lf",&dot[i].x,&dot[i].y,&dot[i].z); 
			ans += dist(dot[i],A,B,C); 
		} 
		double step = ans; 
		//cout<<step<<endl; 
		double best = getDist(A,B,C); 
		//cout<<best<<" "<<ans<<" "<<max<<" "<<min<<endl; 
		double newA,newB,newC; 
		while(step>=0.000001){ 
			bool ok = 1; 
			while(ok){ 
				ok = 0; 
				for(i=-1;i<2;i+=1){ 
					newA = i*step+A; 
					for(j=-1;j<2;j+=1){ 
						newB = j*step +B; 
						for(k=-1;k<2;k+=1){ 
							newC = k*step+C; 
							double dis = getDist(newA,newB,newC); 
							//cout<<"!!!"<<newans<<" "<<dis<<" "<<step<<endl; 
							if(dis<best){ 
								A = newA; 
								B = newB; 
								C = newC; 
								best = dis; 
								/*
								if(best>=0.000001){ 
									ok = true; 
								}								 
								*/
							} 
						} 
 
					} 
				} 
			} 
			cerr<<"best = "<<best<<endl;
			step /=2; 
			//cout<<step<<endl; 
		} 
		printf("%.6lf\n",best); 
		//printf("%.6lf\n",getDist(1,0,0)); 
		printf("Case %d: %.6lf %.6lf %.6lf\n",++cas,A,B,C); 
	} 
	return 0; 
} 


