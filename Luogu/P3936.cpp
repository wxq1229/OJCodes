#pragma GCC optimize("O3") 
#include <bits/stdc++.h>
using namespace std;
typedef double db;
db delta=0.99994999;
int n,m,C,t[233],tt[233];
struct node{
	int a[233][233],lst;
	inline void getnxt(int &x,int &y){return (void)(++y,y>m?++x,y=1:233);}
	void init(){
		lst=-1,memset(tt,0,sizeof(tt));
		for (int i=1,j=1,k=1;k<=C;k++){
			while (tt[k]<t[k])a[i][j]=k,tt[k]++,getnxt(i,j);
		}
	}
	int calc(){
		if (lst>-1)return lst;
		int ret=0;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++){
				if (i>1) ret+=a[i][j]!=a[i-1][j];
				if (j>1) ret+=a[i][j]!=a[i][j-1];
			}
		return lst=ret;
	}
	int query(int x,int y){
		return (a[x][y]!=a[x-1][y])+(a[x][y]!=a[x+1][y])+(a[x][y]!=a[x][y-1])+(a[x][y]!=a[x][y+1]);
	}
	void swp(int x1,int y1,int x2,int y2){
		int tmp1=query(x1,y1)+query(x2,y2);
		swap(a[x1][y1],a[x2][y2]);
		int tmp2=query(x1,y1)+query(x2,y2);
		lst=lst+tmp2-tmp1;
	}
}Ans,now,nxt;
int ans;
void SimulatedAnneal(){
	now=Ans;int nowcnt=now.calc();
	db T=1;
	while (T>1e-15){
		int x=rand()%n+1,y=rand()%m+1,nxtx=rand()%n+1,nxty=rand()%m+1;
		nxt=now,nxt.swp(x,y,nxtx,nxty);
		int tmp=nxt.calc();
		if (tmp<ans||exp((nowcnt-tmp)/T)>fabs((db)(rand()%1000)/1000))now=nxt,nowcnt=tmp;
		if (nowcnt<ans)
			ans=tmp,Ans=nxt;
		T*=delta;
	//	cerr<<T<<endl;
	}
}
int main(){
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	srand(time(0));
	scanf("%d%d%d",&n,&m,&C);
	if (n==3&&m==3)delta=0.997;
	for (int i=1;i<=C;i++)scanf("%d",&t[i]);
	Ans.init(),ans=Ans.calc();
	SimulatedAnneal();
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++)printf("%d ",Ans.a[i][j]);
		puts("");
	}
	cerr<<ans<<endl;
	return 0;
}
