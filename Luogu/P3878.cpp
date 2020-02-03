#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const db delta=0.998;
int a[233333],n;
ll calc(){
	ll tmp1=0,tmp2=0;
	for (int i=1;i<=(n+1)/2;i++)tmp1+=a[i];
	for (int i=(n+1)/2+1;i<=n;i++)tmp2+=a[i];
	return abs(tmp1-tmp2);
}
ll ans,now;
void SimulatedAnneal(){
	for (db T=5000;T>1e-10;T*=delta){
		int x=rand()%n+1,y=rand()%n+1;
		swap(a[x],a[y]);
		now=calc();
		if (now<ans)ans=now;
		else if (exp((ans-now)/T)<1.0*rand()/RAND_MAX)swap(a[x],a[y]);
	}
}
int main(){
	srand(time(NULL));
	int T;scanf("%d",&T);while (T--){
		scanf("%d",&n);
		for (int i=1;i<=n;i++)scanf("%d",&a[i]);
		ans=1e18;
		for (int it=0;it<10;it++)SimulatedAnneal();
		printf("%lld\n",ans);
	}
	return 0;
}
