#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define mp make_pair
#define pb push_back
#define long long long
#define LONGMAX 1e9+7

void solve() {
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<pair<pair<int, int>, long> > > graph(N);
    vector<int> path;
    for (int i = 0; i < K; i++) {
        int x; cin >> x;
        x--;
        path.pb(x);
    }
    for (int i=0; i<M; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        x--;
        y--;
        graph[x].push_back(make_pair(mp(y, i), z));
        graph[y].push_back(make_pair(mp(x, i), z));
    }
    vector<long> dist(N, LONGMAX), trace(N);
    dist[0]=0;
    priority_queue<pair<long, int>, vector<pair<long, int> >, greater<pair<long, int> > > pq;
    pq.push(make_pair(0, 0));
    while (pq.size()) {
        pair<long, int> top = pq.top(); pq.pop();
        int x = top.second;
        for (int i=0; i < graph[x].size(); i++) {
            pair<pair<int, int>, long> next = graph[x][i];
            int y = next.first.first;
            long d = next.second;
            if (dist[x]+d < dist[y]) {
                dist[y] = dist[x]+d;
                trace[y] = next.first.second;
                pq.push(make_pair(dist[y], y));
            }
        }
    }
    for (int i=1; i < K; i++) {
        int y = path[i];
        for (int j=0; j<graph[y].size(); j++) {
            int x = graph[y][j].first.first, t = graph[y][j].first.second;
            long d = graph[y][j].second;
            if (t != trace[y]) {
                if (dist[x]+d == dist[y]) {
                    cout << "yes\n";
                    return;
                }
            }
        }

    }
    cout << "no\n";
}

int main() {
//	freopen("1.in", "r", stdin);
	ios::sync_with_stdio(false);
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
