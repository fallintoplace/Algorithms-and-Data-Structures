#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define mp make_pair
#define pb push_back
#define long long long
#define LONGMAX 1e18+7

void solve() {
    long N;
    cin >> N;
    vector<long> task(N), pred(N);
    vector<vector<long> > graph(N);
    for (long i=0; i<N; i++) {
        long t, x;
        cin >> t;
        task[i]=t;
        cin >> x;
        for (long j=0; j<x; j++) {
            long y;
            cin >> y;
            y--;
            graph[i].pb(y);
            pred[y]++;
        }
    }
    vector<long> temp=pred, order;
    stack<long> bfs;
    bfs.push(0);
    while (bfs.size()) {
        long x=bfs.top();
        bfs.pop();
        order.pb(x);
        for (long i=0; i<graph[x].size(); i++) {
            long y=graph[x][i];
            pred[y]--;
            if (pred[y]==0) {
                bfs.push(y);
            }
        }
    }
    vector<long> dist(N, -LONGMAX);
    dist[0] = task[0];
    for (long i = 0; i < order.size(); i++) {
        long x = order[i];
        for (long j = 0; j < graph[x].size(); j++) {
            long y = graph[x][j];
            dist[y] = max(dist[y], dist[x]+task[y]);
        }
    }
    cout << dist[N-1] << '\n';
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
