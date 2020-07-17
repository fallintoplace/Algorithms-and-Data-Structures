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
#define max 1e9+7
#define longmax 1e18+7
#define forn(i, n) for(int i=0; i<n; i++)

int N, M, board[10][10], startX, startY, W, bIndex[10][10], startIndex,
    dir[4][2]={{-1, 0}, {1, 0}, {0, -1}, {0, 1}}, totTool;
bool marked[16777216][25], hasAns;

bool valid(int x, int y) {
    return x>=0 && y>=0 && x<N && y<M;
}

void dfs(int state, int pos, int x, int y, int total) {
//    cout << state<< " " << x << " " << y << " " << total << endl;
    if (hasAns) return;
    if (total == totTool) {
        hasAns=true;
        return;
    }
    forn(i, 4) {
        int u=x+dir[i][0], v=y+dir[i][1];
        if (valid(u, v) && bIndex[u][v]>=0 && bIndex[u][v]!=24 && (state&(1<<bIndex[u][v]))==0 &&
             !marked[state|(1<<bIndex[u][v])][bIndex[u][v]]) {
            marked[state|(1<<bIndex[u][v])][bIndex[u][v]] = true;
            dfs(state|(1<<bIndex[u][v]), bIndex[u][v], u, v, total+(board[u][v]==2));
        }
    }
}

void solve() {

    cin >> N >> M;
    swap(N, M);
    W=0; totTool=0; hasAns=false;
    forn(i, N) forn(j, M) bIndex[i][j]=-1;
    forn(i, N) {
        string s;
        cin >> s;
        forn(j, M) {
            if (s[j]=='L') {
                board[i][j]=1;
                startIndex=24;
                bIndex[i][j]=24;
                startX=i;
                startY=j;
            }
            if (s[j]=='T') {
                board[i][j]=2;
                bIndex[i][j]=W;
                W++;
                totTool++;
            }
            if (s[j]=='_') {
                board[i][j]=3;
                bIndex[i][j]=W;
                W++;
            }
        }
    }
    forn(i, (1<<W)) forn(j, W) marked[i][j]=0;
    marked[0][startIndex]=true;
    dfs(0, startIndex, startX, startY, 0);
    if (hasAns) cout << "yes\n";
    else cout << "no\n";

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
