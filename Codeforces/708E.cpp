#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1510,mod=1e9+7;
inline int mpow(int a,int b) {int ans=1; for (a=(a+mod)%mod;b;b>>=1,a=(ll)a*a%mod) if (b&1) ans=(ll)ans*a%mod; return ans;}
inline void upd(int& x,int y) {x=x+y-mod;x+=x>>31&mod;}
int fac[100010],ifac[100010];
void genfac(int n){
    fac[0]=1;
    for (int i=1;i<=n;i++) fac[i]=(ll)fac[i-1]*i%mod;
    ifac[n]=mpow(fac[n],mod-2);
    for (int i=n-1;i>=0;i--) ifac[i]=(ll)ifac[i+1]*(i+1)%mod;
}
inline int comb(int n,int r) {
    if (n<0||r<0||n-r<0) return 0;
    return (ll)fac[n]*ifac[r]%mod*ifac[n-r]%mod;
}
int n,m,k,p;
int ps[N],ls[N][N],f[N][N],sum[N][N],pr[N];
int main(){
    int a,b;
    scanf("%d%d%d%d%d",&n,&m,&a,&b,&k);
    p=(ll)a*mpow(b,mod-2)%mod;
    genfac(k);
    for (int i=0;i<=k;i++){
        pr[i]=(ll)comb(k,i)*mpow(p,i)%mod*mpow(1-p,k-i)%mod;
        // cerr<<pr[i]<<endl;
    }
    auto P=[&](int l,int r) {return (ll)pr[l-1]*pr[m-r]%mod;};
    for (int i=1;i<=m;i++){
        ps[i]=0;
        for (int j=1;j<=i;j++) upd(ps[i],P(j,i));
        // cerr<<ps[i]<<endl;
    }
    for (int i=1;i<=m;i++) f[1][i]=ps[i];
    ls[1][0]=0;
    for (int j=1;j<=m;j++){
        ls[1][j]=(ls[1][j-1]+f[1][j])%mod;
    }
    sum[1][0]=0;
    for (int j=1;j<=m;j++){
        sum[1][j]=(sum[1][j-1]+(ll)pr[j-1]*ls[1][j-1]%mod)%mod;
    }
    for (int i=2;i<=n;i++){
        for (int j=1;j<=m;j++){
            f[i][j]=(ll)(ls[i-1][m]-ls[i-1][m-j]+mod)*ps[j]%mod-(ll)pr[m-j]*sum[i-1][j]%mod;
            f[i][j]+=f[i][j]>>31&mod;
        }
        ls[i][0]=0;
        for (int j=1;j<=m;j++){
            ls[i][j]=(ls[i][j-1]+f[i][j])%mod;
        }
        sum[i][0]=0;
        for (int j=1;j<=m;j++){
            sum[i][j]=(sum[i][j-1]+(ll)pr[j-1]*ls[i][j-1]%mod)%mod;
        }
    }
    int ans=0;
    for (int i=1;i<=m;i++) upd(ans,f[n][i]);
    printf("%d\n",ans);
    return 0;
}