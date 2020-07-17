#include<bits/stdc++.h>
using namespace std;
#define err1(x) {cerr << '(' << x << ')' << '\n';}
#define err2(x) {cerr << '{' << x << '}' << '\n';}
#define err3(x) {cerr << '[' << x << ']' << '\n';}
#define FOR(i, N) for (int i=0; i<N; i++)
#define mp make_pair
#define pb push_back
#define MAX 1e9+7
#define long long double

void solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, long> > > graph(N);
    for (int i=0; i<M; i++) {
        int x, y;
        long z;
        cin >> x >> y >> z;
        x--;
        y--;
        z = log(z);
        graph[x].push_back(make_pair(y, z));
    }
    vector<long> dist(N, MAX);
    dist[0]=0;
    vector<int> length(N);
    priority_queue<pair<long, int>, vector<pair<long, int> >, greater<pair<long, int> > > pq;
    pq.push(make_pair(0, 0));
    while (pq.size()) {
        pair<long, int> top = pq.top(); pq.pop();
        int x = top.second;
        if (length[x] > N) {
            cout << "Jackpot\n"; return;
        }
        for (int i = 0; i < graph[x].size(); i++) {
            pair<int, long> next = graph[x][i];
            int y = next.first;
            long d = next.second;
            if (dist[x]+d < dist[y]) {
                dist[y] = dist[x]+d;
                length[y] = length[x]+1;
                pq.push(make_pair(dist[y], y));
            }
        }
    }
    if (dist[N-1]==MAX) {
        cout << "impossible\n"; return;
    }
    cout << setprecision(10) << exp(dist[N-1]) << '\n';
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
