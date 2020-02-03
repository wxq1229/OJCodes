#include <bits/stdc++.h>
using namespace std;
typedef double db;
const db delta=0.99995;
int n;
struct point{
	db d[1010];
	point(){memset(d,0,sizeof(d));}
	point operator + (const point& k1) const{
		point res;
		for (int i=1;i<=n;i++) res.d[i]=d[i]+k1.d[i];
		return res;
	}
	point operator - (const point& k1) const{
		point res;
		for (int i=1;i<=n;i++) res.d[i]=d[i]-k1.d[i];
		return res;
	}	
	point operator * (const db& k1) const{
		point res;
		for (int i=1;i<=n;i++) res.d[i]=d[i]*k1;
		return res;
	}
	point operator / (const db& k1) const{
		point res;
		for (int i=1;i<=n;i++) res.d[i]=d[i]/k1;
		return res;
	}
	db abs(){
		db dis=0.0;
		for (int i=1;i<=n;i++) dis+=d[i]*d[i];
		return sqrt(dis);
	}
	void scan(){for (int i=1;i<=n;i++)scanf("%lf",&d[i]);}
}P[1010],ans;
db dis[1010];
int main(){
	srand(time(NULL));
	scanf("%d",&n);
	for (int i=1;i<=n+1;i++)P[i].scan(),ans=ans+P[i];
	ans=ans/(n+1);
	db T;
	for (T=10001;T>0.0001;T*=delta){
		db tmp=0.0;
		for (int i=1;i<=n+1;i++)
			dis[i]=(P[i]-ans).abs(),tmp+=dis[i];
		tmp/=n+1;
		point V;
		for (int i=1;i<=n+1;i++)
			for (int j=1;j<=n;j++)
				V.d[j]+=(dis[i]-tmp)/(n+1)*(P[i].d[j]-ans.d[j]);
		ans=ans+V*T;
	}
	for (int it=0;1.0*clock()/CLOCKS_PER_SEC<0.9;it++){
		db tmp=0.0;
		for (int i=1;i<=n+1;i++)
			dis[i]=(P[i]-ans).abs(),tmp+=dis[i];
		tmp/=n+1;
		point V;
		for (int i=1;i<=n+1;i++)
			for (int j=1;j<=n;j++)
				V.d[j]+=(dis[i]-tmp)/(n+1)*(P[i].d[j]-ans.d[j]);
		ans=ans+V*T;
	}
	for (int i=1;i<=n;i++)printf("%.3f ",ans.d[i]);
	return 0;
}










