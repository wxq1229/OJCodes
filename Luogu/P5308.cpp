 #include <bits/stdc++.h>
using namespace std;
typedef double db;
const db eps=1e-12;
inline int sign(db a){return a<-eps?-1:a>eps;}
const int N=1e5+10;
int n,k;
db dp[N];
inline db X(int i) {return i;}
inline db Y(int i) {return dp[i];}
inline db slope(int i,int j){
	assert(X(i)<X(j));
	return 1.0*(Y(j)-Y(i))/(X(j)-X(i));
}
int q[N],ql,qr,cnt[N];
int calc(db mid){
//	cerr<<"mid = "<<mid<<endl;
	cnt[0]=dp[0]=0;
	q[ql=qr=1]=0;
	for (int i=1;i<=n;i++){
		while (ql<qr&&sign(slope(q[ql],q[ql+1])-1.0/i)>=0) ++ql;
		int j=q[ql];
		cnt[i]=cnt[j]+1;
		dp[i]=dp[j]-mid+1.0*(i-j)/i;
		while (ql<qr&&sign(slope(q[qr-1],q[qr])-slope(q[qr-1],i))<=0) --qr;
		q[++qr]=i;
	}
//	cerr<<"DP[n] = "<<dp[n]<<endl;
//	cerr<<"DP:\n";
//	for (int i=0;i<=n;i++) cerr<<dp[i]<<" ";cerr<<endl;
//	cerr<<cnt[n]<<endl;
	return cnt[n];
}
int main(){
    scanf("%d%d",&n,&k);
	db lo=-1e6,hi=1e6;
    while (lo+eps<hi){
		db mid=(lo+hi)/2.0;
		if (calc(mid)>=k) lo=mid;
		else hi=mid;
    }
//	cerr<<lo<<endl;
	calc(lo);
//	cerr<<dp[n]<<endl;
	printf("%.9f\n",dp[n]+lo*k);
	return 0;
}
