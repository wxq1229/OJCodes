#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
const int N=1010;
const int NONE=0x3f3f3f3f;
typedef pair<int,int> pii;
string code[N][4];
int n;
inline string to_str(int x){
	string ret="";
	while(x)ret=(char)(x%10+48)+ret,x/=10;
	return ret;
}
struct OT{
	int bs,e;
	inline string to_str(){
		if(bs==0)return "O(1)";
		else return "O(n^"+::to_str(e)+")";
	}
	OT(){}
	OT(string s){
		if(s=="O(1)")bs=0;
		else{
			int n=s.size(),p=s.find('^');
			int tmp=0;
			rep(i,p+1,n-1)if(s[i]!=')')tmp=tmp*10+s[i]-'0'; else break;
			bs=1,e=tmp;
		}
	}
}tim;
string Std;
int checkVal(){
	stack<string>val;
	map<string,int>vis;
	rep(i,1,n){
		if(code[i][0]=="E")vis[val.top()]=0,val.pop();
		else{
			string name=code[i][1];
			if(vis[name])return 0;
			vis[name]=1;
			val.push(name);
		}
	}
	return 1;
}
int checkLR(){
	int t1=0,t2=0;
	int top=0;
	rep(i,1,n){
		if(code[i][0]=="F")++top;
		else{
			if(!top)return 0;
			top--;
		}
	}
	return top==0;
}
inline int check(){return checkLR()&&checkVal();}
inline int getE(pii seg){
	if(seg.fi==NONE&&seg.se!=NONE)return 0;
	else if(seg.fi!=NONE&&seg.se!=NONE) return 0;
	else if(seg.fi==NONE&&seg.se==NONE)return 0;
	else return 1;
}
inline int chk0(pii seg){
	if(seg.fi==NONE&&seg.se!=NONE)return 1;
	else if(seg.fi!=NONE&&seg.se!=NONE&&seg.fi>seg.se)return 1;
	else return 0;
}
inline int to_int(string s){
	int tmp=0;
	rep(i,0,s.size()-1)tmp=tmp*10+s[i]-'0';
	return tmp;
}
inline pii get(string bg,string ed){
	int l,r;
	if(bg=="n")l=NONE; else l=to_int(bg);
	if(ed=="n")r=NONE; else r=to_int(ed);
	return mp(l,r);
}
OT getTim(){
	OT ret;
	ret.bs=0,ret.e=0;
	int nwE=0;
	stack<pii> lr;
	stack<int> t;
	int has=0;
	rep(i,1,n){
		if(code[i][0]=="E"){
			if(chk0(lr.top()))has--;
			nwE-=t.top(),lr.pop(),t.pop();
		}else{
			pii nw=get(code[i][2],code[i][3]);
			nwE+=has?0:getE(nw);
			if(chk0(nw))++has;
			lr.push(nw),t.push(has?0:getE(nw));
		}
//		cout<<"LINE "<<i<<": "<<nwE<<endl;
		ret.e=max(ret.e,nwE);
	}
	if(ret.e)ret.bs=1;
	return ret;
}
void solve(){
	cin>>n>>Std;
	rep(i,1,n){
		cin>>code[i][0];
		if(code[i][0]=="F")cin>>code[i][1]>>code[i][2]>>code[i][3];
	}
	if(!check())puts("ERR");
	else{
		tim=getTim();
//		cout<<tim.to_str()<<endl;
		if(tim.to_str()==Std)puts("Yes");
		else puts("No");
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T; cin>>T; while(T--)solve();
	return 0;
}
