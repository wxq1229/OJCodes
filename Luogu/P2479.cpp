#include <bits/stdc++.h>
using namespace std;
const int MAXN=100010;
const int INF=1e9;
int cmptype;
struct KDTree{
	struct node{
		int d[2],minv[2],maxv[2];
		int lc,rc;
		bool operator < (const node& k1)const{return d[cmptype]<k1.d[cmptype];}
	}a[MAXN],t[MAXN];
	int root,cnt;
	KDTree(){root=0,cnt=0;}
	void pushup(int x){
		for (int i=0;i<2;i++)t[x].minv[i]=t[x].maxv[i]=t[x].d[i];
		for (int i=0;i<2;i++){
			if (t[x].lc)
				t[x].minv[i]=min(t[x].minv[i],t[t[x].lc].minv[i]),
				t[x].maxv[i]=max(t[x].maxv[i],t[t[x].lc].maxv[i]);
			if (t[x].rc)
				t[x].minv[i]=min(t[x].minv[i],t[t[x].rc].minv[i]),
				t[x].maxv[i]=max(t[x].maxv[i],t[t[x].rc].maxv[i]);
		}
	}
	void build(int& x,int l,int r,int type){
		if (l>r){x=0;return;}
		cmptype=type;
		int mid=(l+r)>>1;
		nth_element(a+l,a+mid,a+r+1);
		t[x=++cnt]=a[mid];
		build(t[x].lc,l,mid-1,type^1);
		build(t[x].rc,mid+1,r,type^1);
		pushup(x);
	}
	int dist(node k1,node k2){return abs(k1.d[0]-k2.d[0])+abs(k1.d[1]-k2.d[1]);}
	node T;int res;
	int getmax(int x){
		if (x==0)return -INF;
		int ans=0;
		for (int i=0;i<2;i++)
			ans+=max(abs(T.d[i]-t[x].minv[i]),abs(T.d[i]-t[x].maxv[i]));
		return ans;
	}
	void queryMax(int x){
		if (!x)return;
		res=max(res,dist(T,t[x]));
		int dl=getmax(t[x].lc),dr=getmax(t[x].rc);
		if (dl>dr){
			if (dl>res)queryMax(t[x].lc);
			if (dr>res)queryMax(t[x].rc);
		}else{
			if (dr>res)queryMax(t[x].rc);
			if (dl>res)queryMax(t[x].lc);
		}
	}
	int getmin(int x){
		if (x==0)return INF;
		int ans=0;
		for (int i=0;i<2;i++){
			ans+=max(t[x].minv[i]-T.d[i],0);
			ans+=max(T.d[i]-t[x].maxv[i],0);
		}
		return ans;
	}
	void queryMin(int x){
		if (!x)return;
		int tmp=dist(T,t[x]);
		if (tmp)res=min(res,tmp);
		int dl=getmin(t[x].lc),dr=getmin(t[x].rc);
		if (dl<dr){
			if (dl<res)queryMin(t[x].lc);
			if (dr<res)queryMin(t[x].rc);
		}else{
			if (dr<res)queryMin(t[x].rc);
			if (dl<res)queryMin(t[x].lc);
		}
	}
	int query(int x,int y,int type){
		T.d[0]=x,T.d[1]=y;
		if (type==0)res=INF,queryMin(root);
		else res=-INF,queryMax(root);
		return res;
	}
}kdt;
int main(){
//	freopen("input","r",stdin);
	int n;scanf("%d",&n);
	for (int i=1;i<=n;i++)scanf("%d%d",&kdt.a[i].d[0],&kdt.a[i].d[1]);
	kdt.build(kdt.root,1,n,0);
	int ans=INF;
	for (int i=1;i<=n;i++){
		int x=kdt.a[i].d[0],y=kdt.a[i].d[1];
		int Max=kdt.query(x,y,1),Min=kdt.query(x,y,0);
		//cerr << Max << " " << Min << endl;
		ans=min(ans,Max-Min);
		//cerr << ans << endl;
	}
	printf("%d\n",ans);
	return 0;	
}








