#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}

pair<vector<int>, pair<int, int> > cal(int N, int start, vector<vector<int> > *graph) {
    vector<int> dist(N), trace(N);
    vector<bool> marked(N);
    marked[start] = true;
    int furthest = start;
    stack<int> bfs; bfs.push(start);
    while (bfs.size()) {
        int x = bfs.top(); bfs.pop();
        if (dist[x] > dist[furthest]) furthest=x;
        for (int i=0; i < (*graph)[x].size(); i++) {
            int y = (*graph)[x][i];
            if (marked[y] == false) {
                marked[y] = true;
                bfs.push(y);
                dist[y] = dist[x]+1;
                trace[y] = x;
            }
        }
    }
    return make_pair(trace, make_pair(furthest, dist[furthest]));
}

void solve() {
    int N;
    cin >> N;
    vector<vector<int> > graph(N);
    for (int i=0; i<N-1; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    int sta=cal(N, 0, &graph).second.first;
    pair<vector<int>, pair<int, int> > pack=cal(N, sta, &graph);
    int dist=pack.second.second, ans=pack.second.first;
    vector<int> trace=pack.first;
    dist/=2;
    while (dist--) {
        ans=trace[ans];
    }
    cout << ans << '\n';
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
