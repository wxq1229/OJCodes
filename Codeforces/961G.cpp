#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7,N=2e5+10;
inline int mpow(int a,int b){int ans=1; for (;b;b>>=1,a=(ll)a*a%mod) if (b&1) ans=(ll)ans*a%mod; return ans;}
int fac[N],ifac[N];
void fac_init(int n){
    fac[0]=1;
    for (int i=1;i<=n;i++) fac[i]=(ll)fac[i-1]*i%mod;
    ifac[n]=mpow(fac[n],mod-2);
    for (int i=n-1;i>=0;i--) ifac[i]=(ll)ifac[i+1]*(i+1)%mod;
}
int C(int n,int r){
    if (r<0||n<0||n-r<0) return 0;
    return (ll)fac[n]*ifac[n-r]%mod*ifac[r]%mod;
}
int S(int n,int m){
    int ans=0;
    for (int i=0;i<=m;i++){
        ans+=(ll)((m-i)&1?mod-1:1)*C(m,i)%mod*mpow(i,n)%mod-mod;
        ans+=ans>>31&mod;
    }
    return (ll)ans*ifac[m]%mod;
}
int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    fac_init(max(n,k));
    int sw=0;
    for (int i=1;i<=n;i++){
        int w;scanf("%d",&w);
        sw=(sw+w)%mod;
    }
    printf("%d\n",(ll)sw*(S(n,k)+(ll)(n-1)*S(n-1,k)%mod)%mod);
    return 0;
}