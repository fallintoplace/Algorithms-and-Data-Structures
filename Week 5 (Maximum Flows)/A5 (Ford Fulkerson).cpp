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
#define LONGMAX 1e18+7

void solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<int> > graph, flow, adj(N);
    graph=flow=vector<vector<int> >(N, vector<int>(N));
    for (int i=0; i<M; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        x--; y--;
        if (graph[x][y] == 0) {
            adj[x].pb(y); adj[y].pb(x);
        }
        graph[x][y] += w;
        graph[y][x] += w;
    }
    while (true) {
        bool exist = false;
        stack<int> dfs;
        vector<int> trace(N);
        dfs.push(0);
        vector<bool> marked(N);
        marked[0] = true;
        while (dfs.size()) {
            int x = dfs.top(); dfs.pop();
            if (x == N-1) {
                exist=true;
                break;
            }
            for (int i=0; i < adj[x].size(); i++) {
                int y = adj[x][i];
                if (!marked[y]) {
                    if (graph[x][y]>flow[x][y] || flow[y][x]>0) {
                        trace[y] = x;
                        dfs.push(y);
                        marked[y] = true;
                    }

                }
            }
        }
        if (!exist) break;
        int now = N-1, cf = 1e9+7;
        while (true) {
            int before=trace[now];
            if (graph[before][now] > flow[before][now]) cf = min(cf, graph[before][now]-flow[before][now]);
            else cf = min(cf, flow[now][before]);
            now=before;
            if (now==0) break;
        }
        now=N-1;
        while (true) {
            int before = trace[now];
            if (graph[before][now] > flow[before][now]) flow[before][now] += cf;
            else flow[now][before] -= cf;
            now=before;
            if (now==0) break;
        }
    }
    int res = 0;
    for (int i=0; i<N; i++) res += flow[i][N-1];
    if (res == 0) cout << "impossible\n";
    else cout << res << endl;
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
