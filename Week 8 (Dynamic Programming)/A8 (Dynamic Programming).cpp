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
#define pmax 1e9+7
#define longmax 1e18+7
#define forn(i, n) for(int i=0; i<n; i++)

int value[101];
int f[101][100001];
vector<int> res, saving;

int calculate(int n, int c, bool trace) {
    if (f[n][c]!=-1 && trace==false) return f[n][c];
    if (c==0) return 0;
    int x=pmax, y=pmax;
    if (c-value[n]>=0) y=calculate(n, c-value[n], false)+1;
    if (n>0) x=calculate(n-1, c, false);
    if (trace==true) {
        if (y<x) {
            res.pb(n);
            calculate(n, c-value[n], true);
        } else {
            calculate(n-1, c, true);
        }
    }
    f[n][c]=min(x, y);
    return f[n][c];
}

void solve() {
    int N, C;
    cin >> N >> C;
    res.clear();
    saving=vector<int>(N);
    forn(i, N) {
        cin >> value[i];
    }
    forn(i, N) forn(j, C+1) {
        f[i][j]=-1;
    }

    forn(n, N) forn(c, C+1) {
        if (c==0) {
            f[n][c]=0;
        } else {
            int x=pmax, y=pmax;
            if (c-value[n]>=0) y=f[n][c-value[n]]+1;
            if (n>0) x=f[n-1][c];
            f[n][c]=min(x, y);
        }
    }
    int n=N-1, c=C;
    while (c!=0) {
        int x=pmax, y=pmax;
        if (c-value[n]>=0) y=f[n][c-value[n]]+1;
        if (n>0) x=f[n-1][c];
        f[n][c]=min(x, y);
        if (y<x) {
            res.pb(n);
            c=c-value[n];
        } else {
            n--;
        }
    }
//    calculate(N-1, C, true);
    forn(i, res.size()) saving[res[i]]++;
    forn(i, N) cout << saving[i] << " ";
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
