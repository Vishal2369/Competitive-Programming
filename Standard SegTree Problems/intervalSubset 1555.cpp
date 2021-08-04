// Problem: E. Boring Segments
// Contest: Codeforces - Educational Codeforces Round 112 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1555/problem/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms

// Code by : Abhishek Tiwari @devil_within
#pragma GCC optimize("Ofast")  
#pragma GCC target("avx,avx2,fma") 

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define all(v) (v).begin(), (v).end()
#define mp make_pair
#define pb push_back
#define pf push_front
#define ff first
#define ss second
#define lcm(a, b) ((a) * (b)) / __gcd(a, b)
#define vt vector<int>
#define pii pair<int, int>
#define ar array
using namespace std;

using namespace __gnu_pbds;
template <class T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// #define int int64_t
using ll = long long int;
using ld = long double;

mt19937 mt_rng(chrono::steady_clock::now().time_since_epoch().count());
ll randint(ll a, ll b)
{
    return uniform_int_distribution<ll>(a, b)(mt_rng);
}

/*******************************************************************************************/
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v);
template <typename T> ostream &operator<<(ostream &os, const set<T> &v);
template <typename T, typename S> ostream &operator<<(ostream &os, const map<T, S> &v);
template <typename T, typename S> ostream &operator<<(ostream &os, const pair<T, S> &v);
template <typename T> inline istream &operator>>(istream &in, vector<T> &a);
/*******************************************************************************************/
// N dimensional Vector, Vec<n , int>
template <int D, typename T> struct Vec : public vector<Vec<D - 1, T>>
{
    static_assert(D >= 1, "Vector dimension must be greater than zero!");
    template <typename... Args> Vec(int n = 0, Args... args) : vector<Vec<D - 1, T>>(n, Vec<D - 1, T>(args...))
    {
    }
};
template <typename T> struct Vec<1, T> : public vector<T>
{
    Vec(int n = 0, const T &val = T()) : vector<T>(n, val)
    {
    }
};
/*******************************************************************************************/
template<typename T>
void __p(T a) { cout << a << " "; }
template<typename T>
void __p(std::vector<T> a) { cout << "{ "; for (auto p : a) __p(p); cout << "}"; }
template<typename T, typename F>
void __p(pair<T, F> a) { cout << "{ "; __p(a.first); __p(a.second); cout << "}"; }
template<typename T, typename ...Arg>
void __p(T a1, Arg ...a) { __p(a1); __p(a...); }
template<typename Arg1>
void __f(const char *name, Arg1 &&arg1) {
    cout<<name<<" : ";__p(arg1);cout<<endl;
}
template<typename Arg1, typename ... Args>
void __f(const char *names, Arg1 &&arg1, Args &&... args) {
    int bracket=0,i=0;
    for(; ;i++)
        if(names[i]==','&&bracket==0)
            break;
        else if(names[i]=='(')
            bracket++;
        else if(names[i]==')')
            bracket--;
    const char *comma=names+i;
    cout.write(names,comma-names)<<" : ";
    __p(arg1);
    cout<<"| ";
    __f(comma+1,args...);
}

#define trace(...) //cout <<"L:"<<__LINE__<<" "; __f(#__VA_ARGS__, __VA_ARGS__)

const ll INF = LONG_LONG_MAX;
const int MOD = 1e9 + 7;

ll fpow(ll b, ll e, ll mod=MOD) {
    ll ans=1; for(;e;b=b*b%mod,e/=2) if(e&1) ans=ans*b%mod; return ans; }

struct node
{
    int sum;
    bool operator == (const node &a) {
        return a.sum == sum;
    }
    void operator = (const node &a) {
        sum = a.sum;
    }
};

struct segTree
{
    
    vector<node> tree;
    vector<bool> clazy;
    vector<int> lazy;
    int n;
    int MAXN;
    
    node OUT_OF_RANGE = { INT_MAX }; // For Range Query Only
    int LAZY_DEFAULT = 0;
    
    void merge(node &cur, node &l, node &r)
    {
        // complete merge here
        if(l == OUT_OF_RANGE ) {
            cur = r;
        } 
        else if(r == OUT_OF_RANGE ) {
            cur = l;
        }
        else {
            cur.sum = min(l.sum , r.sum);
        }
    }

