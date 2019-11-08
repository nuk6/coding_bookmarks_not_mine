// Q: https://codeforces.com/contest/924/F

#include<bits/stdc++.h>
#define ll long long
typedef std::pair<unsigned ll,unsigned>set;
const ll MAX=1000000000000000000ll;
int tot[20],to[20][12300][10],rev[10][1<<10];
std::map<set,int>M[20];
int abs(int x){return x<0?-x:x;}
int init(int i,set s){
	if(!s.first&&!s.second)return-1; if(!i){ while(i<10&&!(s.first>>i&1))i++; return i; }
	if(M[i].count(s))return M[i][s];
	int o=M[i][s]=tot[i]++,l=i*9+1;
	for(int x=0;x<10;x++){
		set t=x?std::make_pair(s.first<<x|s.first>>x|(unsigned ll)(s.second<<32-x)<<32|rev[x][s.first&(1<<x)-1],unsigned(s.first>>64-x|s.second<<x|s.second>>x)):s;
		if(l<64)t.first&=(1ull<<l)-1,t.second=0; else if(l<96)t.second&=(1u<<l-64)-1; to[i][o][x]=init(i-1,t);
	}
	return o;
}
ll f[10][20][12300];
ll dfs(int k,int i,int o){if(o<0)return 0;if(!i)return o<=k; if(f[k][i][o])return f[k][i][o]-1; for(int x=0;x<10;x++)f[k][i][o]+=dfs(k,i-1,to[i][o][x]); return f[k][i][o]++;}
ll cal(ll r,int k){
	ll s=0; int d[20],l=0,o=0; if(r>MAX)k?s++:1,r--; while(r)d[l++]=r%10,r/=10;
	while(l--&&o>-1){ for(int x=0;x<d[l];x++)s+=dfs(k,l,to[l+1][o][x]); o=to[l+1][o][d[l]]; }
	return s;
}
int main(){
	int q;scanf("%d",&q);
	for(int i=1;i<10;i++) for(int s=1;s<1<<i;s++)rev[i][s]=rev[i-1][s>>1]|(s&1)<<i;
	init(18,std::make_pair(1ull,0u));
	while(q--){ ll l,r;int k; scanf("%lld%lld%d",&l,&r,&k); printf("%lld\n",cal(r+1,k)-cal(l,k)); }
}
