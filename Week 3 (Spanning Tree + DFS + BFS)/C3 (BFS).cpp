#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}


void solve() {
    int N, M, L;
    cin >> N >> M >> L;
    vector<vector<int> > graph(N);
    vector<int> level(N, -1), pred(N);
    for (int i=0; i<M; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        graph[x].push_back(y);
        pred[y]++;
    }
    vector<pair<int, int> > query;
    for (int i=0; i<L; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        query.push_back(make_pair(x, y));
    }
    int count=0;
    stack<int> bfs;
    for (int i=0; i<N; i++) {
        if (pred[i]==0) {
            bfs.push(i);
        }
    }
    while (bfs.size()) {
        int x=bfs.top(); bfs.pop();
        level[x]=count++;
        for (int i=0; i<graph[x].size(); i++) {
            int y=graph[x][i];
            pred[y]--;
            if (pred[y]==0) {
                bfs.push(y);
            }
        }
    }
    for (int i=0; i<N; i++) {
        if (level[i]==-1) {
            cout << "no\n";
            return;
        }
    }

    cout << "yes\n";
    for (int i=0; i<L; i++) {
        int x=query[i].first, y=query[i].second;
        assert(level[x]!=level[y]);
        if (level[x]<level[y]) cout << x+1 << " " << y+1 << '\n';
        else cout << y+1 << " " << x+1 << '\n';
    }


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
