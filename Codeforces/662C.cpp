#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void fwt(ll *f,int n,int flg){
    for (int len=2;len<=n;len<<=1){
        int k=len>>1;
        for (int i=0;i<n;i+=len)
            for (int j=i;j<i+k;j++){
                ll x=f[j],y=f[j+k];
                f[j]=x+y,f[j+k]=x-y;
                if (flg==-1) f[j]>>=1,f[j+k]>>=1;
            }
    }   
}
char s[23][100010];
ll A[1<<21],B[1<<21];
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%s",s[i]+1);
    for (int j=1;j<=m;j++){
        int x=0;
        for (int i=1;i<=n;i++) x=x<<1|(s[i][j]=='1');
        ++A[x];
    }
    for (int i=0;i<(1<<n);i++){
        int k=__builtin_popcount(i);
        B[i]=min(k,n-k);
    }
    fwt(A,1<<n,1),fwt(B,1<<n,1);
    for (int i=0;i<(1<<n);i++) A[i]*=B[i];
    fwt(A,1<<n,-1);
    ll ans=0x3f3f3f3f3f3f3f3f;
    for (int i=0;i<(1<<n);i++) ans=min(ans,A[i]);
    printf("%lld\n",ans);
    return 0;
}