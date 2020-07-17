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
    int NN, MM;
    cin >> NN >> MM;
    vector<int> wins(NN), M(NN);
    vector<vector<int> > rem(NN, vector<int>(NN));
    for (int i=0; i < NN; i++) cin >> wins[i], M[i] = wins[i];
    for (int i=0; i < MM; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        if (x>y) swap(x, y);
        rem[x][y]++;
        M[x]++; M[y]++;
    }
    if (NN >= 3) {
        for (int cur=0; cur < NN; cur++) {
            int N = 2+(NN-1)*(NN-2)+NN;
            vector<vector<int> > graph, flow, adj(N);
            graph = flow = vector<vector<int> >(N, vector<int>(N));
            int k = 0;
            for (int i=0; i < NN-1; i++) for (int j=i+1; j < NN; j++) {
                if (i==cur || j==cur) continue;
                ++k;
                graph[0][k] = rem[i][j];
                graph[k][(NN-1)*(NN-2)/2+i+1]=20000;
                graph[k][(NN-1)*(NN-2)/2+j+1]=20000;
                adj[0].pb(k);
                adj[k].pb(0);
                adj[k].pb((NN-1)*(NN-2)/2+i+1);
                adj[(NN-1)*(NN-2)/2+i+1].pb(k);
                adj[k].pb((NN-1)*(NN-2)/2+j+1);
                adj[(NN-1)*(NN-2)/2+j+1].pb(k);
            }
            assert(k==(NN-1)*(NN-2)/2);
            bool bad = false;
            for (int i=0; i<NN; i++) {
                ++k;
                if (i == cur) continue;
                graph[k][N-1] = M[cur]-wins[i];
                if (M[cur]-wins[i] < 0) {
                    bad=true;
                    break;
                }
                adj[k].pb(N-1);
                adj[N-1].pb(k);
            }
            if (bad) { cout << "no "; continue;}
            while (true) {
                bool exist=false;
                stack<int> dfs;
                vector<int> trace(N);
                dfs.push(0);
                vector<bool> marked(N);
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
                    now=before;
                    if (now==0) break;
                }
                now=N-1;
                while (true) {
                    int before=trace[now];
                    if (graph[before][now] > flow[before][now]) flow[before][now]+=cf;
                    else flow[now][before] -= cf;
                    now=before;
                    if (now==0) break;
                }
            }
            k=0;
            bool res=true;
            for (int i=0; i < NN-1; i++) for (int j=i+1; j<NN; j++) {
                if (i==cur || j==cur) continue;
                k++;
                if (flow[0][k] != rem[i][j]) res=false;
            }
            if (res) cout << "yes ";
            else cout << "no ";

        }
    } else {
        if (wins[0]+rem[0][1] < wins[1]) cout << "no ";
        else cout << "yes ";
        if (wins[1]+rem[0][1] < wins[0]) cout << "no ";
        else cout << "yes ";
    }
    cout << endl;
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
