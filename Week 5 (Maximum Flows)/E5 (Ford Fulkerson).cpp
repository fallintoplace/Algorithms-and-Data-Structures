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

void print(tuple<int, int, bool, int> top) {
    int x = get<0>(top), y = get<1>(top), out = get<2>(top), day = get<3>(top);
    cout << x << " " << y << " " << out << " " << day << endl;
}

bool valid(int x, int y, int N) {
    return x>=0 && y>=0 && x<N && y<N;
}

void solve() {
    int N, K, D;
    cin >> N >> K >> D;
    vector<vector<int> > height(N, vector<int>(N));
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            cin >> height[i][j];

    vector<pair<int, int> > camel;

    for (int i=0; i<K; i++) {
        int x, y;
        cin >> x >> y;
        camel.pb(mp(x, y));
    }

    vector<int> snow(D);
    for (int i=0; i < D; i++) cin >> snow[i];
    int dir[5][2] = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}, {0, 0}};

    map<pair<tuple<int, int, bool, int>, tuple<int, int, bool, int> >, int> flow;
    tuple<int, int, bool, int> source = mt(N, N, true, -2), target = mt(N+1, N+1, false, D);
    for (int i=0; ; i++) {
        bool exist=false;
        stack<tuple<int, int, bool, int> > dfs;
        map<tuple<int, int, bool, int>, bool> marked;
        map<tuple<int, int, bool, int>, pair<tuple<int, int, bool, int>, bool> > trace;
        dfs.push(source);
        while (dfs.size()) {
            tuple<int, int, bool, int> top = dfs.top(); dfs.pop();
            if (marked[top]) continue;
            marked[top]=true;
            int x = get<0>(top), y = get<1>(top), out = get<2>(top), day = get<3>(top);
            if (top == target) {
                exist = true;
                break;
            } else if (day == -2) {
                for (int i=0; i<K; i++) {
                    tuple<int, int, bool, int> next = mt(camel[i].first, camel[i].second, false, day+1);
                    if (!marked[next] && flow[mp(top, next)]==0) {
                        dfs.push(next);
                        trace[next] = mp(top, true);
                    }
                }
            } else if (day==-1 && out==false) {
                tuple<int, int, bool, int> next = mt(x, y, true, day);
                if (!marked[next] && flow[mp(top, next)] == 0) {
                    dfs.push(next);
                    trace[next]=mp(top, true);
                }
                if (flow[mp(source, top)] == 1) {
                    dfs.push(source);
                    trace[source]=mp(top, false);
                }
            } else if (day==D-1 && out==true) {
                if (flow[mp(top, target)] == 0) {
                    dfs.push(target);
                    trace[target]=mp(top, true);
                }
                tuple<int, int, bool, int> back = mt(x, y, false, day);
                if (!marked[back] && flow[mp(back, top)] == 1) {
                    dfs.push(back);
                    trace[back]=mp(top, false);
                }
            } else {
                if (out == false) {
                    tuple<int, int, bool, int> next = mt(x, y, true, day);
                    if (!marked[next] && flow[mp(top, next)] == 0) {
                        dfs.push(next);
                        trace[next]=mp(top, true);
                    }
                    for (int i=0; i<5; i++) {
                        int u=x+dir[i][0], v=y+dir[i][1];
                        if (valid(u, v, N) && (day<=0 || height[u][v]>snow[day-1])) {
                            tuple<int, int, bool, int> back=mt(u, v, true, day-1);
                            if (!marked[back] && flow[mp(back, top)]==1) {
                                dfs.push(back);
                                trace[back]=mp(top, false);
                            }
                        }
                    }
                } else if (out==true) {
                    for (int i=0; i<5; i++) {
                        int u=x+dir[i][0], v=y+dir[i][1];
                        if (valid(u, v, N) && (day<=-2 || height[u][v]>snow[day+1])) {
                            tuple<int, int, bool, int> next=mt(u, v, false, day+1);
                            if (!marked[next] && flow[mp(top, next)]==0) {
                                dfs.push(next);
                                trace[next]=mp(top, true);
                            }
                        }
                    }
                    tuple<int, int, bool, int> back=mt(x, y, false, day);
                    if (!marked[back] && flow[mp(back, top)]==1) {
                        dfs.push(back);
                        trace[back]=mp(top, false);
                    }
                }
            }
        }
        if (!exist) break;
        tuple<int, int, bool, int> now=target;
        while (true) {
            pair<tuple<int, int, bool, int>, bool> info=trace[now];
            tuple<int, int, bool, int> before=info.first;
            bool forEdge=info.second;
            if (forEdge) {
                assert(flow[mp(before, now)] == 0);
                flow[mp(before, now)]++;
            } else {
                assert(flow[mp(now, before)] == 1);
                flow[mp(now, before)]--;
            }
            now=before;
            if (before==source) break;

        }
    }
    int res=0;
    for (int i=0; i<N; i++) for (int j=0; j<N; j++) res += flow[mp(mt(i, j, true, D-1), target)];
    cout << res << endl;
}

int main() {
	freopen("3.in", "r", stdin);
	ios::sync_with_stdio(false);
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
