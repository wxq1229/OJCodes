#include <bits/stdc++.h>
using namespace std;
#define L 1
#define R 2
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
const int N=233333*3;
typedef long long ll;
struct edge{
	int to,nxt;
}e[N*2];
int head[N],cnt=0;
inline void adde(int x,int y){
	e[++cnt]=(edge){y,head[x]};
	head[x]=cnt;
}
void addedge(int x,int y){adde(x,y),adde(y,x);}
int chr[N];
ll f[N],sum[N],ans=0;
int top,stk[N],fa[N];
void getans(int x,int prev){
	fa[x]=prev;
	int tmp=-1;
	if(chr[x]==R){
		if(top)tmp=stk[top],f[x]=f[fa[stk[top]]]+1,--top;
		else f[x]=0;
	}
	else f[x]=0,stk[++top]=x;
	sum[x]=sum[prev]+f[x];
	for(int i=head[x];i;i=e[i].nxt){
		int v=e[i].to; if(v==prev)continue;
		getans(v,x);
	}
	if(tmp!=-1)stk[++top]=tmp;
	if(chr[x]==L)--top;
}
int n;
char buf[N];
int main(){
	scanf("%d",&n);
	scanf("%s",buf);
	rep(i,1,n)chr[i]=buf[i-1]=='('?L:R;
	rep(i,2,n){int x; scanf("%d",&x); addedge(x,i);}
	getans(1,0);
	ans=sum[1];
	rep(i,2,n)ans^=sum[i]*i;
	printf("%lld\n",ans);
	return 0;
}
