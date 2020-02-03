#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	for (;!isdigit(ch);ch=getchar())if(ch=='-')f*=-1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	return x*f;
}
int main(){
	ll n=read(),m=read();
	if (n>=m)puts("YES");
	else puts("NO");
	return 0;
}
