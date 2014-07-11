
typedef char T;
const int maxm = 1010101;
struct KMP{
	T p[maxm]; int m;//index from 0
	int f[maxm];
	void getFail(int m){// m is p's length
		f[0] = f[1] = 0; this->m = m;
		for(int s = 1; s < m; s++){ // s from p[s - 1], s extended by p[s]
			int ns = f[s];
			while(ns && p[ns] != p[s]) ns = f[ns];
			f[s + 1] = (p[ns] == p[s] ? ns + 1: 0);
		}
	}
	// before getFail(m);
	void find(T * mo, int n){
		int s = 0;
		for(int i = 0; i < n; i++){
			while(s && p[s] != mo[i]) s = f[s];
			if(p[s] == mo[i]) s++;
			if(s == m){
				printf("pos = %d, find it\n", i - m + 1);
			}
		}
	}

	void gao(){
		int ans = 0;
		if( m % (m - f[m]) == 0 ){
			ans = m / (m - f[m]);
		}else ans = 1;
		printf("%d\n", ans);
	}
}g;
