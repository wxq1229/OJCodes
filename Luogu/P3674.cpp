#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for (int i=(int)(a); i<=(int)(b); i++)
#define per(i,a,b) for (int i=(int)(a); i>=(int)(b); i--)

const int N = 1e5+10;
int a[N], bl[N];

struct Query{
	int l, r, x, opt, id;
} q[N];

int cmp(Query a, Query b){
	if (bl[a.l] == bl[b.l])
		return (bl[a.l]&1) ? a.r < b.r : a.r > b.r;
	else return bl[a.l] < bl[b.l];
}

bitset<N> s;
bitset<N * 2> sp, sn;
int cnt[N];

void add(int i){
	cnt[a[i]]++;
	if (cnt[a[i]] > 0) s[a[i]] = 1, sp[a[i] + N] = sn[-a[i] + N] = 1;
}

void del(int i){
	cnt[a[i]]--;
	if (cnt[a[i]] <= 0) s[a[i]] = 0, sp[a[i] + N] = sn[-a[i] + N] = 0;
}

int ans[N];

int main(){
	int n, m; scanf("%d%d", &n, &m);
	const int T = sqrt(n);
	rep(i,1,n) scanf("%d",&a[i]), bl[i] = (i-1) / T + 1;
	rep(i,1,m) scanf("%d%d%d%d", &q[i].opt, &q[i].l, &q[i].r, &q[i].x), q[i].id = i;
	sort(q+1, q+m+1, cmp);
//	rep(i,1,m) printf("%d\n", q[i].id); puts("");
	int l = 1, r = 0;
	rep(i,1,m){
		while (r < q[i].r) add(++r);
		while (r > q[i].r) del(r--);
		while (l > q[i].l) add(--l);
		while (l < q[i].l) del(l++);
		if (q[i].opt==1)
			ans[q[i].id] = (s & (s<<q[i].x)).any();
		else if (q[i].opt==2)
			ans[q[i].id] = (sp & (sn<<q[i].x)).any();
		else if (q[i].opt==3){
			int found = 0; 
			for (int j = 1; j*j <= q[i].x; j++)
				if (q[i].x%j == 0){
					if (s[j] && s[q[i].x / j]) {
						found = 1; break;
					}
				}
			ans[q[i].id] = found;
		}
	}
	rep(i,1,m) puts(ans[i] ? "hana" : "bi");
	return 0;
}








