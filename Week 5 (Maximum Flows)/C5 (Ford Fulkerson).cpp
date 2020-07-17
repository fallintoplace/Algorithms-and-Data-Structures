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
    vector<vector<int> > graph, flow, adj(2*N);
    graph = flow = vector<vector<int> >(2*N, vector<int>(2*N));
    for (int i=0; i<M; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        if (x>y) swap(x, y);
        if (x!=0) adj[x+N].pb(y), adj[y].pb(x+N), graph[x+N][y]=1;
        else adj[0].pb(y), adj[y].pb(0), graph[0][y]=1;
        if (y!=N-1) adj[y+N].pb(x), adj[x].pb(y+N), graph[y+N][x]=1;
        else adj[N-1].pb(x), adj[x].pb(N-1), graph[N-1][x]=1;
    }
    for (int i = 1; i < N-1; i++) adj[i+N].pb(i), adj[i].pb(i+N), graph[i][i+N]=1;
    while (true) {
        bool exist = false;
        stack<int> dfs;
        vector<int> trace(2*N);
        dfs.push(0);
        vector<bool> marked(2*N);
        marked[0]=true;
        while (dfs.size()) {
            int x=dfs.top(); dfs.pop();
            if (x == N-1) {
                exist=true;
                break;
            }
            for (int i=0; i < adj[x].size(); i++) {
                int y = adj[x][i];
                if (!marked[y]) {
                    if (graph[x][y]>flow[x][y] || flow[y][x]>0) {
                        trace[y]=x;
                        dfs.push(y);
                        marked[y]=true;
                    }

                }
            }
        }
        if (!exist) break;
        int now=N-1, cf=1e9+7;
        while (true) {
            int before=trace[now];
            if (graph[before][now] > flow[before][now]) cf = min(cf, graph[before][now]-flow[before][now]);
            else cf = min(cf, flow[now][before]);
            now = before;
            if (now==0) break;
        }
        now=N-1;
        while (true) {
            int before = trace[now];
            if (graph[before][now] > flow[before][now]) flow[before][now] += cf;
            else flow[now][before] -= cf;
            now = before;
            if (now == 0) break;
        }
    }
    int res=0;
    for (int i=0; i<2*N; i++) res += flow[i][N-1];
    cout << res << endl;
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
