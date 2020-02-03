#include <bits/stdc++.h>
using namespace std;
const int N=233333;
int head[N],cnt=0,n,m;
struct edge{int to,nxt,w;}e[N*2];
void adde(int x,int y,int w){e[++cnt]=(edge){y,head[x],w},head[x]=cnt;}
void addedge(int x,int y,int w){adde(x,y,w),adde(y,x,w);}
int ans,chkd;multiset<int>s[N];
#define v e[i].to
int getans(int x,int prev){
	s[x].clear();
	for (int i=head[x];i;i=e[i].nxt)if (v!=prev){
		int k1=getans(v,x)+e[i].w;
		if (k1>=chkd)++ans;else s[x].insert(k1);
	}
	int ret=0;
	while (s[x].size()){
		auto it=s[x].begin();auto nxt=s[x].lower_bound(chkd-*it);
		if (nxt==it)++nxt;
		if (nxt==s[x].end())ret=max(ret,*it),s[x].erase(it);
		else ++ans,s[x].erase(nxt),s[x].erase(it);
	}
	return ret;
}
#undef v
int check(int mid){
	chkd=mid,ans=0,getans(1,0);
	return ans>=m;
}
int main(){
	scanf("%d%d",&n,&m);
	int l=0,r=0,ans=-1;
	for (int x,y,w,i=1;i<=n-1;i++)scanf("%d%d%d",&x,&y,&w),addedge(x,y,w),r+=w;
	while (l<=r){
		int mid=(l+r)>>1;
		if (check(mid))ans=mid,l=mid+1;else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}