    void propogate(int v, int tl, int tr)
    {
        // complete propogation here
        if (clazy[v] == true)
        {
            if (tl != tr)
            {
                clazy[2 * v] = true;
                clazy[2 * v + 1] = true;
                lazy[2 * v] += lazy[v];
                lazy[2 * v + 1] +=  lazy[v];
            }
            
            tree[v].sum += ( lazy[v] );

            clazy[v] = false;
            lazy[v] = LAZY_DEFAULT;
        }
    }
    void Build(int v, int tl, int tr, vector<int> &a)
    {
        if (tl == tr)
        {
            // complete here
            tree[v].sum = a[tl];
        }
        else
        {
            int tmid = (tl + tr) / 2;
            Build(2 * v, tl, tmid, a);
            Build(2 * v + 1, tmid + 1, tr, a);
            merge(tree[v], tree[2 * v], tree[2 * v + 1]);
        }
    }
    void build(vector<int> &a)
    {
        MAXN = a.size() + 1;
        n = a.size();
        tree.resize(4 * MAXN);
        clazy.assign(4 * MAXN, false);
        lazy.assign( 4 * MAXN, LAZY_DEFAULT);
        Build(1, 0, n - 1 , a);
    }

    void build(int nn ,int init_val)
    {
        vector< int > a(nn , init_val );
        build(a);
    }

    void Update(int v, int tl, int tr, int l, int r, int val)
    {
        if(clazy[v])
            propogate(v, tl, tr);
        if (l > tr || tl > r)
        {
            return;
        }
        if (tl >= l && tr <= r)
        {
            clazy[v] = true;
            lazy[v] = val;
            propogate(v , tl , tr);
        }
        else
        {
            int tmid = (tl + tr) / 2;
            Update(2 * v, tl, tmid, l, r, val);
            Update(2 * v + 1, tmid + 1, tr, l, r, val);
            merge(tree[v], tree[2 * v], tree[2 * v + 1]);
        }
    }

    node Query(int v, int tl, int tr, int l, int r)
    {
        if(clazy[v])
            propogate(v, tl, tr);
        if (l > tr || tl > r)
        {
            // return value out of range
            return OUT_OF_RANGE;
        }
        if (tl >= l && tr <= r)
        {
            return tree[v];
        }
        else
        {
            int tmid = (tl + tr) / 2;
            node cur;
            node left = Query(2 * v, tl, tmid, l, r);
            node right = Query(2 * v + 1, tmid + 1, tr, l, r);
            merge(cur , left , right);
            return cur;
        }
    }
    void pUpdate(int v, int tl, int tr, int idx , int val) {
        if(clazy[v])
            propogate(v , tl , tr);
        if(tl == tr) {
            clazy[v] = true;
            lazy[v] = val;
            propogate(v , tl ,  tr);
            return;
        }
        int tmid = (tl + tr)/2;
        if( idx > tmid )
            pUpdate(2*v + 1 , tmid + 1 , tr , idx , val);
        else 
            pUpdate(2*v ,tl ,tmid ,idx , val);
        merge(tree[v] , tree[2*v] , tree[2*v + 1]);
    }
    
