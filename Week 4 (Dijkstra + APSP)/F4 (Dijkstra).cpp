#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '{' << x << '}' << '\n';}
#define err2(x, y) {cerr << '(' << x << " " << y << ')' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define err4(x, y, z) {cerr << '(' << x << " " << y << " " << z << ')' << '\n';}
#define mp make_pair
#define pb push_back
#define mt make_tuple
#define long long long
#define double long double
#define pmax (1e9+7)
#define longmax (1e18+7)
#define forn(i, n) for(int i=0; i<n; i++)
#define F first
#define S second

void solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<tuple<int, int, int> > > edge(N);
    vector<vector<int> > trace(N);
    vector<int> dist(N, pmax);
    vector<int> mark(N, 0);
    vector<int> len(M, pmax);
    map<pair<int, int>, int> mymap;
    forn(i, M) {
        int x, y, z;
        cin >> x >> y >> z;
        edge[x].pb(mt(y, z, i));
        edge[y].pb(mt(x, z, i));
        len[i] = z;
        mymap[mp(x, i)] = y;
        mymap[mp(y, i)] = x;

    }
    priority_queue<pair<int, int>,  vector<pair<int, int>  >, greater<pair<int, int>  > > pq;
    pq.push(mp(0, 0));
    dist[0]=0;
    while (pq.size()) {
        pair<int, int> top = pq.top();
        pq.pop();
        int x=top.S;
        forn(i, edge[x].size()) {
            tuple<int, int, int> t = edge[x][i];
            int y = get<0>(t),
            w = get<1>(t),
            z = get<2>(t);
            if (dist[y] > dist[x]+w) {
//                printf("%d %d %d %d %d\n", x, y, dist[y], dist[x]+w, w);
                dist[y] = dist[x]+w;
                pq.push(mp(dist[y], y));
                trace[y].clear();
                trace[y].pb(z);
            } else if (dist[y] == dist[x]+w) {
                if (count(trace[y].begin(), trace[y].end(), z)==0)
                trace[y].pb(z);
            }
        }
    }
//    forn(i, N) {
//        forn(j, trace[i].size()) printf("%d ", trace[i][j]);
//        cout << endl;
//    }
    stack<int> s; s.push(N-1); int res = 0;
    while (s.size() != 0) {
        int x = s.top(); s.pop();
        if (mark[x]) continue;
        mark[x] = 1;
        forn(i, trace[x].size()) {
            res+=len[trace[x][i]];
            s.push(mymap[mp(x, trace[x][i])]);
        }
    }
    cout << res*2 << endl;
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
