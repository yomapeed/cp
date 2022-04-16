       
   //                                                  '-.-'
   //                                         ()      __.'.__
   //                                      .-:--:-.  |_______|
   //                               ()      \____/    \=====/
   //                               /\      {====}     )___(
   //                    (\=,      //\\      )__(     /_____\
   //    __    |'-'-'|  //  .\    (    )    /____\     |   |
   //   /  \   |_____| (( \_  \    )__(      |  |      |   |
   //   \__/    |===|   ))  `\_)  /____\     |  |      |   |
   //  /____\   |   |  (/     \    |  |      |  |      |   |
   //   |  |    |   |   | _.-'|    |  |      |  |      |   |
   //   |__|    )___(    )___(    /____\    /____\    /_____\
   //  (====)  (=====)  (=====)  (======)  (======)  (=======)
   //  }===={  }====={  }====={  }======{  }======{  }======={
   // (______)(_______)(_______)(________)(________)(_________)
   //
   // Credits :- Joan G. Stark
   //|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
   //|                      AUTHOR - KASPAROVIAN                                     |
   //|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define frr(i,n) for(int i=0;i<(n);i++)
#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(),(v).end()
#define fr first
#define sc second
#define mk make_pair
#define endl '\n'
#define MOD 1000000007
#define in insert
#define sz(x) (ll)(x).size()
#define mem(a,b) memset(a,b,sizeof(a))
// #define int long long
#define runtime() ((double)clock() / CLOCKS_PER_SEC) 
#define fast ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
#define TRACE 
  
#ifdef TRACE 
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__) 
template <typename Arg1> 
void __f(const char* name, Arg1&& arg1){ 
    cerr << name << " : " << arg1 << endl; 
} 
template <typename Arg1, typename... Args> 
void __f(const char* names, Arg1&& arg1, Args&&... args){ 
    const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...); 
} 
#else 
#define trace(...) 
#endif 
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double ld;
typedef pair<ll,ll> pl;
typedef pair<int,int> pi;
typedef pair<int,pi> ppi;
typedef vector<vi> graph;
template<class T> void mxi(T & a, const T & b) { a = max(a, b); }
template<class T> void mni(T & a, const T & b) { a = min(a, b); }
ld EPS=1e-9;
mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count());  
#define SHUF(v) shuffle(all(v), RNG); 
// Use mt19937_64 for 64 bit random numbers. 
const int SZ=1e9+100;
struct node
{
	int cnt,lazy; node *c[2];
	node()
	{
		cnt=lazy=0;
		c[0]=c[1]=NULL;
	}
	#define mid ((l+r)>>1)
	void push(int l,int r)
	{
		if(lazy)
		{
			cnt=r-l+1;
			if(l!=r)
			{
				frr(i,2)
				{
					if(!c[i])c[i]=new node();
					c[i]->lazy=1;
				}
				c[0]->cnt=mid-l+1;
				c[1]->cnt=r-mid;
			}
		}
		lazy=0;
	}
	void upd(int lq,int rq,int l=0,int r=SZ-1)
	{
		push(l,r);
		if(lq<=l&&rq>=r)
		{

			lazy=1; push(l,r); return;
		}
		if(rq<=mid)
		{
			if(!c[0])c[0]=new node();
			c[0]->upd(lq,rq,l,mid);
		}
		else if(lq>=mid+1)
		{
			if(!c[1])c[1]=new node();
			c[1]->upd(lq,rq,mid+1,r);
		}
		else
		{
			frr(i,2)
			{
				if(!c[i])c[i]=new node();
			}
			c[0]->upd(lq,rq,l,mid);
			c[1]->upd(lq,rq,mid+1,r);
		}
		cnt=0;
		frr(i,2)if(c[i])cnt+=c[i]->cnt;
	}
	int qu(int lq,int rq,int l=0,int r=SZ-1)
	{
		push(l,r);
		if(rq<l||r<lq)return 0;
		else if(lq<=l&&rq>=r)
		{
			return cnt;
		}
		int ans=0;
		if(c[0])ans+=c[0]->qu(lq,rq,l,mid);
		if(c[1])ans+=c[1]->qu(lq,rq,mid+1,r);
		return ans;
	}
};
void solve()
{
  int q,c=0; cin>>q;
  node Seg;
  while(q--)
  {
  	int d,x,y; cin>>d>>x>>y;
  	if(d==1)
  	{
  		int ans=Seg.qu(x+c,y+c);
  		c=ans;
  		cout<<ans<<endl;
  	}
  	else
  	{
  		Seg.upd(x+c,y+c);
  	}
  }
}
signed main()
{
  fast;
  int t,tab;
  t=1;
  tab=t;
  while(t--)
  {
    //cout<<"Case #"<<(tab-t)<<": ";
    solve();
  }
  cerr<<runtime();
}
//APPROACHING A QUESTION
//+ Think of binary search (max of min etc also if n<=2*10^5)
//+ Think of common dp states (Even if it appears as maths but constraints are small)
//+ Check constraints
//+ Keep calm and enjoy the question
//+ Be sure to remove MOD from binpow (if needed)
//+ Try bidirectional analysis for constructive questions
//+ If given some sequence try thinking of prefix sums
//+ If constraints are too large maybe its simple maths
//+ In questions with binary operations think of bits independently and also the change pattern
//+ If two or more binary operations are given mostly there is a relation between them and an arithmatic operator