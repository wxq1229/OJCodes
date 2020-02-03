#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
inline char nc(){
	char ch; while(isspace(ch=getchar()));
	return ch;
}
const int N=1e6+10;
struct SA{
	char s[N]; int n;
	int sa[N],sb[N],rk[N],x[N],y[N],cnt[N];
	void build(){
		rep(i,0,555)cnt[i]=0; 
		rep(i,1,n)cnt[s[i]]++; rep(i,1,555)cnt[i]+=cnt[i-1];
		rep(i,1,n)sa[cnt[s[i]]--]=i; 
		rk[sa[1]]=1; rep(i,2,n)rk[sa[i]]=rk[sa[i-1]]+(s[sa[i]]!=s[sa[i-1]]);
		for (int k=1;rk[sa[n]]!=n&&k<n;k<<=1){
		//	rep(i,1,n)printf("%d ",rk[i]); puts("");
			rep(i,1,n)x[i]=rk[i],y[i]=i+k<=n?rk[i+k]:0;
			rep(i,0,n)cnt[i]=0; rep(i,1,n)cnt[y[i]]++; 
			rep(i,1,n)cnt[i]+=cnt[i-1]; 
			rep(i,1,n)sb[cnt[y[i]]--]=i;
			rep(i,0,n)cnt[i]=0; rep(i,1,n)cnt[x[i]]++; 
			rep(i,1,n)cnt[i]+=cnt[i-1]; 
			per(i,n,1)sa[cnt[x[sb[i]]]--]=sb[i];
			rk[sa[1]]=1; rep(i,2,n)
				rk[sa[i]]=rk[sa[i-1]]+(x[sa[i]]!=x[sa[i-1]]||y[sa[i]]!=y[sa[i-1]]);
		}
		//rep(i,1,n)printf("%d ",rk[i]); puts("");
	}
	void init(char *str,int len){
		n=len; rep(i,1,n)s[i]=*(str++);
	}
}sa;
int n;
char ch[N],ans[N];
int main(){
	scanf("%d",&n);
	rep(i,1,n)ch[i]=nc();
	rep(i,1,n)ch[i+n+1]=ch[n-i+1];
	ch[n+1]=48;
	sa.init(ch+1,n*2+1),sa.build();
	int l=1,r=n,nw=0;
	while(l<=r){
		if(sa.rk[l]<sa.rk[n*2-r+2])ans[++nw]=ch[l++];
		else ans[++nw]=ch[r--];
	}
	rep(i,1,nw){
		putchar(ans[i]);
		if(i%80==0)puts("");
	}
	return 0;
}
