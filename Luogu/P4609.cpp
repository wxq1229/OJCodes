#include <bits/stdc++.h>
using namespace std;
const int N=50010,P=1e9+7;
inline int add(int x,int y){return (x+=y)>=P?x-P:x;}
inline int sub(int x,int y){return (x-=y)<0?x+P:x;}
int s[N][310],C[310][310];
int main()
{
    s[0][0]=1;
    for(int i=1;i<=50000;i++)
        for(int j=1;j<=min(i,200);j++)
            s[i][j]=add(1ll*s[i-1][j]*(i-1)%P,s[i-1][j-1]);
    C[0][0]=1;
    for(int i=1;i<=200;i++)
    {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++) 
            C[i][j]=add(C[i-1][j],C[i-1][j-1]);
    }
    // cout<<"Finish\n";
    int _;scanf("%d",&_);while(_--)
    {
        int n,A,B; scanf("%d%d%d",&n,&A,&B);
        printf("%d\n",1ll*s[n-1][A+B-2]*C[A+B-2][A-1]%P);
    }
    return 0;
}