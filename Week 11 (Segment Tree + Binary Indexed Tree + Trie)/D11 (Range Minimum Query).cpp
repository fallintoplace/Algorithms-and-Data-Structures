#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define long long long
#define double long double
#define pmax (1e9+7)
#define longmax (1e18+7)
#define forn(i, n) for(int i=0; i<n; i++)

int parent[20][5001];

void solve() {
    int N;
    cin >> N;
    vector<vector<int> > edge(N);
    vector<int> height(N);
//    height[5000]=5000;
//    for (int i=0; i<15; i++) forn(j, N) parent[i][j]=5000;
    forn(i, N) {
        int c;
        cin >> c;
        forn(j, c) {
            int y;
            cin >> y; y--;
            edge[i].pb(y);
        }
    }
    stack<int> st;
    st.push(0);
    while (st.size()) {
        int x=st.top(); st.pop();
        forn(j, edge[x].size()) {
            int y=edge[x][j];
            st.push(y);
            height[y]=height[x]+1;
            parent[0][y]=x;
        }
    }

    int layer=0;
    for(int i=1; (1<<(i-1))<=N; i++) forn(j, N) {
        parent[i][j]=parent[i-1][parent[i-1][j]];
        layer=i;
    }
    int Q;
    cin >> Q;
    vector<int> query;
    query.pb(0);
    forn(i, Q) {
        int x;
        cin >> x;
        x--;
        query.pb(x);
    }
    int ans=0;
    forn(i, Q) {
        int x=query[i], y=query[i+1];
        if (x==y) continue;
        if (height[x]<height[y]) swap(x, y);
        for (int j=layer; j>=0; j--) {
            if (height[parent[j][x]]>height[y]) {
                x=parent[j][x];
                ans+=(1<<j);
            }
        }
        if (height[x]>height[y]) {
            x=parent[0][x];
            ans++;
        }
        assert(height[x]==height[y]);
        if (x==y) continue;
        for (int j=layer; j>=0; j--) {
            if (parent[j][x]!=parent[j][y]) {
                x=parent[j][x];
                y=parent[j][y];
                ans+=(1<<(j+1));
            }
        }
        assert(parent[0][x]==parent[0][y]);
        if (x!=y) ans+=2;

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
