#include <bits/stdc++.h>
using namespace std;
#define pb push_back
const int N=50010;
int n,m;
vector<int>from,to,g[N];
#define adde(x,y) from.pb(x),to.pb(y),g[x].pb(to.size()-1)
#define addedge(x,y) adde(x,y),adde(y,x)
void stdG(){
	auto cmp=[&](int i,int j){return to[i]<to[j];};
	for (int i=1;i<=n;i++)sort(g[i].begin(),g[i].end(),cmp);
}
vector<int>ring;
int dep[N],fae[N];
#define v to[ei]
void dfs(int x,int lste,int deep){
	dep[x]=deep,fae[x]=lste;
	for (auto ei:g[x]){
		if (dep[v]==0)dfs(v,ei,deep+1);
		else if (v!=from[fae[x]]&&dep[v]<dep[x]){
			int nw=x;ring.pb(ei);
			while (nw!=v)ring.pb(fae[nw]),nw=from[fae[nw]];
		}
	}
}
void findRing(){dfs(1,-1,1);}
int Ans[N],tot=0,vis[N],mark[N];
void getAns(int x,int prev){
	Ans[++tot]=x;
	for (auto ei:g[x]) if (!vis[ei]&&v!=prev)getAns(v,x);
}
#undef v
int ans[N];
int chkAns(){
//	for (int i=1;i<=n;i++)printf("%d ",Ans[i]);puts("");
	for (int i=1;i<=n;i++){
		if (ans[i]==Ans[i])continue;
		return ans[i]>Ans[i];
	}
//	assert(false);
}
void updateAns(){
	if (chkAns())for (int i=1;i<=n;i++)ans[i]=Ans[i];
}
int main(){
	scanf("%d%d",&n,&m);
	for (int x,y,i=1;i<=m;i++)scanf("%d%d",&x,&y),addedge(x,y);
	stdG();
	if (m==n-1){
		tot=0,getAns(1,0);
		for (int i=1;i<=n;i++)printf("%d%c",Ans[i]," \n"[i==n]);
		return 0;
	}else{
		findRing(),ans[1]=23333333;
		for (auto ei:ring){
			tot=0,vis[ei]=vis[ei^1]=1,getAns(1,0);
			updateAns(),vis[ei]=vis[ei^1]=0;
		}
		for (int i=1;i<=n;i++)printf("%d%c",ans[i]," \n"[i==n]);
	}
	return 0;
}