       node pQuery(int v, int tl, int tr , int idx) {
        if(clazy[v])
            propogate(v , tl , tr);
        if(tl == tr)
            return tree[v];
        int tmid = (tl + tr)/2;
        if(idx > tmid ) 
            return pQuery(2*v + 1 , tmid + 1, tr , idx); 
        else 
            return pQuery(2*v , tl , tmid , idx);
    }
//     first index in [l,r] where a[idx]>=k 
//     int get_first(int v, int tl, int tr, int l, int r, int k) {
//     	if(clazy[v])
//     		propogate(v, tl , tr);
//     	if(tree[v].sum < k )
//     		return -1;
//     	if(tr < l || tl > r) 
//     		return -1;	
//     	if(tl == tr){
//     		return tl;
//     	}	
//     	int tmid = (tl + tr)/2;
//     	int res = get_first(2*v, tl, tmid, l, r, k);
//     	if(res != -1) return res;
//     	return get_first(2*v+1, tmid+1, tr, l, r, k);
//     }
//     int get_first(int l , int r, int k){
//     	return get_first(1, 0, n-1, l , r, k);
//     }
    
//     int kthOne(int v, int tl , int tr, int k) {  
//     	if(clazy[v]) 	
//     		propogate(v ,tl , tr);
//     	if(tree[v].sum < k)  // does not exist
//     		return -1;
//     	if(tl == tr) 
//     		return tl;
//     	int tmid = (tl + tr)/2;
//     	if(tree[2*v].sum < k) 
//     		return kthOne(2*v + 1 , tmid + 1 , tr , k - tree[2*v].sum); 
//     	else 
//     		return kthOne(2*v , tl , tmid , k);
//     }
//     int KthOne(int k) {
//     	return kthOne(1 , 0 , n-1 , k);
//     }
	
    void update(int l, int r, int v)
    {
        Update(1, 0, n - 1, l, r, v);
    }
    void update(int idx , int val) {
        pUpdate(1 , 0 , n-1 , idx , val);
    }
    node query(int l, int r)
    {
        return Query(1, 0, n - 1, l, r);
    }
    node query(int idx) {
        return pQuery(1 , 0 , n-1 , idx);
    }
};
const int NAX = 1e6 + 10;
void solve()
{
	int n, m;
	cin >> n >> m;
	Vec<2,int> a(n, 3);
	cin >> a;
	sort(all(a) , [&](auto a, auto b) {
		if(a[2] == b[2])
			return a[0]!=b[0] ? a[0] < b[0] : a[1] < b[1];
		return a[2] < b[2];
	}); // sort by wt, start, end
	// cout << a;
	/*
	fix a minimum w, to minimize ans we need max w s.t. a path from 1-m exixts
	2 pointer + segTree
	
	tree leaf stores number of segments that cover the node i
	*/
	segTree tree;
	tree.build( NAX , 0);
	int ans = INT_MAX;
	int i = 0, j = 0;
	multiset<int> wset;
	
	while(i < n) {
		while(j < n && tree.query(1, m-1).sum == 0) {
			tree.update(a[j][0], a[j][1]-1, 1); //ins
			wset.insert(a[j][2]);
			++j;
		}
		trace(i, j, tree.query(1,m-1).sum);
		if(tree.query(1,m-1).sum > 0) {
			int cur = *wset.rbegin() - *wset.begin();
			trace(cur);
			ans = min(ans, cur);
		}
		
		// erase i
		tree.update(a[i][0], a[i][1]-1, -1);
		wset.erase(wset.find(a[i][2]));
		++i;		
	} 
	cout << ans << "\n";
}

signed main()
{
    // freopen("input.txt" , "r" , stdin);freopen("output.txt" , "w" ,stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout << fixed << setprecision(12);
    int T = 1;
    // cin >> T;
    for (int tc = 1; tc <= T; ++tc)
    {
        // cout << "Case #"<<tc<<": \n";
        solve();
    }
}

// Functions

template <typename T> ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "[";
    for (int i = 0; i < (int)v.size(); ++i)
    {
        if (i)
            os << ", ";
        os << v[i];
    }
    os << "]\n";
    return os;
}
template <typename T> ostream &operator<<(ostream &os, const set<T> &v)
{
    os << "{";
    for (auto it : v)
    {
        os << it;
        if (it != *v.rbegin())
            os << ", ";
    }
    os << "}\n";
    return os;
}
template <typename T, typename S> ostream &operator<<(ostream &os, const map<T, S> &v)
{
    os << "{";
    for (auto it : v)
    {
        os << "(" << it.first << " : " << it.second << ")";
        if (it != *v.rbegin())
            os << ", ";
    }
    os << "}\n";
    return os;
}
template <typename T, typename S> ostream &operator<<(ostream &os, const pair<T, S> &v)
{
    os << "(";
    os << v.first << ", " << v.second << ")";
    return os;
}
template <typename T> inline istream &operator>>(istream &in, vector<T> &a)
{
    for (auto &x : a)
        in >> x;
    return in;
}
