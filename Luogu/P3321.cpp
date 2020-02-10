#include <bits/stdc++.h>
using namespace std;
const int N=20100,P=1004535809,gen=3,igen=334845270;
inline int add(int x,int y,int mod=P){
	return x+y>=mod?x+y-mod:x+y;
}
inline int sub(int x,int y,int mod=P){
	return x-y<0?x-y+mod:x-y;
}
inline int fpow(int x,int y,int mod=P){
	int ret=1; for(x%=mod;y;y>>=1,x=1ll*x*x%mod)
		if(y&1) ret=1ll*ret*x%mod;
	return ret;
}
int rev[N];
void init(int n){
	for(int i=0;i<n;i++)
		rev[i]=rev[i>>1]>>1|((i&1)?n>>1:0);
}
void ntt(int *f,int n,int flg){
	for(int i=0;i<n;i++) if(rev[i]<i) swap(f[i],f[rev[i]]);
	for(int len=2,k=1;len<=n;len<<=1,k<<=1){
		int wn=fpow(flg==1?gen:igen,(P-1)/len);
		for(int i=0;i<n;i+=len){
			for(int w=1,j=i;j<i+k;j++,w=1ll*w*wn%P){
				int tmp=1ll*f[j+k]*w%P;
				f[j+k]=sub(f[j],tmp),f[j]=add(f[j],tmp);
			}
		}
	}
	if(flg==-1){
		int inv=fpow(n,P-2);
		for(int i=0;i<n;i++) f[i]=1ll*f[i]*inv%P;
	}
}
int limit,m,n,X,C;
void mult(int *f,int *g){
	static int F[N],G[N];
	for(int i=0;i<m-1;i++) F[i]=f[i],G[i]=g[i];
	for(int i=m-1;i<limit;i++) F[i]=G[i]=0;
	ntt(F,limit,1),ntt(G,limit,1);
	for(int i=0;i<limit;i++) F[i]=1ll*F[i]*G[i]%P;
	ntt(F,limit,-1);
	for(int i=0;i<m-1;i++) f[i]=add(F[i],F[i+m-1]);
}

int chk(int g){
	for(int i=2;i*i<=m-1;i++)
		if((m-1)%i==0&&(fpow(g,i,m)==1||fpow(g,(m-1)/i,m)==1)) return 0;
	return 1;
}
int getG(){
	for(int i=2;;i++) if(chk(i))return i;
}
map<int,int> id;
void getans(int *f,int n,int *ans){
	for(ans[id[1]]=1;n;n>>=1,mult(f,f))
		if(n&1) mult(ans,f);
}
int f[N],ans[N];
int main(){
	scanf("%d%d%d%d",&n,&m,&X,&C);
	limit=1; while(limit<=m*2)limit<<=1; init(limit);
	int g=getG();
	for(int i=0;i<m-1;i++)id[fpow(g,i,m)]=i;
	for(int i=1;i<=C;i++){
		int x; scanf("%d",&x),x%=m;
		if(x) f[id[x]]=1;
	}
//	for(int i=0;i<m-1;i++) cout<<f[i]<<" "; cout<<endl;
	getans(f,n,ans);
	printf("%d\n",ans[id[X]]);
	return 0;
}
