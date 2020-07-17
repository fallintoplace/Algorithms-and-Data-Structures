#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define FOR(i, N) for (int i=0; i<N; i++)
#define mp make_pair
#define pb push_back
#define int long long
#define MAX 1e12+7

void solve() {
    int N, M, A, B, S;
    cin >> N >> M >> S >> A >> B;
    A--; B--;
    vector<vector<pair<int, int> > > graph(N);
    for (int i=0; i<M; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        x--; y--;
        graph[x].pb(mp(z, y));
        graph[y].pb(mp(z, x));
    }
    vector<int> sup(N, MAX);
    FOR(i, S) {
        int x, s;
        cin >> x >> s;
        x--;
        sup[x]=s;
    }
    priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > pq;
    pq.push(mp(0, mp(A, 0)));
    vector<vector<int> > dist(N, vector<int>(2, MAX));
    vector<vector<bool> > marked(N, vector<bool>(2, false));
    dist[A][0] = 0;
    while (pq.size()) {
        pair<int, pair<int, int> > top = pq.top(); pq.pop();
        int x = top.second.first, s = top.second.second;
//        if (marked[x][s]) continue;
//        marked[x][s]=true;
        FOR(i, graph[x].size()) {
            int y = graph[x][i].second, w = graph[x][i].first;
            if (dist[y][s] > dist[x][s]+w) {
                dist[y][s] = dist[x][s]+w;
                pq.push(mp(dist[y][s], mp(y, s)));
            }
        }
        if (sup[x] != MAX && s == 0) {
            if (dist[x][1] > dist[x][0]+sup[x]) {
                dist[x][1] = dist[x][0]+sup[x];
                pq.push(mp(dist[x][1], mp(x, 1)));
            }
        }
    }
    if (dist[B][1]==MAX) cout << "impossible\n";
    else {
        cout << dist[B][1]/60 << ":";
        int x=dist[B][1]%60;
        cout << setfill('0') << setw(2) << x << "\n";
    }
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
