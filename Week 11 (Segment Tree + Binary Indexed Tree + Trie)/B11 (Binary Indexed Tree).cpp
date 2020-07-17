#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define int long long
#define double long double
#define pmax (1e9+7)
#define longmax (1e18+7)
#define forn(i, n) for(int i=0; i<n; i++)

vector<int> B1, B2;
int N;

inline void add(vector<int> &b, int idx, int x) {
    while (idx<=N) {
        b[idx]+=x;
        idx+=idx&-idx;
    }
}

inline void rangeAdd(int l, int r, int x) {
    add(B1, l, x);
    add(B1, r+1, -x);
    add(B2, l, x*(l-1));
    add(B2, r+1, -x*r);
}

inline int sum(const vector<int> &b, int idx) {
    int total=0;
    while (idx>0) {
        total+=b[idx];
        idx-=idx&-idx;
    }
    return total;
}

inline int prefixSum(int idx) {
    return sum(B1, idx)*idx-sum(B2, idx);
}

int rangeSum(int l, int r) {
    return prefixSum(r)-prefixSum(l-1);
}

void solve() {
    int K;
    cin >> N >> K;

    B1=vector<int>(N+1);
    B2=vector<int>(N+1);
    int ans=0;
    forn(i, K) {
        char c;
        cin >> c;
        if (c=='i') {
            int u, v, w;
            cin >> u >> v >> w;
            rangeAdd(u, v, w);
        } else {
            int u;
            cin >> u;
            ans=(ans+rangeSum(u, u))%(1000000000+7);
        }
    }
    cout << ans << endl;
}

main() {
//	freopen("1.in", "r", stdin);
	ios::sync_with_stdio(false);
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
