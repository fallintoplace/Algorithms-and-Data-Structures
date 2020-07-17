#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define FOR(i, N) for (int i=0; i<N; i++)
#define mp make_pair
#define pb push_back
#define MAX 1e9+7
#define long long long

void solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, long> > > graph(N);
    for (int i=0; i<M; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        x--;
        y--;
        graph[x].push_back(make_pair(y, z));
        graph[y].push_back(make_pair(x, z));
    }
    vector<long> dist(N, INT_MAX);
    dist[0]=0;
    priority_queue<pair<long, int>, vector<pair<long, int> >, greater<pair<long, int> > > pq;
    pq.push(make_pair(0, 0));
    while (pq.size()) {
        pair<long, int> top = pq.top(); pq.pop();
        int x = top.second;
        for (int i = 0; i < graph[x].size(); i++) {
            pair<int, long> next = graph[x][i];
            int y = next.first, d = next.second;
            if (dist[x]+d < dist[y]) {
                dist[y] = dist[x]+d;
                pq.push(make_pair(dist[y], y));
            }
        }
    }
    cout << dist[N-1] << '\n';
}

int main() {
//	freopen("2.in", "r", stdin);
	ios::sync_with_stdio(false);
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
