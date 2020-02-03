#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
const int N=1e6+10;
int p[N],n,m;
char s[N],t[N];
int main(){
	scanf("%s%s",s+1,t+1),n=strlen(s+1),m=strlen(t+1);
	p[1]=0;
	rep(i,2,m){
		int j=p[i-1];
		while(j&&t[j+1]!=t[i])j=p[j];
		p[i]=j+(t[j+1]==t[i]);
	}
	int nw=0;
	rep(i,1,n){
		while(nw&&s[i]!=t[nw+1])nw=p[nw];
		if(s[i]==t[nw+1])nw++;
		if(nw==m)printf("%d\n",i-m+1);
	}
	rep(i,1,m)printf("%d%c",p[i]," \n"[i==m]);
	return 0;
}
