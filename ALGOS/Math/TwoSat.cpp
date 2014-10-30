const int maxn = 1111;
// x ^ y == 1 <==> ((x==1 || y==1) && (x==0 || y==0))
// x ^ y == 0 <==> ((x==1 || y==0) && (x==0 || y==1))
struct TwoSAT{
	int n;
	vector<int> mp[maxn*2];
	bool mark[maxn*2];
	int S[maxn*2], c;
	bool dfs(int x){
		if(mark[x^1]) return false;
		if(mark[x]) return true;
		mark[x] = true;
		S[c++] = x;
		for(int i = 0; i < mp[x].size(); i++)
			if(!dfs(mp[x][i])) return false;
		return true;
	}

	void init(int nn){
		n = nn;
		for(int i = 0; i < n *2; i++) mp[i].clear();
		memset(mark,0,sizeof(mark));
	}

	// x == xval or y == yval  <==>  ( !x -> y && !y -> x )
	void add_or(int x,int xval,int y,int yval){
		x = x * 2 + xval;  y = y * 2 + yval;
		mp[x^1].push_back(y);
		mp[y^1].push_back(x);
	}

	// x == xval && y == yval  <==>  ( !x -> x && !y -> y )
	void add_bing(int x,int xval,int y,int yval){
		x = x * 2 + xval;  y = y * 2 + yval;
		mp[x^1].push_back(x);
		mp[y^1].push_back(y);
	}

	bool solve(){
		for(int i = 0; i < n * 2; i += 2){
			c = 0;
			if(!dfs(i)){
				while(c > 0) mark[S[--c]] = false;
				if(!dfs(i + 1)) return false;
			}
		}
		return true;
	}
}lx;
