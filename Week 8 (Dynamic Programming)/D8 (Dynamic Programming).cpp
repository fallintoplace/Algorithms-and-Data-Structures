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

vector<tuple<int, int, int> > tour;
int N, f[5001][5001];

int calculate(int n, int d) {
    if (n==N) return 0;
    if (f[n][d]!=-1) return f[n][d];
    f[n][d] = calculate(n+1, d);
    if (d<get<0>(tour[n])) f[n][d] = max(f[n][d], calculate(n+1, get<1>(tour[n]))+get<2>(tour[n]));
    return f[n][d];
}

void solve() {
    cin >> N;
    tour.clear();
    forn(i, N) {
        int x, y, z;
        cin >> x >> y >> z;
        tour.pb(mt(x, y, z));
    }
    forn(i, N) forn(j, 5001) f[i][j]=-1;
    sort(tour.begin(), tour.end());
    for (int n=N; n>=0; n--) for (int d=5000; d>=0; d--) {
        if (n==N) f[n][d]=0;
        else {
            f[n][d] = f[n+1][d];
            if (d<get<0>(tour[n])) f[n][d] = max(f[n][d], f[n+1][get<1>(tour[n])]+get<2>(tour[n]));
        }
    }
    cout << f[0][0] << endl;
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
