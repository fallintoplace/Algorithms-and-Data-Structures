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



void solve() {
    int N, K;
    cin >> N >> K;
    vector<int> field(N+3);
    int ans=0;
    forn(i, K) {
        int W, H, P;
        cin >> W >> H >> P;
        int m=0;
        for (int i=P; i<P+W; i++) {
            m=max(m, field[i]);
        }
        for (int i=P; i<P+W; i++) {
            ans=max(ans, m+H);
            field[i]=m+H;
        }
        cout << ans << " ";
    }

    cout << endl;
}

main() {
//	freopen("1.in", "r", stdin);
	ios::sync_with_stdio(false);
	int Case;
	cin >> Case;
	for (int i=1; i<=Case; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
