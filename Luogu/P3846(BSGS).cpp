#include <bits/stdc++.h>
using namespace std;
inline int fpow(int a,int b,int c){
	int ret=1; for (a%=c;b;b>>=1,a=1ll*a*a%c) if (b&1) ret=1ll*ret*a%c;
	return ret;
}
int BSGS(int a,int b,int n,int &ans){
	a%=n,b%=n;
	if (a==0){if (b==0){ans=1;return 1;} else return 0;}
	map<int,int> h; int m=ceil(sqrt(n));
	for (int tmp=b,i=0;i<=m;i++,tmp=1ll*tmp*a%n) h[tmp]=i;
	a=fpow(a,m,n);
	for (int tmp=a,i=1;i<=m;i++,tmp=1ll*tmp*a%n)
		if (h.count(tmp)){
			ans=1ll*i*m-h[tmp]; return 1;
		}
	return 0;
}
int main(){
	int n,a,b; scanf("%d%d%d",&n,&a,&b);
	int ans,flg=BSGS(a,b,n,ans);
	if (!flg)puts("no solution"); else printf("%d\n",ans);
	return 0;
}
