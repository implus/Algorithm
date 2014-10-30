/*
0.	基本注意点：
1）  val 数组记录了当前的状态对应的哪个给定串，val == 0 代表没有给定串对应，为了方便表示，所以加入串的时候第一个串就用1代表。
	2） insert 函数要使用len传入准确长度，避免中间转化后的节点出现’\0’而导致串没有完全加入
1.	有些题目要扩展使用到一些节点相关信息，如：
1）  到根节点的深度 dep[0] = 0; 处理字符串去掉首字符的变短转移需要将串长和dep比较，直接通过fail转移
2）  cnt数组判重
3）  重复元素并查集记录
*/

#define maxnode 60005// 单词个数 x 长度
#define sigma_size 2//字母表序号
//int sigma_size = 0;
struct AC{
	//Trie
	int ch[maxnode][sigma_size];
	int dis[maxnode][sigma_size];// 对应节点间的距离
	int Q[maxnode];//cal fail queue
	int val[maxnode];// node  编号
	//int dep[maxnode];// node  深度
	//int cnt[maxnode];// node  附加信息，出现了几次
	//int index[N];// 重复单词只要处理某一个就行了，利用并查集思想
	int sz;
	//map<char,int> mp;
// 初始化，每次都要重新初始化trie树
	void Trie(){
		sz = 1;memset(ch[0],0,sizeof(ch[0]));
	}
//很重要，映射函数，将字符与下标0开始的数字进行对应
	int idx(char c){//mapping table,26 or 128 or more
		return c - '0';
	}
	void insert(char *s,int len,int v){// v为s 的附加信息，如第几个模板串
		int u = 0;
		for(int i = 0; i < len; i++){
			int c = idx(s[i]);
			if( !ch[u][c] ){
				memset(ch[sz],0,sizeof(ch[sz]));
				val[sz] = 0;	//dep[sz] = dep[u] + 1;
				ch[u][c] = sz++;
			}
			u = ch[u][c];
		}
		val[u] = v;
	}

	int last[maxnode];// suffix link 指向沿着失败指针回溯遇到的下一个 单词编号 
	int f[maxnode];//   fail pointer
	void getFail(){
		int *s = Q, *e = Q;
		//init 
		f[0] = 0;
		for(int c = 0; c < sigma_size; c++){
			int u = ch[0][c];
			if(u){ f[u] = 0; last[u] = 0; *e++ = u; }
		}
		// bfs
		while(s != e){
			int r = *s++;
			for(int c = 0; c < sigma_size; c++){
				int& u = ch[r][c];
				if(!u){
					u = ch[f[r]][c];
				}else{
					*e++ = u;
					f[u] = ch[f[r]][c];
					//val[u] |= val[f[u]];// 2进制 若单词少（<12，可状态压缩）				
					//last[u] = val[f[u]] ? f[u] : last[f[u]];// val > 0 代表单词节点 ，所以单词列表下标从1开始
				}
			}
		}
	}
	/*
	int gao(int s){
        int ans =0;
        while(s){
            ans = max(dp[s],ans);
            s = last[s];
        }
        return ans;
    }*/
	void gao(){
		//if(val[s])t = max(t,gao(s));
        //else if(last[s])t = max(t,gao(last[s]));
	}
}lx;

int main(){
	while(scanf("%d%d",&n,&m)==2 && (n||m)){
		lx.Trie();
		for(int i=1;i<=n+m;i++){
			scanf("%s",temp);
			lx.insert(temp,strlen(temp),i);
		}
		lx.getFail();
		lx.gao();
	}
	return 0;
}

