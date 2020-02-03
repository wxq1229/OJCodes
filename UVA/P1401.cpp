#include <bits/stdc++.h>
using namespace std;
#define root 1
typedef long long ll;
const int MAXN=400010;
const int MOD=20071027;
int ch[MAXN][256],val[MAXN],size=1;
#define idx(c) ((c)-'a'+1)
void insert(char *s,int n){
	int x=root;
	for (int i=0;i<n;i++){
		if (!ch[x][idx(s[i])])ch[x][idx(s[i])]=++size;
		x=ch[x][idx(s[i])];
	}
	val[x]=1;
}
char str[300010],buf[233];
ll dp[300010];
int main(){
	int kase=0;while (scanf("%s",str+1)==1){
		memset(dp,0,sizeof(dp));
		memset(val,0,sizeof(val));
		memset(ch,0,sizeof(ch));
		int n=strlen(str+1);
		int m;scanf("%d",&m);
		for (int i=1;i<=m;i++){
			scanf("%s",buf);
			int len=strlen(buf);
			insert(buf,len);
		}
		dp[n+1]=1;
		for (int i=n;i>=1;i--){
			int now=root;
			for (int j=i;now&&j<=n;j++){
				now=ch[now][idx(str[j])];
				//cerr<<now<<" ";
				if (val[now]==1) dp[i]=(dp[i]+dp[j+1])%MOD;
			}
			//cerr<<endl;
		}
	//	for (int i=1;i<=n;i++)printf("%d ",dp[i]);puts("");
		printf("Case %d: %lld\n",++kase,dp[1]);
	}
	return 0;
}
/*
abcd
4
a
b
cd
ab
*/
