#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}


void solve() {
    int N, M, K, L;
    cin >> N >> M >> K >> L;
    priority_queue<pair<int, int> > pq;
    vector<vector<pair<int, int> > > graph(N);
    vector<int> control(N, L), dist(N, -1);
    for (int i=0; i<M; i++) {
        int x, y, l;
        cin >> x >> y >> l;
        x--; y--;
        graph[x].push_back(make_pair(l, y));
        graph[y].push_back(make_pair(l, x));
    }
    for (int i=0; i<K; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        control[x]=y;
    }

    vector<bool> visited(N);
    pq.push(make_pair(L, 0));
    int minLev=L, curLev=L;
    while (pq.size()) {
        pair<int, int> top=pq.top(); pq.pop();
        int x = top.second, lev = top.first;
        if (visited[x] == true) continue;
        if (lev < minLev) break;
        curLev=min(curLev, lev);
        minLev=min(minLev, control[x]);
        visited[x] = true;
        for (int i=0; i < graph[x].size(); i++) {
            int y = graph[x][i].second, w = graph[x][i].first;
            if (!visited[y]) {
                if (w > dist[y]) {
                    dist[y] = w;
                    pq.push(graph[x][i]);
                }
            }
        }
    }
    for (int i=0; i<N; i++) if (!visited[i]) {
        cout << "impossible\n";
        return;
    }
    cout << curLev << '\n';
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
