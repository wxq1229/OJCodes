#include <bits/stdc++.h>
using namespace std;
const int P=1e9+7,N=5010;
inline int fpow(int x,int y)
{
    int ret=1; for(x%=P;y;y>>=1,x=1ll*x*x%P)
        if(y&1) ret=1ll*ret*x%P;
    return ret;
}
inline int add(int x,int y){return (x+=y)>=P?x-P:x;}
inline int sub(int x,int y){return (x-=y)<0?x+P:x;}
int S[N][N],dwn[N],n,k;
int main()
{
    scanf("%d%d",&n,&k);
    dwn[0]=1; for(int i=1;i<=k;i++) dwn[i]=1ll*dwn[i-1]*(n-i+1)%P;
    S[0][0]=1; for(int i=1;i<=k;i++)
        for(int j=1;j<=i;j++)
            S[i][j]=add(S[i-1][j-1],1ll*j*S[i-1][j]%P);
    int ans=0,pw2=fpow(2,n),i2=fpow(2,P-2);
    for(int j=0;j<=k;j++,pw2=1ll*pw2*i2%P)
        ans=add(ans,1ll*S[k][j]*dwn[j]%P*pw2%P);
    printf("%d\n",ans);
    return 0;
}