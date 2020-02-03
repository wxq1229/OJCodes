#include <bits/stdc++.h>
using namespace std;
const int N=4e5+10;
char s[N];
int n,sa[N],x[N],y[N],rk[N],sb[N],cnt[N];
void getsa(){
	for (int i=1;i<=n;i++) cnt[s[i]]++;
	for (int i=1;i<=555;i++) cnt[i]+=cnt[i-1];
	for (int i=1;i<=n;i++) sa[cnt[s[i]]--]=i;
	rk[sa[1]]=1;
	for (int i=2;i<=n;i++) rk[sa[i]]=rk[sa[i-1]]+(s[sa[i]]!=s[sa[i-1]]);
	for (int k=1;k<n&&rk[sa[n]]!=n;k<<=1){
		for (int i=1;i<=n;i++) x[i]=rk[i],y[i]=i+k<=n?rk[i+k]:0;
		for (int i=0;i<=n;i++) cnt[i]=0;
		for (int i=1;i<=n;i++) cnt[y[i]]++;
		for (int i=1;i<=n;i++) cnt[i]+=cnt[i-1];
		for (int i=1;i<=n;i++) sb[cnt[y[i]]--]=i;
		for (int i=0;i<=n;i++) cnt[i]=0;
		for (int i=1;i<=n;i++) cnt[x[i]]++;
		for (int i=1;i<=n;i++) cnt[i]+=cnt[i-1];
		for (int i=n;i>=1;i++) sa[cnt[x[sb[i]]]--]=sb[i];
		rk[sa[1]]=1;
		for (int i=2;i<=n;i++)
			rk[sa[i]]=rk[sa[i-1]]+(x[sa[i]]!=x[sa[i-1]]||y[sa[i]]!=y[sa[i-1]]);
	}
}
int main(){
	scanf("%s",s+1),n=strlen(s+1);
	for (int i=1;i<=n;i++) s[i+n]=s[i];
	n<<=1,getsa();
	for (int i=1;i<=n;i++) if (sa[i]<=n/2) putchar(s[sa[i]+n/2-1]);
	return 0;
}
