#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct segtree{
	int lc[233333*400],rc[233333*400],sum[233333*400],cnt=0;
	ll ret1,ret2;
	void pushup(int x){sum[x]=sum[lc[x]]+sum[rc[x]];}
	void ins(int &x,int l,int r,int p,int v){
		if (!x)x=++cnt;
		if (l==r){sum[x]+=v;return;}
		int mid=(l+r)>>1;
		if (p<=mid)ins(lc[x],l,mid,p,v);else ins(rc[x],mid+1,r,p,v);
		pushup(x);
	}
	int merge(int a,int b,int l,int r){
		if (!a||!b)return a+b;
		if (l==r){sum[a]+=sum[b];return a;}
		ret1+=1ll*sum[lc[a]]*sum[rc[b]],ret2+=1ll*sum[rc[a]]*sum[lc[b]];
		int mid=(l+r)>>1;
		lc[a]=merge(lc[a],lc[b],l,mid);rc[a]=merge(rc[a],rc[b],mid+1,r);
		return pushup(a),a;
	}
}T;
int n,size=0;ll ans;
int rt[233333*400];
int solve(){
	int p;scanf("%d",&p);
	int x=++size;
	if (p) T.ins(rt[x],1,n,p,1);
	else{
		int lc=solve(),rc=solve();
		T.ret1=T.ret2=0;
		rt[x]=T.merge(rt[lc],rt[rc],1,n);
		ans+=min(T.ret1,T.ret2);
	}
	return x;
}
int main(){
	scanf("%d",&n);
	printf("%lld\n",(solve(),ans));
	return 0;
}
