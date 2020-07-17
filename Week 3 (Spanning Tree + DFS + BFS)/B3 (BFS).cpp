#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}

void solve() {
    int N, K, R, D;
    cin >> N >> K >> R >> D;
    vector<int> alive;
    for (int i=0; i<K; i++) {
        int x;
        cin >> x;
        x--;
        alive.push_back(x);
    }
    vector<bool> dead(N), marked(N);
    for (int i=0; i<R; i++) {
        int x;
        cin >> x;
        x--;
        dead[x]=true;
    }
    vector<vector<int> > graph(N);
    for (int i=0; i < D; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        graph[x].push_back(y);
    }
    stack<int> bfs;
    for (int i=0; i < alive.size(); i++) {
        int start = alive[i];
        bfs.push(start);
        marked[start] = true;
    }
    while (bfs.size()) {
        int x = bfs.top(); bfs.pop();
        if (dead[x] == true) {
            cout << "conflict\n";
            return;
        }
        for (int i=0; i < graph[x].size(); i++) {
            int y = graph[x][i];
            if (!marked[y]) {
                bfs.push(y);
                marked[y]=true;
            }
        }
    }
    cout << "ok\n";
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
