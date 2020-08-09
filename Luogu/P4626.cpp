#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=100000007,N=1e8+10;
bool vis[N];
int ps[N/10],pn;
int n;
int main(){
    scanf("%d",&n);
    int ans=1;
    for (int i=2;i<=n;i++){
        if (!vis[i]){
            ps[++pn]=i;
            int pw=1;
            while ((ll)pw*i<=n) pw*=i;
            ans=(ll)ans*pw%mod;
        }
        for (int j=1;j<=pn&&i*ps[j]<=n;j++){
            vis[i*ps[j]]=1;
            if (i%ps[j]==0) break;
        }
    }
    printf("%d\n",ans);
    return 0;
}