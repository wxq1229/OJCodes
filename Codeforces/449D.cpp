#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
inline int mpow(int a,int b){int ans=1; for (;b;b>>=1,a=(ll)a*a%mod) if (b&1) ans=(ll)ans*a%mod; return ans;}
void upd(int &x,int y) {x=x+y-mod;x+=x>>31&mod;}
void fwt(int *f,int n,int flg){
    for (int len=2;len<=n;len<<=1){
        int k=len>>1;
        for (int i=0;i<n;i+=len)
            for (int j=i;j<i+k;j++) upd(f[j],flg==1?f[j+k]:mod-f[j+k]);
    }
}
const int N=1e6+10;
int n,a[N];
int A[1<<23];
int main(){
    scanf("%d",&n);
    int mx=0;
    for (int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        ++A[a[i]];
        mx=max(mx,a[i]);
    }
    int lim=2;
    while (lim<=mx) lim<<=1;
    for (int len=2;len<=lim;len<<=1){
        int k=len>>1;
        for (int i=0;i<lim;i+=len)
            for (int j=i;j<i+k;j++) A[j]=(A[j]+A[j+k])%(mod-1);
    }
    for (int i=0;i<lim;i++) A[i]=mpow(2,A[i]);
    fwt(A,lim,-1);
    printf("%d\n",A[0]);
    return 0;
}