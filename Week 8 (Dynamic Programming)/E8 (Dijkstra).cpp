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
#define pmax (1e9+7)
#define longmax (1e18+7)
#define forn(i, n) for(int i=0; i<n; i++)

int N, M, G;
vector<int> values;
int weight[555][555], dist[555];
vector<vector<int> > adj;
int f[555][27001];

bool contain(vector<int> v, int x) {
    forn(i, v.size()) if (v[i]==x) return 1;
    return 0;
}

int func(int x, int d) {
    if (x==0) return 0;
    if (f[x][d]>=0) return f[x][d];
    f[x][d] = -pmax;
    forn(i, adj[x].size()) {
        int y = adj[x][i];
        if (y<x && d+weight[x][y]<dist[y]) {
            f[x][d] = max(f[x][d], values[x]+func(y, d+weight[x][y]));
        }
    }
//    printf("%d %d %d\n", x, d, f[x][d]);
    return f[x][d];
}

void solve() {
    cin >> N >> M >> G;
    values.resize(N+1);
    forn(i, N) cin >> values[i+1];
    adj.clear();
    adj=vector<vector<int> >(N+1);
    forn(i, N+1) forn(j, N+1) weight[i][j]=pmax;
    forn(i, M) {
        int a, b, c;
        cin >> a >> b >> c;
        if (!contain(adj[a], b)) adj[a].pb(b);
        if (!contain(adj[b], a)) adj[b].pb(a);
        weight[a][b]=min(weight[a][b], c);
        weight[b][a]=min(weight[b][a], c);
    }
    priority_queue<pair<int, int > > pq;
    pq.push(mp(0, G));
    forn(i, N+1) dist[i]=pmax; dist[G]=0;
    while (pq.size()) {
        pair<int, int> nearest = pq.top(); pq.pop();
        int x = nearest.second, d = -nearest.first;
        forn(i, adj[x].size()) {
            int y = adj[x][i];
            if (weight[x][y]+dist[x] < dist[y]) {
                dist[y] = weight[x][y]+dist[x];
                pq.push(mp(-dist[y], y));
            }
        }
    }
    forn(i, N+1) forn(j, (N+2)*52) f[i][j]=-pmax;
//    forn(i, N+1) printf("%d ", dist[i]); printf("\n");
    func(N, 0);
    if (f[N][0]<0) cout << "impossible";
    else cout << f[N][0];
    cout << endl;
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
